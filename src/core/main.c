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
#include "texture.h"
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

#define UNIT_SIZE 16 // Define unit sizes
#define PLAYER_BBOX_X (1 * UNIT_SIZE * ONE)
#define PLAYER_BBOX_Y (4 * UNIT_SIZE * ONE)
#define PLAYER_BBOX_Z (1 * UNIT_SIZE * ONE)


// Built-in debug textures
extern const uint8_t fontData[];
extern const uint8_t fontPalette[];
TextureInfo font;
extern const uint8_t default_32Data[];
extern const uint8_t default_32Palette[];
TextureInfo default_32;


extern const uint8_t filth_128Data[];
TextureInfo filth_128;



Camera mainCamera;
Player3 player;
char str_Buffer[256];
//int screenColor = 0xfa823c;
int screenColor = 0x000000;
int wallColor = 0x3c82fa;
int gteScaleFactor = 0;
int debugVariable = 0;
bool drawOutlines = true;

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
void drawTri2_texturedFlat(Tri2_texturedFlat tri, TextureInfo *texinfo, int max_recursion){

    int32_t maxX = max32s(tri.a.x, max32s(tri.b.x, tri.c.x));
    int32_t minX = min32s(tri.a.x, min32s(tri.b.x, tri.c.x));
    int32_t maxY = max32s(tri.a.y, max32s(tri.b.y, tri.c.y));
    int32_t minY = min32s(tri.a.y, min32s(tri.b.y, tri.c.y));
    //printf("maxX: %d (%d %d %d)\n", (int)maxX, (int)tri.a.x, (int)tri.b.x, (int)tri.c.x);
    //printf("maxY: %d (%d %d %d)\n\n", (int)maxY, (int)tri.a.y, (int)tri.b.y, (int)tri.c.y);

    if(maxX < 0 || minX > SCREEN_WIDTH || maxY < 0 || minY > SCREEN_WIDTH){
        // Outside screen, don't draw
        return;
    }

    int32_t width  = maxX - minX;
    int32_t height = maxY - minY;

    // If triangle too big, subdivide it
    if(width > 1023 || height > 511){
        Vector2_16 va = {(tri.a.x + tri.b.x) >> 1,(tri.a.y + tri.b.y) >> 1};
        Vector2_16 vb = {(tri.b.x + tri.c.x) >> 1,(tri.b.y + tri.c.y) >> 1};
        Vector2_16 vc = {(tri.c.x + tri.a.x) >> 1,(tri.c.y + tri.a.y) >> 1};
        Vector2    ta = {(tri.auv.x + tri.buv.x) >> 1,(tri.auv.y + tri.buv.y) >> 1};
        Vector2    tb = {(tri.buv.x + tri.cuv.x) >> 1,(tri.buv.y + tri.cuv.y) >> 1};
        Vector2    tc = {(tri.cuv.x + tri.auv.x) >> 1,(tri.cuv.y + tri.auv.y) >> 1};

        // Repeat the process for all sub-triangles
        drawTri2_texturedFlat(
            (Tri2_texturedFlat) {
                tri.a, va, vc,
                tri.z,
                tri.auv, ta, tc
            },
            texinfo,
            max_recursion
        );
        drawTri2_texturedFlat(
            (Tri2_texturedFlat) {
                va, tri.b, vb,
                tri.z,
                ta, tri.buv, tb
            },
            texinfo,
            max_recursion
        );
        drawTri2_texturedFlat(
            (Tri2_texturedFlat) {
                vb, tri.c, vc,
                tri.z,
                tb, tri.cuv, tc
            },
            texinfo,
            max_recursion
        );
        drawTri2_texturedFlat(
            (Tri2_texturedFlat) {
                va, vb, vc,
                tri.z,
                ta, tb, tc
            },
            texinfo,
            max_recursion
        );
        return;
    }

    // Base case: Triangle is of renderable size, so render it
    int32_t xy0 = gp0_xy(tri.a.x, tri.a.y);
    int32_t xy1 = gp0_xy(tri.b.x, tri.b.y);
    int32_t xy2 = gp0_xy(tri.c.x, tri.c.y);
    int32_t uv0 = gp0_uv(texinfo->u + tri.auv.x, texinfo->v + tri.auv.y, texinfo->clut);
    int32_t uv1 = gp0_uv(texinfo->u + tri.buv.x, texinfo->v + tri.buv.y, texinfo->page);
    int32_t uv2 = gp0_uv(texinfo->u + tri.cuv.x, texinfo->v + tri.cuv.y, 0);

    // Only supports tiling textures that are powers of 2 
    // TODO: This assumes tiling. We might not necessarily want that. Perhaps add an
    // Also this just BREAKS if the numbers are wrong. So don't let the numbers be wrong (must be powers of 2 >= 8)
    
    uint8_t bitmask_u = 0xFF << (31-__builtin_clz(texinfo->w));
    uint8_t bitmask_v = 0xFF << (31-__builtin_clz(texinfo->h));

    dmaPtr = allocatePacket(activeChain, tri.z, 8);
    dmaPtr[0] = gp0_texwindow(texinfo->u>>3, texinfo->v>>3, bitmask_u>>3, bitmask_v>>3);
    //dmaPtr[0] = gp0_texwindow(0, 4, 0b11100, 0b11100);
    //printf("%d %d\n", texinfo->u, bitmask_u);
    dmaPtr[1] = 0x808080 | gp0_triangle(true, false);
    dmaPtr[2] = xy0;
    dmaPtr[3] = uv0;
    dmaPtr[4] = xy1;
    dmaPtr[5] = uv1;
    dmaPtr[6] = xy2;
    dmaPtr[7] = uv2;

    if(drawOutlines){
        drawLine2((Vector2){tri.a.x, tri.a.y},(Vector2){tri.b.x, tri.b.y}, 0xFFFFFF); // AB
        drawLine2((Vector2){tri.b.x, tri.b.y},(Vector2){tri.c.x, tri.c.y}, 0xFFFFFF); // BC
        drawLine2((Vector2){tri.c.x, tri.c.y},(Vector2){tri.a.x, tri.a.y}, 0xFFFFFF); // CA
    }

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
    int32_t currentTx = gte_getControlReg(GTE_TRX);
    int32_t currentTy = gte_getControlReg(GTE_TRY);
    int32_t currentTz = gte_getControlReg(GTE_TRZ);
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

    // A single point means we can read the Z index from the SZ3 register rather than averaging them
    int zIndex = gte_getDataReg(GTE_SZ3);
    
    // Don't render things too far away.
    if(zIndex >= ORDERING_TABLE_SIZE){
        return false;
    }
    
    // Get the XY coordinate of the transformed cross
    uint32_t XY0 = gte_getDataReg(GTE_SXY2);
    Vector2 transformedCross;
    transformedCross.x = XY0 & 0xFFFF;
    transformedCross.y = XY0 >> 16;
    
    result->x = transformedCross.x;
    result->y = transformedCross.y;

    // Restore the translation and rotation back to the initial state as to not clobber any other models.
    gte_setControlReg(GTE_TRX, currentTx);
    gte_setControlReg(GTE_TRY, currentTy);
    gte_setControlReg(GTE_TRZ, currentTz);
    return true;
}
bool transformTri(Camera *cam, Tri3 tri, Tri2 *result){
    // Range check. Is it too big to be drawn?
    if(
        abs(cam->x - (tri.a.x>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->y - (tri.a.y>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->z - (tri.a.z>>GTE_SCALE_FACTOR)) > INT16_MAX ||
        abs(cam->x - (tri.b.x>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->y - (tri.b.y>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->z - (tri.b.z>>GTE_SCALE_FACTOR)) > INT16_MAX ||
        abs(cam->x - (tri.c.x>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->y - (tri.c.y>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->z - (tri.c.z>>GTE_SCALE_FACTOR)) > INT16_MAX
    ){
        // Out of range. Don't render
        //printf("Out of range. (too large)\n");
        return false;
    }

    // Save the current translation vector
    uint32_t currentTx = gte_getControlReg(GTE_TRX);
    uint32_t currentTy = gte_getControlReg(GTE_TRY);
    uint32_t currentTz = gte_getControlReg(GTE_TRZ);
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
    int MAC0 = gte_getDataReg(GTE_MAC0);
    uint32_t flags = gte_getControlReg(GTE_FLAG);
    bool clip = flags & GTE_FLAG_DIVIDE_OVERFLOW;
    
    //printf("%s | ", clip ? "True" : "False");
    //printf("0x%08x & 0x%08x = 0x%08x | ", flags, GTE_FLAG_DIVIDE_OVERFLOW, flags & GTE_FLAG_DIVIDE_OVERFLOW);

    if(MAC0 <= 0){
        gte_setControlReg(GTE_TRX, currentTx);
        gte_setControlReg(GTE_TRY, currentTy);
        gte_setControlReg(GTE_TRZ, currentTz);
        //printf("MAC0 (%d) <= 0\n", MAC0);
        return false;
    }
    if(clip){
        gte_setControlReg(GTE_TRX, currentTx);
        gte_setControlReg(GTE_TRY, currentTy);
        gte_setControlReg(GTE_TRZ, currentTz);
        //printf("Clip is set\n");
        return false;
    }
    uint32_t xy0 = gte_getDataReg(GTE_SXY0);
    uint32_t xy1 = gte_getDataReg(GTE_SXY1);
    uint32_t xy2 = gte_getDataReg(GTE_SXY2);


    gte_command(GTE_CMD_AVSZ3 | GTE_SF);
    int zIndex = gte_getDataReg(GTE_OTZ);
    //int sz0 = gte_getDataReg(GTE_SZ0);
    //int sz1 = gte_getDataReg(GTE_SZ1);
    //int sz2 = gte_getDataReg(GTE_SZ2);
    //int zIndex = max(max(sz0, sz1), sz2);

    if(zIndex < 1 || zIndex >= ORDERING_TABLE_SIZE){
        gte_setControlReg(GTE_TRX, currentTx);
        gte_setControlReg(GTE_TRY, currentTy);
        gte_setControlReg(GTE_TRZ, currentTz);
        //printf("Invalid Z index: %d\n", zIndex);
        return false;
    }
    
    // Save result
    result->a = (Vector2_16){xy0 & 0xFFFF, xy0 >> 16};
    result->b = (Vector2_16){xy1 & 0xFFFF, xy1 >> 16};
    result->c = (Vector2_16){xy2 & 0xFFFF, xy2 >> 16};
    result->z = zIndex;

    // Restore the translation and rotation back to the initial state as to not clobber any other models.
    gte_setControlReg(GTE_TRX, currentTx);
    gte_setControlReg(GTE_TRY, currentTy);
    gte_setControlReg(GTE_TRZ, currentTz);
    //printf("Valid triangle. (Z: %d, MAC0: %d)\n", zIndex, MAC0);

    return true;
}
bool transformTri_texturedFlat(Camera *cam, Tri3_texturedFlat tri, Tri2_texturedFlat *result){
    // Convert the textured_flat triangle to a regular triangle
    Tri3 _tri;
    _tri.a = tri.a;
    _tri.b = tri.b;
    _tri.c = tri.c;

    // To store the result
    Tri2 _result;
    bool ret = transformTri(cam, _tri, &_result);

    result->a = _result.a;
    result->b = _result.b;
    result->c = _result.c;
    result->z = _result.z;
    
    result->auv=tri.auv;
    result->buv=tri.buv;
    result->cuv=tri.cuv;
    
    return ret;
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
    int32_t currentTx = gte_getControlReg(GTE_TRX);
    int32_t currentTy = gte_getControlReg(GTE_TRY);
    int32_t currentTz = gte_getControlReg(GTE_TRZ);

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

    if(gte_getDataReg(GTE_MAC0) <= 0){
        // Restore matrices.
        gte_setControlReg(GTE_TRX, currentTx);
        gte_setControlReg(GTE_TRY, currentTy);
        gte_setControlReg(GTE_TRZ, currentTz);
        return false;
    }

    xy0 = gte_getDataReg(GTE_SXY0);
    
    // Load the last vert    
    gte_loadV0(&verts[3]);
    gte_command(GTE_CMD_RTPS | GTE_SF);

    sz0 = gte_getDataReg(GTE_SZ0);
    sz1 = gte_getDataReg(GTE_SZ1);
    sz2 = gte_getDataReg(GTE_SZ2);
    sz3 = gte_getDataReg(GTE_SZ3);
    int zIndex = max(max(sz0, sz1),max(sz2, sz3));

    if(zIndex < 0 || zIndex >= ORDERING_TABLE_SIZE){
        // Restore matrices.
        gte_setControlReg(GTE_TRX, currentTx);
        gte_setControlReg(GTE_TRY, currentTy);
        gte_setControlReg(GTE_TRZ, currentTz);
        return false;
    }

    xy1 = gte_getDataReg(GTE_SXY0);
    xy2 = gte_getDataReg(GTE_SXY1);
    xy3 = gte_getDataReg(GTE_SXY2);
    
    // Save result
    result->a = (Vector2){xy0 & 0xFFFF, xy0 >> 16};
    result->b = (Vector2){xy1 & 0xFFFF, xy1 >> 16};
    result->c = (Vector2){xy2 & 0xFFFF, xy2 >> 16};
    result->d = (Vector2){xy3 & 0xFFFF, xy3 >> 16};
    result->z = zIndex;

    // Restore matrices.
    gte_setControlReg(GTE_TRX, currentTx);
    gte_setControlReg(GTE_TRY, currentTy);
    gte_setControlReg(GTE_TRZ, currentTz);

    return true;
}

#pragma endregion



///////////////////////////////////////////////
// BSP Tree Definition and Shape Definitions //
///////////////////////////////////////////////
#pragma region BSPTree
int numTextures = 17;
BSPTextureInfo bspTextureInfo[] = {
    {
        "01F7.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01F1.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "SAVE.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01F5.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01L3.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01L4.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01L1.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01F6.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01DOOR.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01L0.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01F2.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "MISSING.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01F0.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01F8.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01F4.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01L2.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01F3.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
};
BSPNode3 bspNodes_hitscan[] = {
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 0,
        .children = {
            1, 10
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 0,
        .children = {
            2, 6
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 327680,
        .children = {
            -1, 3
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 327680,
        .children = {
            -1, 4
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -65536,
        .children = {
            5, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 65536,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 327680,
        .children = {
            -1, 7
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -327680,
        .children = {
            8, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -65536,
        .children = {
            9, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 65536,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 0,
        .children = {
            11, 15
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -327680,
        .children = {
            12, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 327680,
        .children = {
            -1, 13
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -65536,
        .children = {
            14, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 65536,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -327680,
        .children = {
            16, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -327680,
        .children = {
            17, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -65536,
        .children = {
            18, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 65536,
        .children = {
            -1, -2
        }
    },
};
BSPTree3 bsp_hitscan = {.nodes=bspNodes_hitscan, .numNodes = 19};

BSPNode3 bspNodes_player[] = {
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -131072,
        .children = {
            1, 10
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 131072,
        .children = {
            2, 6
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 458752,
        .children = {
            -1, 3
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 458752,
        .children = {
            -1, 4
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -327680,
        .children = {
            5, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 327680,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 458752,
        .children = {
            -1, 7
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -458752,
        .children = {
            8, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -327680,
        .children = {
            9, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 327680,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -458752,
        .children = {
            11, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -327680,
        .children = {
            12, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 327680,
        .children = {
            -1, 13
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -131072,
        .children = {
            14, 16
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 131072,
        .children = {
            15, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 458752,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -458752,
        .children = {
            -2, -1
        }
    },
};
BSPTree3 bsp_player = {.nodes=bspNodes_player, .numNodes = 17};

int numTris = 48;
Tri3_texturedFlat tris[] = {
    {
        {-327680, 65536, 327680},
        {-327680, -65536, 0},
        {-327680, 65536, 0},
        {63, 15},
        {0, 240},
        {0, 15},
        11
    },
    {
        {-327680, 65536, 327680},
        {-327680, -65536, 327680},
        {-327680, -65536, 0},
        {63, 15},
        {63, 240},
        {0, 240},
        11
    },
    {
        {0, -65536, 0},
        {-327680, 65536, 0},
        {-327680, -65536, 0},
        {255, 240},
        {176, 15},
        {176, 240},
        11
    },
    {
        {0, -65536, 0},
        {0, 65536, 0},
        {-327680, 65536, 0},
        {255, 240},
        {255, 15},
        {176, 15},
        11
    },
    {
        {0, 65536, 0},
        {-327680, 65536, 327680},
        {-327680, 65536, 0},
        {255, 255},
        {176, 176},
        {176, 255},
        11
    },
    {
        {0, 65536, 0},
        {0, 65536, 327680},
        {-327680, 65536, 327680},
        {255, 255},
        {255, 176},
        {176, 176},
        11
    },
    {
        {0, -65536, 327680},
        {-327680, -65536, 0},
        {-327680, -65536, 327680},
        {255, 224},
        {224, 255},
        {224, 224},
        12
    },
    {
        {0, -65536, 327680},
        {0, -65536, 0},
        {-327680, -65536, 0},
        {255, 224},
        {255, 255},
        {224, 255},
        12
    },
    {
        {0, 65536, 327680},
        {-327680, -65536, 327680},
        {-327680, 65536, 327680},
        {255, 15},
        {176, 240},
        {176, 15},
        11
    },
    {
        {0, 65536, 327680},
        {0, -65536, 327680},
        {-327680, -65536, 327680},
        {255, 15},
        {255, 240},
        {176, 240},
        11
    },
    {
        {0, -65536, 327680},
        {0, 65536, 0},
        {0, -65536, 0},
        {79, 240},
        {0, 15},
        {0, 240},
        11
    },
    {
        {0, -65536, 327680},
        {0, 65536, 327680},
        {0, 65536, 0},
        {79, 240},
        {79, 15},
        {0, 15},
        11
    },
    {
        {0, 65536, 327680},
        {0, -65536, 0},
        {0, 65536, 0},
        {79, 15},
        {0, 240},
        {0, 15},
        11
    },
    {
        {0, 65536, 327680},
        {0, -65536, 327680},
        {0, -65536, 0},
        {79, 15},
        {79, 240},
        {0, 240},
        11
    },
    {
        {327680, -65536, 0},
        {0, 65536, 0},
        {0, -65536, 0},
        {79, 240},
        {0, 15},
        {0, 240},
        11
    },
    {
        {327680, -65536, 0},
        {327680, 65536, 0},
        {0, 65536, 0},
        {79, 240},
        {79, 15},
        {0, 15},
        11
    },
    {
        {327680, 65536, 0},
        {0, 65536, 327680},
        {0, 65536, 0},
        {79, 255},
        {0, 176},
        {0, 255},
        11
    },
    {
        {327680, 65536, 0},
        {327680, 65536, 327680},
        {0, 65536, 327680},
        {79, 255},
        {79, 176},
        {0, 176},
        11
    },
    {
        {327680, -65536, 327680},
        {0, -65536, 0},
        {0, -65536, 327680},
        {224, 224},
        {255, 255},
        {224, 255},
        12
    },
    {
        {327680, -65536, 327680},
        {327680, -65536, 0},
        {0, -65536, 0},
        {224, 224},
        {255, 224},
        {255, 255},
        12
    },
    {
        {327680, 65536, 327680},
        {0, -65536, 327680},
        {0, 65536, 327680},
        {79, 15},
        {0, 240},
        {0, 15},
        11
    },
    {
        {327680, 65536, 327680},
        {327680, -65536, 327680},
        {0, -65536, 327680},
        {79, 15},
        {79, 240},
        {0, 240},
        11
    },
    {
        {327680, -65536, 327680},
        {327680, 65536, 0},
        {327680, -65536, 0},
        {79, 240},
        {0, 15},
        {0, 240},
        11
    },
    {
        {327680, -65536, 327680},
        {327680, 65536, 327680},
        {327680, 65536, 0},
        {79, 240},
        {79, 15},
        {0, 15},
        11
    },
    {
        {-327680, 65536, 0},
        {-327680, -65536, -327680},
        {-327680, 65536, -327680},
        {255, 15},
        {176, 240},
        {176, 15},
        11
    },
    {
        {-327680, 65536, 0},
        {-327680, -65536, 0},
        {-327680, -65536, -327680},
        {255, 15},
        {255, 240},
        {176, 240},
        11
    },
    {
        {0, -65536, -327680},
        {-327680, 65536, -327680},
        {-327680, -65536, -327680},
        {255, 240},
        {176, 15},
        {176, 240},
        11
    },
    {
        {0, -65536, -327680},
        {0, 65536, -327680},
        {-327680, 65536, -327680},
        {255, 240},
        {255, 15},
        {176, 15},
        11
    },
    {
        {0, 65536, -327680},
        {-327680, 65536, 0},
        {-327680, 65536, -327680},
        {255, 79},
        {176, 0},
        {176, 79},
        11
    },
    {
        {0, 65536, -327680},
        {0, 65536, 0},
        {-327680, 65536, 0},
        {255, 79},
        {255, 0},
        {176, 0},
        11
    },
    {
        {0, -65536, 0},
        {-327680, -65536, -327680},
        {-327680, -65536, 0},
        {255, 255},
        {224, 224},
        {255, 224},
        12
    },
    {
        {0, -65536, 0},
        {0, -65536, -327680},
        {-327680, -65536, -327680},
        {255, 255},
        {224, 255},
        {224, 224},
        12
    },
    {
        {0, 65536, 0},
        {-327680, -65536, 0},
        {-327680, 65536, 0},
        {255, 15},
        {176, 240},
        {176, 15},
        11
    },
    {
        {0, 65536, 0},
        {0, -65536, 0},
        {-327680, -65536, 0},
        {255, 15},
        {255, 240},
        {176, 240},
        11
    },
    {
        {0, -65536, 0},
        {0, 65536, -327680},
        {0, -65536, -327680},
        {255, 240},
        {176, 15},
        {176, 240},
        11
    },
    {
        {0, -65536, 0},
        {0, 65536, 0},
        {0, 65536, -327680},
        {255, 240},
        {255, 15},
        {176, 15},
        11
    },
    {
        {0, 65536, 0},
        {0, -65536, -327680},
        {0, 65536, -327680},
        {255, 15},
        {176, 240},
        {176, 15},
        11
    },
    {
        {0, 65536, 0},
        {0, -65536, 0},
        {0, -65536, -327680},
        {255, 15},
        {255, 240},
        {176, 240},
        11
    },
    {
        {327680, -65536, -327680},
        {0, 65536, -327680},
        {0, -65536, -327680},
        {79, 240},
        {0, 15},
        {0, 240},
        11
    },
    {
        {327680, -65536, -327680},
        {327680, 65536, -327680},
        {0, 65536, -327680},
        {79, 240},
        {79, 15},
        {0, 15},
        11
    },
    {
        {327680, 65536, -327680},
        {0, 65536, 0},
        {0, 65536, -327680},
        {79, 79},
        {0, 0},
        {0, 79},
        11
    },
    {
        {327680, 65536, -327680},
        {327680, 65536, 0},
        {0, 65536, 0},
        {79, 79},
        {79, 0},
        {0, 0},
        11
    },
    {
        {327680, -65536, 0},
        {0, -65536, -327680},
        {0, -65536, 0},
        {224, 255},
        {255, 224},
        {255, 255},
        12
    },
    {
        {327680, -65536, 0},
        {327680, -65536, -327680},
        {0, -65536, -327680},
        {224, 255},
        {224, 224},
        {255, 224},
        12
    },
    {
        {327680, 65536, 0},
        {0, -65536, 0},
        {0, 65536, 0},
        {79, 15},
        {0, 240},
        {0, 15},
        11
    },
    {
        {327680, 65536, 0},
        {327680, -65536, 0},
        {0, -65536, 0},
        {79, 15},
        {79, 240},
        {0, 240},
        11
    },
    {
        {327680, -65536, 0},
        {327680, 65536, -327680},
        {327680, -65536, -327680},
        {255, 240},
        {176, 15},
        {176, 240},
        11
    },
    {
        {327680, -65536, 0},
        {327680, 65536, 0},
        {327680, 65536, -327680},
        {255, 240},
        {255, 15},
        {176, 15},
        11
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
    if(gteScaleFactor > 255){
        gteScaleFactor = 255;
    }
}
void incrementDebugVariable(void){
    debugVariable ++;
    if(debugVariable > 255){
        debugVariable = 255;
    }
}
void decrementDebugVariable(void){
    debugVariable --;
    if(debugVariable < 0){
        debugVariable = 0;
    }
}


void resetPlayer(void){
    player.position = (Vector3){0, -(512<<GTE_SCALE_FACTOR), 0};
    player.velocity = (Vector3){0,    0, 0};
    player.coyoteTimer = 0;
    player.isGrounded = false;
}

void toggleOutlines(void){
    drawOutlines = !drawOutlines;
}


bool controlCamera = false;
void toggleControlSet(void){
    controlCamera = !controlCamera;
    if(controlCamera){
        controller_subscribeOnKeyHold(moveCameraLeft,         BUTTON_INDEX_LEFT    );
        controller_subscribeOnKeyHold(moveCameraRight,        BUTTON_INDEX_RIGHT   );
        controller_subscribeOnKeyHold(moveCameraForward,      BUTTON_INDEX_UP      );
        controller_subscribeOnKeyHold(moveCameraBackward,     BUTTON_INDEX_DOWN    );
        controller_subscribeOnKeyHold(moveCameraUp,           BUTTON_INDEX_R2      );
        controller_subscribeOnKeyHold(moveCameraDown,         BUTTON_INDEX_L2      );
        controller_subscribeOnKeyHold(lookLeft,               BUTTON_INDEX_SQUARE  );
        controller_subscribeOnKeyHold(lookRight,              BUTTON_INDEX_CIRCLE  );
        controller_subscribeOnKeyHold(lookUp,                 BUTTON_INDEX_TRIANGLE);
        controller_subscribeOnKeyHold(lookDown,               BUTTON_INDEX_X       );
        
        controller_subscribeOnKeyDown(decrementDebugVariable, BUTTON_INDEX_L1      );
        controller_subscribeOnKeyDown(incrementDebugVariable, BUTTON_INDEX_R1      );
        controller_subscribeOnKeyDown(toggleOutlines,         BUTTON_INDEX_SELECT  );
        controller_subscribeOnKeyDown(toggleControlSet,       BUTTON_INDEX_START   );
    } else {
        controller_subscribeOnKeyHold(movePlayerLeft,         BUTTON_INDEX_LEFT    );
        controller_subscribeOnKeyHold(movePlayerRight,        BUTTON_INDEX_RIGHT   );
        controller_subscribeOnKeyHold(movePlayerForward,      BUTTON_INDEX_UP      );
        controller_subscribeOnKeyHold(movePlayerBackward,     BUTTON_INDEX_DOWN    );
        controller_subscribeOnKeyHold(movePlayerUp,           BUTTON_INDEX_R2      );
        controller_subscribeOnKeyHold(movePlayerDown,         BUTTON_INDEX_L2      );
        controller_subscribeOnKeyHold(lookLeft,               BUTTON_INDEX_SQUARE  );
        controller_subscribeOnKeyHold(lookRight,              BUTTON_INDEX_CIRCLE  );
        controller_subscribeOnKeyHold(lookUp,                 BUTTON_INDEX_TRIANGLE);
        controller_subscribeOnKeyHold(lookDown,               BUTTON_INDEX_X       );

        controller_subscribeOnKeyDown(decrementDebugVariable, BUTTON_INDEX_L1      );
        controller_subscribeOnKeyDown(incrementDebugVariable, BUTTON_INDEX_R1      );
        controller_subscribeOnKeyDown(toggleOutlines,         BUTTON_INDEX_SELECT  );
        controller_subscribeOnKeyDown(toggleControlSet,       BUTTON_INDEX_START   );
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
    uploadIndexedTexture(&font, fontData, 960, 0, FONT_WIDTH, FONT_HEIGHT, 
        fontPalette, 960, FONT_HEIGHT, GP0_COLOR_4BPP);
    //uploadIndexedTexture(&default_32, default_32Data, 960-64, 128, 32, 32,
    //    default_32Palette, SCREEN_WIDTH, 128+32, GP0_COLOR_8BPP);
    //uploadTexture(&default_32, default_32Data, SCREEN_WIDTH+32, 0, 32, 32);
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
void main(void){

    // Tell the compiler that variables might be updated randomly (ie, IRQ handlers)
    __atomic_signal_fence(__ATOMIC_ACQUIRE);

    // Initialise important things for later
    initHardware();

    // Run this stuff once before the main loop.
    toggleControlSet();
    // Creates a new list and initialises with nulls
    Model filth;
    model_load("FILTH.MDL;1", &filth);
    uploadTexture(&filth_128, filth_128Data, SCREEN_WIDTH, 256, 128, 128);

    // Load all the necessary textures from disc
    printf("Loading textures from disc...\n");
    for(int i = 0; i<numTextures; i++){
        printf(" %d | Need to load texture %s\n", i, bspTextureInfo[i].name);
        int bytesLoaded = texture_loadTIM(bspTextureInfo[i].name, &bspTextureInfo[i].textureInfo);
        if(bytesLoaded >= 0){
            printf("Loaded %d bytes\n", bytesLoaded);
        } else {
            printf("Error loading texture: %d", bytesLoaded);
        }
    }

    int t = 4;

    printf("Texinfo: %d %d %d %d\n", bspTextureInfo[t].textureInfo.u, bspTextureInfo[t].textureInfo.v, bspTextureInfo[t].textureInfo.w, bspTextureInfo[t].textureInfo.h);
    
    uint8_t bitmask_u = 0xFF << (31-__builtin_clz(bspTextureInfo[t].textureInfo.w));
    uint8_t bitmask_v = 0xFF << (31-__builtin_clz(bspTextureInfo[t].textureInfo.h));
    printf("texwindow(%d, %d, %d, %d)\n",
        bspTextureInfo[t].textureInfo.u>>3,
        bspTextureInfo[t].textureInfo.v>>3,
        bitmask_u,
        bitmask_v
    );
    printf("(%d, %d, %x, %x)\n",
        bspTextureInfo[t].textureInfo.u,
        bspTextureInfo[t].textureInfo.v,
        bitmask_u,
        bitmask_v
    );
    printf("%d %d %d %d\n", bspTextureInfo[t].textureInfo.u, bspTextureInfo[t].textureInfo.v, bspTextureInfo[t].textureInfo.w, bspTextureInfo[t].textureInfo.h);
    printf("%d %d %d %d\n", bspTextureInfo[t].textureInfo.w, __builtin_clz(bspTextureInfo[t].textureInfo.w), 31-__builtin_clz(bspTextureInfo[t].textureInfo.w), bitmask_u);
    printf("%d %d %d %d\n", bspTextureInfo[t].textureInfo.h, __builtin_clz(bspTextureInfo[t].textureInfo.h), 31-__builtin_clz(bspTextureInfo[t].textureInfo.h), bitmask_v);
    printf("%d %d %d %d\n", bspTextureInfo[t].textureInfo.u, bspTextureInfo[t].textureInfo.u>>3, bspTextureInfo[t].textureInfo.v, bspTextureInfo[t].textureInfo.v>>3);


    

    // Init camera
    mainCamera.x     = 0;
    mainCamera.y     = -512;
    mainCamera.z     = -1500;
    mainCamera.pitch = 0;
    mainCamera.roll  = 0;
    mainCamera.yaw   = 0;

    resetPlayer();
    
    //printf("Min: %d\n", min32s(1, min32s(2, 3)));
    //printf("Max: %d\n", max32s(1, max32s(2, 3)));
    //while (true) {
    //    __asm__("");
    //}

    debug("Start of main loop\n");
    // Main loop. Runs every frame, forever
    for(;;){

        ///////////////////////////
        //       Game logic      //
        ///////////////////////////
        //debug("Game Logic\n");
        #pragma region Game logic
        printf("Game Logic\n");
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
        //Player3_move(&bsp_player, &player);
        uint32_t playerColour = 0x000000;
        int32_t bspResult = BSPTree3_pointContents(&bsp_player, 0, player.position);
        playerColour = bspResult == -1 ? 0x000000 : 0xFFFFFF;


        #pragma endregion



        ///////////////////////////
        //       Rendering       //
        ///////////////////////////
        //debug("Rendering\n");
        #pragma region Rendering
        printf("Rendering\n");
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
        Tri2_texturedFlat transformedTri;
        TextureInfo *texinfo;
        for(int i = 0; i<numTris; i++){
            int32_t ti = tris[i].textureIndex;
            if(ti == -1){
                continue; // Don't render empty brushes. TODO: Fix this elsewhere.
            }
            if(ti > numTextures){
                printf(
                    "Texture index %d is out of range! (numTextures: %d)\n",
                    ti, numTextures
                );
                continue;
            }
            if(
                transformTri_texturedFlat(&mainCamera, tris[i], &transformedTri)
            ){
                // Assume texture is loaded otherwise.
                // Ideally, if the correct texture isn't loaded, then the "missing"
                // texture will take its place in the texinfo field.
                drawTri2_texturedFlat(transformedTri, &bspTextureInfo[ti].textureInfo, 5);
            }
        }


        sprintf(str_Buffer, 
            "%s Mode\n"
            "Debug Variable: %d\n",
            controlCamera ? "Camera" : "Player",
            debugVariable
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
        printf("Framebuffer\n");

        // Set the framebuffer offset.
        dmaPtr = allocatePacket(activeChain, ORDERING_TABLE_SIZE - 1, 4);
        dmaPtr[0] = gp0_texpage(0, true, false);
        dmaPtr[1] = gp0_fbOffset1(bufferX, bufferY);
        dmaPtr[2] = gp0_fbOffset2(bufferX + SCREEN_WIDTH - 1, bufferY + SCREEN_HEIGHT - 2);
        dmaPtr[3] = gp0_fbOrigin(bufferX, bufferY);

        // This will wait for the GPU to be ready,
        waitForGP0Ready();
        

        // Give DMA a pointer to the last item in the ordering table.
        // We don't need to add a terminator, as it is already done for us by the OTC.
        sendLinkedList(&(activeChain->orderingTable)[ORDERING_TABLE_SIZE - 1]);
        waitForVblank();
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
   

        //debug("\n***\n\n"); // Add a separator between frames to make it easier to read debug output
    }
}
