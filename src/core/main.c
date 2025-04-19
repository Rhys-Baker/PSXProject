// Define RELEASE to remove all debug() print statements and other debug features
//#define RELEASE

#pragma region Includes
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "bsp.h"
#include "camera.h"
#include "cdrom.h"
#include "controller.h"
#include "filesystem.h"
#include "fixedPoint.h"
#include "font.h"
#include "gpu.h"
#include "gte.h"
#include "irq.h"
#include "math.h"
#include "model.h"
#include "menu.h"
#include "spu.h"
#include "stream.h"
#include "trig.h"
#include "types.h"
#include "util.h"

#include "registers.h"
#include "system.h"
#pragma endregion

#define MOVEMENT_SPEED 10

#define ACCELERATION_CONSTANT 1
#define MAX_SPEED 3
#define JUMP_FORCE 10
#define FRICTION_CONSTANT 1
#define TERMINAL_VELOCITY 5
#define GRAVITY_CONSTANT 1


// Include texture data files
extern const uint8_t fontData[];
extern const uint8_t fontPalette[];
TextureInfo font;

extern const uint8_t filth_128Data[];
TextureInfo *filth_128;

Camera mainCamera;
Player3 player;
char str_Buffer[256];
int screenColor = 0xfa823c;
int wallColor = 0x3c82fa;
int gteScaleFactor = 0;

// 3D direction Gizmo
Vector3 gizmoPoints[4] = {
    {0, 0, 0},
    {100<<GTE_SCALE_FACTOR, 0, 0},
    {0, 100<<GTE_SCALE_FACTOR, 0},
    {0, 0, 100<<GTE_SCALE_FACTOR}
};
Vector2 transformedGizmoPoints[4];


//////////////////////////////
// Drawing Helper Functions //
//////////////////////////////
#pragma region Drawing Helpers
void drawCross2(Vector2 p, uint32_t colour){
    int32_t x, y;
    x = p.x;
    y = p.y;

    dmaPtr = allocatePacket(activeChain, 0, 3);
    dmaPtr[0] = colour | gp0_line(false, false);
    dmaPtr[1] = gp0_xy(x-2, y-2);
    dmaPtr[2] = gp0_xy(x+2, y+2);

    dmaPtr = allocatePacket(activeChain, 0, 3);
    dmaPtr[0] = colour | gp0_line(false, false);
    dmaPtr[1] = gp0_xy(x+2, y-2);
    dmaPtr[2] = gp0_xy(x-2, y+2);
}
void drawLine2(Vector2 a, Vector2 b, uint32_t colour){
    dmaPtr = allocatePacket(activeChain, 0, 3);
    dmaPtr[0] = colour | gp0_line(false, false);
    dmaPtr[1] = gp0_xy(a.x, a.y);
    dmaPtr[2] = gp0_xy(b.x, b.y);
}
void drawTri2(Tri2 tri, uint32_t colour){
    dmaPtr = allocatePacket(activeChain, tri.z, 4);
    dmaPtr[0] = colour | gp0_triangle(false, false);
    dmaPtr[1] = gp0_xy(tri.a.x, tri.a.y);
    dmaPtr[2] = gp0_xy(tri.b.x, tri.b.y);
    dmaPtr[3] = gp0_xy(tri.c.x, tri.c.y);
}
void drawQuad2(Quad2 quad, uint32_t colour){    
    dmaPtr = allocatePacket(activeChain, quad.z, 5);
    dmaPtr[0] = colour | gp0_shadedQuad(false, false, false);
    dmaPtr[1] = gp0_xy(quad.a.x, quad.a.y);
    dmaPtr[2] = gp0_xy(quad.b.x, quad.b.y);
    dmaPtr[3] = gp0_xy(quad.c.x, quad.c.y);
    dmaPtr[4] = gp0_xy(quad.d.x, quad.d.y);
}

bool transformVertex(Camera *cam, Vector3 point, Vector2 *result){
    int32_t distX = abs(cam->x>>GTE_SCALE_FACTOR - point.x>>GTE_SCALE_FACTOR);
    int32_t distY = abs(cam->y>>GTE_SCALE_FACTOR - point.y>>GTE_SCALE_FACTOR);
    int32_t distZ = abs(cam->z>>GTE_SCALE_FACTOR - point.z>>GTE_SCALE_FACTOR);
    
    if(distX > INT16_MAX || distY > INT16_MAX || distZ > INT16_MAX){
        return false;
    }
    // Save the current translation vector
    int32_t currentTx, currentTy, currentTz;
    gte_getTranslationVector(&currentTx, &currentTy, &currentTz);
    // Translate model
    updateTranslationMatrix(cam->x, cam->y, cam->z);
    // Rotate model
    rotateCurrentMatrix(0, 0, 0);

    GTEVector16 vert;
    vert.x = (int16_t)(point.x>>GTE_SCALE_FACTOR);
    vert.y = (int16_t)(point.y>>GTE_SCALE_FACTOR);
    vert.z = (int16_t)(point.z>>GTE_SCALE_FACTOR);
    gte_loadV0(&vert);
    gte_command(GTE_CMD_RTPS | GTE_SF);

    //gte_command(GTE_CMD_AVSZ3 | GTE_SF);
    int zIndex = gte_getOTZ();
    
    // Don't render things too far away.
    if(zIndex >= ORDERING_TABLE_SIZE){
        return false;
    }
    
    // Get the XY coordinate of the transformed cross
    uint32_t XY0 = gte_getSXY2();
    Vector2 transformedCross;
    transformedCross.x = XY0 & 0xFFFF;
    transformedCross.y = XY0 >> 16;
    
    result->x = transformedCross.x;
    result->y = transformedCross.y;

    // Restore the translation and rotation back to the initial state as to not clobber any other models.
    gte_setTranslationVector(currentTx, currentTy, currentTz);
    return true;
}
bool transformTri(Camera *cam, Tri3 tri, Tri2 *result){
    // TODO: Replace AVZ3 with a Max 
    uint32_t xy0, xy1, xy2;

    // Range check. Is it too big to be drawn?
    if(
        abs(cam->x - (tri.a.x>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->y - (tri.a.y>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->z - (tri.a.z>>GTE_SCALE_FACTOR)) > INT16_MAX ||
        abs(cam->x - (tri.b.x>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->y - (tri.b.y>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->z - (tri.b.z>>GTE_SCALE_FACTOR)) > INT16_MAX ||
        abs(cam->x - (tri.c.x>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->y - (tri.c.y>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->z - (tri.c.z>>GTE_SCALE_FACTOR)) > INT16_MAX
    ){
        // Out of range. Don't render
        return false;
    }

    // Save the current translation vector
    int32_t currentTx, currentTy, currentTz;
    gte_getTranslationVector(&currentTx, &currentTy, &currentTz);
    // Translate model
    updateTranslationMatrix(cam->x, cam->y, cam->z);
    // Rotate model
    rotateCurrentMatrix(0, 0, 0);

    GTEVector16 verts[3] = {
        {(int16_t)(tri.a.x>>GTE_SCALE_FACTOR), (int16_t)(tri.a.y>>GTE_SCALE_FACTOR), (int16_t)(tri.a.z>>GTE_SCALE_FACTOR)},
        {(int16_t)(tri.b.x>>GTE_SCALE_FACTOR), (int16_t)(tri.b.y>>GTE_SCALE_FACTOR), (int16_t)(tri.b.z>>GTE_SCALE_FACTOR)},
        {(int16_t)(tri.c.x>>GTE_SCALE_FACTOR), (int16_t)(tri.c.y>>GTE_SCALE_FACTOR), (int16_t)(tri.c.z>>GTE_SCALE_FACTOR)}
    };

    gte_loadV0(&verts[0]);
    gte_loadV1(&verts[1]);
    gte_loadV2(&verts[2]);
    gte_command(GTE_CMD_RTPT | GTE_SF);
    gte_command(GTE_CMD_NCLIP);
    if(gte_getMAC0() <= 0){
        gte_setTranslationVector(currentTx, currentTy, currentTz);
        return false;
    }
    xy0 = gte_getSXY0();
    xy1 = gte_getSXY1();
    xy2 = gte_getSXY2();

    gte_command(GTE_CMD_AVSZ3 | GTE_SF);
    int zIndex = gte_getOTZ();

    if(zIndex < 0 || zIndex >= ORDERING_TABLE_SIZE){
        gte_setTranslationVector(currentTx, currentTy, currentTz);
        return false;
    }

    // Save result
    result->a = (Vector2){xy0 & 0xFFFF, xy0 >> 16};
    result->b = (Vector2){xy1 & 0xFFFF, xy1 >> 16};
    result->c = (Vector2){xy2 & 0xFFFF, xy2 >> 16};
    result->z = zIndex;

    // Restore the translation and rotation back to the initial state as to not clobber any other models.
    gte_setTranslationVector(currentTx, currentTy, currentTz);
    return true;
}
bool transformQuad(Camera *cam, Quad3 quad, Quad2 *result){
    uint32_t xy0, xy1, xy2, xy3;
    uint32_t sz0, sz1, sz2, sz3;

    // Range check. Is it too big to be drawn?
    if(
        abs(cam->x - (quad.a.x>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->y - (quad.a.y>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->z - (quad.a.z>>GTE_SCALE_FACTOR)) > INT16_MAX ||
        abs(cam->x - (quad.b.x>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->y - (quad.b.y>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->z - (quad.b.z>>GTE_SCALE_FACTOR)) > INT16_MAX ||
        abs(cam->x - (quad.c.x>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->y - (quad.c.y>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->z - (quad.c.z>>GTE_SCALE_FACTOR)) > INT16_MAX ||
        abs(cam->x - (quad.d.x>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->y - (quad.d.y>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->z - (quad.d.z>>GTE_SCALE_FACTOR)) > INT16_MAX
    ){
        // Out of range. Don't render
        return false;
    }

    // Save the current matrices so we don't clobber them.
    Vector3 currentT;
    gte_getTranslationVector(&currentT.x, &currentT.y, &currentT.z);

    // Translate model
    updateTranslationMatrix(cam->x, cam->y, cam->z);
    // Rotate model
    rotateCurrentMatrix(0, 0, 0);

    GTEVector16 verts[4] = {
        {(int16_t)(quad.a.x>>GTE_SCALE_FACTOR), (int16_t)(quad.a.y>>GTE_SCALE_FACTOR), (int16_t)(quad.a.z>>GTE_SCALE_FACTOR)},
        {(int16_t)(quad.b.x>>GTE_SCALE_FACTOR), (int16_t)(quad.b.y>>GTE_SCALE_FACTOR), (int16_t)(quad.b.z>>GTE_SCALE_FACTOR)},
        {(int16_t)(quad.c.x>>GTE_SCALE_FACTOR), (int16_t)(quad.c.y>>GTE_SCALE_FACTOR), (int16_t)(quad.c.z>>GTE_SCALE_FACTOR)},
        {(int16_t)(quad.d.x>>GTE_SCALE_FACTOR), (int16_t)(quad.d.y>>GTE_SCALE_FACTOR), (int16_t)(quad.d.z>>GTE_SCALE_FACTOR)}
    };
    

    // Load the first 3 verts
    gte_loadV0(&verts[0]);
    gte_loadV1(&verts[1]);
    gte_loadV2(&verts[2]);
    gte_command(GTE_CMD_RTPT | GTE_SF);
    gte_command(GTE_CMD_NCLIP);

    if(gte_getMAC0() <= 0){
        // Restore matrices.
        gte_setTranslationVector(currentT.x, currentT.y, currentT.z);
        return false;
    }

    xy0 = gte_getSXY0();
    
    // Load the last vert    
    gte_loadV0(&verts[3]);
    gte_command(GTE_CMD_RTPS | GTE_SF);

    sz0 = gte_getSZ0();
    sz1 = gte_getSZ1();
    sz2 = gte_getSZ2();
    sz3 = gte_getSZ3();
    int zIndex = max(max(sz0, sz1),max(sz2, sz3));

    if(zIndex < 0 || zIndex >= ORDERING_TABLE_SIZE){
        // Restore matrices.
        gte_setTranslationVector(currentT.x, currentT.y, currentT.z);
        return false;
    }

    xy1 = gte_getSXY0();
    xy2 = gte_getSXY1();
    xy3 = gte_getSXY2();
    
    // Save result
    result->a = (Vector2){xy0 & 0xFFFF, xy0 >> 16};
    result->b = (Vector2){xy1 & 0xFFFF, xy1 >> 16};
    result->c = (Vector2){xy2 & 0xFFFF, xy2 >> 16};
    result->d = (Vector2){xy3 & 0xFFFF, xy3 >> 16};
    result->z = zIndex;

    // Restore matrices.
    gte_setTranslationVector(currentT.x, currentT.y, currentT.z);

    return true;
}

#pragma endregion



///////////////////////////////////////////////
// BSP Tree Definition and Shape Definitions //
///////////////////////////////////////////////
#pragma region BSP Tree
BSPNode3 bspNodes[];

BSPTree3 bspTree = {.nodes=bspNodes, .numNodes = 12};
BSPNode3 bspNodes[] = {
{
    .normal = {
        .x=-4096,
        .y=0,
        .z=0
    },
    .distance = 589824,
    .children = {
        1, 2
    }
},
{
    .normal = {
        .x=-4096,
        .y=0,
        .z=0
    },
    .distance = 589824,
    .children = {
        -1, -2
    }
},
{
    .normal = {
        .x=0,
        .y=0,
        .z=-4096
    },
    .distance = 262144,
    .children = {
        3, 4
    }
},
{
    .normal = {
        .x=0,
        .y=0,
        .z=-4096
    },
    .distance = 262144,
    .children = {
        -1, -2
    }
},
{
    .normal = {
        .x=0,
        .y=4096,
        .z=0
    },
    .distance = 65536,
    .children = {
        5, 6
    }
},
{
    .normal = {
        .x=0,
        .y=4096,
        .z=0
    },
    .distance = -393216,
    .children = {
        -1, -2
    }
},
{
    .normal = {
        .x=0,
        .y=-4096,
        .z=0
    },
    .distance = 65536,
    .children = {
        7, 8
    }
},
{
    .normal = {
        .x=0,
        .y=-4096,
        .z=0
    },
    .distance = 524288,
    .children = {
        -1, -2
    }
},
{
    .normal = {
        .x=0,
        .y=0,
        .z=4096
    },
    .distance = 262144,
    .children = {
        9, 10
    }
},
{
    .normal = {
        .x=0,
        .y=0,
        .z=4096
    },
    .distance = 262144,
    .children = {
        -1, -2
    }
},
{
    .normal = {
        .x=4096,
        .y=0,
        .z=0
    },
    .distance = 589824,
    .children = {
        11, -2
    }
},
{
    .normal = {
        .x=4096,
        .y=0,
        .z=0
    },
    .distance = 589824,
    .children = {
        -1, -2
    }
},
};

int numTris = 24;
Tri3 tris[] = {
    {
        {-144<<GTE_SCALE_FACTOR, -16<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, 16<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, 16<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
    },
    {
        {-144<<GTE_SCALE_FACTOR, -16<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, -16<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, 16<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
    },
    {
        {-144<<GTE_SCALE_FACTOR, 16<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, -16<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, -16<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
    },
    {
        {144<<GTE_SCALE_FACTOR, 16<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, 16<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, -16<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
    },
    {
        {-144<<GTE_SCALE_FACTOR, 16<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, 16<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, 16<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
    },
    {
        {144<<GTE_SCALE_FACTOR, 16<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, 16<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, 16<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
    },
    {
        {-144<<GTE_SCALE_FACTOR, -16<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, -16<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, -16<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
    },
    {
        {144<<GTE_SCALE_FACTOR, -16<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, -16<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, -16<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
    },
    {
        {-144<<GTE_SCALE_FACTOR, -16<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, 16<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, 16<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
    },
    {
        {144<<GTE_SCALE_FACTOR, -16<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, -16<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, 16<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
    },
    {
        {144<<GTE_SCALE_FACTOR, 16<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, -16<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, -16<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
    },
    {
        {144<<GTE_SCALE_FACTOR, 16<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, 16<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, -16<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
    },
    {
        {-144<<GTE_SCALE_FACTOR, -128<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, -96<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, -96<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
    },
    {
        {-144<<GTE_SCALE_FACTOR, -128<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, -128<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, -96<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
    },
    {
        {-144<<GTE_SCALE_FACTOR, -96<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, -128<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, -128<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
    },
    {
        {144<<GTE_SCALE_FACTOR, -96<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, -96<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, -128<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
    },
    {
        {-144<<GTE_SCALE_FACTOR, -96<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, -96<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, -96<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
    },
    {
        {144<<GTE_SCALE_FACTOR, -96<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, -96<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, -96<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
    },
    {
        {-144<<GTE_SCALE_FACTOR, -128<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, -128<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, -128<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
    },
    {
        {144<<GTE_SCALE_FACTOR, -128<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, -128<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, -128<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
    },
    {
        {-144<<GTE_SCALE_FACTOR, -128<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, -96<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, -96<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
    },
    {
        {144<<GTE_SCALE_FACTOR, -128<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
        {-144<<GTE_SCALE_FACTOR, -128<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, -96<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
    },
    {
        {144<<GTE_SCALE_FACTOR, -96<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, -128<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, -128<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
    },
    {
        {144<<GTE_SCALE_FACTOR, -96<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, -96<<GTE_SCALE_FACTOR,  -64<<GTE_SCALE_FACTOR},
        {144<<GTE_SCALE_FACTOR, -128<<GTE_SCALE_FACTOR,  64<<GTE_SCALE_FACTOR},
    },
};

#pragma endregion



//////////////////////////
// Controller Functions //
//////////////////////////
#pragma region Controller Funcs


// Functions for look controls
void lookLeft(void){
    mainCamera.yaw += 20;
}
void lookRight(void){
    mainCamera.yaw -= 20;
}
void lookUp(void){
    mainCamera.pitch -= 20;
}
void lookDown(void){
    mainCamera.pitch += 20;
}

// Functions for move controls
void moveCameraForward(void){
    mainCamera.x -=  ((isin(mainCamera.yaw) * MOVEMENT_SPEED)>>12);
    mainCamera.z +=  ((icos(mainCamera.yaw) * MOVEMENT_SPEED)>>12);
}
void moveCameraBackward(void){
    mainCamera.x +=  ((isin(mainCamera.yaw) * MOVEMENT_SPEED)>>12);
    mainCamera.z -=  ((icos(mainCamera.yaw) * MOVEMENT_SPEED)>>12);
}
void moveCameraLeft(void){
    mainCamera.x -=  ((icos(mainCamera.yaw) * MOVEMENT_SPEED)>>12);
    mainCamera.z += -((isin(mainCamera.yaw) * MOVEMENT_SPEED)>>12);
}
void moveCameraRight(void){
    mainCamera.x +=  ((icos(mainCamera.yaw) * MOVEMENT_SPEED)>>12);
    mainCamera.z -= -((isin(mainCamera.yaw) * MOVEMENT_SPEED)>>12);
}
void moveCameraUp(void){
    mainCamera.y -= MOVEMENT_SPEED;
}
void moveCameraDown(void){
    mainCamera.y += MOVEMENT_SPEED;
}

// Functions for move controls
void movePlayerForward(void){
    player.position.x -=  (isin(mainCamera.yaw) * MOVEMENT_SPEED);
    player.position.z +=  (icos(mainCamera.yaw) * MOVEMENT_SPEED);
}
void movePlayerBackward(void){
    player.position.x +=  (isin(mainCamera.yaw) * MOVEMENT_SPEED);
    player.position.z -=  (icos(mainCamera.yaw) * MOVEMENT_SPEED);
}
void movePlayerLeft(void){
    player.position.x -=  (icos(mainCamera.yaw) * MOVEMENT_SPEED);
    player.position.z += -(isin(mainCamera.yaw) * MOVEMENT_SPEED);
}
void movePlayerRight(void){
    player.position.x +=  (icos(mainCamera.yaw) * MOVEMENT_SPEED);
    player.position.z -= -(isin(mainCamera.yaw) * MOVEMENT_SPEED);
}
void movePlayerUp(void){
    player.position.y -= MOVEMENT_SPEED<<GTE_SCALE_FACTOR;
}
void movePlayerDown(void){
    player.position.y += MOVEMENT_SPEED<<GTE_SCALE_FACTOR;
}

void incrementScaleFactor(void){
    gteScaleFactor ++;
    if(gteScaleFactor > 16){
        gteScaleFactor = 16;
    }
}
void decrementScaleFactor(void){
    gteScaleFactor --;
    if(gteScaleFactor < 0){
        gteScaleFactor = 0;
    }
}

void resetPlayer(void){
    player.position = (Vector3){0, -(512<<GTE_SCALE_FACTOR), 0};
    player.velocity = (Vector3){0,    0, 0};
    player.coyoteTimer = 0;
    player.isGrounded = false;
}


bool controlCamera = false;
void toggleControlSet(void){
    controlCamera = !controlCamera;
    if(controlCamera){
        controller_subscribeOnKeyHold(moveCameraLeft,       BUTTON_INDEX_LEFT    );
        controller_subscribeOnKeyHold(moveCameraRight,      BUTTON_INDEX_RIGHT   );
        controller_subscribeOnKeyHold(moveCameraForward,    BUTTON_INDEX_UP      );
        controller_subscribeOnKeyHold(moveCameraBackward,   BUTTON_INDEX_DOWN    );
        controller_subscribeOnKeyHold(moveCameraUp,         BUTTON_INDEX_R2      );
        controller_subscribeOnKeyHold(moveCameraDown,       BUTTON_INDEX_L2      );
        controller_subscribeOnKeyHold(lookLeft,             BUTTON_INDEX_SQUARE  );
        controller_subscribeOnKeyHold(lookRight,            BUTTON_INDEX_CIRCLE  );
        controller_subscribeOnKeyHold(lookUp,               BUTTON_INDEX_TRIANGLE);
        controller_subscribeOnKeyHold(lookDown,             BUTTON_INDEX_X       );
        
        controller_subscribeOnKeyDown(resetPlayer,          BUTTON_INDEX_SELECT  );
        controller_subscribeOnKeyDown(decrementScaleFactor, BUTTON_INDEX_L1      );
        controller_subscribeOnKeyDown(incrementScaleFactor, BUTTON_INDEX_R1      );
        controller_subscribeOnKeyDown(resetPlayer,          BUTTON_INDEX_SELECT  );
        controller_subscribeOnKeyDown(toggleControlSet,     BUTTON_INDEX_START   );
    } else {
        controller_subscribeOnKeyHold(movePlayerLeft,       BUTTON_INDEX_LEFT    );
        controller_subscribeOnKeyHold(movePlayerRight,      BUTTON_INDEX_RIGHT   );
        controller_subscribeOnKeyHold(movePlayerForward,    BUTTON_INDEX_UP      );
        controller_subscribeOnKeyHold(movePlayerBackward,   BUTTON_INDEX_DOWN    );
        controller_subscribeOnKeyHold(movePlayerUp,         BUTTON_INDEX_R2      );
        controller_subscribeOnKeyHold(movePlayerDown,       BUTTON_INDEX_L2      );
        controller_subscribeOnKeyHold(lookLeft,             BUTTON_INDEX_SQUARE  );
        controller_subscribeOnKeyHold(lookRight,            BUTTON_INDEX_CIRCLE  );
        controller_subscribeOnKeyHold(lookUp,               BUTTON_INDEX_TRIANGLE);
        controller_subscribeOnKeyHold(lookDown,             BUTTON_INDEX_X       );

        controller_subscribeOnKeyDown(resetPlayer,          BUTTON_INDEX_SELECT  );
        controller_subscribeOnKeyDown(decrementScaleFactor, BUTTON_INDEX_L1      );
        controller_subscribeOnKeyDown(incrementScaleFactor, BUTTON_INDEX_R1      );
        controller_subscribeOnKeyDown(resetPlayer,          BUTTON_INDEX_SELECT  );
        controller_subscribeOnKeyDown(toggleControlSet,     BUTTON_INDEX_START   );
    }
}


#pragma endregion


// Gets called once at the start of main.
void initHardware(void){
    // Enable display blanking if not already.
    // Prevents logo from appearing while loading.
    GPU_GP1 = gp1_dispBlank(true);

    // Initialise the serial port for printing
    initSerialIO(115200);
    initSPU();
    initIRQ();
    initControllerBus();
    initCDROM();
    initFilesystem();
    initGPU();
    
    setupGTE(SCREEN_WIDTH, SCREEN_HEIGHT);
    // Upload textures
    uploadIndexedTexture(&font, fontData, SCREEN_WIDTH, 0, FONT_WIDTH, FONT_HEIGHT, 
        fontPalette, SCREEN_WIDTH, FONT_HEIGHT, GP0_COLOR_4BPP);
    // Initalise the transformed verts list
    // TODO: Look into whether this is actually useful or not
    transformedVerts = malloc(sizeof(TransformedVert) * maxNumVerts);

    
    // Point to the relevant DMA chain for this frame, then swap the active frame.
    activeChain = &dmaChains[usingSecondFrame];
    usingSecondFrame = !usingSecondFrame;
    // Reset the ordering table to a blank state.
    clearOrderingTable((activeChain->orderingTable), ORDERING_TABLE_SIZE);
    activeChain->nextPacket = activeChain->data;

    
    // TODO: Render a logo/loading screen to the framebuffer

    
    // Manually disable display blanking after all loading is complete
    GPU_GP1 = gp1_dispBlank(false);
}

// Start of main
__attribute__((noreturn))
int main(void){

    // Tell the compiler that variables might be updated randomly (ie, IRQ handlers)
    __atomic_signal_fence(__ATOMIC_ACQUIRE);

    // Initialise important things for later
    initHardware();

    // Run this stuff once before the main loop.
    toggleControlSet();


    // Init camera
    mainCamera.x     = 0;
    mainCamera.y     = -512;
    mainCamera.z     = 1500;
    mainCamera.pitch = 0;
    mainCamera.roll  = 0;
    mainCamera.yaw   = 2048;

    resetPlayer();

    Model filth;
    model_load("FILTH.MDL;1", &filth);
    uploadTexture(filth_128, filth_128Data, SCREEN_WIDTH, 256, 128, 128);
    

    debug("Start of main loop\n");
    // Main loop. Runs every frame, forever
    for(;;){

        ///////////////////////////
        //       Game logic      //
        ///////////////////////////
        //debug("Game Logic\n");
        #pragma region Game logic
        // Poll the controllers and run their assoicated functions
        controller_update();

        // Apply gravity if not grounded
        //if(!player.isGrounded){
        //    if(player.velocity.y + GRAVITY_CONSTANT > TERMINAL_VELOCITY){
        //        player.velocity.y = TERMINAL_VELOCITY;
        //    } else {
        //        player.velocity.y += GRAVITY_CONSTANT;
        //    }
        //}
        //// Collide with the BSP tree
        //Player3_move(&bspTree, &player);
        uint32_t playerColour = 0x000000;
        int32_t bspResult = BSPTree3_pointContents(&bspTree, 0, player.position);
        playerColour = bspResult == -1 ? 0x000000 : 0x00FF00;

        printf("BSPResult: %d\nplayerColor = %d\n", bspResult, playerColour);


        #pragma endregion



        ///////////////////////////
        //       Rendering       //
        ///////////////////////////
        //debug("Rendering\n");
        #pragma region Rendering

        // Set matrices to default
        gte_setRotationMatrix(
            ONE, 0, 0,
            0, ONE, 0,
            0, 0, ONE
        );
        
        // Move camera into position
        rotateCurrentMatrix(mainCamera.pitch, mainCamera.roll, mainCamera.yaw);
        setTranslationMatrix(0, 0, 0);
        

        // Render gizmo
        for (int i = 0; i<4; i++){
            transformVertex(&mainCamera, gizmoPoints[i], &transformedGizmoPoints[i]);
        };
        drawLine2(transformedGizmoPoints[0], transformedGizmoPoints[1], 0x0000FF);
        drawLine2(transformedGizmoPoints[0], transformedGizmoPoints[2], 0x00FF00);
        drawLine2(transformedGizmoPoints[0], transformedGizmoPoints[3], 0xFF0000);
        
        uint32_t colours[6] = {
            0x0000FF,
            0x00FF00,
            0xFF0000,
            0x00FFFF,
            0xFF00FF,
            0xFFFF00
        };

        // Render world
        Tri2 transformedTri;
        for(int i = 0; i<numTris; i++){
            Vector2 a, b, c;
            if(
                transformTri(&mainCamera, tris[i], &transformedTri)
            ){
                drawTri2(transformedTri, colours[i%6]);
            }
        }

        // Render player
        Vector3 scaledPlayerPos = {
            player.position.x,
            player.position.y,
            player.position.z,
        };
        Vector2 transformedPlayerPosB;
        if(transformVertex(&mainCamera, scaledPlayerPos, &transformedPlayerPosB)){
            drawCross2(transformedPlayerPosB, playerColour);
        }
        
        

        sprintf(str_Buffer, 
            "%s Mode\n"
            "Scale Factor: %d\n",
            controlCamera ? "Camera" : "Player",
            GTE_SCALE_FACTOR
        );
        // Text rendering
        printString(activeChain, &font, 10, 10, str_Buffer);

        // Draw a plain background
        dmaPtr = allocatePacket(activeChain, ORDERING_TABLE_SIZE -1 , 3);
        dmaPtr[0] = screenColor | gp0_vramFill();
        dmaPtr[1] = gp0_xy(bufferX, bufferY);
        dmaPtr[2] = gp0_xy(SCREEN_WIDTH, SCREEN_HEIGHT);

        #pragma endregion



        ///////////////////////////
        //   Framebuffer Logic   //
        ///////////////////////////
        //debug("Framebuffer Logic\n");
        #pragma region Framebuffer Logic

        // Set the framebuffer offset.
        dmaPtr = allocatePacket(activeChain, ORDERING_TABLE_SIZE - 1, 4);
        dmaPtr[0] = gp0_texpage(0, true, false);
        dmaPtr[1] = gp0_fbOffset1(bufferX, bufferY);
        dmaPtr[2] = gp0_fbOffset2(bufferX + SCREEN_WIDTH - 1, bufferY + SCREEN_HEIGHT - 2);
        dmaPtr[3] = gp0_fbOrigin(bufferX, bufferY);

        // This will wait for the GPU to be ready,
        // It also waits for Vblank.
        waitForGP0Ready();
        waitForVblank();

        // Give DMA a pointer to the last item in the ordering table.
        // We don't need to add a terminator, as it is already done for us by the OTC.
        sendLinkedList(&(activeChain->orderingTable)[ORDERING_TABLE_SIZE - 1]);

        // Swap the frame buffers.
        bufferY = usingSecondFrame ? 0 : SCREEN_HEIGHT;
        GPU_GP1 = gp1_fbOffset(bufferX, bufferY);

        // Point to the relevant DMA chain for this frame, then swap the active frame.
        activeChain = &dmaChains[usingSecondFrame];
        usingSecondFrame = !usingSecondFrame;

        // Reset the ordering table to a blank state.
        clearOrderingTable((activeChain->orderingTable), ORDERING_TABLE_SIZE);
        activeChain->nextPacket = activeChain->data;

        #pragma endregion
   

        printf("\n***\n\n"); // Add a separator between frames to make it easier to read debug output
    }
    __builtin_unreachable();
}