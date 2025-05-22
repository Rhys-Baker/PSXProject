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
    int32_t distX = abs((cam->x>>GTE_SCALE_FACTOR) - (point.x>>GTE_SCALE_FACTOR));
    int32_t distY = abs((cam->y>>GTE_SCALE_FACTOR) - (point.y>>GTE_SCALE_FACTOR));
    int32_t distZ = abs((cam->z>>GTE_SCALE_FACTOR) - (point.z>>GTE_SCALE_FACTOR));
    
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

    // ensure the command has “gone to hardware” before we read back regs:
    __asm__ volatile ("" ::: "memory");

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
    uint32_t currentTx;
    uint32_t currentTy;
    uint32_t currentTz;

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
    currentTx = gte_getControlReg(GTE_TRX);
    currentTy = gte_getControlReg(GTE_TRY);
    currentTz = gte_getControlReg(GTE_TRZ);

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

    // ensure the command has “gone to hardware” before we read back regs:
    __asm__ volatile ("" ::: "memory");

    int MAC0 = gte_getDataReg(GTE_MAC0);
    uint32_t flags = gte_getControlReg(GTE_FLAG);
    bool clip = flags & GTE_FLAG_DIVIDE_OVERFLOW;
    
    //printf("%s | ", clip ? "True" : "False");
    //printf("0x%08x & 0x%08x = 0x%08x | ", flags, GTE_FLAG_DIVIDE_OVERFLOW, flags & GTE_FLAG_DIVIDE_OVERFLOW);
    

    if(MAC0 <= 0){
        gte_setControlReg(GTE_TRX, currentTx);
        gte_setControlReg(GTE_TRY, currentTy);
        gte_setControlReg(GTE_TRZ, currentTz);
        return false;
    }
    if(clip){
        gte_setControlReg(GTE_TRX, currentTx);
        gte_setControlReg(GTE_TRY, currentTy);
        gte_setControlReg(GTE_TRZ, currentTz);
        return false;
    }
    uint32_t xy0 = gte_getDataReg(GTE_SXY0);
    uint32_t xy1 = gte_getDataReg(GTE_SXY1);
    uint32_t xy2 = gte_getDataReg(GTE_SXY2);


    gte_command(GTE_CMD_AVSZ3 | GTE_SF);
    int zIndex = gte_getDataReg(GTE_OTZ);

    if(zIndex < 1 || zIndex >= ORDERING_TABLE_SIZE){
        gte_setControlReg(GTE_TRX, currentTx);
        gte_setControlReg(GTE_TRY, currentTy);
        gte_setControlReg(GTE_TRZ, currentTz);
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

    return true;
}
bool transformTri_texturedFlat(Camera *cam, Tri3_texturedFlat tri, Tri2_texturedFlat *result){
    // Convert the textured_flat triangle to a regular triangle
    Tri3 _tri;
    _tri.a = tri.a;
    _tri.b = tri.b;
    _tri.c = tri.c;

    // To store the result
    Tri2 _result = {
        {0, 0},
        {0, 0},
        {0, 0},
        0
    };

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
            1, 315
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 655360,
        .children = {
            2, 152
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2293760,
        .children = {
            3, 58
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 983040,
        .children = {
            -1, 4
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
            5, 50
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3604480,
        .children = {
            6, 27
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            7, 16
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            8, 11
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1048576,
        .children = {
            -1, 9
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            -1, 10
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
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
        .distance = 983040,
        .children = {
            -1, 12
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            13, 15
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 14
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3932160,
        .children = {
            17, 22
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -1, 18
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            19, 21
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 20
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -1, 23
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            24, 26
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 25
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2949120,
        .children = {
            28, 39
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3276800,
        .children = {
            29, 34
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -1, 30
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            31, 33
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 32
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -1, 35
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            36, 38
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 37
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2621440,
        .children = {
            40, 45
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -1, 41
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            42, 44
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 43
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -1, 46
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            47, 49
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 48
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            51, 56
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3604480,
        .children = {
            52, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            53, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            54, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            -1, 55
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            57, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
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
            59, 115
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 983040,
        .children = {
            60, 71
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            61, 66
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            -1, 62
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1343488,
        .children = {
            -1, 63
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1638400,
        .children = {
            64, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1966080,
        .children = {
            65, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
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
        .distance = 360448,
        .children = {
            -1, 67
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 688128,
        .children = {
            68, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1638400,
        .children = {
            69, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1966080,
        .children = {
            70, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
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
        .distance = 983040,
        .children = {
            72, 75
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1048576,
        .children = {
            -1, 73
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            74, -1
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
            .y = -4096,
            .z = 0
        },
        .distance = 983040,
        .children = {
            76, 95
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1638400,
        .children = {
            77, 86
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1966080,
        .children = {
            78, 82
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            79, 81
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 80
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            83, 85
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 84
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            87, 91
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            88, 90
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 89
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            92, 94
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 93
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
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
            96, 105
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 655360,
        .children = {
            97, 101
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            98, 100
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 99
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            102, 104
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 103
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            106, 110
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            107, 109
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 108
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 655360,
        .children = {
            111, 113
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            112, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
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
        .distance = 917504,
        .children = {
            -1, 114
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 983040,
        .children = {
            116, 140
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 688128,
        .children = {
            117, 130
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1343488,
        .children = {
            118, 122
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1376256,
        .children = {
            -1, 119
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1638400,
        .children = {
            120, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1966080,
        .children = {
            121, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
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
        .distance = 229376,
        .children = {
            123, 125
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2260992,
        .children = {
            124, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            126, 128
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
        .children = {
            127, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2326528,
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
        .distance = 2293760,
        .children = {
            129, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2326528,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 655360,
        .children = {
            131, 134
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1638400,
        .children = {
            132, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1966080,
        .children = {
            133, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 458752,
        .children = {
            135, 137
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 229376,
        .children = {
            -1, 136
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
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
        .distance = 229376,
        .children = {
            -1, 138
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -1, 139
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1638400,
        .children = {
            141, 144
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1966080,
        .children = {
            142, 143
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 655360,
        .children = {
            145, 148
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            146, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            -2, 147
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 688128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            149, 151
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 229376,
        .children = {
            150, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2293760,
        .children = {
            153, 245
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1048576,
        .children = {
            154, 167
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
            155, 161
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            -1, 156
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
            -1, 157
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3276800,
        .children = {
            158, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3932160,
        .children = {
            159, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            160, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
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
        .distance = 1114112,
        .children = {
            -1, 162
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
            163, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3276800,
        .children = {
            164, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3932160,
        .children = {
            165, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            166, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
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
        .distance = -983040,
        .children = {
            168, 239
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3604480,
        .children = {
            169, 200
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            170, 181
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            171, 172
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
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
        .distance = 983040,
        .children = {
            173, 176
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            174, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1092476,
        .children = {
            -2, 175
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1092476,
        .children = {
            -2, -1
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
            177, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            178, 179
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, 180
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3932160,
        .children = {
            182, 191
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            183, 186
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            184, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1092476,
        .children = {
            -2, 185
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1092476,
        .children = {
            -2, -1
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
            187, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            188, 189
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, 190
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
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
        .distance = 983040,
        .children = {
            192, 195
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            193, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1092476,
        .children = {
            -2, 194
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1092476,
        .children = {
            -2, -1
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
            196, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            197, 198
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, 199
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2949120,
        .children = {
            201, 220
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3276800,
        .children = {
            202, 211
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            203, 206
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            204, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1092476,
        .children = {
            -2, 205
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1092476,
        .children = {
            -2, -1
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
            207, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            208, 209
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, 210
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
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
        .distance = 983040,
        .children = {
            212, 215
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            213, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1092476,
        .children = {
            -2, 214
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1092476,
        .children = {
            -2, -1
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
            216, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            217, 218
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, 219
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2621440,
        .children = {
            221, 230
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            222, 225
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            223, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1092476,
        .children = {
            -2, 224
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1092476,
        .children = {
            -2, -1
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
            226, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            227, 228
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, 229
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
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
        .distance = 983040,
        .children = {
            231, 234
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            232, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1092476,
        .children = {
            -2, 233
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1092476,
        .children = {
            -2, -1
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
            235, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            236, 237
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, 238
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
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
            -1, 240
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1048576,
        .children = {
            241, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3276800,
        .children = {
            242, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3932160,
        .children = {
            243, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            244, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
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
        .distance = 1048576,
        .children = {
            246, 258
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
            247, 252
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            -1, 248
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
            -1, 249
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -2, 250
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
            -2, 251
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            -1, 253
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
            254, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            -2, 255
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 655360,
        .children = {
            -2, 256
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
            -2, 257
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            259, 294
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -983040,
        .children = {
            260, 292
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            261, 265
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1092476,
        .children = {
            262, 264
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            -2, 263
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
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1092476,
        .children = {
            -2, -1
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
            266, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 983040,
        .children = {
            267, 285
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1638400,
        .children = {
            268, 277
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1966080,
        .children = {
            269, 273
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            270, 271
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, 272
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
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
        .distance = -917504,
        .children = {
            274, 275
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, 276
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            278, 282
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            279, 280
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, 281
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, 283
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            -1, 284
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, 286
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            -1, 287
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
            288, 291
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 655360,
        .children = {
            289, 290
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
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
            -1, 293
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1048576,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            295, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 655360,
        .children = {
            296, 308
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            297, 304
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
            298, 301
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
            299, 300
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1092476,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, -1
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
            302, 303
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1092476,
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
            -2, 305
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
            -2, 306
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            -2, 307
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
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
            309, 312
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
            -2, 310
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            -2, 311
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            -2, -1
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
            -2, 313
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            -2, 314
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -983040,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 655360,
        .children = {
            316, 466
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2293760,
        .children = {
            317, 372
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 983040,
        .children = {
            -1, 318
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
            319, 327
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            320, 325
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3604480,
        .children = {
            321, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            322, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            323, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            -1, 324
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            326, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3604480,
        .children = {
            328, 349
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            329, 338
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            330, 333
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1048576,
        .children = {
            331, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            -1, 332
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
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
        .distance = -983040,
        .children = {
            334, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            335, 337
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            336, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3932160,
        .children = {
            339, 344
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            340, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            341, 343
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            342, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
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
        .distance = -983040,
        .children = {
            345, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            346, 348
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            347, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2949120,
        .children = {
            350, 361
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3276800,
        .children = {
            351, 356
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            352, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            353, 355
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            354, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
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
        .distance = -983040,
        .children = {
            357, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            358, 360
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            359, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2621440,
        .children = {
            362, 367
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            363, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            364, 366
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            365, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
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
        .distance = -983040,
        .children = {
            368, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            369, 371
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            370, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
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
            373, 410
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 983040,
        .children = {
            374, 398
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 688128,
        .children = {
            375, 388
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1343488,
        .children = {
            376, 380
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1376256,
        .children = {
            -1, 377
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1638400,
        .children = {
            378, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1966080,
        .children = {
            379, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
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
        .distance = -229376,
        .children = {
            381, 386
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            382, 384
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
        .children = {
            383, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2326528,
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
        .distance = 2293760,
        .children = {
            385, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2326528,
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
        .distance = 2260992,
        .children = {
            387, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 655360,
        .children = {
            389, 392
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1638400,
        .children = {
            390, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1966080,
        .children = {
            391, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 458752,
        .children = {
            393, 395
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -229376,
        .children = {
            394, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
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
        .distance = -229376,
        .children = {
            396, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -1, 397
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1638400,
        .children = {
            399, 402
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1966080,
        .children = {
            400, 401
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 655360,
        .children = {
            403, 406
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            404, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            -2, 405
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 688128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            407, 409
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -229376,
        .children = {
            -1, 408
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 983040,
        .children = {
            411, 422
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            412, 417
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            413, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1343488,
        .children = {
            -1, 414
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1638400,
        .children = {
            415, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1966080,
        .children = {
            416, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
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
        .distance = -360448,
        .children = {
            418, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 688128,
        .children = {
            419, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1638400,
        .children = {
            420, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1966080,
        .children = {
            421, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
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
        .distance = -983040,
        .children = {
            423, 463
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 983040,
        .children = {
            424, 443
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1638400,
        .children = {
            425, 434
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1966080,
        .children = {
            426, 430
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            427, 429
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            428, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
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
        .distance = 917504,
        .children = {
            431, 433
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            432, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            435, 439
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            436, 438
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            437, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
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
        .distance = 917504,
        .children = {
            440, 442
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            441, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
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
            444, 453
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 655360,
        .children = {
            445, 449
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            446, 448
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            447, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
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
        .distance = 917504,
        .children = {
            450, 452
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            451, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            454, 458
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            455, 457
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            456, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
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
        .distance = -655360,
        .children = {
            459, 461
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            -1, 460
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            462, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1048576,
        .children = {
            464, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            465, -1
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
            .y = -4096,
            .z = 0
        },
        .distance = 2293760,
        .children = {
            467, 558
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1048576,
        .children = {
            468, 546
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -983040,
        .children = {
            469, 540
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3604480,
        .children = {
            470, 501
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            471, 482
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            472, 473
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
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
        .distance = -983040,
        .children = {
            474, 479
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
            -1, 475
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            476, 477
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            478, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            480, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1092476,
        .children = {
            481, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1092476,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3932160,
        .children = {
            483, 492
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            484, 489
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
            -1, 485
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            486, 487
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            488, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            490, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1092476,
        .children = {
            491, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1092476,
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
        .distance = -983040,
        .children = {
            493, 498
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
            -1, 494
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            495, 496
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            497, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            499, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1092476,
        .children = {
            500, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1092476,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2949120,
        .children = {
            502, 521
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3276800,
        .children = {
            503, 512
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            504, 509
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
            -1, 505
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            506, 507
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            508, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            510, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1092476,
        .children = {
            511, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1092476,
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
        .distance = -983040,
        .children = {
            513, 518
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
            -1, 514
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            515, 516
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            517, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            519, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1092476,
        .children = {
            520, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1092476,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2621440,
        .children = {
            522, 531
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            523, 528
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
            -1, 524
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            525, 526
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            527, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            529, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1092476,
        .children = {
            530, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1092476,
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
        .distance = -983040,
        .children = {
            532, 537
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
            -1, 533
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            534, 535
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            536, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            538, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1092476,
        .children = {
            539, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1092476,
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
            541, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1048576,
        .children = {
            542, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3276800,
        .children = {
            543, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3932160,
        .children = {
            544, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            545, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
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
            547, 552
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            548, -1
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
            -1, 549
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3604480,
        .children = {
            550, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            551, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
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
        .distance = -1114112,
        .children = {
            553, -1
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
            554, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3276800,
        .children = {
            555, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3932160,
        .children = {
            556, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            557, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
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
        .distance = -1048576,
        .children = {
            559, 616
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            560, 595
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -983040,
        .children = {
            561, 593
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            562, 589
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
            -1, 563
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 983040,
        .children = {
            564, 582
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1638400,
        .children = {
            565, 574
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1966080,
        .children = {
            566, 570
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            567, 568
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            569, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            571, 572
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            573, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            575, 579
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            576, 577
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            578, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            580, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            -1, 581
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            583, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            -1, 584
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
            585, 588
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 655360,
        .children = {
            586, 587
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1092476,
        .children = {
            590, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            591, 592
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1092476,
        .children = {
            -1, -2
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
            594, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1048576,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            596, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -655360,
        .children = {
            597, 605
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
            598, 601
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
            -2, 599
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            -2, 600
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -983040,
        .children = {
            -2, -1
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
            -2, 602
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
            -2, 603
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            -2, 604
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            606, 609
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
            -2, 607
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            -2, 608
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            -2, -1
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
            610, 613
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
            611, 612
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1092476,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, -1
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
            614, 615
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1092476,
        .children = {
            -2, -1
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
            617, 622
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            618, -1
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
            -1, 619
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -2, 620
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
            -2, 621
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            623, -1
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
            624, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -2, 625
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
            -2, 626
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -2, -1
        }
    },
};
BSPTree3 bsp_hitscan = {.nodes=bspNodes_hitscan, .numNodes = 627};

BSPNode3 bspNodes_player[] = {
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2228224,
        .children = {
            1, 418
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1114112,
        .children = {
            -1, 2
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
            3, 173
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 786432,
        .children = {
            4, 46
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -131072,
        .children = {
            5, 28
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3342336,
        .children = {
            6, 27
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4194304,
        .children = {
            7, 26
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4849664,
        .children = {
            8, 11
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -1, 9
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1081344,
        .children = {
            -1, 10
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4915200,
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
        .distance = 1179648,
        .children = {
            -1, 12
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4521984,
        .children = {
            13, 18
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 524288,
        .children = {
            14, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 973159,
        .children = {
            15, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 819200,
        .children = {
            16, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            17, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1081344,
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
        .distance = 524288,
        .children = {
            19, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 973159,
        .children = {
            20, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1081344,
        .children = {
            21, 23
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 819200,
        .children = {
            22, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
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
        .distance = 819200,
        .children = {
            24, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            25, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4325376,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
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
        .distance = 1114112,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3342336,
        .children = {
            29, 45
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3997696,
        .children = {
            30, 40
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4849664,
        .children = {
            31, 34
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            32, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1081344,
        .children = {
            -1, 33
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4915200,
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
        .distance = -819200,
        .children = {
            -2, 35
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            36, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1081344,
        .children = {
            37, 38
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, 39
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4325376,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3670016,
        .children = {
            41, 43
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -819200,
        .children = {
            -2, 42
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -819200,
        .children = {
            -2, 44
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1245184,
        .children = {
            47, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3670016,
        .children = {
            48, 91
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 851968,
        .children = {
            49, 68
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1245184,
        .children = {
            -1, 50
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4849664,
        .children = {
            51, 53
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -1, 52
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4915200,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4521984,
        .children = {
            54, 56
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            55, -2
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            57, 58
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
        .distance = 524288,
        .children = {
            -2, 59
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4194304,
        .children = {
            60, 65
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 917504,
        .children = {
            -2, 61
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            62, 64
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4325376,
        .children = {
            -2, 63
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4325376,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 917504,
        .children = {
            -2, 66
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            67, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3997696,
        .children = {
            69, 82
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4849664,
        .children = {
            70, 72
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            71, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4915200,
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
        .distance = -917504,
        .children = {
            73, 80
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -851968,
        .children = {
            74, 77
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -973159,
        .children = {
            75, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4325376,
        .children = {
            -2, 76
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 973159,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4325376,
        .children = {
            -2, 78
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            79, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -938244,
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
        .distance = 458752,
        .children = {
            81, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            83, 88
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -851968,
        .children = {
            84, 86
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -973159,
        .children = {
            85, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 973159,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            87, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -938244,
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
        .distance = 458752,
        .children = {
            89, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, 90
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3014656,
        .children = {
            92, 124
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 851968,
        .children = {
            93, 104
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1245184,
        .children = {
            -1, 94
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            95, 96
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
        .distance = 524288,
        .children = {
            -2, 97
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3538944,
        .children = {
            98, 101
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 917504,
        .children = {
            -2, 99
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            100, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 917504,
        .children = {
            -2, 102
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            103, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3342336,
        .children = {
            105, 114
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            106, 111
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -851968,
        .children = {
            107, 109
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -973159,
        .children = {
            108, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 973159,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            110, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -938244,
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
        .distance = 458752,
        .children = {
            112, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, 113
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            115, 121
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -851968,
        .children = {
            116, 118
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -973159,
        .children = {
            117, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 973159,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            119, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 524288,
        .children = {
            -2, 120
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -938244,
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
        .distance = 196608,
        .children = {
            122, -2
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
            123, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -851968,
        .children = {
            125, 151
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -973159,
        .children = {
            126, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1245184,
        .children = {
            -1, 127
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 851968,
        .children = {
            128, 146
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 524288,
        .children = {
            129, 130
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
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
        .distance = 917504,
        .children = {
            131, 140
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2555904,
        .children = {
            132, 138
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            133, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2883584,
        .children = {
            134, 136
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            135, -2
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
        .distance = 458752,
        .children = {
            137, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
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
        .distance = 458752,
        .children = {
            139, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
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
        .distance = 196608,
        .children = {
            141, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2883584,
        .children = {
            142, 143
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2555904,
        .children = {
            144, 145
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2359296,
        .children = {
            147, 150
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2686976,
        .children = {
            148, 149
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 973159,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 973159,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 973159,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2686976,
        .children = {
            152, 158
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            153, 155
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            154, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -938244,
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
        .distance = 458752,
        .children = {
            156, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, 157
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2359296,
        .children = {
            159, 166
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            160, 162
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            161, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -938244,
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
        .distance = 131072,
        .children = {
            163, -2
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
            164, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, 165
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            167, 169
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            168, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -938244,
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
        .distance = 131072,
        .children = {
            170, -2
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
            171, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, 172
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1179648,
        .children = {
            174, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 131072,
        .children = {
            175, 288
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1245184,
        .children = {
            -1, 176
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2359296,
        .children = {
            177, 269
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4849664,
        .children = {
            178, 181
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -1, 179
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1114112,
        .children = {
            180, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4915200,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3670016,
        .children = {
            182, 213
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            183, 198
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 851968,
        .children = {
            184, 194
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4521984,
        .children = {
            185, 188
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 917504,
        .children = {
            186, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            187, -2
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
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 917504,
        .children = {
            189, 191
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
            -2, 190
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4325376,
        .children = {
            -2, 192
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            193, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3997696,
        .children = {
            195, 197
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4325376,
        .children = {
            -2, 196
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 973159,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 973159,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -1, 199
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4521984,
        .children = {
            200, 202
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1114112,
        .children = {
            -2, 201
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
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1114112,
        .children = {
            203, 212
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
            204, 206
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            205, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4325376,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4194304,
        .children = {
            207, 210
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            208, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4325376,
        .children = {
            -2, 209
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            211, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            -2, -1
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
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 851968,
        .children = {
            214, 251
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1114112,
        .children = {
            215, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3342336,
        .children = {
            216, 224
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
            217, 219
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 917504,
        .children = {
            -2, 218
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -1, 220
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            221, 222
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            223, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2686976,
        .children = {
            225, 242
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3014656,
        .children = {
            226, 234
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
            227, 229
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 917504,
        .children = {
            -2, 228
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -1, 230
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            231, 232
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            -2, 233
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
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
            235, 237
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 917504,
        .children = {
            -2, 236
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -1, 238
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            239, 240
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            241, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            243, 248
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 917504,
        .children = {
            244, 247
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -196607,
        .children = {
            -2, 245
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
            -2, 246
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -1, 249
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            250, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3014656,
        .children = {
            252, 260
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            253, 258
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            254, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            255, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3342336,
        .children = {
            256, 257
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 973159,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 973159,
        .children = {
            -2, -1
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
            259, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1114112,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            261, 267
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            262, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2686976,
        .children = {
            263, 265
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            264, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 973159,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            266, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 973159,
        .children = {
            -2, -1
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
            268, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1114112,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            270, 283
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 851968,
        .children = {
            271, 280
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            272, 277
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 917504,
        .children = {
            273, 276
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -196607,
        .children = {
            -2, 274
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            275, -2
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
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -1, 278
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            279, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            281, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            282, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 973159,
        .children = {
            -2, -1
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
            284, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1114112,
        .children = {
            285, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 524288,
        .children = {
            286, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 819200,
        .children = {
            287, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3670016,
        .children = {
            289, 339
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4849664,
        .children = {
            290, 293
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            291, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1114112,
        .children = {
            292, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4915200,
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
        .distance = -1114112,
        .children = {
            294, 338
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -851968,
        .children = {
            295, 311
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4521984,
        .children = {
            -2, 296
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -524288,
        .children = {
            297, 303
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            298, 299
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4325376,
        .children = {
            -2, -1
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
            300, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            301, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
        .children = {
            302, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4325376,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4325376,
        .children = {
            -2, 304
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -819200,
        .children = {
            305, 310
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4194304,
        .children = {
            306, 308
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            307, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -973159,
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
        .distance = -786432,
        .children = {
            309, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -973159,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -973159,
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
        .distance = -1245184,
        .children = {
            312, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4325376,
        .children = {
            313, 319
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            314, 317
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            -2, 315
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
            -2, 316
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, 318
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3997696,
        .children = {
            320, 329
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            321, 326
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            322, 323
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -938244,
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
        .distance = -196607,
        .children = {
            -2, 324
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, 325
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
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, 327
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            328, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            330, 335
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            331, 332
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -938244,
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
        .distance = -196607,
        .children = {
            -2, 333
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, 334
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
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, 336
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            337, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            -2, -1
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1245184,
        .children = {
            340, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3014656,
        .children = {
            341, 369
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1114112,
        .children = {
            342, 368
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -524288,
        .children = {
            343, 347
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            -1, 344
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
            345, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            346, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
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
        .distance = -524288,
        .children = {
            348, 359
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3342336,
        .children = {
            349, 354
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            350, 351
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -938244,
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
        .distance = -196607,
        .children = {
            -2, 352
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, 353
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
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            355, 356
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -938244,
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
        .distance = -196607,
        .children = {
            -2, 357
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, 358
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
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            360, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -851968,
        .children = {
            361, 363
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -973159,
        .children = {
            362, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3342336,
        .children = {
            364, 366
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, 365
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, 367
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            -2, -1
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            370, 400
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2359296,
        .children = {
            371, 390
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -851968,
        .children = {
            372, 373
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -973159,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2686976,
        .children = {
            374, 382
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            375, 380
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            376, 377
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -938244,
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
        .distance = -196607,
        .children = {
            -2, 378
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, 379
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
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, 381
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            383, 388
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            384, 385
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -938244,
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
        .distance = -196607,
        .children = {
            -2, 386
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, 387
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
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, 389
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -851968,
        .children = {
            391, 392
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -973159,
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
        .distance = -524288,
        .children = {
            393, 398
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            394, 395
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -938244,
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
        .distance = -196607,
        .children = {
            -2, 396
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, 397
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
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, 399
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            401, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -131072,
        .children = {
            402, 403
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2359296,
        .children = {
            404, 412
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
            405, 411
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2686976,
        .children = {
            406, 408
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            407, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
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
        .distance = -1114112,
        .children = {
            409, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            410, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
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
        .distance = -1114112,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1114112,
        .children = {
            413, 417
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -524288,
        .children = {
            414, -2
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
            415, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            416, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 393216,
        .children = {
            419, 906
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 524288,
        .children = {
            420, 632
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1114112,
        .children = {
            421, 562
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -491520,
        .children = {
            422, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1507328,
        .children = {
            423, 502
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 491520,
        .children = {
            -1, 424
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1638400,
        .children = {
            -1, 425
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2424832,
        .children = {
            426, 435
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 884736,
        .children = {
            427, 431
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            428, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            -1, 429
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2457600,
        .children = {
            -1, 430
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1605632,
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
        .distance = -360448,
        .children = {
            432, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            -1, 433
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2457600,
        .children = {
            -1, 434
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 425984,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -131072,
        .children = {
            436, 469
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 425984,
        .children = {
            437, 466
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1835008,
        .children = {
            438, 460
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1605632,
        .children = {
            439, 440
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
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2097152,
        .children = {
            441, 455
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
            -2, 442
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            -2, 443
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1277952,
        .children = {
            -2, 444
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2129920,
        .children = {
            445, 452
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 884736,
        .children = {
            446, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            -2, 447
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 950272,
        .children = {
            448, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -98304,
        .children = {
            449, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -2, 450
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 98304,
        .children = {
            -2, 451
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2162688,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 950272,
        .children = {
            453, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            -2, 454
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1277952,
        .children = {
            -2, 456
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
            -2, 457
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 950272,
        .children = {
            458, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            -2, 459
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            461, 464
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1277952,
        .children = {
            462, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1605632,
        .children = {
            463, -2
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
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -2, 465
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 950272,
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
        .distance = 2097152,
        .children = {
            467, 468
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
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1835008,
        .children = {
            470, 488
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1605632,
        .children = {
            471, 472
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 425984,
        .children = {
            473, 487
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
            474, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2097152,
        .children = {
            475, 483
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 884736,
        .children = {
            476, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1277952,
        .children = {
            -2, 477
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            478, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 950272,
        .children = {
            479, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2162688,
        .children = {
            -2, 480
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
        .children = {
            481, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -2, 482
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2129920,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1277952,
        .children = {
            -2, 484
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 950272,
        .children = {
            485, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
        .children = {
            486, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -2, -1
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1277952,
        .children = {
            489, 492
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
        .children = {
            -2, 490
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1605632,
        .children = {
            491, -2
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
            -2, -1
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
            493, 501
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 425984,
        .children = {
            494, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1769472,
        .children = {
            495, 498
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
        .children = {
            496, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 950272,
        .children = {
            497, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 950272,
        .children = {
            499, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
        .children = {
            500, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 425984,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 491520,
        .children = {
            -1, 503
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1638400,
        .children = {
            -1, 504
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -131072,
        .children = {
            505, 536
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1179648,
        .children = {
            506, 525
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            507, 515
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            508, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1441792,
        .children = {
            509, 512
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1277952,
        .children = {
            510, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1605632,
        .children = {
            511, -2
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
            513, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1277952,
        .children = {
            514, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1605632,
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
        .distance = 196608,
        .children = {
            516, 524
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 950272,
        .children = {
            -2, 517
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1441792,
        .children = {
            518, 521
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 753664,
        .children = {
            -2, 519
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
            520, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 425984,
        .children = {
            -2, -1
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
            522, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 753664,
        .children = {
            -2, 523
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 425984,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 950272,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            526, 530
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            527, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1277952,
        .children = {
            528, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1605632,
        .children = {
            529, -2
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
            531, 533
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 753664,
        .children = {
            -2, 532
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 425984,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 917504,
        .children = {
            534, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            -2, 535
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 950272,
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
        .distance = 1179648,
        .children = {
            537, 551
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1277952,
        .children = {
            538, 541
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
        .children = {
            -2, 539
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1605632,
        .children = {
            540, -2
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
            -2, -1
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
            542, 550
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 425984,
        .children = {
            543, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1441792,
        .children = {
            544, 547
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
        .children = {
            545, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 950272,
        .children = {
            546, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 950272,
        .children = {
            548, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
        .children = {
            549, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 425984,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1605632,
        .children = {
            552, 553
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 950272,
        .children = {
            554, 556
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
        .children = {
            555, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
        .children = {
            -2, 557
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 917504,
        .children = {
            -2, 558
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            -2, 559
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 753664,
        .children = {
            -2, 560
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
            -2, 561
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 425984,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 131072,
        .children = {
            563, 600
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -1, 564
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 851968,
        .children = {
            565, 582
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1376256,
        .children = {
            566, 574
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1703936,
        .children = {
            567, 572
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2031616,
        .children = {
            568, 570
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            569, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 786432,
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
        .distance = 786432,
        .children = {
            571, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
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
        .distance = 1114112,
        .children = {
            573, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 786432,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 720896,
        .children = {
            575, 580
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1048576,
        .children = {
            576, 578
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            577, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 786432,
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
        .distance = 1114112,
        .children = {
            579, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 786432,
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
        .distance = 1114112,
        .children = {
            581, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 786432,
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
        .distance = 524288,
        .children = {
            583, 591
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1572864,
        .children = {
            584, 589
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1900544,
        .children = {
            585, 587
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 973159,
        .children = {
            -2, 586
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 786432,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 973159,
        .children = {
            -2, 588
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 786432,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 973159,
        .children = {
            -2, 590
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 786432,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 786432,
        .children = {
            592, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1900544,
        .children = {
            -2, 593
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 491520,
        .children = {
            -2, 594
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1638400,
        .children = {
            -2, 595
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            -2, 596
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -2, 597
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 917504,
        .children = {
            598, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1048576,
        .children = {
            -2, 599
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 950272,
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
        .distance = -1179648,
        .children = {
            601, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 786432,
        .children = {
            602, 610
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            603, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -524288,
        .children = {
            604, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1703936,
        .children = {
            -2, 605
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
        .children = {
            606, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 950272,
        .children = {
            607, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1376256,
        .children = {
            -2, 608
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -2, 609
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1048576,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1376256,
        .children = {
            611, 622
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1703936,
        .children = {
            612, 619
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2031616,
        .children = {
            613, 616
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            614, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -851968,
        .children = {
            615, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -973159,
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
        .distance = -1114112,
        .children = {
            617, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -851968,
        .children = {
            618, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -973159,
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
        .distance = -1114112,
        .children = {
            620, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -851968,
        .children = {
            621, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -973159,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1048576,
        .children = {
            623, 626
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            624, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -851968,
        .children = {
            625, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -973159,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 720896,
        .children = {
            627, 629
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            628, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -973159,
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
        .distance = -1114112,
        .children = {
            630, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -851968,
        .children = {
            631, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -973159,
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
        .distance = 131072,
        .children = {
            633, 784
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1245184,
        .children = {
            -1, 634
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1376256,
        .children = {
            635, 711
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1179648,
        .children = {
            636, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1703936,
        .children = {
            637, 688
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
            638, 647
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 917504,
        .children = {
            639, 645
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            640, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2031616,
        .children = {
            641, 643
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
            642, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
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
        .distance = 1179648,
        .children = {
            644, -2
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
        .distance = 196608,
        .children = {
            646, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2031616,
        .children = {
            648, 667
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            649, 662
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 917504,
        .children = {
            650, 656
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
            -2, 651
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
            -2, 652
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -1, 653
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            -2, 654
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            655, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 851968,
        .children = {
            657, 659
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            658, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            660, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            661, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 973159,
        .children = {
            -2, -1
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
            663, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1114112,
        .children = {
            664, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 524288,
        .children = {
            665, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 819200,
        .children = {
            666, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
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
            668, 670
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 917504,
        .children = {
            -2, 669
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -1, 671
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
            672, 684
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1114112,
        .children = {
            673, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 851968,
        .children = {
            674, 678
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            675, 676
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            -2, 677
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
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
        .distance = 524288,
        .children = {
            679, 683
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 819200,
        .children = {
            680, 681
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 973159,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            682, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 973159,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
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
        .distance = -1114112,
        .children = {
            685, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            686, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            687, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
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
        .distance = -851968,
        .children = {
            689, 706
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 917504,
        .children = {
            690, 699
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
            691, 694
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            692, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            693, -2
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
            -2, 695
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -1, 696
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            -2, 697
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            698, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            700, 703
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            701, 702
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            704, 705
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 973159,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            -2, -1
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
            707, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1114112,
        .children = {
            708, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 524288,
        .children = {
            709, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 819200,
        .children = {
            710, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 720896,
        .children = {
            712, 761
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1048576,
        .children = {
            713, 737
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1179648,
        .children = {
            714, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            715, 732
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 917504,
        .children = {
            716, 725
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
            717, 720
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            718, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            719, -2
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
            -2, 721
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -1, 722
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            -2, 723
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            724, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            726, 729
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            727, 728
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            730, 731
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 973159,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            -2, -1
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
            733, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1114112,
        .children = {
            734, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 524288,
        .children = {
            735, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 819200,
        .children = {
            736, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
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
        .distance = -1179648,
        .children = {
            738, -1
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
            739, 745
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 917504,
        .children = {
            740, 743
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            741, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            742, -2
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
        .distance = 196608,
        .children = {
            744, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            746, 754
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 917504,
        .children = {
            747, 750
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -196607,
        .children = {
            -2, 748
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
            -2, 749
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
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
        .distance = 851968,
        .children = {
            751, 753
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            752, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 973159,
        .children = {
            -2, -1
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
            755, 758
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1114112,
        .children = {
            756, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 819200,
        .children = {
            757, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
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
        .distance = -1114112,
        .children = {
            759, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            760, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1179648,
        .children = {
            762, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            763, 780
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 917504,
        .children = {
            764, 773
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
            765, 768
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            766, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            767, -2
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
            -2, 769
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -1, 770
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            -2, 771
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            772, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            774, 779
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            775, 778
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            776, 777
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 973159,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            -2, -1
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
            781, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1114112,
        .children = {
            782, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 819200,
        .children = {
            783, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
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
        .distance = -1245184,
        .children = {
            785, -1
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
            786, 826
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1703936,
        .children = {
            787, 803
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2031616,
        .children = {
            788, 795
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            789, 791
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            790, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -938244,
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
        .distance = 131072,
        .children = {
            792, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            793, -2
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
            794, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, -1
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
            796, 802
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            797, 799
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            798, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -938244,
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
        .distance = 196608,
        .children = {
            800, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, 801
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1048576,
        .children = {
            804, 817
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1376256,
        .children = {
            805, 811
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            806, 808
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            807, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -938244,
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
        .distance = 196608,
        .children = {
            809, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, 810
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            812, 814
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            813, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -938244,
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
        .distance = 196608,
        .children = {
            815, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, 816
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
            .y = -4096,
            .z = 0
        },
        .distance = 720896,
        .children = {
            818, 820
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            -1, 819
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            821, 823
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            822, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -938244,
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
        .distance = 196608,
        .children = {
            824, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, 825
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
        .distance = -1179648,
        .children = {
            827, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            828, 869
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -851968,
        .children = {
            829, 830
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -973159,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2031616,
        .children = {
            831, 836
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            832, 833
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -938244,
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
            -2, 834
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, 835
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 720896,
        .children = {
            837, 864
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1376256,
        .children = {
            838, 853
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            839, 848
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            840, 843
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1703936,
        .children = {
            841, 842
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -938244,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -938244,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1703936,
        .children = {
            844, 846
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
            -2, 845
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, -1
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
            -2, 847
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1703936,
        .children = {
            849, 851
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, 850
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, 852
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            854, 858
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1048576,
        .children = {
            855, 856
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -938244,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -938244,
        .children = {
            -1, 857
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
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
            -2, 859
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            860, 862
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            861, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1048576,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            863, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1048576,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            865, 866
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -938244,
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
            -2, 867
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, 868
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            870, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1048576,
        .children = {
            871, 895
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2031616,
        .children = {
            872, 878
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            873, 875
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -819200,
        .children = {
            874, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
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
        .distance = -131072,
        .children = {
            -2, 876
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
            -2, 877
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1114112,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1703936,
        .children = {
            879, 885
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -524288,
        .children = {
            880, 884
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
            881, 883
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            882, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
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
        .distance = -1114112,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1114112,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            886, 892
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1376256,
        .children = {
            887, 889
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -819200,
        .children = {
            888, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
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
        .distance = -819200,
        .children = {
            890, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -973159,
        .children = {
            891, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
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
        .distance = -196608,
        .children = {
            -2, 893
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1114112,
        .children = {
            -2, 894
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 720896,
        .children = {
            896, 900
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
            897, 899
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            898, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
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
        .distance = -1114112,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            901, 903
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -819200,
        .children = {
            902, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
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
        .distance = -131072,
        .children = {
            -2, 904
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
            -2, 905
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1114112,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -393216,
        .children = {
            907, -1
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
            908, 1035
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1114112,
        .children = {
            909, 917
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 196608,
        .children = {
            910, 913
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            911, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            -1, 912
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1146880,
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
        .distance = -360448,
        .children = {
            914, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            -1, 915
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1146880,
        .children = {
            -1, 916
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 524288,
        .children = {
            918, 966
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1245184,
        .children = {
            -1, 919
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            920, 924
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
            921, 922
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
        .distance = 458752,
        .children = {
            -1, 923
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 524288,
        .children = {
            925, 946
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 851968,
        .children = {
            926, 938
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
            927, 930
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            928, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 786432,
        .children = {
            929, -2
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
        .distance = 1114112,
        .children = {
            931, 935
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 786432,
        .children = {
            932, 933
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 934
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1246708,
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
        .distance = 786432,
        .children = {
            936, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 937
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1343887,
        .children = {
            -1, -2
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
            939, 942
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 786432,
        .children = {
            -2, 940
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            941, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 973159,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 786432,
        .children = {
            943, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 786432,
        .children = {
            944, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 945
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1343887,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            947, 950
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 917504,
        .children = {
            -2, 948
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            949, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 851968,
        .children = {
            951, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            952, 956
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
            -2, 953
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
            954, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 955
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1246708,
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
        .distance = 917504,
        .children = {
            957, -2
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
            958, 962
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
            -2, 959
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 960
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            961, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -294912,
        .children = {
            -2, -1
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
            -2, 963
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 964
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            965, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -294912,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -851968,
        .children = {
            967, 998
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            968, 984
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 786432,
        .children = {
            969, 983
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -524288,
        .children = {
            970, -2
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
            971, -2
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
            -2, 972
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -98304,
        .children = {
            973, 979
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            -2, 974
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 98304,
        .children = {
            975, 978
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 851968,
        .children = {
            -2, 976
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            -2, 977
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 819200,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 851968,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            980, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 851968,
        .children = {
            -2, 981
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
        .children = {
            982, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 819200,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -973159,
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
        .distance = 524288,
        .children = {
            985, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -524288,
        .children = {
            986, 995
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 786432,
        .children = {
            987, -2
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
            988, 993
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 989
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -131072,
        .children = {
            990, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            991, -2
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
            992, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1048576,
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
        .distance = 1048576,
        .children = {
            994, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 996
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 786432,
        .children = {
            997, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1343887,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            999, 1029
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 524288,
        .children = {
            1000, 1011
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
            1001, 1004
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, 1002
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 786432,
        .children = {
            1003, -2
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
        .distance = -1114112,
        .children = {
            1005, 1007
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 1006
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1343887,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 786432,
        .children = {
            1008, 1009
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 1010
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1246708,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            1012, 1015
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            1013, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            1014, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -938244,
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
        .distance = 458752,
        .children = {
            1016, 1019
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
            -2, 1017
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 1018
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1246708,
        .children = {
            -2, -1
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
            -2, 1020
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
            1021, 1025
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 1022
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, 1023
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 196608,
        .children = {
            -2, 1024
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -294912,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            -2, 1026
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 1027
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, 1028
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -294912,
        .children = {
            -2, -1
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
            1030, 1032
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1245184,
        .children = {
            1031, -1
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1245184,
        .children = {
            1033, -1
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
            -1, 1034
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -131072,
        .children = {
            1036, 1103
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            1037, 1040
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1245184,
        .children = {
            -1, 1038
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
            1039, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1179648,
        .children = {
            1041, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1114112,
        .children = {
            1042, 1098
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 851968,
        .children = {
            1043, 1069
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -196607,
        .children = {
            1044, 1050
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            1045, 1046
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 917504,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 917504,
        .children = {
            1047, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 1048
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            1049, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -294912,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            1051, 1058
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            1052, 1055
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            1053, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 917504,
        .children = {
            -2, 1054
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 938244,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -294912,
        .children = {
            1056, 1057
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1246708,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1246708,
        .children = {
            -1, -2
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
            1059, 1063
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            -2, 1060
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            1061, -2
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
            1062, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
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
        .distance = -786432,
        .children = {
            1064, 1067
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            1065, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 1066
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1246708,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 1068
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1343887,
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
        .distance = -524288,
        .children = {
            1070, 1071
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
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
        .distance = 131072,
        .children = {
            1072, 1095
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 524288,
        .children = {
            1073, 1084
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
            1074, 1080
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1048576,
        .children = {
            1075, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            1076, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 819200,
        .children = {
            1077, 1078
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 973159,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            1079, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 973159,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            -2, 1081
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 786432,
        .children = {
            1082, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 1083
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1343887,
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
        .distance = -786432,
        .children = {
            1085, 1086
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
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
            1087, 1090
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
            -2, 1088
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 1089
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1048576,
        .children = {
            -2, -1
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
            1091, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1048576,
        .children = {
            1092, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            -2, 1093
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            1094, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            -1, -2
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
            1096, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            1097, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
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
            -1, 1099
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
            -2, 1100
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1101, 1102
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1114112,
        .children = {
            1104, 1167
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -851968,
        .children = {
            1105, 1133
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            1106, 1115
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -524288,
        .children = {
            1107, 1111
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            -1, 1108
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
            1109, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
        .children = {
            1110, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
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
        .distance = -819200,
        .children = {
            1112, 1114
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            1113, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -973159,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -973159,
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
        .distance = -524288,
        .children = {
            1116, 1122
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            -2, 1117
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
            -2, 1118
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
        .children = {
            -2, 1119
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 1120
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
            -2, 1121
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1048576,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            -2, 1123
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
            -2, 1124
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            -2, 1125
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -351703,
        .children = {
            1126, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -973159,
        .children = {
            -2, 1127
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -819200,
        .children = {
            1128, 1131
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1048576,
        .children = {
            -2, 1129
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 1130
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1343887,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 1132
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1343887,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1245184,
        .children = {
            1134, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1179648,
        .children = {
            1135, 1164
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -524288,
        .children = {
            1136, 1153
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -196607,
        .children = {
            1137, 1142
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            1138, 1140
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -917504,
        .children = {
            1139, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
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
        .distance = -1114112,
        .children = {
            -2, 1141
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -294912,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            1143, 1151
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1246708,
        .children = {
            1144, -2
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
            1145, -2
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
            1146, 1149
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            1147, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            1148, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -938244,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            1150, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -938244,
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
        .distance = -1114112,
        .children = {
            -2, 1152
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1246708,
        .children = {
            -2, -1
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
            1154, 1158
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            -2, 1155
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            1156, -2
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
            1157, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -786432,
        .children = {
            1159, 1162
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            -2, 1160
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 1161
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1246708,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 1163
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1343887,
        .children = {
            -2, -1
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
            1165, -1
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
            -2, 1166
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
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
            1168, 1170
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
            1169, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1179648,
        .children = {
            -2, -1
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
            1171, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1179648,
        .children = {
            1172, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
};
BSPTree3 bsp_player = {.nodes=bspNodes_player, .numNodes = 1173};

int numTris = 968;
Tri3_texturedFlat tris[] = {
    {
        {327680, 0, 0},
        {0, 0, -327680},
        {0, 0, 0},
        {224, 255},
        {255, 224},
        {255, 255},
        12
    },
    {
        {327680, 0, 0},
        {327680, 0, -327680},
        {0, 0, -327680},
        {224, 255},
        {224, 224},
        {255, 224},
        12
    },
    {
        {327680, 0, -983040},
        {0, -327680, -983040},
        {0, 0, -983040},
        {31, 255},
        {0, 224},
        {0, 255},
        16
    },
    {
        {327680, 0, -983040},
        {327680, -327680, -983040},
        {0, -327680, -983040},
        {31, 255},
        {31, 224},
        {0, 224},
        16
    },
    {
        {327680, 0, -917504},
        {327680, -327680, -983040},
        {327680, 0, -983040},
        {31, 255},
        {16, 176},
        {16, 255},
        11
    },
    {
        {327680, 0, -917504},
        {327680, -327680, -917504},
        {327680, -327680, -983040},
        {31, 255},
        {31, 176},
        {16, 176},
        11
    },
    {
        {655360, 0, -917504},
        {327680, -327680, -917504},
        {327680, 0, -917504},
        {63, 255},
        {32, 224},
        {32, 255},
        15
    },
    {
        {655360, 0, -917504},
        {655360, -327680, -917504},
        {327680, -327680, -917504},
        {63, 255},
        {63, 224},
        {32, 224},
        15
    },
    {
        {655360, -327680, -917504},
        {688128, 0, -983040},
        {688128, -327680, -983040},
        {15, 176},
        {0, 255},
        {0, 176},
        11
    },
    {
        {655360, -327680, -917504},
        {655360, 0, -917504},
        {688128, 0, -983040},
        {15, 176},
        {15, 255},
        {0, 255},
        11
    },
    {
        {-655360, 0, -917504},
        {-688128, -327680, -983040},
        {-688128, 0, -983040},
        {15, 255},
        {0, 176},
        {0, 255},
        11
    },
    {
        {-655360, 0, -917504},
        {-655360, -327680, -917504},
        {-688128, -327680, -983040},
        {15, 255},
        {15, 176},
        {0, 176},
        11
    },
    {
        {-327680, 0, -917504},
        {-655360, -327680, -917504},
        {-655360, 0, -917504},
        {223, 255},
        {192, 224},
        {192, 255},
        15
    },
    {
        {-327680, 0, -917504},
        {-327680, -327680, -917504},
        {-655360, -327680, -917504},
        {223, 255},
        {223, 224},
        {192, 224},
        15
    },
    {
        {-327680, -327680, -917504},
        {-327680, 0, -983040},
        {-327680, -327680, -983040},
        {15, 176},
        {0, 255},
        {0, 176},
        11
    },
    {
        {-327680, -327680, -917504},
        {-327680, 0, -917504},
        {-327680, 0, -983040},
        {15, 176},
        {15, 255},
        {0, 255},
        11
    },
    {
        {-655360, 0, -983040},
        {-983040, -327680, -655360},
        {-983040, 0, -655360},
        {0, 162},
        {31, 193},
        {0, 193},
        16
    },
    {
        {-655360, 0, -983040},
        {-655360, -327680, -983040},
        {-983040, -327680, -655360},
        {0, 162},
        {31, 162},
        {31, 193},
        16
    },
    {
        {-1048576, -327680, 0},
        {-1048576, 0, -327680},
        {-1048576, -327680, -327680},
        {255, 224},
        {224, 255},
        {224, 224},
        16
    },
    {
        {-1048576, -327680, 0},
        {-1048576, 0, 0},
        {-1048576, 0, -327680},
        {255, 224},
        {255, 255},
        {224, 255},
        16
    },
    {
        {1048576, 0, -327680},
        {983040, -327680, -655360},
        {983040, 0, -655360},
        {32, 255},
        {63, 224},
        {63, 255},
        14
    },
    {
        {1048576, 0, -327680},
        {1048576, -327680, -327680},
        {983040, -327680, -655360},
        {32, 255},
        {32, 224},
        {63, 224},
        14
    },
    {
        {327680, -327680, -917504},
        {327680, -655360, -983040},
        {327680, -327680, -983040},
        {15, 175},
        {0, 96},
        {0, 175},
        11
    },
    {
        {327680, -327680, -917504},
        {327680, -655360, -917504},
        {327680, -655360, -983040},
        {15, 175},
        {15, 96},
        {0, 96},
        11
    },
    {
        {655360, -327680, -917504},
        {327680, -655360, -917504},
        {327680, -327680, -917504},
        {63, 223},
        {32, 192},
        {32, 223},
        6
    },
    {
        {655360, -327680, -917504},
        {655360, -655360, -917504},
        {327680, -655360, -917504},
        {63, 223},
        {63, 192},
        {32, 192},
        6
    },
    {
        {655360, -655360, -917504},
        {688128, -327680, -983040},
        {688128, -655360, -983040},
        {15, 96},
        {0, 175},
        {0, 96},
        11
    },
    {
        {655360, -655360, -917504},
        {655360, -327680, -917504},
        {688128, -327680, -983040},
        {15, 96},
        {15, 175},
        {0, 175},
        11
    },
    {
        {327680, -655360, -917504},
        {327680, -983040, -983040},
        {327680, -655360, -983040},
        {15, 95},
        {0, 16},
        {0, 95},
        11
    },
    {
        {327680, -655360, -917504},
        {327680, -983040, -917504},
        {327680, -983040, -983040},
        {15, 95},
        {15, 16},
        {0, 16},
        11
    },
    {
        {655360, -655360, -917504},
        {327680, -983040, -917504},
        {327680, -655360, -917504},
        {63, 191},
        {32, 160},
        {32, 191},
        6
    },
    {
        {655360, -655360, -917504},
        {655360, -983040, -917504},
        {327680, -983040, -917504},
        {63, 191},
        {63, 160},
        {32, 160},
        6
    },
    {
        {655360, -983040, -917504},
        {688128, -655360, -983040},
        {688128, -983040, -983040},
        {15, 16},
        {0, 95},
        {0, 16},
        11
    },
    {
        {655360, -983040, -917504},
        {655360, -655360, -917504},
        {688128, -655360, -983040},
        {15, 16},
        {15, 95},
        {0, 95},
        11
    },
    {
        {327680, -983040, -917504},
        {327680, -1310720, -983040},
        {327680, -983040, -983040},
        {15, 15},
        {0, 192},
        {0, 15},
        11
    },
    {
        {327680, -983040, -917504},
        {327680, -1310720, -917504},
        {327680, -1310720, -983040},
        {15, 15},
        {15, 192},
        {0, 192},
        11
    },
    {
        {655360, -983040, -917504},
        {327680, -1310720, -917504},
        {327680, -983040, -917504},
        {63, 159},
        {32, 128},
        {32, 159},
        9
    },
    {
        {655360, -983040, -917504},
        {655360, -1310720, -917504},
        {327680, -1310720, -917504},
        {63, 159},
        {63, 128},
        {32, 128},
        9
    },
    {
        {655360, -1310720, -917504},
        {688128, -983040, -983040},
        {688128, -1310720, -983040},
        {15, 192},
        {0, 15},
        {0, 192},
        11
    },
    {
        {655360, -1310720, -917504},
        {655360, -983040, -917504},
        {688128, -983040, -983040},
        {15, 192},
        {15, 15},
        {0, 15},
        11
    },
    {
        {-655360, -327680, -917504},
        {-688128, -655360, -983040},
        {-688128, -327680, -983040},
        {15, 175},
        {0, 96},
        {0, 175},
        11
    },
    {
        {-655360, -327680, -917504},
        {-655360, -655360, -917504},
        {-688128, -655360, -983040},
        {15, 175},
        {15, 96},
        {0, 96},
        11
    },
    {
        {-327680, -327680, -917504},
        {-655360, -655360, -917504},
        {-655360, -327680, -917504},
        {223, 223},
        {192, 192},
        {192, 223},
        6
    },
    {
        {-327680, -327680, -917504},
        {-327680, -655360, -917504},
        {-655360, -655360, -917504},
        {223, 223},
        {223, 192},
        {192, 192},
        6
    },
    {
        {-327680, -655360, -917504},
        {-327680, -327680, -983040},
        {-327680, -655360, -983040},
        {15, 96},
        {0, 175},
        {0, 96},
        11
    },
    {
        {-327680, -655360, -917504},
        {-327680, -327680, -917504},
        {-327680, -327680, -983040},
        {15, 96},
        {15, 175},
        {0, 175},
        11
    },
    {
        {-655360, -655360, -917504},
        {-688128, -983040, -983040},
        {-688128, -655360, -983040},
        {15, 95},
        {0, 16},
        {0, 95},
        11
    },
    {
        {-655360, -655360, -917504},
        {-655360, -983040, -917504},
        {-688128, -983040, -983040},
        {15, 95},
        {15, 16},
        {0, 16},
        11
    },
    {
        {-327680, -655360, -917504},
        {-655360, -983040, -917504},
        {-655360, -655360, -917504},
        {223, 191},
        {192, 160},
        {192, 191},
        6
    },
    {
        {-327680, -655360, -917504},
        {-327680, -983040, -917504},
        {-655360, -983040, -917504},
        {223, 191},
        {223, 160},
        {192, 160},
        6
    },
    {
        {-327680, -983040, -917504},
        {-327680, -655360, -983040},
        {-327680, -983040, -983040},
        {15, 16},
        {0, 95},
        {0, 16},
        11
    },
    {
        {-327680, -983040, -917504},
        {-327680, -655360, -917504},
        {-327680, -655360, -983040},
        {15, 16},
        {15, 95},
        {0, 95},
        11
    },
    {
        {-655360, -983040, -917504},
        {-688128, -1310720, -983040},
        {-688128, -983040, -983040},
        {15, 15},
        {0, 192},
        {0, 15},
        11
    },
    {
        {-655360, -983040, -917504},
        {-655360, -1310720, -917504},
        {-688128, -1310720, -983040},
        {15, 15},
        {15, 192},
        {0, 192},
        11
    },
    {
        {-327680, -983040, -917504},
        {-655360, -1310720, -917504},
        {-655360, -983040, -917504},
        {223, 159},
        {192, 128},
        {192, 159},
        9
    },
    {
        {-327680, -983040, -917504},
        {-327680, -1310720, -917504},
        {-655360, -1310720, -917504},
        {223, 159},
        {223, 128},
        {192, 128},
        9
    },
    {
        {-327680, -1310720, -917504},
        {-327680, -983040, -983040},
        {-327680, -1310720, -983040},
        {15, 192},
        {0, 15},
        {0, 192},
        11
    },
    {
        {-327680, -1310720, -917504},
        {-327680, -983040, -917504},
        {-327680, -983040, -983040},
        {15, 192},
        {15, 15},
        {0, 15},
        11
    },
    {
        {0, 0, 0},
        {-327680, 0, -327680},
        {-327680, 0, 0},
        {255, 255},
        {224, 224},
        {255, 224},
        12
    },
    {
        {0, 0, 0},
        {0, 0, -327680},
        {-327680, 0, -327680},
        {255, 255},
        {224, 255},
        {224, 224},
        12
    },
    {
        {327680, 0, 327680},
        {0, 0, 0},
        {0, 0, 327680},
        {224, 224},
        {255, 255},
        {224, 255},
        12
    },
    {
        {327680, 0, 327680},
        {327680, 0, 0},
        {0, 0, 0},
        {224, 224},
        {255, 224},
        {255, 255},
        12
    },
    {
        {0, 0, 327680},
        {-327680, 0, 0},
        {-327680, 0, 327680},
        {255, 224},
        {224, 255},
        {224, 224},
        12
    },
    {
        {0, 0, 327680},
        {0, 0, 0},
        {-327680, 0, 0},
        {255, 224},
        {255, 255},
        {224, 255},
        12
    },
    {
        {327680, 0, 655360},
        {0, 0, 327680},
        {0, 0, 655360},
        {31, 192},
        {0, 223},
        {0, 192},
        1
    },
    {
        {327680, 0, 655360},
        {327680, 0, 327680},
        {0, 0, 327680},
        {31, 192},
        {31, 223},
        {0, 223},
        1
    },
    {
        {0, 0, 655360},
        {-327680, 0, 327680},
        {-327680, 0, 655360},
        {255, 192},
        {224, 223},
        {224, 192},
        1
    },
    {
        {0, 0, 655360},
        {0, 0, 327680},
        {-327680, 0, 327680},
        {255, 192},
        {255, 223},
        {224, 223},
        1
    },
    {
        {0, 0, 983040},
        {-327680, 0, 655360},
        {-327680, 0, 983040},
        {255, 160},
        {224, 191},
        {224, 160},
        1
    },
    {
        {0, 0, 983040},
        {0, 0, 655360},
        {-327680, 0, 655360},
        {255, 160},
        {255, 191},
        {224, 191},
        1
    },
    {
        {327680, 0, 983040},
        {0, 0, 655360},
        {0, 0, 983040},
        {31, 160},
        {0, 191},
        {0, 160},
        1
    },
    {
        {327680, 0, 983040},
        {327680, 0, 655360},
        {0, 0, 655360},
        {31, 160},
        {31, 191},
        {0, 191},
        1
    },
    {
        {-655360, 0, 0},
        {-983040, 0, -327680},
        {-983040, 0, 0},
        {255, 191},
        {224, 160},
        {255, 160},
        1
    },
    {
        {-655360, 0, 0},
        {-655360, 0, -327680},
        {-983040, 0, -327680},
        {255, 191},
        {224, 191},
        {224, 160},
        1
    },
    {
        {-655360, 0, 327680},
        {-983040, 0, 0},
        {-983040, 0, 327680},
        {31, 191},
        {0, 160},
        {31, 160},
        1
    },
    {
        {-655360, 0, 327680},
        {-655360, 0, 0},
        {-983040, 0, 0},
        {31, 191},
        {0, 191},
        {0, 160},
        1
    },
    {
        {-327680, 0, 327680},
        {-655360, 0, 0},
        {-655360, 0, 327680},
        {31, 223},
        {0, 192},
        {31, 192},
        1
    },
    {
        {-327680, 0, 327680},
        {-327680, 0, 0},
        {-655360, 0, 0},
        {31, 223},
        {0, 223},
        {0, 192},
        1
    },
    {
        {-327680, 0, 0},
        {-655360, 0, -327680},
        {-655360, 0, 0},
        {255, 223},
        {224, 192},
        {255, 192},
        1
    },
    {
        {-327680, 0, 0},
        {-327680, 0, -327680},
        {-655360, 0, -327680},
        {255, 223},
        {224, 223},
        {224, 192},
        1
    },
    {
        {655360, 0, 0},
        {327680, 0, -327680},
        {327680, 0, 0},
        {255, 63},
        {224, 32},
        {255, 32},
        1
    },
    {
        {655360, 0, 0},
        {655360, 0, -327680},
        {327680, 0, -327680},
        {255, 63},
        {224, 63},
        {224, 32},
        1
    },
    {
        {655360, 0, 327680},
        {327680, 0, 0},
        {327680, 0, 327680},
        {31, 63},
        {0, 32},
        {31, 32},
        1
    },
    {
        {655360, 0, 327680},
        {655360, 0, 0},
        {327680, 0, 0},
        {31, 63},
        {0, 63},
        {0, 32},
        1
    },
    {
        {983040, 0, 327680},
        {655360, 0, 0},
        {655360, 0, 327680},
        {31, 95},
        {0, 64},
        {31, 64},
        1
    },
    {
        {983040, 0, 327680},
        {983040, 0, 0},
        {655360, 0, 0},
        {31, 95},
        {0, 95},
        {0, 64},
        1
    },
    {
        {983040, 0, 0},
        {655360, 0, -327680},
        {655360, 0, 0},
        {255, 95},
        {224, 64},
        {255, 64},
        1
    },
    {
        {983040, 0, 0},
        {983040, 0, -327680},
        {655360, 0, -327680},
        {255, 95},
        {224, 95},
        {224, 64},
        1
    },
    {
        {0, 0, -655360},
        {-327680, 0, -983040},
        {-327680, 0, -655360},
        {255, 64},
        {224, 95},
        {224, 64},
        1
    },
    {
        {0, 0, -655360},
        {0, 0, -983040},
        {-327680, 0, -983040},
        {255, 64},
        {255, 95},
        {224, 95},
        1
    },
    {
        {0, 0, -327680},
        {-327680, 0, -655360},
        {-327680, 0, -327680},
        {255, 32},
        {224, 63},
        {224, 32},
        1
    },
    {
        {0, 0, -327680},
        {0, 0, -655360},
        {-327680, 0, -655360},
        {255, 32},
        {255, 63},
        {224, 63},
        1
    },
    {
        {327680, 0, -327680},
        {0, 0, -655360},
        {0, 0, -327680},
        {31, 32},
        {0, 63},
        {0, 32},
        1
    },
    {
        {327680, 0, -327680},
        {327680, 0, -655360},
        {0, 0, -655360},
        {31, 32},
        {31, 63},
        {0, 63},
        1
    },
    {
        {327680, 0, -655360},
        {0, 0, -983040},
        {0, 0, -655360},
        {31, 64},
        {0, 95},
        {0, 64},
        1
    },
    {
        {327680, 0, -655360},
        {327680, 0, -983040},
        {0, 0, -983040},
        {31, 64},
        {31, 95},
        {0, 95},
        1
    },
    {
        {-983040, 0, 327680},
        {-1048576, 0, 0},
        {-1048576, 0, 327680},
        {31, 159},
        {0, 153},
        {31, 153},
        1
    },
    {
        {-983040, 0, 327680},
        {-983040, 0, 0},
        {-1048576, 0, 0},
        {31, 159},
        {0, 159},
        {0, 153},
        1
    },
    {
        {-983040, 0, 0},
        {-1048576, 0, -327680},
        {-1048576, 0, 0},
        {255, 159},
        {224, 153},
        {255, 153},
        1
    },
    {
        {-983040, 0, 0},
        {-983040, 0, -327680},
        {-1048576, 0, -327680},
        {255, 159},
        {224, 159},
        {224, 153},
        1
    },
    {
        {1048576, 0, 0},
        {983040, 0, -327680},
        {983040, 0, 0},
        {255, 101},
        {224, 96},
        {255, 96},
        1
    },
    {
        {1048576, 0, 0},
        {1048576, 0, -327680},
        {983040, 0, -327680},
        {255, 101},
        {224, 101},
        {224, 96},
        1
    },
    {
        {1048576, 0, 327680},
        {983040, 0, 0},
        {983040, 0, 327680},
        {31, 101},
        {0, 96},
        {31, 96},
        1
    },
    {
        {1048576, 0, 327680},
        {1048576, 0, 0},
        {983040, 0, 0},
        {31, 101},
        {0, 101},
        {0, 96},
        1
    },
    {
        {655360, 0, 917504},
        {327680, 0, 655360},
        {327680, 0, 917504},
        {89, 63},
        {64, 32},
        {89, 32},
        10
    },
    {
        {655360, 0, 917504},
        {655360, 0, 655360},
        {327680, 0, 655360},
        {89, 63},
        {64, 63},
        {64, 32},
        10
    },
    {
        {655360, 0, 655360},
        {327680, 0, 327680},
        {327680, 0, 655360},
        {63, 63},
        {32, 32},
        {63, 32},
        10
    },
    {
        {655360, 0, 655360},
        {655360, 0, 327680},
        {327680, 0, 327680},
        {63, 63},
        {32, 63},
        {32, 32},
        10
    },
    {
        {983040, 0, 655360},
        {655360, 0, 327680},
        {655360, 0, 655360},
        {63, 95},
        {32, 64},
        {63, 64},
        10
    },
    {
        {983040, 0, 655360},
        {983040, 0, 327680},
        {655360, 0, 327680},
        {63, 95},
        {32, 95},
        {32, 64},
        10
    },
    {
        {983040, 0, 655360},
        {1048576, 0, 327680},
        {983040, 0, 327680},
        {63, 96},
        {32, 101},
        {32, 96},
        10
    },
    {
        {655360, 0, 983040},
        {983040, 0, 655360},
        {655360, 0, 655360},
        {64, 160},
        {95, 191},
        {64, 191},
        10
    },
    {
        {-327680, 0, 655360},
        {-655360, 0, 327680},
        {-655360, 0, 655360},
        {63, 223},
        {32, 192},
        {63, 192},
        10
    },
    {
        {-327680, 0, 655360},
        {-327680, 0, 327680},
        {-655360, 0, 327680},
        {63, 223},
        {32, 223},
        {32, 192},
        10
    },
    {
        {-655360, 0, 655360},
        {-983040, 0, 327680},
        {-983040, 0, 655360},
        {63, 191},
        {32, 160},
        {63, 160},
        10
    },
    {
        {-655360, 0, 655360},
        {-655360, 0, 327680},
        {-983040, 0, 327680},
        {63, 191},
        {32, 191},
        {32, 160},
        10
    },
    {
        {-983040, 0, 655360},
        {-983040, 0, 327680},
        {-1048576, 0, 327680},
        {63, 159},
        {32, 159},
        {32, 153},
        10
    },
    {
        {-655360, 0, 983040},
        {-655360, 0, 655360},
        {-983040, 0, 655360},
        {191, 160},
        {191, 191},
        {160, 191},
        10
    },
    {
        {-327680, 0, 917504},
        {-655360, 0, 655360},
        {-655360, 0, 917504},
        {89, 223},
        {64, 192},
        {89, 192},
        10
    },
    {
        {-327680, 0, 917504},
        {-327680, 0, 655360},
        {-655360, 0, 655360},
        {89, 223},
        {64, 223},
        {64, 192},
        10
    },
    {
        {-327680, 0, -327680},
        {-655360, 0, -655360},
        {-655360, 0, -327680},
        {223, 223},
        {192, 192},
        {223, 192},
        10
    },
    {
        {-327680, 0, -327680},
        {-327680, 0, -655360},
        {-655360, 0, -655360},
        {223, 223},
        {192, 223},
        {192, 192},
        10
    },
    {
        {-655360, 0, -327680},
        {-983040, 0, -655360},
        {-983040, 0, -327680},
        {223, 191},
        {192, 160},
        {223, 160},
        10
    },
    {
        {-655360, 0, -327680},
        {-655360, 0, -655360},
        {-983040, 0, -655360},
        {223, 191},
        {192, 191},
        {192, 160},
        10
    },
    {
        {-983040, 0, -327680},
        {-983040, 0, -655360},
        {-1048576, 0, -327680},
        {223, 159},
        {192, 159},
        {223, 153},
        10
    },
    {
        {-655360, 0, -655360},
        {-655360, 0, -983040},
        {-983040, 0, -655360},
        {191, 64},
        {191, 95},
        {160, 64},
        10
    },
    {
        {-327680, 0, -655360},
        {-655360, 0, -917504},
        {-655360, 0, -655360},
        {191, 223},
        {166, 192},
        {191, 192},
        10
    },
    {
        {-327680, 0, -655360},
        {-327680, 0, -917504},
        {-655360, 0, -917504},
        {191, 223},
        {166, 223},
        {166, 192},
        10
    },
    {
        {655360, 0, -327680},
        {327680, 0, -655360},
        {327680, 0, -327680},
        {223, 63},
        {192, 32},
        {223, 32},
        10
    },
    {
        {655360, 0, -327680},
        {655360, 0, -655360},
        {327680, 0, -655360},
        {223, 63},
        {192, 63},
        {192, 32},
        10
    },
    {
        {983040, 0, -327680},
        {655360, 0, -655360},
        {655360, 0, -327680},
        {223, 95},
        {192, 64},
        {223, 64},
        10
    },
    {
        {983040, 0, -327680},
        {983040, 0, -655360},
        {655360, 0, -655360},
        {223, 95},
        {192, 95},
        {192, 64},
        10
    },
    {
        {1048576, 0, -327680},
        {983040, 0, -655360},
        {983040, 0, -327680},
        {223, 101},
        {192, 96},
        {223, 96},
        10
    },
    {
        {983040, 0, -655360},
        {655360, 0, -983040},
        {655360, 0, -655360},
        {95, 64},
        {64, 95},
        {64, 64},
        10
    },
    {
        {655360, 0, -655360},
        {327680, 0, -917504},
        {327680, 0, -655360},
        {191, 63},
        {166, 32},
        {191, 32},
        10
    },
    {
        {655360, 0, -655360},
        {655360, 0, -917504},
        {327680, 0, -917504},
        {191, 63},
        {166, 63},
        {166, 32},
        10
    },
    {
        {-655360, -327680, -983040},
        {-983040, -655360, -655360},
        {-983040, -327680, -655360},
        {32, 162},
        {63, 193},
        {32, 193},
        16
    },
    {
        {-655360, -327680, -983040},
        {-655360, -655360, -983040},
        {-983040, -655360, -655360},
        {32, 162},
        {63, 162},
        {63, 193},
        16
    },
    {
        {-655360, -655360, -983040},
        {-983040, -983040, -655360},
        {-983040, -655360, -655360},
        {64, 162},
        {95, 193},
        {64, 193},
        16
    },
    {
        {-655360, -655360, -983040},
        {-655360, -983040, -983040},
        {-983040, -983040, -655360},
        {64, 162},
        {95, 162},
        {95, 193},
        16
    },
    {
        {-655360, -983040, -983040},
        {-983040, -1310720, -655360},
        {-983040, -983040, -655360},
        {96, 162},
        {127, 193},
        {96, 193},
        16
    },
    {
        {-655360, -983040, -983040},
        {-655360, -1310720, -983040},
        {-983040, -1310720, -655360},
        {96, 162},
        {127, 162},
        {127, 193},
        16
    },
    {
        {-655360, -1966080, -983040},
        {-983040, -2293760, -655360},
        {-983040, -1966080, -655360},
        {192, 162},
        {223, 193},
        {192, 193},
        16
    },
    {
        {-655360, -1966080, -983040},
        {-655360, -2293760, -983040},
        {-983040, -2293760, -655360},
        {192, 162},
        {223, 162},
        {223, 193},
        16
    },
    {
        {-655360, -2293760, -983040},
        {-983040, -2621440, -655360},
        {-983040, -2293760, -655360},
        {224, 162},
        {255, 193},
        {224, 193},
        16
    },
    {
        {-655360, -2293760, -983040},
        {-655360, -2621440, -983040},
        {-983040, -2621440, -655360},
        {224, 162},
        {255, 162},
        {255, 193},
        16
    },
    {
        {-655360, -1638400, -983040},
        {-983040, -1966080, -655360},
        {-983040, -1638400, -655360},
        {160, 162},
        {191, 193},
        {160, 193},
        16
    },
    {
        {-655360, -1638400, -983040},
        {-655360, -1966080, -983040},
        {-983040, -1966080, -655360},
        {160, 162},
        {191, 162},
        {191, 193},
        16
    },
    {
        {-655360, -1310720, -983040},
        {-983040, -1638400, -655360},
        {-983040, -1310720, -655360},
        {128, 162},
        {159, 193},
        {128, 193},
        16
    },
    {
        {-655360, -1310720, -983040},
        {-655360, -1638400, -983040},
        {-983040, -1638400, -655360},
        {128, 162},
        {159, 162},
        {159, 193},
        16
    },
    {
        {-655360, -3276800, -983040},
        {-983040, -3604480, -655360},
        {-983040, -3276800, -655360},
        {64, 162},
        {95, 193},
        {64, 193},
        16
    },
    {
        {-655360, -3276800, -983040},
        {-655360, -3604480, -983040},
        {-983040, -3604480, -655360},
        {64, 162},
        {95, 162},
        {95, 193},
        16
    },
    {
        {-655360, -3604480, -983040},
        {-983040, -3932160, -655360},
        {-983040, -3604480, -655360},
        {96, 162},
        {127, 193},
        {96, 193},
        16
    },
    {
        {-655360, -3604480, -983040},
        {-655360, -3932160, -983040},
        {-983040, -3932160, -655360},
        {96, 162},
        {127, 162},
        {127, 193},
        16
    },
    {
        {-655360, -2949120, -983040},
        {-983040, -3276800, -655360},
        {-983040, -2949120, -655360},
        {32, 162},
        {63, 193},
        {32, 193},
        16
    },
    {
        {-655360, -2949120, -983040},
        {-655360, -3276800, -983040},
        {-983040, -3276800, -655360},
        {32, 162},
        {63, 162},
        {63, 193},
        16
    },
    {
        {-655360, -2621440, -983040},
        {-983040, -2949120, -655360},
        {-983040, -2621440, -655360},
        {0, 162},
        {31, 193},
        {0, 193},
        16
    },
    {
        {-655360, -2621440, -983040},
        {-655360, -2949120, -983040},
        {-983040, -2949120, -655360},
        {0, 162},
        {31, 162},
        {31, 193},
        16
    },
    {
        {-655360, -4259840, -983040},
        {-983040, -4587520, -655360},
        {-983040, -4259840, -655360},
        {160, 162},
        {191, 193},
        {160, 193},
        16
    },
    {
        {-655360, -4259840, -983040},
        {-655360, -4587520, -983040},
        {-983040, -4587520, -655360},
        {160, 162},
        {191, 162},
        {191, 193},
        16
    },
    {
        {-655360, -3932160, -983040},
        {-983040, -4259840, -655360},
        {-983040, -3932160, -655360},
        {128, 162},
        {159, 193},
        {128, 193},
        16
    },
    {
        {-655360, -3932160, -983040},
        {-655360, -4259840, -983040},
        {-983040, -4259840, -655360},
        {128, 162},
        {159, 162},
        {159, 193},
        16
    },
    {
        {-983040, -327680, 655360},
        {-655360, 0, 983040},
        {-983040, 0, 655360},
        {31, 66},
        {0, 97},
        {0, 66},
        16
    },
    {
        {-983040, -327680, 655360},
        {-655360, -327680, 983040},
        {-655360, 0, 983040},
        {31, 66},
        {31, 97},
        {0, 97},
        16
    },
    {
        {-983040, -655360, 655360},
        {-655360, -327680, 983040},
        {-983040, -327680, 655360},
        {63, 66},
        {32, 97},
        {32, 66},
        16
    },
    {
        {-983040, -655360, 655360},
        {-655360, -655360, 983040},
        {-655360, -327680, 983040},
        {63, 66},
        {63, 97},
        {32, 97},
        16
    },
    {
        {-983040, -983040, 655360},
        {-655360, -655360, 983040},
        {-983040, -655360, 655360},
        {95, 66},
        {64, 97},
        {64, 66},
        16
    },
    {
        {-983040, -983040, 655360},
        {-655360, -983040, 983040},
        {-655360, -655360, 983040},
        {95, 66},
        {95, 97},
        {64, 97},
        16
    },
    {
        {-983040, -1310720, 655360},
        {-655360, -983040, 983040},
        {-983040, -983040, 655360},
        {127, 66},
        {96, 97},
        {96, 66},
        16
    },
    {
        {-983040, -1310720, 655360},
        {-655360, -1310720, 983040},
        {-655360, -983040, 983040},
        {127, 66},
        {127, 97},
        {96, 97},
        16
    },
    {
        {-983040, -1638400, 655360},
        {-655360, -1310720, 983040},
        {-983040, -1310720, 655360},
        {159, 66},
        {128, 97},
        {128, 66},
        16
    },
    {
        {-983040, -1638400, 655360},
        {-655360, -1638400, 983040},
        {-655360, -1310720, 983040},
        {159, 66},
        {159, 97},
        {128, 97},
        16
    },
    {
        {-983040, -1966080, 655360},
        {-655360, -1638400, 983040},
        {-983040, -1638400, 655360},
        {191, 66},
        {160, 97},
        {160, 66},
        16
    },
    {
        {-983040, -1966080, 655360},
        {-655360, -1966080, 983040},
        {-655360, -1638400, 983040},
        {191, 66},
        {191, 97},
        {160, 97},
        16
    },
    {
        {-983040, -2293760, 655360},
        {-655360, -1966080, 983040},
        {-983040, -1966080, 655360},
        {223, 66},
        {192, 97},
        {192, 66},
        16
    },
    {
        {-983040, -2293760, 655360},
        {-655360, -2293760, 983040},
        {-655360, -1966080, 983040},
        {223, 66},
        {223, 97},
        {192, 97},
        16
    },
    {
        {-983040, -2621440, 655360},
        {-655360, -2293760, 983040},
        {-983040, -2293760, 655360},
        {255, 66},
        {224, 97},
        {224, 66},
        16
    },
    {
        {-983040, -2621440, 655360},
        {-655360, -2621440, 983040},
        {-655360, -2293760, 983040},
        {255, 66},
        {255, 97},
        {224, 97},
        16
    },
    {
        {-983040, -2949120, 655360},
        {-655360, -2621440, 983040},
        {-983040, -2621440, 655360},
        {31, 66},
        {0, 97},
        {0, 66},
        16
    },
    {
        {-983040, -2949120, 655360},
        {-655360, -2949120, 983040},
        {-655360, -2621440, 983040},
        {31, 66},
        {31, 97},
        {0, 97},
        16
    },
    {
        {-983040, -3276800, 655360},
        {-655360, -2949120, 983040},
        {-983040, -2949120, 655360},
        {63, 66},
        {32, 97},
        {32, 66},
        16
    },
    {
        {-983040, -3276800, 655360},
        {-655360, -3276800, 983040},
        {-655360, -2949120, 983040},
        {63, 66},
        {63, 97},
        {32, 97},
        16
    },
    {
        {-983040, -3604480, 655360},
        {-655360, -3276800, 983040},
        {-983040, -3276800, 655360},
        {95, 66},
        {64, 97},
        {64, 66},
        16
    },
    {
        {-983040, -3604480, 655360},
        {-655360, -3604480, 983040},
        {-655360, -3276800, 983040},
        {95, 66},
        {95, 97},
        {64, 97},
        16
    },
    {
        {-983040, -3932160, 655360},
        {-655360, -3604480, 983040},
        {-983040, -3604480, 655360},
        {127, 66},
        {96, 97},
        {96, 66},
        16
    },
    {
        {-983040, -3932160, 655360},
        {-655360, -3932160, 983040},
        {-655360, -3604480, 983040},
        {127, 66},
        {127, 97},
        {96, 97},
        16
    },
    {
        {-983040, -4259840, 655360},
        {-655360, -3932160, 983040},
        {-983040, -3932160, 655360},
        {159, 66},
        {128, 97},
        {128, 66},
        16
    },
    {
        {-983040, -4259840, 655360},
        {-655360, -4259840, 983040},
        {-655360, -3932160, 983040},
        {159, 66},
        {159, 97},
        {128, 97},
        16
    },
    {
        {-983040, -4587520, 655360},
        {-655360, -4259840, 983040},
        {-983040, -4259840, 655360},
        {191, 66},
        {160, 97},
        {160, 66},
        16
    },
    {
        {-983040, -4587520, 655360},
        {-655360, -4587520, 983040},
        {-655360, -4259840, 983040},
        {191, 66},
        {191, 97},
        {160, 97},
        16
    },
    {
        {983040, 0, -655360},
        {655360, -327680, -983040},
        {655360, 0, -983040},
        {0, 193},
        {31, 162},
        {0, 162},
        16
    },
    {
        {983040, 0, -655360},
        {983040, -327680, -655360},
        {655360, -327680, -983040},
        {0, 193},
        {31, 193},
        {31, 162},
        16
    },
    {
        {983040, -327680, -655360},
        {655360, -655360, -983040},
        {655360, -327680, -983040},
        {32, 193},
        {63, 162},
        {32, 162},
        16
    },
    {
        {983040, -327680, -655360},
        {983040, -655360, -655360},
        {655360, -655360, -983040},
        {32, 193},
        {63, 193},
        {63, 162},
        16
    },
    {
        {983040, -655360, -655360},
        {655360, -983040, -983040},
        {655360, -655360, -983040},
        {64, 193},
        {95, 162},
        {64, 162},
        16
    },
    {
        {983040, -655360, -655360},
        {983040, -983040, -655360},
        {655360, -983040, -983040},
        {64, 193},
        {95, 193},
        {95, 162},
        16
    },
    {
        {983040, -983040, -655360},
        {655360, -1310720, -983040},
        {655360, -983040, -983040},
        {96, 193},
        {127, 162},
        {96, 162},
        16
    },
    {
        {983040, -983040, -655360},
        {983040, -1310720, -655360},
        {655360, -1310720, -983040},
        {96, 193},
        {127, 193},
        {127, 162},
        16
    },
    {
        {983040, -1310720, -655360},
        {655360, -1638400, -983040},
        {655360, -1310720, -983040},
        {128, 193},
        {159, 162},
        {128, 162},
        16
    },
    {
        {983040, -1310720, -655360},
        {983040, -1638400, -655360},
        {655360, -1638400, -983040},
        {128, 193},
        {159, 193},
        {159, 162},
        16
    },
    {
        {983040, -1638400, -655360},
        {655360, -1966080, -983040},
        {655360, -1638400, -983040},
        {160, 193},
        {191, 162},
        {160, 162},
        16
    },
    {
        {983040, -1638400, -655360},
        {983040, -1966080, -655360},
        {655360, -1966080, -983040},
        {160, 193},
        {191, 193},
        {191, 162},
        16
    },
    {
        {983040, -1966080, -655360},
        {655360, -2293760, -983040},
        {655360, -1966080, -983040},
        {192, 193},
        {223, 162},
        {192, 162},
        16
    },
    {
        {983040, -1966080, -655360},
        {983040, -2293760, -655360},
        {655360, -2293760, -983040},
        {192, 193},
        {223, 193},
        {223, 162},
        16
    },
    {
        {983040, -2293760, -655360},
        {655360, -2621440, -983040},
        {655360, -2293760, -983040},
        {224, 193},
        {255, 162},
        {224, 162},
        16
    },
    {
        {983040, -2293760, -655360},
        {983040, -2621440, -655360},
        {655360, -2621440, -983040},
        {224, 193},
        {255, 193},
        {255, 162},
        16
    },
    {
        {983040, -2621440, -655360},
        {655360, -2949120, -983040},
        {655360, -2621440, -983040},
        {0, 193},
        {31, 162},
        {0, 162},
        16
    },
    {
        {983040, -2621440, -655360},
        {983040, -2949120, -655360},
        {655360, -2949120, -983040},
        {0, 193},
        {31, 193},
        {31, 162},
        16
    },
    {
        {983040, -2949120, -655360},
        {655360, -3276800, -983040},
        {655360, -2949120, -983040},
        {32, 193},
        {63, 162},
        {32, 162},
        16
    },
    {
        {983040, -2949120, -655360},
        {983040, -3276800, -655360},
        {655360, -3276800, -983040},
        {32, 193},
        {63, 193},
        {63, 162},
        16
    },
    {
        {983040, -3276800, -655360},
        {655360, -3604480, -983040},
        {655360, -3276800, -983040},
        {64, 193},
        {95, 162},
        {64, 162},
        16
    },
    {
        {983040, -3276800, -655360},
        {983040, -3604480, -655360},
        {655360, -3604480, -983040},
        {64, 193},
        {95, 193},
        {95, 162},
        16
    },
    {
        {983040, -3604480, -655360},
        {655360, -3932160, -983040},
        {655360, -3604480, -983040},
        {96, 193},
        {127, 162},
        {96, 162},
        16
    },
    {
        {983040, -3604480, -655360},
        {983040, -3932160, -655360},
        {655360, -3932160, -983040},
        {96, 193},
        {127, 193},
        {127, 162},
        16
    },
    {
        {983040, -3932160, -655360},
        {655360, -4259840, -983040},
        {655360, -3932160, -983040},
        {128, 193},
        {159, 162},
        {128, 162},
        16
    },
    {
        {983040, -3932160, -655360},
        {983040, -4259840, -655360},
        {655360, -4259840, -983040},
        {128, 193},
        {159, 193},
        {159, 162},
        16
    },
    {
        {983040, -4259840, -655360},
        {655360, -4587520, -983040},
        {655360, -4259840, -983040},
        {160, 193},
        {191, 162},
        {160, 162},
        16
    },
    {
        {983040, -4259840, -655360},
        {983040, -4587520, -655360},
        {655360, -4587520, -983040},
        {160, 193},
        {191, 193},
        {191, 162},
        16
    },
    {
        {983040, -327680, 655360},
        {655360, 0, 983040},
        {655360, -327680, 983040},
        {31, 66},
        {0, 97},
        {31, 97},
        16
    },
    {
        {983040, -327680, 655360},
        {983040, 0, 655360},
        {655360, 0, 983040},
        {31, 66},
        {0, 66},
        {0, 97},
        16
    },
    {
        {983040, -655360, 655360},
        {655360, -327680, 983040},
        {655360, -655360, 983040},
        {63, 66},
        {32, 97},
        {63, 97},
        16
    },
    {
        {983040, -655360, 655360},
        {983040, -327680, 655360},
        {655360, -327680, 983040},
        {63, 66},
        {32, 66},
        {32, 97},
        16
    },
    {
        {983040, -983040, 655360},
        {655360, -655360, 983040},
        {655360, -983040, 983040},
        {95, 66},
        {64, 97},
        {95, 97},
        16
    },
    {
        {983040, -983040, 655360},
        {983040, -655360, 655360},
        {655360, -655360, 983040},
        {95, 66},
        {64, 66},
        {64, 97},
        16
    },
    {
        {983040, -1310720, 655360},
        {655360, -983040, 983040},
        {655360, -1310720, 983040},
        {127, 66},
        {96, 97},
        {127, 97},
        16
    },
    {
        {983040, -1310720, 655360},
        {983040, -983040, 655360},
        {655360, -983040, 983040},
        {127, 66},
        {96, 66},
        {96, 97},
        16
    },
    {
        {983040, -1638400, 655360},
        {655360, -1310720, 983040},
        {655360, -1638400, 983040},
        {159, 66},
        {128, 97},
        {159, 97},
        16
    },
    {
        {983040, -1638400, 655360},
        {983040, -1310720, 655360},
        {655360, -1310720, 983040},
        {159, 66},
        {128, 66},
        {128, 97},
        16
    },
    {
        {983040, -1966080, 655360},
        {655360, -1638400, 983040},
        {655360, -1966080, 983040},
        {191, 66},
        {160, 97},
        {191, 97},
        16
    },
    {
        {983040, -1966080, 655360},
        {983040, -1638400, 655360},
        {655360, -1638400, 983040},
        {191, 66},
        {160, 66},
        {160, 97},
        16
    },
    {
        {983040, -2293760, 655360},
        {655360, -1966080, 983040},
        {655360, -2293760, 983040},
        {223, 66},
        {192, 97},
        {223, 97},
        16
    },
    {
        {983040, -2293760, 655360},
        {983040, -1966080, 655360},
        {655360, -1966080, 983040},
        {223, 66},
        {192, 66},
        {192, 97},
        16
    },
    {
        {983040, -2621440, 655360},
        {655360, -2293760, 983040},
        {655360, -2621440, 983040},
        {255, 66},
        {224, 97},
        {255, 97},
        16
    },
    {
        {983040, -2621440, 655360},
        {983040, -2293760, 655360},
        {655360, -2293760, 983040},
        {255, 66},
        {224, 66},
        {224, 97},
        16
    },
    {
        {983040, -2949120, 655360},
        {655360, -2621440, 983040},
        {655360, -2949120, 983040},
        {31, 66},
        {0, 97},
        {31, 97},
        16
    },
    {
        {983040, -2949120, 655360},
        {983040, -2621440, 655360},
        {655360, -2621440, 983040},
        {31, 66},
        {0, 66},
        {0, 97},
        16
    },
    {
        {983040, -3276800, 655360},
        {655360, -2949120, 983040},
        {655360, -3276800, 983040},
        {63, 66},
        {32, 97},
        {63, 97},
        16
    },
    {
        {983040, -3276800, 655360},
        {983040, -2949120, 655360},
        {655360, -2949120, 983040},
        {63, 66},
        {32, 66},
        {32, 97},
        16
    },
    {
        {983040, -3604480, 655360},
        {655360, -3276800, 983040},
        {655360, -3604480, 983040},
        {95, 66},
        {64, 97},
        {95, 97},
        16
    },
    {
        {983040, -3604480, 655360},
        {983040, -3276800, 655360},
        {655360, -3276800, 983040},
        {95, 66},
        {64, 66},
        {64, 97},
        16
    },
    {
        {983040, -3932160, 655360},
        {655360, -3604480, 983040},
        {655360, -3932160, 983040},
        {127, 66},
        {96, 97},
        {127, 97},
        16
    },
    {
        {983040, -3932160, 655360},
        {983040, -3604480, 655360},
        {655360, -3604480, 983040},
        {127, 66},
        {96, 66},
        {96, 97},
        16
    },
    {
        {983040, -4259840, 655360},
        {655360, -3932160, 983040},
        {655360, -4259840, 983040},
        {159, 66},
        {128, 97},
        {159, 97},
        16
    },
    {
        {983040, -4259840, 655360},
        {983040, -3932160, 655360},
        {655360, -3932160, 983040},
        {159, 66},
        {128, 66},
        {128, 97},
        16
    },
    {
        {983040, -4587520, 655360},
        {655360, -4259840, 983040},
        {655360, -4587520, 983040},
        {191, 66},
        {160, 97},
        {191, 97},
        16
    },
    {
        {983040, -4587520, 655360},
        {983040, -4259840, 655360},
        {655360, -4259840, 983040},
        {191, 66},
        {160, 66},
        {160, 97},
        16
    },
    {
        {0, 0, -983040},
        {-327680, -327680, -983040},
        {-327680, 0, -983040},
        {255, 255},
        {224, 224},
        {224, 255},
        16
    },
    {
        {0, 0, -983040},
        {0, -327680, -983040},
        {-327680, -327680, -983040},
        {255, 255},
        {255, 224},
        {224, 224},
        16
    },
    {
        {0, -327680, -983040},
        {-327680, -655360, -983040},
        {-327680, -327680, -983040},
        {255, 223},
        {224, 192},
        {224, 223},
        0
    },
    {
        {0, -327680, -983040},
        {0, -655360, -983040},
        {-327680, -655360, -983040},
        {255, 223},
        {255, 192},
        {224, 192},
        0
    },
    {
        {327680, -327680, -983040},
        {0, -655360, -983040},
        {0, -327680, -983040},
        {31, 223},
        {0, 192},
        {0, 223},
        0
    },
    {
        {327680, -327680, -983040},
        {327680, -655360, -983040},
        {0, -655360, -983040},
        {31, 223},
        {31, 192},
        {0, 192},
        0
    },
    {
        {1048576, -327680, -327680},
        {983040, -655360, -655360},
        {983040, -327680, -655360},
        {32, 223},
        {63, 192},
        {63, 223},
        14
    },
    {
        {1048576, -327680, -327680},
        {1048576, -655360, -327680},
        {983040, -655360, -655360},
        {32, 223},
        {32, 192},
        {63, 192},
        14
    },
    {
        {1048576, -655360, -327680},
        {983040, -983040, -655360},
        {983040, -655360, -655360},
        {32, 191},
        {63, 160},
        {63, 191},
        14
    },
    {
        {1048576, -655360, -327680},
        {1048576, -983040, -327680},
        {983040, -983040, -655360},
        {32, 191},
        {32, 160},
        {63, 160},
        14
    },
    {
        {1048576, -983040, -327680},
        {983040, -1310720, -655360},
        {983040, -983040, -655360},
        {32, 159},
        {63, 128},
        {63, 159},
        14
    },
    {
        {1048576, -983040, -327680},
        {1048576, -1310720, -327680},
        {983040, -1310720, -655360},
        {32, 159},
        {32, 128},
        {63, 128},
        14
    },
    {
        {1048576, -1310720, -327680},
        {983040, -1638400, -655360},
        {983040, -1310720, -655360},
        {32, 127},
        {63, 96},
        {63, 127},
        14
    },
    {
        {1048576, -1310720, -327680},
        {1048576, -1638400, -327680},
        {983040, -1638400, -655360},
        {32, 127},
        {32, 96},
        {63, 96},
        14
    },
    {
        {1048576, -1638400, -327680},
        {983040, -1966080, -655360},
        {983040, -1638400, -655360},
        {32, 95},
        {63, 64},
        {63, 95},
        14
    },
    {
        {1048576, -1638400, -327680},
        {1048576, -1966080, -327680},
        {983040, -1966080, -655360},
        {32, 95},
        {32, 64},
        {63, 64},
        14
    },
    {
        {1048576, -327680, 327680},
        {983040, 0, 655360},
        {983040, -327680, 655360},
        {223, 224},
        {192, 255},
        {192, 224},
        14
    },
    {
        {1048576, -327680, 327680},
        {1048576, 0, 327680},
        {983040, 0, 655360},
        {223, 224},
        {223, 255},
        {192, 255},
        14
    },
    {
        {1048576, -655360, 327680},
        {983040, -327680, 655360},
        {983040, -655360, 655360},
        {223, 192},
        {192, 223},
        {192, 192},
        14
    },
    {
        {1048576, -655360, 327680},
        {1048576, -327680, 327680},
        {983040, -327680, 655360},
        {223, 192},
        {223, 223},
        {192, 223},
        14
    },
    {
        {1048576, -983040, 327680},
        {983040, -655360, 655360},
        {983040, -983040, 655360},
        {223, 160},
        {192, 191},
        {192, 160},
        14
    },
    {
        {1048576, -983040, 327680},
        {1048576, -655360, 327680},
        {983040, -655360, 655360},
        {223, 160},
        {223, 191},
        {192, 191},
        14
    },
    {
        {1048576, -1310720, 327680},
        {983040, -983040, 655360},
        {983040, -1310720, 655360},
        {223, 128},
        {192, 159},
        {192, 128},
        14
    },
    {
        {1048576, -1310720, 327680},
        {1048576, -983040, 327680},
        {983040, -983040, 655360},
        {223, 128},
        {223, 159},
        {192, 159},
        14
    },
    {
        {1048576, -1638400, 327680},
        {983040, -1310720, 655360},
        {983040, -1638400, 655360},
        {223, 96},
        {192, 127},
        {192, 96},
        14
    },
    {
        {1048576, -1638400, 327680},
        {1048576, -1310720, 327680},
        {983040, -1310720, 655360},
        {223, 96},
        {223, 127},
        {192, 127},
        14
    },
    {
        {1048576, -1966080, 327680},
        {983040, -1638400, 655360},
        {983040, -1966080, 655360},
        {223, 64},
        {192, 95},
        {192, 64},
        14
    },
    {
        {1048576, -1966080, 327680},
        {1048576, -1638400, 327680},
        {983040, -1638400, 655360},
        {223, 64},
        {223, 95},
        {192, 95},
        14
    },
    {
        {-1048576, -327680, 327680},
        {-983040, 0, 655360},
        {-1048576, 0, 327680},
        {223, 224},
        {192, 255},
        {223, 255},
        14
    },
    {
        {-1048576, -327680, 327680},
        {-983040, -327680, 655360},
        {-983040, 0, 655360},
        {223, 224},
        {192, 224},
        {192, 255},
        14
    },
    {
        {-1048576, -655360, 327680},
        {-983040, -327680, 655360},
        {-1048576, -327680, 327680},
        {223, 192},
        {192, 223},
        {223, 223},
        14
    },
    {
        {-1048576, -655360, 327680},
        {-983040, -655360, 655360},
        {-983040, -327680, 655360},
        {223, 192},
        {192, 192},
        {192, 223},
        14
    },
    {
        {-1048576, -983040, 327680},
        {-983040, -655360, 655360},
        {-1048576, -655360, 327680},
        {223, 160},
        {192, 191},
        {223, 191},
        14
    },
    {
        {-1048576, -983040, 327680},
        {-983040, -983040, 655360},
        {-983040, -655360, 655360},
        {223, 160},
        {192, 160},
        {192, 191},
        14
    },
    {
        {-1048576, -1310720, 327680},
        {-983040, -983040, 655360},
        {-1048576, -983040, 327680},
        {223, 128},
        {192, 159},
        {223, 159},
        14
    },
    {
        {-1048576, -1310720, 327680},
        {-983040, -1310720, 655360},
        {-983040, -983040, 655360},
        {223, 128},
        {192, 128},
        {192, 159},
        14
    },
    {
        {-1048576, -1638400, 327680},
        {-983040, -1310720, 655360},
        {-1048576, -1310720, 327680},
        {223, 96},
        {192, 127},
        {223, 127},
        14
    },
    {
        {-1048576, -1638400, 327680},
        {-983040, -1638400, 655360},
        {-983040, -1310720, 655360},
        {223, 96},
        {192, 96},
        {192, 127},
        14
    },
    {
        {-1048576, -1966080, 327680},
        {-983040, -1638400, 655360},
        {-1048576, -1638400, 327680},
        {223, 64},
        {192, 95},
        {223, 95},
        14
    },
    {
        {-1048576, -1966080, 327680},
        {-983040, -1966080, 655360},
        {-983040, -1638400, 655360},
        {223, 64},
        {192, 64},
        {192, 95},
        14
    },
    {
        {-983040, 0, -655360},
        {-1048576, -327680, -327680},
        {-1048576, 0, -327680},
        {63, 255},
        {32, 224},
        {32, 255},
        14
    },
    {
        {-983040, 0, -655360},
        {-983040, -327680, -655360},
        {-1048576, -327680, -327680},
        {63, 255},
        {63, 224},
        {32, 224},
        14
    },
    {
        {-983040, -327680, -655360},
        {-1048576, -655360, -327680},
        {-1048576, -327680, -327680},
        {63, 223},
        {32, 192},
        {32, 223},
        14
    },
    {
        {-983040, -327680, -655360},
        {-983040, -655360, -655360},
        {-1048576, -655360, -327680},
        {63, 223},
        {63, 192},
        {32, 192},
        14
    },
    {
        {-983040, -655360, -655360},
        {-1048576, -983040, -327680},
        {-1048576, -655360, -327680},
        {63, 191},
        {32, 160},
        {32, 191},
        14
    },
    {
        {-983040, -655360, -655360},
        {-983040, -983040, -655360},
        {-1048576, -983040, -327680},
        {63, 191},
        {63, 160},
        {32, 160},
        14
    },
    {
        {-983040, -983040, -655360},
        {-1048576, -1310720, -327680},
        {-1048576, -983040, -327680},
        {63, 159},
        {32, 128},
        {32, 159},
        14
    },
    {
        {-983040, -983040, -655360},
        {-983040, -1310720, -655360},
        {-1048576, -1310720, -327680},
        {63, 159},
        {63, 128},
        {32, 128},
        14
    },
    {
        {-983040, -1310720, -655360},
        {-1048576, -1638400, -327680},
        {-1048576, -1310720, -327680},
        {63, 127},
        {32, 96},
        {32, 127},
        14
    },
    {
        {-983040, -1310720, -655360},
        {-983040, -1638400, -655360},
        {-1048576, -1638400, -327680},
        {63, 127},
        {63, 96},
        {32, 96},
        14
    },
    {
        {-983040, -1638400, -655360},
        {-1048576, -1966080, -327680},
        {-1048576, -1638400, -327680},
        {63, 95},
        {32, 64},
        {32, 95},
        14
    },
    {
        {-983040, -1638400, -655360},
        {-983040, -1966080, -655360},
        {-1048576, -1966080, -327680},
        {63, 95},
        {63, 64},
        {32, 64},
        14
    },
    {
        {-1048576, -327680, 327680},
        {-1048576, 0, 0},
        {-1048576, -327680, 0},
        {31, 224},
        {0, 255},
        {0, 224},
        16
    },
    {
        {-1048576, -327680, 327680},
        {-1048576, 0, 327680},
        {-1048576, 0, 0},
        {31, 224},
        {31, 255},
        {0, 255},
        16
    },
    {
        {-1048576, -655360, 0},
        {-1048576, -327680, -327680},
        {-1048576, -655360, -327680},
        {255, 192},
        {224, 223},
        {224, 192},
        15
    },
    {
        {-1048576, -655360, 0},
        {-1048576, -327680, 0},
        {-1048576, -327680, -327680},
        {255, 192},
        {255, 223},
        {224, 223},
        15
    },
    {
        {-1048576, -655360, 327680},
        {-1048576, -327680, 0},
        {-1048576, -655360, 0},
        {31, 192},
        {0, 223},
        {0, 192},
        15
    },
    {
        {-1048576, -655360, 327680},
        {-1048576, -327680, 327680},
        {-1048576, -327680, 0},
        {31, 192},
        {31, 223},
        {0, 223},
        15
    },
    {
        {-1048576, -983040, 0},
        {-1048576, -655360, -327680},
        {-1048576, -983040, -327680},
        {31, 160},
        {0, 191},
        {0, 160},
        6
    },
    {
        {-1048576, -983040, 0},
        {-1048576, -655360, 0},
        {-1048576, -655360, -327680},
        {31, 160},
        {31, 191},
        {0, 191},
        6
    },
    {
        {-1048576, -983040, 327680},
        {-1048576, -655360, 0},
        {-1048576, -983040, 0},
        {63, 160},
        {32, 191},
        {32, 160},
        6
    },
    {
        {-1048576, -983040, 327680},
        {-1048576, -655360, 327680},
        {-1048576, -655360, 0},
        {63, 160},
        {63, 191},
        {32, 191},
        6
    },
    {
        {-1048576, -1310720, 0},
        {-1048576, -983040, -327680},
        {-1048576, -1310720, -327680},
        {31, 128},
        {0, 159},
        {0, 128},
        6
    },
    {
        {-1048576, -1310720, 0},
        {-1048576, -983040, 0},
        {-1048576, -983040, -327680},
        {31, 128},
        {31, 159},
        {0, 159},
        6
    },
    {
        {-1048576, -1310720, 327680},
        {-1048576, -983040, 0},
        {-1048576, -1310720, 0},
        {63, 128},
        {32, 159},
        {32, 128},
        6
    },
    {
        {-1048576, -1310720, 327680},
        {-1048576, -983040, 327680},
        {-1048576, -983040, 0},
        {63, 128},
        {63, 159},
        {32, 159},
        6
    },
    {
        {-1048576, -1638400, 0},
        {-1048576, -1310720, -327680},
        {-1048576, -1638400, -327680},
        {31, 96},
        {0, 127},
        {0, 96},
        6
    },
    {
        {-1048576, -1638400, 0},
        {-1048576, -1310720, 0},
        {-1048576, -1310720, -327680},
        {31, 96},
        {31, 127},
        {0, 127},
        6
    },
    {
        {-1048576, -1638400, 327680},
        {-1048576, -1310720, 0},
        {-1048576, -1638400, 0},
        {63, 96},
        {32, 127},
        {32, 96},
        6
    },
    {
        {-1048576, -1638400, 327680},
        {-1048576, -1310720, 327680},
        {-1048576, -1310720, 0},
        {63, 96},
        {63, 127},
        {32, 127},
        6
    },
    {
        {-1048576, -1966080, 0},
        {-1048576, -1638400, -327680},
        {-1048576, -1966080, -327680},
        {31, 64},
        {0, 95},
        {0, 64},
        9
    },
    {
        {-1048576, -1966080, 0},
        {-1048576, -1638400, 0},
        {-1048576, -1638400, -327680},
        {31, 64},
        {31, 95},
        {0, 95},
        9
    },
    {
        {-1048576, -1966080, 327680},
        {-1048576, -1638400, 0},
        {-1048576, -1966080, 0},
        {63, 64},
        {32, 95},
        {32, 64},
        9
    },
    {
        {-1048576, -1966080, 327680},
        {-1048576, -1638400, 327680},
        {-1048576, -1638400, 0},
        {63, 64},
        {63, 95},
        {32, 95},
        9
    },
    {
        {1048576, -1638400, 0},
        {1048576, -1966080, -327680},
        {1048576, -1638400, -327680},
        {31, 95},
        {0, 64},
        {0, 95},
        9
    },
    {
        {1048576, -1638400, 0},
        {1048576, -1966080, 0},
        {1048576, -1966080, -327680},
        {31, 95},
        {31, 64},
        {0, 64},
        9
    },
    {
        {1048576, -1310720, 0},
        {1048576, -1638400, -327680},
        {1048576, -1310720, -327680},
        {31, 127},
        {0, 96},
        {0, 127},
        6
    },
    {
        {1048576, -1310720, 0},
        {1048576, -1638400, 0},
        {1048576, -1638400, -327680},
        {31, 127},
        {31, 96},
        {0, 96},
        6
    },
    {
        {1048576, -983040, 0},
        {1048576, -1310720, -327680},
        {1048576, -983040, -327680},
        {31, 159},
        {0, 128},
        {0, 159},
        6
    },
    {
        {1048576, -983040, 0},
        {1048576, -1310720, 0},
        {1048576, -1310720, -327680},
        {31, 159},
        {31, 128},
        {0, 128},
        6
    },
    {
        {1048576, -655360, 0},
        {1048576, -983040, -327680},
        {1048576, -655360, -327680},
        {31, 191},
        {0, 160},
        {0, 191},
        6
    },
    {
        {1048576, -655360, 0},
        {1048576, -983040, 0},
        {1048576, -983040, -327680},
        {31, 191},
        {31, 160},
        {0, 160},
        6
    },
    {
        {1048576, -327680, 0},
        {1048576, -655360, -327680},
        {1048576, -327680, -327680},
        {255, 223},
        {224, 192},
        {224, 223},
        15
    },
    {
        {1048576, -327680, 0},
        {1048576, -655360, 0},
        {1048576, -655360, -327680},
        {255, 223},
        {255, 192},
        {224, 192},
        15
    },
    {
        {1048576, 0, 0},
        {1048576, -327680, -327680},
        {1048576, 0, -327680},
        {31, 255},
        {0, 224},
        {0, 255},
        16
    },
    {
        {1048576, 0, 0},
        {1048576, -327680, 0},
        {1048576, -327680, -327680},
        {31, 255},
        {31, 224},
        {0, 224},
        16
    },
    {
        {1048576, 0, 327680},
        {1048576, -327680, 0},
        {1048576, 0, 0},
        {63, 255},
        {32, 224},
        {32, 255},
        16
    },
    {
        {1048576, 0, 327680},
        {1048576, -327680, 327680},
        {1048576, -327680, 0},
        {63, 255},
        {63, 224},
        {32, 224},
        16
    },
    {
        {1048576, -327680, 327680},
        {1048576, -655360, 0},
        {1048576, -327680, 0},
        {31, 223},
        {0, 192},
        {0, 223},
        15
    },
    {
        {1048576, -327680, 327680},
        {1048576, -655360, 327680},
        {1048576, -655360, 0},
        {31, 223},
        {31, 192},
        {0, 192},
        15
    },
    {
        {1048576, -655360, 327680},
        {1048576, -983040, 0},
        {1048576, -655360, 0},
        {63, 191},
        {32, 160},
        {32, 191},
        6
    },
    {
        {1048576, -655360, 327680},
        {1048576, -983040, 327680},
        {1048576, -983040, 0},
        {63, 191},
        {63, 160},
        {32, 160},
        6
    },
    {
        {1048576, -983040, 327680},
        {1048576, -1310720, 0},
        {1048576, -983040, 0},
        {63, 159},
        {32, 128},
        {32, 159},
        6
    },
    {
        {1048576, -983040, 327680},
        {1048576, -1310720, 327680},
        {1048576, -1310720, 0},
        {63, 159},
        {63, 128},
        {32, 128},
        6
    },
    {
        {1048576, -1310720, 327680},
        {1048576, -1638400, 0},
        {1048576, -1310720, 0},
        {63, 127},
        {32, 96},
        {32, 127},
        6
    },
    {
        {1048576, -1310720, 327680},
        {1048576, -1638400, 327680},
        {1048576, -1638400, 0},
        {63, 127},
        {63, 96},
        {32, 96},
        6
    },
    {
        {1048576, -1638400, 327680},
        {1048576, -1966080, 0},
        {1048576, -1638400, 0},
        {63, 95},
        {32, 64},
        {32, 95},
        9
    },
    {
        {1048576, -1638400, 327680},
        {1048576, -1966080, 327680},
        {1048576, -1966080, 0},
        {63, 95},
        {63, 64},
        {32, 64},
        9
    },
    {
        {-1048576, -2293760, 327680},
        {-983040, -1966080, 655360},
        {-1048576, -1966080, 327680},
        {39, 32},
        {70, 63},
        {39, 63},
        7
    },
    {
        {-1048576, -2293760, 327680},
        {-983040, -2293760, 655360},
        {-983040, -1966080, 655360},
        {39, 32},
        {70, 32},
        {70, 63},
        7
    },
    {
        {-1048576, -2621440, 327680},
        {-983040, -2293760, 655360},
        {-1048576, -2293760, 327680},
        {39, 0},
        {70, 31},
        {39, 31},
        7
    },
    {
        {-1048576, -2621440, 327680},
        {-983040, -2621440, 655360},
        {-983040, -2293760, 655360},
        {39, 0},
        {70, 0},
        {70, 31},
        7
    },
    {
        {-1048576, -2949120, 327680},
        {-983040, -2621440, 655360},
        {-1048576, -2621440, 327680},
        {39, 224},
        {70, 255},
        {39, 255},
        7
    },
    {
        {-1048576, -2949120, 327680},
        {-983040, -2949120, 655360},
        {-983040, -2621440, 655360},
        {39, 224},
        {70, 224},
        {70, 255},
        7
    },
    {
        {-1048576, -3276800, 327680},
        {-983040, -2949120, 655360},
        {-1048576, -2949120, 327680},
        {39, 192},
        {70, 223},
        {39, 223},
        7
    },
    {
        {-1048576, -3276800, 327680},
        {-983040, -3276800, 655360},
        {-983040, -2949120, 655360},
        {39, 192},
        {70, 192},
        {70, 223},
        7
    },
    {
        {-1048576, -3604480, 327680},
        {-983040, -3276800, 655360},
        {-1048576, -3276800, 327680},
        {39, 160},
        {70, 191},
        {39, 191},
        7
    },
    {
        {-1048576, -3604480, 327680},
        {-983040, -3604480, 655360},
        {-983040, -3276800, 655360},
        {39, 160},
        {70, 160},
        {70, 191},
        7
    },
    {
        {-1048576, -3932160, 327680},
        {-983040, -3604480, 655360},
        {-1048576, -3604480, 327680},
        {39, 128},
        {70, 159},
        {39, 159},
        7
    },
    {
        {-1048576, -3932160, 327680},
        {-983040, -3932160, 655360},
        {-983040, -3604480, 655360},
        {39, 128},
        {70, 128},
        {70, 159},
        7
    },
    {
        {-1048576, -4259840, 327680},
        {-983040, -3932160, 655360},
        {-1048576, -3932160, 327680},
        {39, 96},
        {70, 127},
        {39, 127},
        7
    },
    {
        {-1048576, -4259840, 327680},
        {-983040, -4259840, 655360},
        {-983040, -3932160, 655360},
        {39, 96},
        {70, 96},
        {70, 127},
        7
    },
    {
        {-1048576, -4587520, 327680},
        {-983040, -4259840, 655360},
        {-1048576, -4259840, 327680},
        {39, 64},
        {70, 95},
        {39, 95},
        7
    },
    {
        {-1048576, -4587520, 327680},
        {-983040, -4587520, 655360},
        {-983040, -4259840, 655360},
        {39, 64},
        {70, 64},
        {70, 95},
        7
    },
    {
        {-983040, -1966080, -655360},
        {-1048576, -2293760, -327680},
        {-1048576, -1966080, -327680},
        {185, 63},
        {216, 32},
        {216, 63},
        7
    },
    {
        {-983040, -1966080, -655360},
        {-983040, -2293760, -655360},
        {-1048576, -2293760, -327680},
        {185, 63},
        {185, 32},
        {216, 32},
        7
    },
    {
        {-983040, -2293760, -655360},
        {-1048576, -2621440, -327680},
        {-1048576, -2293760, -327680},
        {185, 31},
        {216, 0},
        {216, 31},
        7
    },
    {
        {-983040, -2293760, -655360},
        {-983040, -2621440, -655360},
        {-1048576, -2621440, -327680},
        {185, 31},
        {185, 0},
        {216, 0},
        7
    },
    {
        {-983040, -2621440, -655360},
        {-1048576, -2949120, -327680},
        {-1048576, -2621440, -327680},
        {185, 255},
        {216, 224},
        {216, 255},
        7
    },
    {
        {-983040, -2621440, -655360},
        {-983040, -2949120, -655360},
        {-1048576, -2949120, -327680},
        {185, 255},
        {185, 224},
        {216, 224},
        7
    },
    {
        {-983040, -2949120, -655360},
        {-1048576, -3276800, -327680},
        {-1048576, -2949120, -327680},
        {185, 223},
        {216, 192},
        {216, 223},
        7
    },
    {
        {-983040, -2949120, -655360},
        {-983040, -3276800, -655360},
        {-1048576, -3276800, -327680},
        {185, 223},
        {185, 192},
        {216, 192},
        7
    },
    {
        {-983040, -3276800, -655360},
        {-1048576, -3604480, -327680},
        {-1048576, -3276800, -327680},
        {185, 191},
        {216, 160},
        {216, 191},
        7
    },
    {
        {-983040, -3276800, -655360},
        {-983040, -3604480, -655360},
        {-1048576, -3604480, -327680},
        {185, 191},
        {185, 160},
        {216, 160},
        7
    },
    {
        {-983040, -3604480, -655360},
        {-1048576, -3932160, -327680},
        {-1048576, -3604480, -327680},
        {185, 159},
        {216, 128},
        {216, 159},
        7
    },
    {
        {-983040, -3604480, -655360},
        {-983040, -3932160, -655360},
        {-1048576, -3932160, -327680},
        {185, 159},
        {185, 128},
        {216, 128},
        7
    },
    {
        {-983040, -3932160, -655360},
        {-1048576, -4259840, -327680},
        {-1048576, -3932160, -327680},
        {185, 127},
        {216, 96},
        {216, 127},
        7
    },
    {
        {-983040, -3932160, -655360},
        {-983040, -4259840, -655360},
        {-1048576, -4259840, -327680},
        {185, 127},
        {185, 96},
        {216, 96},
        7
    },
    {
        {-983040, -4259840, -655360},
        {-1048576, -4587520, -327680},
        {-1048576, -4259840, -327680},
        {185, 95},
        {216, 64},
        {216, 95},
        7
    },
    {
        {-983040, -4259840, -655360},
        {-983040, -4587520, -655360},
        {-1048576, -4587520, -327680},
        {185, 95},
        {185, 64},
        {216, 64},
        7
    },
    {
        {1048576, -4259840, -327680},
        {983040, -4587520, -655360},
        {983040, -4259840, -655360},
        {216, 95},
        {185, 64},
        {185, 95},
        7
    },
    {
        {1048576, -4259840, -327680},
        {1048576, -4587520, -327680},
        {983040, -4587520, -655360},
        {216, 95},
        {216, 64},
        {185, 64},
        7
    },
    {
        {1048576, -4587520, 327680},
        {983040, -4259840, 655360},
        {983040, -4587520, 655360},
        {39, 64},
        {70, 95},
        {70, 64},
        7
    },
    {
        {1048576, -4587520, 327680},
        {1048576, -4259840, 327680},
        {983040, -4259840, 655360},
        {39, 64},
        {39, 95},
        {70, 95},
        7
    },
    {
        {1048576, -3932160, -327680},
        {983040, -4259840, -655360},
        {983040, -3932160, -655360},
        {216, 127},
        {185, 96},
        {185, 127},
        7
    },
    {
        {1048576, -3932160, -327680},
        {1048576, -4259840, -327680},
        {983040, -4259840, -655360},
        {216, 127},
        {216, 96},
        {185, 96},
        7
    },
    {
        {1048576, -4259840, 327680},
        {983040, -3932160, 655360},
        {983040, -4259840, 655360},
        {39, 96},
        {70, 127},
        {70, 96},
        7
    },
    {
        {1048576, -4259840, 327680},
        {1048576, -3932160, 327680},
        {983040, -3932160, 655360},
        {39, 96},
        {39, 127},
        {70, 127},
        7
    },
    {
        {1048576, -3932160, 327680},
        {983040, -3604480, 655360},
        {983040, -3932160, 655360},
        {39, 128},
        {70, 159},
        {70, 128},
        7
    },
    {
        {1048576, -3932160, 327680},
        {1048576, -3604480, 327680},
        {983040, -3604480, 655360},
        {39, 128},
        {39, 159},
        {70, 159},
        7
    },
    {
        {1048576, -3604480, 327680},
        {983040, -3276800, 655360},
        {983040, -3604480, 655360},
        {39, 160},
        {70, 191},
        {70, 160},
        7
    },
    {
        {1048576, -3604480, 327680},
        {1048576, -3276800, 327680},
        {983040, -3276800, 655360},
        {39, 160},
        {39, 191},
        {70, 191},
        7
    },
    {
        {1048576, -3276800, 327680},
        {983040, -2949120, 655360},
        {983040, -3276800, 655360},
        {39, 192},
        {70, 223},
        {70, 192},
        7
    },
    {
        {1048576, -3276800, 327680},
        {1048576, -2949120, 327680},
        {983040, -2949120, 655360},
        {39, 192},
        {39, 223},
        {70, 223},
        7
    },
    {
        {1048576, -2949120, 327680},
        {983040, -2621440, 655360},
        {983040, -2949120, 655360},
        {39, 224},
        {70, 255},
        {70, 224},
        7
    },
    {
        {1048576, -2949120, 327680},
        {1048576, -2621440, 327680},
        {983040, -2621440, 655360},
        {39, 224},
        {39, 255},
        {70, 255},
        7
    },
    {
        {1048576, -2621440, 327680},
        {983040, -2293760, 655360},
        {983040, -2621440, 655360},
        {39, 0},
        {70, 31},
        {70, 0},
        7
    },
    {
        {1048576, -2621440, 327680},
        {1048576, -2293760, 327680},
        {983040, -2293760, 655360},
        {39, 0},
        {39, 31},
        {70, 31},
        7
    },
    {
        {1048576, -2293760, 327680},
        {983040, -1966080, 655360},
        {983040, -2293760, 655360},
        {39, 32},
        {70, 63},
        {70, 32},
        7
    },
    {
        {1048576, -2293760, 327680},
        {1048576, -1966080, 327680},
        {983040, -1966080, 655360},
        {39, 32},
        {39, 63},
        {70, 63},
        7
    },
    {
        {1048576, -1966080, -327680},
        {983040, -2293760, -655360},
        {983040, -1966080, -655360},
        {216, 63},
        {185, 32},
        {185, 63},
        7
    },
    {
        {1048576, -1966080, -327680},
        {1048576, -2293760, -327680},
        {983040, -2293760, -655360},
        {216, 63},
        {216, 32},
        {185, 32},
        7
    },
    {
        {1048576, -2293760, -327680},
        {983040, -2621440, -655360},
        {983040, -2293760, -655360},
        {216, 31},
        {185, 0},
        {185, 31},
        7
    },
    {
        {1048576, -2293760, -327680},
        {1048576, -2621440, -327680},
        {983040, -2621440, -655360},
        {216, 31},
        {216, 0},
        {185, 0},
        7
    },
    {
        {1048576, -2621440, -327680},
        {983040, -2949120, -655360},
        {983040, -2621440, -655360},
        {216, 255},
        {185, 224},
        {185, 255},
        7
    },
    {
        {1048576, -2621440, -327680},
        {1048576, -2949120, -327680},
        {983040, -2949120, -655360},
        {216, 255},
        {216, 224},
        {185, 224},
        7
    },
    {
        {1048576, -2949120, -327680},
        {983040, -3276800, -655360},
        {983040, -2949120, -655360},
        {216, 223},
        {185, 192},
        {185, 223},
        7
    },
    {
        {1048576, -2949120, -327680},
        {1048576, -3276800, -327680},
        {983040, -3276800, -655360},
        {216, 223},
        {216, 192},
        {185, 192},
        7
    },
    {
        {1048576, -3276800, -327680},
        {983040, -3604480, -655360},
        {983040, -3276800, -655360},
        {216, 191},
        {185, 160},
        {185, 191},
        7
    },
    {
        {1048576, -3276800, -327680},
        {1048576, -3604480, -327680},
        {983040, -3604480, -655360},
        {216, 191},
        {216, 160},
        {185, 160},
        7
    },
    {
        {1048576, -3604480, -327680},
        {983040, -3932160, -655360},
        {983040, -3604480, -655360},
        {216, 159},
        {185, 128},
        {185, 159},
        7
    },
    {
        {1048576, -3604480, -327680},
        {1048576, -3932160, -327680},
        {983040, -3932160, -655360},
        {216, 159},
        {216, 128},
        {185, 128},
        7
    },
    {
        {1048576, -1966080, 327680},
        {1048576, -2293760, 0},
        {1048576, -1966080, 0},
        {63, 63},
        {32, 32},
        {32, 63},
        3
    },
    {
        {1048576, -1966080, 327680},
        {1048576, -2293760, 327680},
        {1048576, -2293760, 0},
        {63, 63},
        {63, 32},
        {32, 32},
        3
    },
    {
        {1048576, -1966080, 0},
        {1048576, -2293760, -327680},
        {1048576, -1966080, -327680},
        {31, 63},
        {0, 32},
        {0, 63},
        3
    },
    {
        {1048576, -1966080, 0},
        {1048576, -2293760, 0},
        {1048576, -2293760, -327680},
        {31, 63},
        {31, 32},
        {0, 32},
        3
    },
    {
        {1048576, -2293760, 0},
        {1048576, -2621440, -327680},
        {1048576, -2293760, -327680},
        {31, 31},
        {0, 0},
        {0, 31},
        3
    },
    {
        {1048576, -2293760, 0},
        {1048576, -2621440, 0},
        {1048576, -2621440, -327680},
        {31, 31},
        {31, 0},
        {0, 0},
        3
    },
    {
        {1048576, -2293760, 327680},
        {1048576, -2621440, 0},
        {1048576, -2293760, 0},
        {63, 31},
        {32, 0},
        {32, 31},
        3
    },
    {
        {1048576, -2293760, 327680},
        {1048576, -2621440, 327680},
        {1048576, -2621440, 0},
        {63, 31},
        {63, 0},
        {32, 0},
        3
    },
    {
        {1048576, -2949120, 0},
        {1048576, -3276800, -327680},
        {1048576, -2949120, -327680},
        {31, 223},
        {0, 192},
        {0, 223},
        3
    },
    {
        {1048576, -2949120, 0},
        {1048576, -3276800, 0},
        {1048576, -3276800, -327680},
        {31, 223},
        {31, 192},
        {0, 192},
        3
    },
    {
        {1048576, -2949120, 327680},
        {1048576, -3276800, 0},
        {1048576, -2949120, 0},
        {63, 223},
        {32, 192},
        {32, 223},
        3
    },
    {
        {1048576, -2949120, 327680},
        {1048576, -3276800, 327680},
        {1048576, -3276800, 0},
        {63, 223},
        {63, 192},
        {32, 192},
        3
    },
    {
        {1048576, -2621440, 0},
        {1048576, -2949120, -327680},
        {1048576, -2621440, -327680},
        {31, 255},
        {0, 224},
        {0, 255},
        3
    },
    {
        {1048576, -2621440, 0},
        {1048576, -2949120, 0},
        {1048576, -2949120, -327680},
        {31, 255},
        {31, 224},
        {0, 224},
        3
    },
    {
        {1048576, -2621440, 327680},
        {1048576, -2949120, 0},
        {1048576, -2621440, 0},
        {63, 255},
        {32, 224},
        {32, 255},
        3
    },
    {
        {1048576, -2621440, 327680},
        {1048576, -2949120, 327680},
        {1048576, -2949120, 0},
        {63, 255},
        {63, 224},
        {32, 224},
        3
    },
    {
        {1048576, -3604480, 0},
        {1048576, -3932160, -327680},
        {1048576, -3604480, -327680},
        {31, 159},
        {0, 128},
        {0, 159},
        3
    },
    {
        {1048576, -3604480, 0},
        {1048576, -3932160, 0},
        {1048576, -3932160, -327680},
        {31, 159},
        {31, 128},
        {0, 128},
        3
    },
    {
        {1048576, -3604480, 327680},
        {1048576, -3932160, 0},
        {1048576, -3604480, 0},
        {63, 159},
        {32, 128},
        {32, 159},
        3
    },
    {
        {1048576, -3604480, 327680},
        {1048576, -3932160, 327680},
        {1048576, -3932160, 0},
        {63, 159},
        {63, 128},
        {32, 128},
        3
    },
    {
        {1048576, -3276800, 0},
        {1048576, -3604480, -327680},
        {1048576, -3276800, -327680},
        {31, 191},
        {0, 160},
        {0, 191},
        3
    },
    {
        {1048576, -3276800, 0},
        {1048576, -3604480, 0},
        {1048576, -3604480, -327680},
        {31, 191},
        {31, 160},
        {0, 160},
        3
    },
    {
        {1048576, -3276800, 327680},
        {1048576, -3604480, 0},
        {1048576, -3276800, 0},
        {63, 191},
        {32, 160},
        {32, 191},
        3
    },
    {
        {1048576, -3276800, 327680},
        {1048576, -3604480, 327680},
        {1048576, -3604480, 0},
        {63, 191},
        {63, 160},
        {32, 160},
        3
    },
    {
        {1048576, -4259840, 0},
        {1048576, -4587520, -327680},
        {1048576, -4259840, -327680},
        {31, 95},
        {0, 64},
        {0, 95},
        3
    },
    {
        {1048576, -4259840, 0},
        {1048576, -4587520, 0},
        {1048576, -4587520, -327680},
        {31, 95},
        {31, 64},
        {0, 64},
        3
    },
    {
        {1048576, -4259840, 327680},
        {1048576, -4587520, 0},
        {1048576, -4259840, 0},
        {63, 95},
        {32, 64},
        {32, 95},
        3
    },
    {
        {1048576, -4259840, 327680},
        {1048576, -4587520, 327680},
        {1048576, -4587520, 0},
        {63, 95},
        {63, 64},
        {32, 64},
        3
    },
    {
        {1048576, -3932160, 0},
        {1048576, -4259840, -327680},
        {1048576, -3932160, -327680},
        {31, 127},
        {0, 96},
        {0, 127},
        3
    },
    {
        {1048576, -3932160, 0},
        {1048576, -4259840, 0},
        {1048576, -4259840, -327680},
        {31, 127},
        {31, 96},
        {0, 96},
        3
    },
    {
        {1048576, -3932160, 327680},
        {1048576, -4259840, 0},
        {1048576, -3932160, 0},
        {63, 127},
        {32, 96},
        {32, 127},
        3
    },
    {
        {1048576, -3932160, 327680},
        {1048576, -4259840, 327680},
        {1048576, -4259840, 0},
        {63, 127},
        {63, 96},
        {32, 96},
        3
    },
    {
        {-1048576, -2293760, 327680},
        {-1048576, -1966080, 0},
        {-1048576, -2293760, 0},
        {63, 32},
        {32, 63},
        {32, 32},
        3
    },
    {
        {-1048576, -2293760, 327680},
        {-1048576, -1966080, 327680},
        {-1048576, -1966080, 0},
        {63, 32},
        {63, 63},
        {32, 63},
        3
    },
    {
        {-1048576, -2293760, 0},
        {-1048576, -1966080, -327680},
        {-1048576, -2293760, -327680},
        {31, 32},
        {0, 63},
        {0, 32},
        3
    },
    {
        {-1048576, -2293760, 0},
        {-1048576, -1966080, 0},
        {-1048576, -1966080, -327680},
        {31, 32},
        {31, 63},
        {0, 63},
        3
    },
    {
        {-1048576, -2621440, 0},
        {-1048576, -2293760, -327680},
        {-1048576, -2621440, -327680},
        {31, 0},
        {0, 31},
        {0, 0},
        3
    },
    {
        {-1048576, -2621440, 0},
        {-1048576, -2293760, 0},
        {-1048576, -2293760, -327680},
        {31, 0},
        {31, 31},
        {0, 31},
        3
    },
    {
        {-1048576, -2949120, 0},
        {-1048576, -2621440, -327680},
        {-1048576, -2949120, -327680},
        {31, 224},
        {0, 255},
        {0, 224},
        3
    },
    {
        {-1048576, -2949120, 0},
        {-1048576, -2621440, 0},
        {-1048576, -2621440, -327680},
        {31, 224},
        {31, 255},
        {0, 255},
        3
    },
    {
        {-1048576, -3276800, 0},
        {-1048576, -2949120, -327680},
        {-1048576, -3276800, -327680},
        {31, 192},
        {0, 223},
        {0, 192},
        3
    },
    {
        {-1048576, -3276800, 0},
        {-1048576, -2949120, 0},
        {-1048576, -2949120, -327680},
        {31, 192},
        {31, 223},
        {0, 223},
        3
    },
    {
        {-1048576, -3604480, 0},
        {-1048576, -3276800, -327680},
        {-1048576, -3604480, -327680},
        {31, 160},
        {0, 191},
        {0, 160},
        3
    },
    {
        {-1048576, -3604480, 0},
        {-1048576, -3276800, 0},
        {-1048576, -3276800, -327680},
        {31, 160},
        {31, 191},
        {0, 191},
        3
    },
    {
        {-1048576, -3932160, 0},
        {-1048576, -3604480, -327680},
        {-1048576, -3932160, -327680},
        {31, 128},
        {0, 159},
        {0, 128},
        3
    },
    {
        {-1048576, -3932160, 0},
        {-1048576, -3604480, 0},
        {-1048576, -3604480, -327680},
        {31, 128},
        {31, 159},
        {0, 159},
        3
    },
    {
        {-1048576, -4259840, 0},
        {-1048576, -3932160, -327680},
        {-1048576, -4259840, -327680},
        {31, 96},
        {0, 127},
        {0, 96},
        3
    },
    {
        {-1048576, -4259840, 0},
        {-1048576, -3932160, 0},
        {-1048576, -3932160, -327680},
        {31, 96},
        {31, 127},
        {0, 127},
        3
    },
    {
        {-1048576, -4587520, 0},
        {-1048576, -4259840, -327680},
        {-1048576, -4587520, -327680},
        {31, 64},
        {0, 95},
        {0, 64},
        3
    },
    {
        {-1048576, -4587520, 0},
        {-1048576, -4259840, 0},
        {-1048576, -4259840, -327680},
        {31, 64},
        {31, 95},
        {0, 95},
        3
    },
    {
        {-1048576, -4587520, 327680},
        {-1048576, -4259840, 0},
        {-1048576, -4587520, 0},
        {63, 64},
        {32, 95},
        {32, 64},
        3
    },
    {
        {-1048576, -4587520, 327680},
        {-1048576, -4259840, 327680},
        {-1048576, -4259840, 0},
        {63, 64},
        {63, 95},
        {32, 95},
        3
    },
    {
        {-1048576, -4259840, 327680},
        {-1048576, -3932160, 0},
        {-1048576, -4259840, 0},
        {63, 96},
        {32, 127},
        {32, 96},
        3
    },
    {
        {-1048576, -4259840, 327680},
        {-1048576, -3932160, 327680},
        {-1048576, -3932160, 0},
        {63, 96},
        {63, 127},
        {32, 127},
        3
    },
    {
        {-1048576, -3932160, 327680},
        {-1048576, -3604480, 0},
        {-1048576, -3932160, 0},
        {63, 128},
        {32, 159},
        {32, 128},
        3
    },
    {
        {-1048576, -3932160, 327680},
        {-1048576, -3604480, 327680},
        {-1048576, -3604480, 0},
        {63, 128},
        {63, 159},
        {32, 159},
        3
    },
    {
        {-1048576, -3604480, 327680},
        {-1048576, -3276800, 0},
        {-1048576, -3604480, 0},
        {63, 160},
        {32, 191},
        {32, 160},
        3
    },
    {
        {-1048576, -3604480, 327680},
        {-1048576, -3276800, 327680},
        {-1048576, -3276800, 0},
        {63, 160},
        {63, 191},
        {32, 191},
        3
    },
    {
        {-1048576, -3276800, 327680},
        {-1048576, -2949120, 0},
        {-1048576, -3276800, 0},
        {63, 192},
        {32, 223},
        {32, 192},
        3
    },
    {
        {-1048576, -3276800, 327680},
        {-1048576, -2949120, 327680},
        {-1048576, -2949120, 0},
        {63, 192},
        {63, 223},
        {32, 223},
        3
    },
    {
        {-1048576, -2949120, 327680},
        {-1048576, -2621440, 0},
        {-1048576, -2949120, 0},
        {63, 224},
        {32, 255},
        {32, 224},
        3
    },
    {
        {-1048576, -2949120, 327680},
        {-1048576, -2621440, 327680},
        {-1048576, -2621440, 0},
        {63, 224},
        {63, 255},
        {32, 255},
        3
    },
    {
        {-1048576, -2621440, 327680},
        {-1048576, -2293760, 0},
        {-1048576, -2621440, 0},
        {63, 0},
        {32, 31},
        {32, 0},
        3
    },
    {
        {-1048576, -2621440, 327680},
        {-1048576, -2293760, 327680},
        {-1048576, -2293760, 0},
        {63, 0},
        {63, 31},
        {32, 31},
        3
    },
    {
        {327680, -983040, -983040},
        {0, -1310720, -983040},
        {0, -983040, -983040},
        {128, 31},
        {159, 0},
        {128, 0},
        7
    },
    {
        {327680, -983040, -983040},
        {327680, -1310720, -983040},
        {0, -1310720, -983040},
        {128, 31},
        {159, 31},
        {159, 0},
        7
    },
    {
        {0, -983040, -983040},
        {-327680, -1310720, -983040},
        {-327680, -983040, -983040},
        {128, 255},
        {159, 224},
        {128, 224},
        7
    },
    {
        {0, -983040, -983040},
        {0, -1310720, -983040},
        {-327680, -1310720, -983040},
        {128, 255},
        {159, 255},
        {159, 224},
        7
    },
    {
        {327680, -655360, -983040},
        {0, -983040, -983040},
        {0, -655360, -983040},
        {64, 31},
        {95, 0},
        {64, 0},
        7
    },
    {
        {327680, -655360, -983040},
        {327680, -983040, -983040},
        {0, -983040, -983040},
        {64, 31},
        {95, 31},
        {95, 0},
        7
    },
    {
        {0, -655360, -983040},
        {-327680, -983040, -983040},
        {-327680, -655360, -983040},
        {64, 255},
        {95, 224},
        {64, 224},
        7
    },
    {
        {0, -655360, -983040},
        {0, -983040, -983040},
        {-327680, -983040, -983040},
        {64, 255},
        {95, 255},
        {95, 224},
        7
    },
    {
        {327680, -1638400, -983040},
        {0, -1966080, -983040},
        {0, -1638400, -983040},
        {63, 95},
        {32, 64},
        {32, 95},
        16
    },
    {
        {327680, -1638400, -983040},
        {327680, -1966080, -983040},
        {0, -1966080, -983040},
        {63, 95},
        {63, 64},
        {32, 64},
        16
    },
    {
        {0, -1638400, -983040},
        {-327680, -1966080, -983040},
        {-327680, -1638400, -983040},
        {31, 95},
        {0, 64},
        {0, 95},
        16
    },
    {
        {0, -1638400, -983040},
        {0, -1966080, -983040},
        {-327680, -1966080, -983040},
        {31, 95},
        {31, 64},
        {0, 64},
        16
    },
    {
        {0, -1310720, -983040},
        {-327680, -1638400, -983040},
        {-327680, -1310720, -983040},
        {31, 127},
        {0, 96},
        {0, 127},
        0
    },
    {
        {0, -1310720, -983040},
        {0, -1638400, -983040},
        {-327680, -1638400, -983040},
        {31, 127},
        {31, 96},
        {0, 96},
        0
    },
    {
        {327680, -1310720, -983040},
        {0, -1638400, -983040},
        {0, -1310720, -983040},
        {63, 127},
        {32, 96},
        {32, 127},
        0
    },
    {
        {327680, -1310720, -983040},
        {327680, -1638400, -983040},
        {0, -1638400, -983040},
        {63, 127},
        {63, 96},
        {32, 96},
        0
    },
    {
        {327680, -1966080, -983040},
        {0, -2293760, -983040},
        {0, -1966080, -983040},
        {63, 63},
        {32, 32},
        {32, 63},
        3
    },
    {
        {327680, -1966080, -983040},
        {327680, -2293760, -983040},
        {0, -2293760, -983040},
        {63, 63},
        {63, 32},
        {32, 32},
        3
    },
    {
        {0, -1966080, -983040},
        {-327680, -2293760, -983040},
        {-327680, -1966080, -983040},
        {31, 63},
        {0, 32},
        {0, 63},
        3
    },
    {
        {0, -1966080, -983040},
        {0, -2293760, -983040},
        {-327680, -2293760, -983040},
        {31, 63},
        {31, 32},
        {0, 32},
        3
    },
    {
        {0, -2293760, -983040},
        {-327680, -2621440, -983040},
        {-327680, -2293760, -983040},
        {31, 31},
        {0, 0},
        {0, 31},
        3
    },
    {
        {0, -2293760, -983040},
        {0, -2621440, -983040},
        {-327680, -2621440, -983040},
        {31, 31},
        {31, 0},
        {0, 0},
        3
    },
    {
        {327680, -2293760, -983040},
        {0, -2621440, -983040},
        {0, -2293760, -983040},
        {63, 31},
        {32, 0},
        {32, 31},
        3
    },
    {
        {327680, -2293760, -983040},
        {327680, -2621440, -983040},
        {0, -2621440, -983040},
        {63, 31},
        {63, 0},
        {32, 0},
        3
    },
    {
        {0, -2621440, -983040},
        {-327680, -2949120, -983040},
        {-327680, -2621440, -983040},
        {31, 255},
        {0, 224},
        {0, 255},
        3
    },
    {
        {0, -2621440, -983040},
        {0, -2949120, -983040},
        {-327680, -2949120, -983040},
        {31, 255},
        {31, 224},
        {0, 224},
        3
    },
    {
        {327680, -2949120, -983040},
        {0, -3276800, -983040},
        {0, -2949120, -983040},
        {63, 223},
        {32, 192},
        {32, 223},
        3
    },
    {
        {327680, -2949120, -983040},
        {327680, -3276800, -983040},
        {0, -3276800, -983040},
        {63, 223},
        {63, 192},
        {32, 192},
        3
    },
    {
        {0, -2949120, -983040},
        {-327680, -3276800, -983040},
        {-327680, -2949120, -983040},
        {31, 223},
        {0, 192},
        {0, 223},
        3
    },
    {
        {0, -2949120, -983040},
        {0, -3276800, -983040},
        {-327680, -3276800, -983040},
        {31, 223},
        {31, 192},
        {0, 192},
        3
    },
    {
        {327680, -2621440, -983040},
        {0, -2949120, -983040},
        {0, -2621440, -983040},
        {63, 255},
        {32, 224},
        {32, 255},
        3
    },
    {
        {327680, -2621440, -983040},
        {327680, -2949120, -983040},
        {0, -2949120, -983040},
        {63, 255},
        {63, 224},
        {32, 224},
        3
    },
    {
        {0, -3276800, -983040},
        {-327680, -3604480, -983040},
        {-327680, -3276800, -983040},
        {31, 191},
        {0, 160},
        {0, 191},
        3
    },
    {
        {0, -3276800, -983040},
        {0, -3604480, -983040},
        {-327680, -3604480, -983040},
        {31, 191},
        {31, 160},
        {0, 160},
        3
    },
    {
        {327680, -3604480, -983040},
        {0, -3932160, -983040},
        {0, -3604480, -983040},
        {63, 159},
        {32, 128},
        {32, 159},
        3
    },
    {
        {327680, -3604480, -983040},
        {327680, -3932160, -983040},
        {0, -3932160, -983040},
        {63, 159},
        {63, 128},
        {32, 128},
        3
    },
    {
        {0, -3604480, -983040},
        {-327680, -3932160, -983040},
        {-327680, -3604480, -983040},
        {31, 159},
        {0, 128},
        {0, 159},
        3
    },
    {
        {0, -3604480, -983040},
        {0, -3932160, -983040},
        {-327680, -3932160, -983040},
        {31, 159},
        {31, 128},
        {0, 128},
        3
    },
    {
        {327680, -3276800, -983040},
        {0, -3604480, -983040},
        {0, -3276800, -983040},
        {63, 191},
        {32, 160},
        {32, 191},
        3
    },
    {
        {327680, -3276800, -983040},
        {327680, -3604480, -983040},
        {0, -3604480, -983040},
        {63, 191},
        {63, 160},
        {32, 160},
        3
    },
    {
        {0, -3932160, -983040},
        {-327680, -4259840, -983040},
        {-327680, -3932160, -983040},
        {31, 127},
        {0, 96},
        {0, 127},
        3
    },
    {
        {0, -3932160, -983040},
        {0, -4259840, -983040},
        {-327680, -4259840, -983040},
        {31, 127},
        {31, 96},
        {0, 96},
        3
    },
    {
        {327680, -4259840, -983040},
        {0, -4587520, -983040},
        {0, -4259840, -983040},
        {63, 95},
        {32, 64},
        {32, 95},
        3
    },
    {
        {327680, -4259840, -983040},
        {327680, -4587520, -983040},
        {0, -4587520, -983040},
        {63, 95},
        {63, 64},
        {32, 64},
        3
    },
    {
        {0, -4259840, -983040},
        {-327680, -4587520, -983040},
        {-327680, -4259840, -983040},
        {31, 95},
        {0, 64},
        {0, 95},
        3
    },
    {
        {0, -4259840, -983040},
        {0, -4587520, -983040},
        {-327680, -4587520, -983040},
        {31, 95},
        {31, 64},
        {0, 64},
        3
    },
    {
        {327680, -3932160, -983040},
        {0, -4259840, -983040},
        {0, -3932160, -983040},
        {63, 127},
        {32, 96},
        {32, 127},
        3
    },
    {
        {327680, -3932160, -983040},
        {327680, -4259840, -983040},
        {0, -4259840, -983040},
        {63, 127},
        {63, 96},
        {32, 96},
        3
    },
    {
        {-655360, -1310720, -917504},
        {-688128, -1638400, -983040},
        {-688128, -1310720, -983040},
        {15, 191},
        {0, 112},
        {0, 191},
        11
    },
    {
        {-655360, -1310720, -917504},
        {-655360, -1638400, -917504},
        {-688128, -1638400, -983040},
        {15, 191},
        {15, 112},
        {0, 112},
        11
    },
    {
        {-327680, -1310720, -917504},
        {-655360, -1638400, -917504},
        {-655360, -1310720, -917504},
        {223, 127},
        {192, 96},
        {192, 127},
        4
    },
    {
        {-327680, -1310720, -917504},
        {-327680, -1638400, -917504},
        {-655360, -1638400, -917504},
        {223, 127},
        {223, 96},
        {192, 96},
        4
    },
    {
        {-327680, -1638400, -917504},
        {-327680, -1310720, -983040},
        {-327680, -1638400, -983040},
        {15, 112},
        {0, 191},
        {0, 112},
        11
    },
    {
        {-327680, -1638400, -917504},
        {-327680, -1310720, -917504},
        {-327680, -1310720, -983040},
        {15, 112},
        {15, 191},
        {0, 191},
        11
    },
    {
        {-655360, -1638400, -917504},
        {-688128, -1966080, -983040},
        {-688128, -1638400, -983040},
        {15, 111},
        {0, 32},
        {0, 111},
        11
    },
    {
        {-655360, -1638400, -917504},
        {-655360, -1966080, -917504},
        {-688128, -1966080, -983040},
        {15, 111},
        {15, 32},
        {0, 32},
        11
    },
    {
        {-327680, -1638400, -917504},
        {-655360, -1966080, -917504},
        {-655360, -1638400, -917504},
        {223, 95},
        {192, 64},
        {192, 95},
        4
    },
    {
        {-327680, -1638400, -917504},
        {-327680, -1966080, -917504},
        {-655360, -1966080, -917504},
        {223, 95},
        {223, 64},
        {192, 64},
        4
    },
    {
        {-327680, -1966080, -917504},
        {-327680, -1638400, -983040},
        {-327680, -1966080, -983040},
        {15, 32},
        {0, 111},
        {0, 32},
        11
    },
    {
        {-327680, -1966080, -917504},
        {-327680, -1638400, -917504},
        {-327680, -1638400, -983040},
        {15, 32},
        {15, 111},
        {0, 111},
        11
    },
    {
        {327680, -1310720, -917504},
        {327680, -1638400, -983040},
        {327680, -1310720, -983040},
        {15, 191},
        {0, 112},
        {0, 191},
        11
    },
    {
        {327680, -1310720, -917504},
        {327680, -1638400, -917504},
        {327680, -1638400, -983040},
        {15, 191},
        {15, 112},
        {0, 112},
        11
    },
    {
        {655360, -1310720, -917504},
        {327680, -1638400, -917504},
        {327680, -1310720, -917504},
        {63, 127},
        {32, 96},
        {32, 127},
        4
    },
    {
        {655360, -1310720, -917504},
        {655360, -1638400, -917504},
        {327680, -1638400, -917504},
        {63, 127},
        {63, 96},
        {32, 96},
        4
    },
    {
        {655360, -1638400, -917504},
        {688128, -1310720, -983040},
        {688128, -1638400, -983040},
        {15, 112},
        {0, 191},
        {0, 112},
        11
    },
    {
        {655360, -1638400, -917504},
        {655360, -1310720, -917504},
        {688128, -1310720, -983040},
        {15, 112},
        {15, 191},
        {0, 191},
        11
    },
    {
        {327680, -1638400, -917504},
        {327680, -1966080, -983040},
        {327680, -1638400, -983040},
        {15, 111},
        {0, 32},
        {0, 111},
        11
    },
    {
        {327680, -1638400, -917504},
        {327680, -1966080, -917504},
        {327680, -1966080, -983040},
        {15, 111},
        {15, 32},
        {0, 32},
        11
    },
    {
        {655360, -1638400, -917504},
        {327680, -1966080, -917504},
        {327680, -1638400, -917504},
        {63, 95},
        {32, 64},
        {32, 95},
        4
    },
    {
        {655360, -1638400, -917504},
        {655360, -1966080, -917504},
        {327680, -1966080, -917504},
        {63, 95},
        {63, 64},
        {32, 64},
        4
    },
    {
        {655360, -1966080, -917504},
        {688128, -1638400, -983040},
        {688128, -1966080, -983040},
        {15, 32},
        {0, 111},
        {0, 32},
        11
    },
    {
        {655360, -1966080, -917504},
        {655360, -1638400, -917504},
        {688128, -1638400, -983040},
        {15, 32},
        {15, 111},
        {0, 111},
        11
    },
    {
        {-655360, -1966080, -917504},
        {-688128, -2293760, -983040},
        {-688128, -1966080, -983040},
        {15, 31},
        {0, 208},
        {0, 31},
        11
    },
    {
        {-655360, -1966080, -917504},
        {-655360, -2293760, -917504},
        {-688128, -2293760, -983040},
        {15, 31},
        {15, 208},
        {0, 208},
        11
    },
    {
        {-327680, -1966080, -917504},
        {-655360, -2293760, -917504},
        {-655360, -1966080, -917504},
        {223, 63},
        {192, 32},
        {192, 63},
        15
    },
    {
        {-327680, -1966080, -917504},
        {-327680, -2293760, -917504},
        {-655360, -2293760, -917504},
        {223, 63},
        {223, 32},
        {192, 32},
        15
    },
    {
        {-327680, -2293760, -917504},
        {-327680, -1966080, -983040},
        {-327680, -2293760, -983040},
        {15, 208},
        {0, 31},
        {0, 208},
        11
    },
    {
        {-327680, -2293760, -917504},
        {-327680, -1966080, -917504},
        {-327680, -1966080, -983040},
        {15, 208},
        {15, 31},
        {0, 31},
        11
    },
    {
        {-655360, -2293760, -917504},
        {-688128, -2621440, -983040},
        {-688128, -2293760, -983040},
        {15, 207},
        {0, 128},
        {0, 207},
        11
    },
    {
        {-655360, -2293760, -917504},
        {-655360, -2621440, -917504},
        {-688128, -2621440, -983040},
        {15, 207},
        {15, 128},
        {0, 128},
        11
    },
    {
        {-327680, -2293760, -917504},
        {-655360, -2621440, -917504},
        {-655360, -2293760, -917504},
        {223, 31},
        {192, 0},
        {192, 31},
        6
    },
    {
        {-327680, -2293760, -917504},
        {-327680, -2621440, -917504},
        {-655360, -2621440, -917504},
        {223, 31},
        {223, 0},
        {192, 0},
        6
    },
    {
        {-327680, -2621440, -917504},
        {-327680, -2293760, -983040},
        {-327680, -2621440, -983040},
        {15, 128},
        {0, 207},
        {0, 128},
        11
    },
    {
        {-327680, -2621440, -917504},
        {-327680, -2293760, -917504},
        {-327680, -2293760, -983040},
        {15, 128},
        {15, 207},
        {0, 207},
        11
    },
    {
        {-655360, -2621440, -917504},
        {-688128, -2949120, -983040},
        {-688128, -2621440, -983040},
        {15, 127},
        {0, 48},
        {0, 127},
        11
    },
    {
        {-655360, -2621440, -917504},
        {-655360, -2949120, -917504},
        {-688128, -2949120, -983040},
        {15, 127},
        {15, 48},
        {0, 48},
        11
    },
    {
        {-327680, -2621440, -917504},
        {-655360, -2949120, -917504},
        {-655360, -2621440, -917504},
        {223, 255},
        {192, 224},
        {192, 255},
        6
    },
    {
        {-327680, -2621440, -917504},
        {-327680, -2949120, -917504},
        {-655360, -2949120, -917504},
        {223, 255},
        {223, 224},
        {192, 224},
        6
    },
    {
        {-327680, -2949120, -917504},
        {-327680, -2621440, -983040},
        {-327680, -2949120, -983040},
        {15, 48},
        {0, 127},
        {0, 48},
        11
    },
    {
        {-327680, -2949120, -917504},
        {-327680, -2621440, -917504},
        {-327680, -2621440, -983040},
        {15, 48},
        {15, 127},
        {0, 127},
        11
    },
    {
        {-655360, -2949120, -917504},
        {-688128, -3276800, -983040},
        {-688128, -2949120, -983040},
        {15, 47},
        {0, 224},
        {0, 47},
        11
    },
    {
        {-655360, -2949120, -917504},
        {-655360, -3276800, -917504},
        {-688128, -3276800, -983040},
        {15, 47},
        {15, 224},
        {0, 224},
        11
    },
    {
        {-327680, -2949120, -917504},
        {-655360, -3276800, -917504},
        {-655360, -2949120, -917504},
        {223, 223},
        {192, 192},
        {192, 223},
        9
    },
    {
        {-327680, -2949120, -917504},
        {-327680, -3276800, -917504},
        {-655360, -3276800, -917504},
        {223, 223},
        {223, 192},
        {192, 192},
        9
    },
    {
        {-327680, -3276800, -917504},
        {-327680, -2949120, -983040},
        {-327680, -3276800, -983040},
        {15, 224},
        {0, 47},
        {0, 224},
        11
    },
    {
        {-327680, -3276800, -917504},
        {-327680, -2949120, -917504},
        {-327680, -2949120, -983040},
        {15, 224},
        {15, 47},
        {0, 47},
        11
    },
    {
        {327680, -2949120, -917504},
        {327680, -3276800, -983040},
        {327680, -2949120, -983040},
        {15, 47},
        {0, 224},
        {0, 47},
        11
    },
    {
        {327680, -2949120, -917504},
        {327680, -3276800, -917504},
        {327680, -3276800, -983040},
        {15, 47},
        {15, 224},
        {0, 224},
        11
    },
    {
        {655360, -2949120, -917504},
        {327680, -3276800, -917504},
        {327680, -2949120, -917504},
        {63, 223},
        {32, 192},
        {32, 223},
        9
    },
    {
        {655360, -2949120, -917504},
        {655360, -3276800, -917504},
        {327680, -3276800, -917504},
        {63, 223},
        {63, 192},
        {32, 192},
        9
    },
    {
        {655360, -3276800, -917504},
        {688128, -2949120, -983040},
        {688128, -3276800, -983040},
        {15, 224},
        {0, 47},
        {0, 224},
        11
    },
    {
        {655360, -3276800, -917504},
        {655360, -2949120, -917504},
        {688128, -2949120, -983040},
        {15, 224},
        {15, 47},
        {0, 47},
        11
    },
    {
        {327680, -1966080, -917504},
        {327680, -2293760, -983040},
        {327680, -1966080, -983040},
        {31, 31},
        {16, 208},
        {16, 31},
        11
    },
    {
        {327680, -1966080, -917504},
        {327680, -2293760, -917504},
        {327680, -2293760, -983040},
        {31, 31},
        {31, 208},
        {16, 208},
        11
    },
    {
        {655360, -1966080, -917504},
        {327680, -2293760, -917504},
        {327680, -1966080, -917504},
        {63, 63},
        {32, 32},
        {32, 63},
        15
    },
    {
        {655360, -1966080, -917504},
        {655360, -2293760, -917504},
        {327680, -2293760, -917504},
        {63, 63},
        {63, 32},
        {32, 32},
        15
    },
    {
        {655360, -2293760, -917504},
        {688128, -1966080, -983040},
        {688128, -2293760, -983040},
        {15, 208},
        {0, 31},
        {0, 208},
        11
    },
    {
        {655360, -2293760, -917504},
        {655360, -1966080, -917504},
        {688128, -1966080, -983040},
        {15, 208},
        {15, 31},
        {0, 31},
        11
    },
    {
        {327680, -2293760, -917504},
        {327680, -2621440, -983040},
        {327680, -2293760, -983040},
        {15, 207},
        {0, 128},
        {0, 207},
        11
    },
    {
        {327680, -2293760, -917504},
        {327680, -2621440, -917504},
        {327680, -2621440, -983040},
        {15, 207},
        {15, 128},
        {0, 128},
        11
    },
    {
        {655360, -2293760, -917504},
        {327680, -2621440, -917504},
        {327680, -2293760, -917504},
        {63, 31},
        {32, 0},
        {32, 31},
        6
    },
    {
        {655360, -2293760, -917504},
        {655360, -2621440, -917504},
        {327680, -2621440, -917504},
        {63, 31},
        {63, 0},
        {32, 0},
        6
    },
    {
        {655360, -2621440, -917504},
        {688128, -2293760, -983040},
        {688128, -2621440, -983040},
        {15, 128},
        {0, 207},
        {0, 128},
        11
    },
    {
        {655360, -2621440, -917504},
        {655360, -2293760, -917504},
        {688128, -2293760, -983040},
        {15, 128},
        {15, 207},
        {0, 207},
        11
    },
    {
        {327680, -2621440, -917504},
        {327680, -2949120, -983040},
        {327680, -2621440, -983040},
        {15, 127},
        {0, 48},
        {0, 127},
        11
    },
    {
        {327680, -2621440, -917504},
        {327680, -2949120, -917504},
        {327680, -2949120, -983040},
        {15, 127},
        {15, 48},
        {0, 48},
        11
    },
    {
        {655360, -2621440, -917504},
        {327680, -2949120, -917504},
        {327680, -2621440, -917504},
        {63, 255},
        {32, 224},
        {32, 255},
        6
    },
    {
        {655360, -2621440, -917504},
        {655360, -2949120, -917504},
        {327680, -2949120, -917504},
        {63, 255},
        {63, 224},
        {32, 224},
        6
    },
    {
        {655360, -2949120, -917504},
        {688128, -2621440, -983040},
        {688128, -2949120, -983040},
        {15, 48},
        {0, 127},
        {0, 48},
        11
    },
    {
        {655360, -2949120, -917504},
        {655360, -2621440, -917504},
        {688128, -2621440, -983040},
        {15, 48},
        {15, 127},
        {0, 127},
        11
    },
    {
        {327680, -3604480, -917504},
        {327680, -3932160, -983040},
        {327680, -3604480, -983040},
        {15, 143},
        {0, 64},
        {0, 143},
        11
    },
    {
        {327680, -3604480, -917504},
        {327680, -3932160, -917504},
        {327680, -3932160, -983040},
        {15, 143},
        {15, 64},
        {0, 64},
        11
    },
    {
        {655360, -3604480, -917504},
        {327680, -3932160, -917504},
        {327680, -3604480, -917504},
        {63, 159},
        {32, 128},
        {32, 159},
        4
    },
    {
        {655360, -3604480, -917504},
        {655360, -3932160, -917504},
        {327680, -3932160, -917504},
        {63, 159},
        {63, 128},
        {32, 128},
        4
    },
    {
        {655360, -3932160, -917504},
        {688128, -3604480, -983040},
        {688128, -3932160, -983040},
        {15, 64},
        {0, 143},
        {0, 64},
        11
    },
    {
        {655360, -3932160, -917504},
        {655360, -3604480, -917504},
        {688128, -3604480, -983040},
        {15, 64},
        {15, 143},
        {0, 143},
        11
    },
    {
        {327680, -3276800, -917504},
        {327680, -3604480, -983040},
        {327680, -3276800, -983040},
        {15, 223},
        {0, 144},
        {0, 223},
        11
    },
    {
        {327680, -3276800, -917504},
        {327680, -3604480, -917504},
        {327680, -3604480, -983040},
        {15, 223},
        {15, 144},
        {0, 144},
        11
    },
    {
        {655360, -3276800, -917504},
        {327680, -3604480, -917504},
        {327680, -3276800, -917504},
        {63, 191},
        {32, 160},
        {32, 191},
        4
    },
    {
        {655360, -3276800, -917504},
        {655360, -3604480, -917504},
        {327680, -3604480, -917504},
        {63, 191},
        {63, 160},
        {32, 160},
        4
    },
    {
        {655360, -3604480, -917504},
        {688128, -3276800, -983040},
        {688128, -3604480, -983040},
        {15, 144},
        {0, 223},
        {0, 144},
        11
    },
    {
        {655360, -3604480, -917504},
        {655360, -3276800, -917504},
        {688128, -3276800, -983040},
        {15, 144},
        {15, 223},
        {0, 223},
        11
    },
    {
        {327680, -4259840, -917504},
        {327680, -4587520, -983040},
        {327680, -4259840, -983040},
        {15, 239},
        {0, 160},
        {0, 239},
        11
    },
    {
        {327680, -4259840, -917504},
        {327680, -4587520, -917504},
        {327680, -4587520, -983040},
        {15, 239},
        {15, 160},
        {0, 160},
        11
    },
    {
        {655360, -4259840, -917504},
        {327680, -4587520, -917504},
        {327680, -4259840, -917504},
        {63, 95},
        {32, 64},
        {32, 95},
        4
    },
    {
        {655360, -4259840, -917504},
        {655360, -4587520, -917504},
        {327680, -4587520, -917504},
        {63, 95},
        {63, 64},
        {32, 64},
        4
    },
    {
        {655360, -4587520, -917504},
        {688128, -4259840, -983040},
        {688128, -4587520, -983040},
        {15, 160},
        {0, 239},
        {0, 160},
        11
    },
    {
        {655360, -4587520, -917504},
        {655360, -4259840, -917504},
        {688128, -4259840, -983040},
        {15, 160},
        {15, 239},
        {0, 239},
        11
    },
    {
        {327680, -3932160, -917504},
        {327680, -4259840, -983040},
        {327680, -3932160, -983040},
        {15, 63},
        {0, 240},
        {0, 63},
        11
    },
    {
        {327680, -3932160, -917504},
        {327680, -4259840, -917504},
        {327680, -4259840, -983040},
        {15, 63},
        {15, 240},
        {0, 240},
        11
    },
    {
        {655360, -3932160, -917504},
        {327680, -4259840, -917504},
        {327680, -3932160, -917504},
        {63, 127},
        {32, 96},
        {32, 127},
        4
    },
    {
        {655360, -3932160, -917504},
        {655360, -4259840, -917504},
        {327680, -4259840, -917504},
        {63, 127},
        {63, 96},
        {32, 96},
        4
    },
    {
        {655360, -4259840, -917504},
        {688128, -3932160, -983040},
        {688128, -4259840, -983040},
        {15, 240},
        {0, 63},
        {0, 240},
        11
    },
    {
        {655360, -4259840, -917504},
        {655360, -3932160, -917504},
        {688128, -3932160, -983040},
        {15, 240},
        {15, 63},
        {0, 63},
        11
    },
    {
        {-655360, -3604480, -917504},
        {-688128, -3932160, -983040},
        {-688128, -3604480, -983040},
        {15, 143},
        {0, 64},
        {0, 143},
        11
    },
    {
        {-655360, -3604480, -917504},
        {-655360, -3932160, -917504},
        {-688128, -3932160, -983040},
        {15, 143},
        {15, 64},
        {0, 64},
        11
    },
    {
        {-327680, -3604480, -917504},
        {-655360, -3932160, -917504},
        {-655360, -3604480, -917504},
        {223, 159},
        {192, 128},
        {192, 159},
        4
    },
    {
        {-327680, -3604480, -917504},
        {-327680, -3932160, -917504},
        {-655360, -3932160, -917504},
        {223, 159},
        {223, 128},
        {192, 128},
        4
    },
    {
        {-327680, -3932160, -917504},
        {-327680, -3604480, -983040},
        {-327680, -3932160, -983040},
        {15, 64},
        {0, 143},
        {0, 64},
        11
    },
    {
        {-327680, -3932160, -917504},
        {-327680, -3604480, -917504},
        {-327680, -3604480, -983040},
        {15, 64},
        {15, 143},
        {0, 143},
        11
    },
    {
        {-655360, -3276800, -917504},
        {-688128, -3604480, -983040},
        {-688128, -3276800, -983040},
        {15, 223},
        {0, 144},
        {0, 223},
        11
    },
    {
        {-655360, -3276800, -917504},
        {-655360, -3604480, -917504},
        {-688128, -3604480, -983040},
        {15, 223},
        {15, 144},
        {0, 144},
        11
    },
    {
        {-327680, -3276800, -917504},
        {-655360, -3604480, -917504},
        {-655360, -3276800, -917504},
        {223, 191},
        {192, 160},
        {192, 191},
        4
    },
    {
        {-327680, -3276800, -917504},
        {-327680, -3604480, -917504},
        {-655360, -3604480, -917504},
        {223, 191},
        {223, 160},
        {192, 160},
        4
    },
    {
        {-327680, -3604480, -917504},
        {-327680, -3276800, -983040},
        {-327680, -3604480, -983040},
        {15, 144},
        {0, 223},
        {0, 144},
        11
    },
    {
        {-327680, -3604480, -917504},
        {-327680, -3276800, -917504},
        {-327680, -3276800, -983040},
        {15, 144},
        {15, 223},
        {0, 223},
        11
    },
    {
        {-655360, -4259840, -917504},
        {-688128, -4587520, -983040},
        {-688128, -4259840, -983040},
        {15, 239},
        {0, 160},
        {0, 239},
        11
    },
    {
        {-655360, -4259840, -917504},
        {-655360, -4587520, -917504},
        {-688128, -4587520, -983040},
        {15, 239},
        {15, 160},
        {0, 160},
        11
    },
    {
        {-327680, -4259840, -917504},
        {-655360, -4587520, -917504},
        {-655360, -4259840, -917504},
        {223, 95},
        {192, 64},
        {192, 95},
        4
    },
    {
        {-327680, -4259840, -917504},
        {-327680, -4587520, -917504},
        {-655360, -4587520, -917504},
        {223, 95},
        {223, 64},
        {192, 64},
        4
    },
    {
        {-327680, -4587520, -917504},
        {-327680, -4259840, -983040},
        {-327680, -4587520, -983040},
        {15, 160},
        {0, 239},
        {0, 160},
        11
    },
    {
        {-327680, -4587520, -917504},
        {-327680, -4259840, -917504},
        {-327680, -4259840, -983040},
        {15, 160},
        {15, 239},
        {0, 239},
        11
    },
    {
        {-655360, -3932160, -917504},
        {-688128, -4259840, -983040},
        {-688128, -3932160, -983040},
        {15, 63},
        {0, 240},
        {0, 63},
        11
    },
    {
        {-655360, -3932160, -917504},
        {-655360, -4259840, -917504},
        {-688128, -4259840, -983040},
        {15, 63},
        {15, 240},
        {0, 240},
        11
    },
    {
        {-327680, -3932160, -917504},
        {-655360, -4259840, -917504},
        {-655360, -3932160, -917504},
        {223, 127},
        {192, 96},
        {192, 127},
        4
    },
    {
        {-327680, -3932160, -917504},
        {-327680, -4259840, -917504},
        {-655360, -4259840, -917504},
        {223, 127},
        {223, 96},
        {192, 96},
        4
    },
    {
        {-327680, -4259840, -917504},
        {-327680, -3932160, -983040},
        {-327680, -4259840, -983040},
        {15, 240},
        {0, 63},
        {0, 240},
        11
    },
    {
        {-327680, -4259840, -917504},
        {-327680, -3932160, -917504},
        {-327680, -3932160, -983040},
        {15, 240},
        {15, 63},
        {0, 63},
        11
    },
    {
        {327680, -4259840, 983040},
        {327680, -4587520, 917504},
        {327680, -4259840, 917504},
        {223, 239},
        {208, 160},
        {208, 239},
        11
    },
    {
        {327680, -4259840, 983040},
        {327680, -4587520, 983040},
        {327680, -4587520, 917504},
        {223, 239},
        {223, 160},
        {208, 160},
        11
    },
    {
        {655360, -4587520, 917504},
        {327680, -4259840, 917504},
        {327680, -4587520, 917504},
        {63, 64},
        {32, 95},
        {32, 64},
        4
    },
    {
        {655360, -4587520, 917504},
        {655360, -4259840, 917504},
        {327680, -4259840, 917504},
        {63, 64},
        {63, 95},
        {32, 95},
        4
    },
    {
        {688128, -4587520, 983040},
        {655360, -4259840, 917504},
        {655360, -4587520, 917504},
        {223, 160},
        {208, 239},
        {208, 160},
        11
    },
    {
        {688128, -4587520, 983040},
        {688128, -4259840, 983040},
        {655360, -4259840, 917504},
        {223, 160},
        {223, 239},
        {208, 239},
        11
    },
    {
        {327680, -3932160, 983040},
        {327680, -4259840, 917504},
        {327680, -3932160, 917504},
        {223, 63},
        {208, 240},
        {208, 63},
        11
    },
    {
        {327680, -3932160, 983040},
        {327680, -4259840, 983040},
        {327680, -4259840, 917504},
        {223, 63},
        {223, 240},
        {208, 240},
        11
    },
    {
        {655360, -4259840, 917504},
        {327680, -3932160, 917504},
        {327680, -4259840, 917504},
        {63, 96},
        {32, 127},
        {32, 96},
        4
    },
    {
        {655360, -4259840, 917504},
        {655360, -3932160, 917504},
        {327680, -3932160, 917504},
        {63, 96},
        {63, 127},
        {32, 127},
        4
    },
    {
        {688128, -4259840, 983040},
        {655360, -3932160, 917504},
        {655360, -4259840, 917504},
        {223, 240},
        {208, 63},
        {208, 240},
        11
    },
    {
        {688128, -4259840, 983040},
        {688128, -3932160, 983040},
        {655360, -3932160, 917504},
        {223, 240},
        {223, 63},
        {208, 63},
        11
    },
    {
        {327680, -3604480, 983040},
        {327680, -3932160, 917504},
        {327680, -3604480, 917504},
        {223, 143},
        {208, 64},
        {208, 143},
        11
    },
    {
        {327680, -3604480, 983040},
        {327680, -3932160, 983040},
        {327680, -3932160, 917504},
        {223, 143},
        {223, 64},
        {208, 64},
        11
    },
    {
        {655360, -3932160, 917504},
        {327680, -3604480, 917504},
        {327680, -3932160, 917504},
        {63, 128},
        {32, 159},
        {32, 128},
        4
    },
    {
        {655360, -3932160, 917504},
        {655360, -3604480, 917504},
        {327680, -3604480, 917504},
        {63, 128},
        {63, 159},
        {32, 159},
        4
    },
    {
        {688128, -3932160, 983040},
        {655360, -3604480, 917504},
        {655360, -3932160, 917504},
        {223, 64},
        {208, 143},
        {208, 64},
        11
    },
    {
        {688128, -3932160, 983040},
        {688128, -3604480, 983040},
        {655360, -3604480, 917504},
        {223, 64},
        {223, 143},
        {208, 143},
        11
    },
    {
        {327680, -3276800, 983040},
        {327680, -3604480, 917504},
        {327680, -3276800, 917504},
        {223, 223},
        {208, 144},
        {208, 223},
        11
    },
    {
        {327680, -3276800, 983040},
        {327680, -3604480, 983040},
        {327680, -3604480, 917504},
        {223, 223},
        {223, 144},
        {208, 144},
        11
    },
    {
        {655360, -3604480, 917504},
        {327680, -3276800, 917504},
        {327680, -3604480, 917504},
        {63, 160},
        {32, 191},
        {32, 160},
        4
    },
    {
        {655360, -3604480, 917504},
        {655360, -3276800, 917504},
        {327680, -3276800, 917504},
        {63, 160},
        {63, 191},
        {32, 191},
        4
    },
    {
        {688128, -3604480, 983040},
        {655360, -3276800, 917504},
        {655360, -3604480, 917504},
        {223, 144},
        {208, 223},
        {208, 144},
        11
    },
    {
        {688128, -3604480, 983040},
        {688128, -3276800, 983040},
        {655360, -3276800, 917504},
        {223, 144},
        {223, 223},
        {208, 223},
        11
    },
    {
        {327680, -2949120, 983040},
        {327680, -3276800, 917504},
        {327680, -2949120, 917504},
        {223, 47},
        {208, 224},
        {208, 47},
        11
    },
    {
        {327680, -2949120, 983040},
        {327680, -3276800, 983040},
        {327680, -3276800, 917504},
        {223, 47},
        {223, 224},
        {208, 224},
        11
    },
    {
        {655360, -3276800, 917504},
        {327680, -2949120, 917504},
        {327680, -3276800, 917504},
        {63, 192},
        {32, 223},
        {32, 192},
        9
    },
    {
        {655360, -3276800, 917504},
        {655360, -2949120, 917504},
        {327680, -2949120, 917504},
        {63, 192},
        {63, 223},
        {32, 223},
        9
    },
    {
        {688128, -3276800, 983040},
        {655360, -2949120, 917504},
        {655360, -3276800, 917504},
        {223, 224},
        {208, 47},
        {208, 224},
        11
    },
    {
        {688128, -3276800, 983040},
        {688128, -2949120, 983040},
        {655360, -2949120, 917504},
        {223, 224},
        {223, 47},
        {208, 47},
        11
    },
    {
        {327680, -2621440, 983040},
        {327680, -2949120, 917504},
        {327680, -2621440, 917504},
        {223, 127},
        {208, 48},
        {208, 127},
        11
    },
    {
        {327680, -2621440, 983040},
        {327680, -2949120, 983040},
        {327680, -2949120, 917504},
        {223, 127},
        {223, 48},
        {208, 48},
        11
    },
    {
        {655360, -2949120, 917504},
        {327680, -2621440, 917504},
        {327680, -2949120, 917504},
        {63, 224},
        {32, 255},
        {32, 224},
        6
    },
    {
        {655360, -2949120, 917504},
        {655360, -2621440, 917504},
        {327680, -2621440, 917504},
        {63, 224},
        {63, 255},
        {32, 255},
        6
    },
    {
        {688128, -2949120, 983040},
        {655360, -2621440, 917504},
        {655360, -2949120, 917504},
        {223, 48},
        {208, 127},
        {208, 48},
        11
    },
    {
        {688128, -2949120, 983040},
        {688128, -2621440, 983040},
        {655360, -2621440, 917504},
        {223, 48},
        {223, 127},
        {208, 127},
        11
    },
    {
        {327680, -2293760, 983040},
        {327680, -2621440, 917504},
        {327680, -2293760, 917504},
        {223, 207},
        {208, 128},
        {208, 207},
        11
    },
    {
        {327680, -2293760, 983040},
        {327680, -2621440, 983040},
        {327680, -2621440, 917504},
        {223, 207},
        {223, 128},
        {208, 128},
        11
    },
    {
        {655360, -2621440, 917504},
        {327680, -2293760, 917504},
        {327680, -2621440, 917504},
        {63, 0},
        {32, 31},
        {32, 0},
        6
    },
    {
        {655360, -2621440, 917504},
        {655360, -2293760, 917504},
        {327680, -2293760, 917504},
        {63, 0},
        {63, 31},
        {32, 31},
        6
    },
    {
        {688128, -2621440, 983040},
        {655360, -2293760, 917504},
        {655360, -2621440, 917504},
        {223, 128},
        {208, 207},
        {208, 128},
        11
    },
    {
        {688128, -2621440, 983040},
        {688128, -2293760, 983040},
        {655360, -2293760, 917504},
        {223, 128},
        {223, 207},
        {208, 207},
        11
    },
    {
        {327680, -1966080, 983040},
        {327680, -2293760, 917504},
        {327680, -1966080, 917504},
        {239, 31},
        {224, 208},
        {224, 31},
        11
    },
    {
        {327680, -1966080, 983040},
        {327680, -2293760, 983040},
        {327680, -2293760, 917504},
        {239, 31},
        {239, 208},
        {224, 208},
        11
    },
    {
        {655360, -2293760, 917504},
        {327680, -1966080, 917504},
        {327680, -2293760, 917504},
        {63, 32},
        {32, 63},
        {32, 32},
        15
    },
    {
        {655360, -2293760, 917504},
        {655360, -1966080, 917504},
        {327680, -1966080, 917504},
        {63, 32},
        {63, 63},
        {32, 63},
        15
    },
    {
        {688128, -2293760, 983040},
        {655360, -1966080, 917504},
        {655360, -2293760, 917504},
        {223, 208},
        {208, 31},
        {208, 208},
        11
    },
    {
        {688128, -2293760, 983040},
        {688128, -1966080, 983040},
        {655360, -1966080, 917504},
        {223, 208},
        {223, 31},
        {208, 31},
        11
    },
    {
        {327680, -1638400, 983040},
        {327680, -1966080, 917504},
        {327680, -1638400, 917504},
        {223, 111},
        {208, 32},
        {208, 111},
        11
    },
    {
        {327680, -1638400, 983040},
        {327680, -1966080, 983040},
        {327680, -1966080, 917504},
        {223, 111},
        {223, 32},
        {208, 32},
        11
    },
    {
        {655360, -1966080, 917504},
        {327680, -1638400, 917504},
        {327680, -1966080, 917504},
        {63, 64},
        {32, 95},
        {32, 64},
        4
    },
    {
        {655360, -1966080, 917504},
        {655360, -1638400, 917504},
        {327680, -1638400, 917504},
        {63, 64},
        {63, 95},
        {32, 95},
        4
    },
    {
        {688128, -1966080, 983040},
        {655360, -1638400, 917504},
        {655360, -1966080, 917504},
        {223, 32},
        {208, 111},
        {208, 32},
        11
    },
    {
        {688128, -1966080, 983040},
        {688128, -1638400, 983040},
        {655360, -1638400, 917504},
        {223, 32},
        {223, 111},
        {208, 111},
        11
    },
    {
        {327680, -1310720, 983040},
        {327680, -1638400, 917504},
        {327680, -1310720, 917504},
        {223, 191},
        {208, 112},
        {208, 191},
        11
    },
    {
        {327680, -1310720, 983040},
        {327680, -1638400, 983040},
        {327680, -1638400, 917504},
        {223, 191},
        {223, 112},
        {208, 112},
        11
    },
    {
        {655360, -1638400, 917504},
        {327680, -1310720, 917504},
        {327680, -1638400, 917504},
        {63, 96},
        {32, 127},
        {32, 96},
        4
    },
    {
        {655360, -1638400, 917504},
        {655360, -1310720, 917504},
        {327680, -1310720, 917504},
        {63, 96},
        {63, 127},
        {32, 127},
        4
    },
    {
        {688128, -1638400, 983040},
        {655360, -1310720, 917504},
        {655360, -1638400, 917504},
        {223, 112},
        {208, 191},
        {208, 112},
        11
    },
    {
        {688128, -1638400, 983040},
        {688128, -1310720, 983040},
        {655360, -1310720, 917504},
        {223, 112},
        {223, 191},
        {208, 191},
        11
    },
    {
        {327680, -983040, 983040},
        {327680, -1310720, 917504},
        {327680, -983040, 917504},
        {223, 15},
        {208, 192},
        {208, 15},
        11
    },
    {
        {327680, -983040, 983040},
        {327680, -1310720, 983040},
        {327680, -1310720, 917504},
        {223, 15},
        {223, 192},
        {208, 192},
        11
    },
    {
        {655360, -1310720, 917504},
        {327680, -983040, 917504},
        {327680, -1310720, 917504},
        {63, 128},
        {32, 159},
        {32, 128},
        9
    },
    {
        {655360, -1310720, 917504},
        {655360, -983040, 917504},
        {327680, -983040, 917504},
        {63, 128},
        {63, 159},
        {32, 159},
        9
    },
    {
        {688128, -1310720, 983040},
        {655360, -983040, 917504},
        {655360, -1310720, 917504},
        {223, 192},
        {208, 15},
        {208, 192},
        11
    },
    {
        {688128, -1310720, 983040},
        {688128, -983040, 983040},
        {655360, -983040, 917504},
        {223, 192},
        {223, 15},
        {208, 15},
        11
    },
    {
        {-688128, -4259840, 983040},
        {-655360, -4587520, 917504},
        {-655360, -4259840, 917504},
        {223, 239},
        {208, 160},
        {208, 239},
        11
    },
    {
        {-688128, -4259840, 983040},
        {-688128, -4587520, 983040},
        {-655360, -4587520, 917504},
        {223, 239},
        {223, 160},
        {208, 160},
        11
    },
    {
        {-327680, -4587520, 917504},
        {-655360, -4259840, 917504},
        {-655360, -4587520, 917504},
        {223, 64},
        {192, 95},
        {192, 64},
        4
    },
    {
        {-327680, -4587520, 917504},
        {-327680, -4259840, 917504},
        {-655360, -4259840, 917504},
        {223, 64},
        {223, 95},
        {192, 95},
        4
    },
    {
        {-327680, -4587520, 983040},
        {-327680, -4259840, 917504},
        {-327680, -4587520, 917504},
        {223, 160},
        {208, 239},
        {208, 160},
        11
    },
    {
        {-327680, -4587520, 983040},
        {-327680, -4259840, 983040},
        {-327680, -4259840, 917504},
        {223, 160},
        {223, 239},
        {208, 239},
        11
    },
    {
        {-688128, -3932160, 983040},
        {-655360, -4259840, 917504},
        {-655360, -3932160, 917504},
        {223, 63},
        {208, 240},
        {208, 63},
        11
    },
    {
        {-688128, -3932160, 983040},
        {-688128, -4259840, 983040},
        {-655360, -4259840, 917504},
        {223, 63},
        {223, 240},
        {208, 240},
        11
    },
    {
        {-327680, -4259840, 917504},
        {-655360, -3932160, 917504},
        {-655360, -4259840, 917504},
        {223, 96},
        {192, 127},
        {192, 96},
        4
    },
    {
        {-327680, -4259840, 917504},
        {-327680, -3932160, 917504},
        {-655360, -3932160, 917504},
        {223, 96},
        {223, 127},
        {192, 127},
        4
    },
    {
        {-327680, -4259840, 983040},
        {-327680, -3932160, 917504},
        {-327680, -4259840, 917504},
        {223, 240},
        {208, 63},
        {208, 240},
        11
    },
    {
        {-327680, -4259840, 983040},
        {-327680, -3932160, 983040},
        {-327680, -3932160, 917504},
        {223, 240},
        {223, 63},
        {208, 63},
        11
    },
    {
        {-688128, -3604480, 983040},
        {-655360, -3932160, 917504},
        {-655360, -3604480, 917504},
        {223, 143},
        {208, 64},
        {208, 143},
        11
    },
    {
        {-688128, -3604480, 983040},
        {-688128, -3932160, 983040},
        {-655360, -3932160, 917504},
        {223, 143},
        {223, 64},
        {208, 64},
        11
    },
    {
        {-327680, -3932160, 917504},
        {-655360, -3604480, 917504},
        {-655360, -3932160, 917504},
        {223, 128},
        {192, 159},
        {192, 128},
        4
    },
    {
        {-327680, -3932160, 917504},
        {-327680, -3604480, 917504},
        {-655360, -3604480, 917504},
        {223, 128},
        {223, 159},
        {192, 159},
        4
    },
    {
        {-327680, -3932160, 983040},
        {-327680, -3604480, 917504},
        {-327680, -3932160, 917504},
        {223, 64},
        {208, 143},
        {208, 64},
        11
    },
    {
        {-327680, -3932160, 983040},
        {-327680, -3604480, 983040},
        {-327680, -3604480, 917504},
        {223, 64},
        {223, 143},
        {208, 143},
        11
    },
    {
        {-688128, -3276800, 983040},
        {-655360, -3604480, 917504},
        {-655360, -3276800, 917504},
        {223, 223},
        {208, 144},
        {208, 223},
        11
    },
    {
        {-688128, -3276800, 983040},
        {-688128, -3604480, 983040},
        {-655360, -3604480, 917504},
        {223, 223},
        {223, 144},
        {208, 144},
        11
    },
    {
        {-327680, -3604480, 917504},
        {-655360, -3276800, 917504},
        {-655360, -3604480, 917504},
        {223, 160},
        {192, 191},
        {192, 160},
        4
    },
    {
        {-327680, -3604480, 917504},
        {-327680, -3276800, 917504},
        {-655360, -3276800, 917504},
        {223, 160},
        {223, 191},
        {192, 191},
        4
    },
    {
        {-327680, -3604480, 983040},
        {-327680, -3276800, 917504},
        {-327680, -3604480, 917504},
        {223, 144},
        {208, 223},
        {208, 144},
        11
    },
    {
        {-327680, -3604480, 983040},
        {-327680, -3276800, 983040},
        {-327680, -3276800, 917504},
        {223, 144},
        {223, 223},
        {208, 223},
        11
    },
    {
        {-688128, -2949120, 983040},
        {-655360, -3276800, 917504},
        {-655360, -2949120, 917504},
        {223, 47},
        {208, 224},
        {208, 47},
        11
    },
    {
        {-688128, -2949120, 983040},
        {-688128, -3276800, 983040},
        {-655360, -3276800, 917504},
        {223, 47},
        {223, 224},
        {208, 224},
        11
    },
    {
        {-327680, -3276800, 917504},
        {-655360, -2949120, 917504},
        {-655360, -3276800, 917504},
        {223, 192},
        {192, 223},
        {192, 192},
        9
    },
    {
        {-327680, -3276800, 917504},
        {-327680, -2949120, 917504},
        {-655360, -2949120, 917504},
        {223, 192},
        {223, 223},
        {192, 223},
        9
    },
    {
        {-327680, -3276800, 983040},
        {-327680, -2949120, 917504},
        {-327680, -3276800, 917504},
        {223, 224},
        {208, 47},
        {208, 224},
        11
    },
    {
        {-327680, -3276800, 983040},
        {-327680, -2949120, 983040},
        {-327680, -2949120, 917504},
        {223, 224},
        {223, 47},
        {208, 47},
        11
    },
    {
        {-688128, -2621440, 983040},
        {-655360, -2949120, 917504},
        {-655360, -2621440, 917504},
        {223, 127},
        {208, 48},
        {208, 127},
        11
    },
    {
        {-688128, -2621440, 983040},
        {-688128, -2949120, 983040},
        {-655360, -2949120, 917504},
        {223, 127},
        {223, 48},
        {208, 48},
        11
    },
    {
        {-327680, -2949120, 917504},
        {-655360, -2621440, 917504},
        {-655360, -2949120, 917504},
        {223, 224},
        {192, 255},
        {192, 224},
        6
    },
    {
        {-327680, -2949120, 917504},
        {-327680, -2621440, 917504},
        {-655360, -2621440, 917504},
        {223, 224},
        {223, 255},
        {192, 255},
        6
    },
    {
        {-327680, -2949120, 983040},
        {-327680, -2621440, 917504},
        {-327680, -2949120, 917504},
        {223, 48},
        {208, 127},
        {208, 48},
        11
    },
    {
        {-327680, -2949120, 983040},
        {-327680, -2621440, 983040},
        {-327680, -2621440, 917504},
        {223, 48},
        {223, 127},
        {208, 127},
        11
    },
    {
        {-688128, -2293760, 983040},
        {-655360, -2621440, 917504},
        {-655360, -2293760, 917504},
        {223, 207},
        {208, 128},
        {208, 207},
        11
    },
    {
        {-688128, -2293760, 983040},
        {-688128, -2621440, 983040},
        {-655360, -2621440, 917504},
        {223, 207},
        {223, 128},
        {208, 128},
        11
    },
    {
        {-327680, -2621440, 917504},
        {-655360, -2293760, 917504},
        {-655360, -2621440, 917504},
        {223, 0},
        {192, 31},
        {192, 0},
        6
    },
    {
        {-327680, -2621440, 917504},
        {-327680, -2293760, 917504},
        {-655360, -2293760, 917504},
        {223, 0},
        {223, 31},
        {192, 31},
        6
    },
    {
        {-327680, -2621440, 983040},
        {-327680, -2293760, 917504},
        {-327680, -2621440, 917504},
        {223, 128},
        {208, 207},
        {208, 128},
        11
    },
    {
        {-327680, -2621440, 983040},
        {-327680, -2293760, 983040},
        {-327680, -2293760, 917504},
        {223, 128},
        {223, 207},
        {208, 207},
        11
    },
    {
        {-688128, -1966080, 983040},
        {-655360, -2293760, 917504},
        {-655360, -1966080, 917504},
        {223, 31},
        {208, 208},
        {208, 31},
        11
    },
    {
        {-688128, -1966080, 983040},
        {-688128, -2293760, 983040},
        {-655360, -2293760, 917504},
        {223, 31},
        {223, 208},
        {208, 208},
        11
    },
    {
        {-327680, -2293760, 917504},
        {-655360, -1966080, 917504},
        {-655360, -2293760, 917504},
        {223, 32},
        {192, 63},
        {192, 32},
        15
    },
    {
        {-327680, -2293760, 917504},
        {-327680, -1966080, 917504},
        {-655360, -1966080, 917504},
        {223, 32},
        {223, 63},
        {192, 63},
        15
    },
    {
        {-327680, -2293760, 983040},
        {-327680, -1966080, 917504},
        {-327680, -2293760, 917504},
        {223, 208},
        {208, 31},
        {208, 208},
        11
    },
    {
        {-327680, -2293760, 983040},
        {-327680, -1966080, 983040},
        {-327680, -1966080, 917504},
        {223, 208},
        {223, 31},
        {208, 31},
        11
    },
    {
        {-688128, -1638400, 983040},
        {-655360, -1966080, 917504},
        {-655360, -1638400, 917504},
        {223, 111},
        {208, 32},
        {208, 111},
        11
    },
    {
        {-688128, -1638400, 983040},
        {-688128, -1966080, 983040},
        {-655360, -1966080, 917504},
        {223, 111},
        {223, 32},
        {208, 32},
        11
    },
    {
        {-327680, -1966080, 917504},
        {-655360, -1638400, 917504},
        {-655360, -1966080, 917504},
        {223, 64},
        {192, 95},
        {192, 64},
        4
    },
    {
        {-327680, -1966080, 917504},
        {-327680, -1638400, 917504},
        {-655360, -1638400, 917504},
        {223, 64},
        {223, 95},
        {192, 95},
        4
    },
    {
        {-327680, -1966080, 983040},
        {-327680, -1638400, 917504},
        {-327680, -1966080, 917504},
        {223, 32},
        {208, 111},
        {208, 32},
        11
    },
    {
        {-327680, -1966080, 983040},
        {-327680, -1638400, 983040},
        {-327680, -1638400, 917504},
        {223, 32},
        {223, 111},
        {208, 111},
        11
    },
    {
        {-688128, -1310720, 983040},
        {-655360, -1638400, 917504},
        {-655360, -1310720, 917504},
        {223, 191},
        {208, 112},
        {208, 191},
        11
    },
    {
        {-688128, -1310720, 983040},
        {-688128, -1638400, 983040},
        {-655360, -1638400, 917504},
        {223, 191},
        {223, 112},
        {208, 112},
        11
    },
    {
        {-327680, -1638400, 917504},
        {-655360, -1310720, 917504},
        {-655360, -1638400, 917504},
        {223, 96},
        {192, 127},
        {192, 96},
        4
    },
    {
        {-327680, -1638400, 917504},
        {-327680, -1310720, 917504},
        {-655360, -1310720, 917504},
        {223, 96},
        {223, 127},
        {192, 127},
        4
    },
    {
        {-327680, -1638400, 983040},
        {-327680, -1310720, 917504},
        {-327680, -1638400, 917504},
        {223, 112},
        {208, 191},
        {208, 112},
        11
    },
    {
        {-327680, -1638400, 983040},
        {-327680, -1310720, 983040},
        {-327680, -1310720, 917504},
        {223, 112},
        {223, 191},
        {208, 191},
        11
    },
    {
        {-688128, -983040, 983040},
        {-655360, -1310720, 917504},
        {-655360, -983040, 917504},
        {223, 15},
        {208, 192},
        {208, 15},
        11
    },
    {
        {-688128, -983040, 983040},
        {-688128, -1310720, 983040},
        {-655360, -1310720, 917504},
        {223, 15},
        {223, 192},
        {208, 192},
        11
    },
    {
        {-327680, -1310720, 917504},
        {-655360, -983040, 917504},
        {-655360, -1310720, 917504},
        {223, 128},
        {192, 159},
        {192, 128},
        9
    },
    {
        {-327680, -1310720, 917504},
        {-327680, -983040, 917504},
        {-655360, -983040, 917504},
        {223, 128},
        {223, 159},
        {192, 159},
        9
    },
    {
        {-327680, -1310720, 983040},
        {-327680, -983040, 917504},
        {-327680, -1310720, 917504},
        {223, 192},
        {208, 15},
        {208, 192},
        11
    },
    {
        {-327680, -1310720, 983040},
        {-327680, -983040, 983040},
        {-327680, -983040, 917504},
        {223, 192},
        {223, 15},
        {208, 15},
        11
    },
    {
        {-688128, -655360, 983040},
        {-655360, -983040, 917504},
        {-655360, -655360, 917504},
        {223, 95},
        {208, 16},
        {208, 95},
        11
    },
    {
        {-688128, -655360, 983040},
        {-688128, -983040, 983040},
        {-655360, -983040, 917504},
        {223, 95},
        {223, 16},
        {208, 16},
        11
    },
    {
        {-327680, -983040, 917504},
        {-655360, -655360, 917504},
        {-655360, -983040, 917504},
        {223, 160},
        {192, 191},
        {192, 160},
        6
    },
    {
        {-327680, -983040, 917504},
        {-327680, -655360, 917504},
        {-655360, -655360, 917504},
        {223, 160},
        {223, 191},
        {192, 191},
        6
    },
    {
        {-327680, -983040, 983040},
        {-327680, -655360, 917504},
        {-327680, -983040, 917504},
        {223, 16},
        {208, 95},
        {208, 16},
        11
    },
    {
        {-327680, -983040, 983040},
        {-327680, -655360, 983040},
        {-327680, -655360, 917504},
        {223, 16},
        {223, 95},
        {208, 95},
        11
    },
    {
        {-688128, -327680, 983040},
        {-655360, -655360, 917504},
        {-655360, -327680, 917504},
        {223, 175},
        {208, 96},
        {208, 175},
        11
    },
    {
        {-688128, -327680, 983040},
        {-688128, -655360, 983040},
        {-655360, -655360, 917504},
        {223, 175},
        {223, 96},
        {208, 96},
        11
    },
    {
        {-327680, -655360, 917504},
        {-655360, -327680, 917504},
        {-655360, -655360, 917504},
        {223, 192},
        {192, 223},
        {192, 192},
        6
    },
    {
        {-327680, -655360, 917504},
        {-327680, -327680, 917504},
        {-655360, -327680, 917504},
        {223, 192},
        {223, 223},
        {192, 223},
        6
    },
    {
        {-327680, -655360, 983040},
        {-327680, -327680, 917504},
        {-327680, -655360, 917504},
        {223, 96},
        {208, 175},
        {208, 96},
        11
    },
    {
        {-327680, -655360, 983040},
        {-327680, -327680, 983040},
        {-327680, -327680, 917504},
        {223, 96},
        {223, 175},
        {208, 175},
        11
    },
    {
        {-688128, 0, 983040},
        {-655360, -327680, 917504},
        {-655360, 0, 917504},
        {223, 255},
        {208, 176},
        {208, 255},
        11
    },
    {
        {-688128, 0, 983040},
        {-688128, -327680, 983040},
        {-655360, -327680, 917504},
        {223, 255},
        {223, 176},
        {208, 176},
        11
    },
    {
        {-327680, -327680, 917504},
        {-655360, 0, 917504},
        {-655360, -327680, 917504},
        {223, 224},
        {192, 255},
        {192, 224},
        15
    },
    {
        {-327680, -327680, 917504},
        {-327680, 0, 917504},
        {-655360, 0, 917504},
        {223, 224},
        {223, 255},
        {192, 255},
        15
    },
    {
        {-327680, -327680, 983040},
        {-327680, 0, 917504},
        {-327680, -327680, 917504},
        {223, 176},
        {208, 255},
        {208, 176},
        11
    },
    {
        {-327680, -327680, 983040},
        {-327680, 0, 983040},
        {-327680, 0, 917504},
        {223, 176},
        {223, 255},
        {208, 255},
        11
    },
    {
        {327680, 0, 983040},
        {327680, -327680, 917504},
        {327680, 0, 917504},
        {239, 255},
        {224, 176},
        {224, 255},
        11
    },
    {
        {327680, 0, 983040},
        {327680, -327680, 983040},
        {327680, -327680, 917504},
        {239, 255},
        {239, 176},
        {224, 176},
        11
    },
    {
        {655360, -327680, 917504},
        {327680, 0, 917504},
        {327680, -327680, 917504},
        {63, 224},
        {32, 255},
        {32, 224},
        15
    },
    {
        {655360, -327680, 917504},
        {655360, 0, 917504},
        {327680, 0, 917504},
        {63, 224},
        {63, 255},
        {32, 255},
        15
    },
    {
        {688128, -327680, 983040},
        {655360, 0, 917504},
        {655360, -327680, 917504},
        {223, 176},
        {208, 255},
        {208, 176},
        11
    },
    {
        {688128, -327680, 983040},
        {688128, 0, 983040},
        {655360, 0, 917504},
        {223, 176},
        {223, 255},
        {208, 255},
        11
    },
    {
        {327680, -327680, 983040},
        {327680, -655360, 917504},
        {327680, -327680, 917504},
        {223, 175},
        {208, 96},
        {208, 175},
        11
    },
    {
        {327680, -327680, 983040},
        {327680, -655360, 983040},
        {327680, -655360, 917504},
        {223, 175},
        {223, 96},
        {208, 96},
        11
    },
    {
        {655360, -655360, 917504},
        {327680, -327680, 917504},
        {327680, -655360, 917504},
        {63, 192},
        {32, 223},
        {32, 192},
        6
    },
    {
        {655360, -655360, 917504},
        {655360, -327680, 917504},
        {327680, -327680, 917504},
        {63, 192},
        {63, 223},
        {32, 223},
        6
    },
    {
        {688128, -655360, 983040},
        {655360, -327680, 917504},
        {655360, -655360, 917504},
        {223, 96},
        {208, 175},
        {208, 96},
        11
    },
    {
        {688128, -655360, 983040},
        {688128, -327680, 983040},
        {655360, -327680, 917504},
        {223, 96},
        {223, 175},
        {208, 175},
        11
    },
    {
        {327680, -655360, 983040},
        {327680, -983040, 917504},
        {327680, -655360, 917504},
        {223, 95},
        {208, 16},
        {208, 95},
        11
    },
    {
        {327680, -655360, 983040},
        {327680, -983040, 983040},
        {327680, -983040, 917504},
        {223, 95},
        {223, 16},
        {208, 16},
        11
    },
    {
        {655360, -983040, 917504},
        {327680, -655360, 917504},
        {327680, -983040, 917504},
        {63, 160},
        {32, 191},
        {32, 160},
        6
    },
    {
        {655360, -983040, 917504},
        {655360, -655360, 917504},
        {327680, -655360, 917504},
        {63, 160},
        {63, 191},
        {32, 191},
        6
    },
    {
        {688128, -983040, 983040},
        {655360, -655360, 917504},
        {655360, -983040, 917504},
        {223, 16},
        {208, 95},
        {208, 16},
        11
    },
    {
        {688128, -983040, 983040},
        {688128, -655360, 983040},
        {655360, -655360, 917504},
        {223, 16},
        {223, 95},
        {208, 95},
        11
    },
    {
        {327680, -1638400, 917504},
        {0, -1310720, 917504},
        {0, -1638400, 917504},
        {63, 96},
        {32, 127},
        {32, 96},
        0
    },
    {
        {327680, -1638400, 917504},
        {327680, -1310720, 917504},
        {0, -1310720, 917504},
        {63, 96},
        {63, 127},
        {32, 127},
        0
    },
    {
        {0, -1638400, 917504},
        {-327680, -1310720, 917504},
        {-327680, -1638400, 917504},
        {31, 96},
        {0, 127},
        {0, 96},
        0
    },
    {
        {0, -1638400, 917504},
        {0, -1310720, 917504},
        {-327680, -1310720, 917504},
        {31, 96},
        {31, 127},
        {0, 127},
        0
    },
    {
        {0, -1966080, 917504},
        {-327680, -1638400, 917504},
        {-327680, -1966080, 917504},
        {31, 64},
        {0, 95},
        {0, 64},
        16
    },
    {
        {0, -1966080, 917504},
        {0, -1638400, 917504},
        {-327680, -1638400, 917504},
        {31, 64},
        {31, 95},
        {0, 95},
        16
    },
    {
        {0, -2293760, 917504},
        {-327680, -1966080, 917504},
        {-327680, -2293760, 917504},
        {31, 32},
        {0, 63},
        {0, 32},
        3
    },
    {
        {0, -2293760, 917504},
        {0, -1966080, 917504},
        {-327680, -1966080, 917504},
        {31, 32},
        {31, 63},
        {0, 63},
        3
    },
    {
        {0, -2621440, 917504},
        {-327680, -2293760, 917504},
        {-327680, -2621440, 917504},
        {31, 0},
        {0, 31},
        {0, 0},
        3
    },
    {
        {0, -2621440, 917504},
        {0, -2293760, 917504},
        {-327680, -2293760, 917504},
        {31, 0},
        {31, 31},
        {0, 31},
        3
    },
    {
        {0, -2949120, 917504},
        {-327680, -2621440, 917504},
        {-327680, -2949120, 917504},
        {31, 224},
        {0, 255},
        {0, 224},
        3
    },
    {
        {0, -2949120, 917504},
        {0, -2621440, 917504},
        {-327680, -2621440, 917504},
        {31, 224},
        {31, 255},
        {0, 255},
        3
    },
    {
        {0, -3276800, 917504},
        {-327680, -2949120, 917504},
        {-327680, -3276800, 917504},
        {31, 192},
        {0, 223},
        {0, 192},
        3
    },
    {
        {0, -3276800, 917504},
        {0, -2949120, 917504},
        {-327680, -2949120, 917504},
        {31, 192},
        {31, 223},
        {0, 223},
        3
    },
    {
        {0, -3604480, 917504},
        {-327680, -3276800, 917504},
        {-327680, -3604480, 917504},
        {31, 160},
        {0, 191},
        {0, 160},
        3
    },
    {
        {0, -3604480, 917504},
        {0, -3276800, 917504},
        {-327680, -3276800, 917504},
        {31, 160},
        {31, 191},
        {0, 191},
        3
    },
    {
        {0, -3932160, 917504},
        {-327680, -3604480, 917504},
        {-327680, -3932160, 917504},
        {31, 128},
        {0, 159},
        {0, 128},
        3
    },
    {
        {0, -3932160, 917504},
        {0, -3604480, 917504},
        {-327680, -3604480, 917504},
        {31, 128},
        {31, 159},
        {0, 159},
        3
    },
    {
        {0, -4259840, 917504},
        {-327680, -3932160, 917504},
        {-327680, -4259840, 917504},
        {31, 96},
        {0, 127},
        {0, 96},
        3
    },
    {
        {0, -4259840, 917504},
        {0, -3932160, 917504},
        {-327680, -3932160, 917504},
        {31, 96},
        {31, 127},
        {0, 127},
        3
    },
    {
        {0, -4587520, 917504},
        {-327680, -4259840, 917504},
        {-327680, -4587520, 917504},
        {31, 64},
        {0, 95},
        {0, 64},
        3
    },
    {
        {0, -4587520, 917504},
        {0, -4259840, 917504},
        {-327680, -4259840, 917504},
        {31, 64},
        {31, 95},
        {0, 95},
        3
    },
    {
        {327680, -4587520, 917504},
        {0, -4259840, 917504},
        {0, -4587520, 917504},
        {63, 64},
        {32, 95},
        {32, 64},
        3
    },
    {
        {327680, -4587520, 917504},
        {327680, -4259840, 917504},
        {0, -4259840, 917504},
        {63, 64},
        {63, 95},
        {32, 95},
        3
    },
    {
        {327680, -4259840, 917504},
        {0, -3932160, 917504},
        {0, -4259840, 917504},
        {63, 96},
        {32, 127},
        {32, 96},
        3
    },
    {
        {327680, -4259840, 917504},
        {327680, -3932160, 917504},
        {0, -3932160, 917504},
        {63, 96},
        {63, 127},
        {32, 127},
        3
    },
    {
        {327680, -3932160, 917504},
        {0, -3604480, 917504},
        {0, -3932160, 917504},
        {63, 128},
        {32, 159},
        {32, 128},
        3
    },
    {
        {327680, -3932160, 917504},
        {327680, -3604480, 917504},
        {0, -3604480, 917504},
        {63, 128},
        {63, 159},
        {32, 159},
        3
    },
    {
        {327680, -3604480, 917504},
        {0, -3276800, 917504},
        {0, -3604480, 917504},
        {63, 160},
        {32, 191},
        {32, 160},
        3
    },
    {
        {327680, -3604480, 917504},
        {327680, -3276800, 917504},
        {0, -3276800, 917504},
        {63, 160},
        {63, 191},
        {32, 191},
        3
    },
    {
        {327680, -3276800, 917504},
        {0, -2949120, 917504},
        {0, -3276800, 917504},
        {63, 192},
        {32, 223},
        {32, 192},
        3
    },
    {
        {327680, -3276800, 917504},
        {327680, -2949120, 917504},
        {0, -2949120, 917504},
        {63, 192},
        {63, 223},
        {32, 223},
        3
    },
    {
        {327680, -2949120, 917504},
        {0, -2621440, 917504},
        {0, -2949120, 917504},
        {63, 224},
        {32, 255},
        {32, 224},
        3
    },
    {
        {327680, -2949120, 917504},
        {327680, -2621440, 917504},
        {0, -2621440, 917504},
        {63, 224},
        {63, 255},
        {32, 255},
        3
    },
    {
        {327680, -2621440, 917504},
        {0, -2293760, 917504},
        {0, -2621440, 917504},
        {63, 0},
        {32, 31},
        {32, 0},
        3
    },
    {
        {327680, -2621440, 917504},
        {327680, -2293760, 917504},
        {0, -2293760, 917504},
        {63, 0},
        {63, 31},
        {32, 31},
        3
    },
    {
        {327680, -2293760, 917504},
        {0, -1966080, 917504},
        {0, -2293760, 917504},
        {63, 32},
        {32, 63},
        {32, 32},
        3
    },
    {
        {327680, -2293760, 917504},
        {327680, -1966080, 917504},
        {0, -1966080, 917504},
        {63, 32},
        {63, 63},
        {32, 63},
        3
    },
    {
        {327680, -1966080, 917504},
        {0, -1638400, 917504},
        {0, -1966080, 917504},
        {63, 64},
        {32, 95},
        {32, 64},
        16
    },
    {
        {327680, -1966080, 917504},
        {327680, -1638400, 917504},
        {0, -1638400, 917504},
        {63, 64},
        {63, 95},
        {32, 95},
        16
    },
    {
        {229376, -458752, 983040},
        {-229376, 0, 983040},
        {-229376, -458752, 983040},
        {63, 192},
        {0, 255},
        {0, 192},
        8
    },
    {
        {229376, -458752, 983040},
        {229376, 0, 983040},
        {-229376, 0, 983040},
        {63, 192},
        {63, 255},
        {0, 255},
        8
    },
    {
        {-327680, 0, 983040},
        {-327680, -655360, 950272},
        {-327680, 0, 950272},
        {239, 255},
        {232, 96},
        {232, 255},
        11
    },
    {
        {-327680, 0, 983040},
        {-327680, -655360, 983040},
        {-327680, -655360, 950272},
        {239, 255},
        {239, 96},
        {232, 96},
        11
    },
    {
        {-229376, -655360, 950272},
        {-327680, 0, 950272},
        {-327680, -655360, 950272},
        {199, 96},
        {176, 255},
        {176, 96},
        11
    },
    {
        {-229376, -655360, 950272},
        {-229376, 0, 950272},
        {-327680, 0, 950272},
        {199, 96},
        {199, 255},
        {176, 255},
        11
    },
    {
        {-229376, 0, 950272},
        {-327680, 0, 983040},
        {-327680, 0, 950272},
        {199, 23},
        {176, 16},
        {176, 23},
        11
    },
    {
        {-229376, 0, 950272},
        {-229376, 0, 983040},
        {-327680, 0, 983040},
        {199, 23},
        {199, 16},
        {176, 16},
        11
    },
    {
        {-229376, -655360, 983040},
        {-327680, -655360, 950272},
        {-327680, -655360, 983040},
        {199, 16},
        {176, 23},
        {176, 16},
        11
    },
    {
        {-229376, -655360, 983040},
        {-229376, -655360, 950272},
        {-327680, -655360, 950272},
        {199, 16},
        {199, 23},
        {176, 23},
        11
    },
    {
        {-229376, 0, 983040},
        {-327680, -655360, 983040},
        {-327680, 0, 983040},
        {199, 255},
        {176, 96},
        {176, 255},
        11
    },
    {
        {-229376, 0, 983040},
        {-229376, -655360, 983040},
        {-327680, -655360, 983040},
        {199, 255},
        {199, 96},
        {176, 96},
        11
    },
    {
        {-229376, -655360, 983040},
        {-229376, 0, 950272},
        {-229376, -655360, 950272},
        {239, 96},
        {232, 255},
        {232, 96},
        11
    },
    {
        {-229376, -655360, 983040},
        {-229376, 0, 983040},
        {-229376, 0, 950272},
        {239, 96},
        {239, 255},
        {232, 255},
        11
    },
    {
        {229376, 0, 983040},
        {229376, -655360, 950272},
        {229376, 0, 950272},
        {239, 255},
        {232, 96},
        {232, 255},
        11
    },
    {
        {229376, 0, 983040},
        {229376, -655360, 983040},
        {229376, -655360, 950272},
        {239, 255},
        {239, 96},
        {232, 96},
        11
    },
    {
        {327680, -655360, 950272},
        {229376, 0, 950272},
        {229376, -655360, 950272},
        {79, 96},
        {56, 255},
        {56, 96},
        11
    },
    {
        {327680, -655360, 950272},
        {327680, 0, 950272},
        {229376, 0, 950272},
        {79, 96},
        {79, 255},
        {56, 255},
        11
    },
    {
        {327680, 0, 950272},
        {229376, 0, 983040},
        {229376, 0, 950272},
        {79, 23},
        {56, 16},
        {56, 23},
        11
    },
    {
        {327680, 0, 950272},
        {327680, 0, 983040},
        {229376, 0, 983040},
        {79, 23},
        {79, 16},
        {56, 16},
        11
    },
    {
        {327680, -655360, 983040},
        {229376, -655360, 950272},
        {229376, -655360, 983040},
        {79, 16},
        {56, 23},
        {56, 16},
        11
    },
    {
        {327680, -655360, 983040},
        {327680, -655360, 950272},
        {229376, -655360, 950272},
        {79, 16},
        {79, 23},
        {56, 23},
        11
    },
    {
        {327680, 0, 983040},
        {229376, -655360, 983040},
        {229376, 0, 983040},
        {79, 255},
        {56, 96},
        {56, 255},
        11
    },
    {
        {327680, 0, 983040},
        {327680, -655360, 983040},
        {229376, -655360, 983040},
        {79, 255},
        {79, 96},
        {56, 96},
        11
    },
    {
        {327680, -655360, 983040},
        {327680, 0, 950272},
        {327680, -655360, 950272},
        {239, 96},
        {232, 255},
        {232, 96},
        11
    },
    {
        {327680, -655360, 983040},
        {327680, 0, 983040},
        {327680, 0, 950272},
        {239, 96},
        {239, 255},
        {232, 255},
        11
    },
    {
        {229376, -655360, 983040},
        {-229376, -458752, 983040},
        {-229376, -655360, 983040},
        {31, 192},
        {0, 210},
        {0, 192},
        5
    },
    {
        {229376, -655360, 983040},
        {229376, -458752, 983040},
        {-229376, -458752, 983040},
        {31, 192},
        {31, 210},
        {0, 210},
        5
    },
    {
        {0, -688128, 1310720},
        {-327680, -688128, 983040},
        {-327680, -688128, 1310720},
        {255, 128},
        {224, 159},
        {224, 128},
        13
    },
    {
        {0, -688128, 1310720},
        {0, -688128, 983040},
        {-327680, -688128, 983040},
        {255, 128},
        {255, 159},
        {224, 159},
        13
    },
    {
        {327680, -688128, 1310720},
        {0, -688128, 983040},
        {0, -688128, 1310720},
        {31, 128},
        {0, 159},
        {0, 128},
        13
    },
    {
        {327680, -688128, 1310720},
        {327680, -688128, 983040},
        {0, -688128, 983040},
        {31, 128},
        {31, 159},
        {0, 159},
        13
    },
    {
        {0, -688128, 1638400},
        {-327680, -688128, 1310720},
        {-327680, -688128, 1638400},
        {255, 96},
        {224, 127},
        {224, 96},
        13
    },
    {
        {0, -688128, 1638400},
        {0, -688128, 1310720},
        {-327680, -688128, 1310720},
        {255, 96},
        {255, 127},
        {224, 127},
        13
    },
    {
        {327680, -688128, 1638400},
        {0, -688128, 1310720},
        {0, -688128, 1638400},
        {31, 96},
        {0, 127},
        {0, 96},
        13
    },
    {
        {327680, -688128, 1638400},
        {327680, -688128, 1310720},
        {0, -688128, 1310720},
        {31, 96},
        {31, 127},
        {0, 127},
        13
    },
    {
        {0, -688128, 2293760},
        {-327680, -688128, 1966080},
        {-327680, -688128, 2293760},
        {255, 32},
        {224, 63},
        {224, 32},
        13
    },
    {
        {0, -688128, 2293760},
        {0, -688128, 1966080},
        {-327680, -688128, 1966080},
        {255, 32},
        {255, 63},
        {224, 63},
        13
    },
    {
        {327680, -688128, 2293760},
        {0, -688128, 1966080},
        {0, -688128, 2293760},
        {31, 32},
        {0, 63},
        {0, 32},
        13
    },
    {
        {327680, -688128, 2293760},
        {327680, -688128, 1966080},
        {0, -688128, 1966080},
        {31, 32},
        {31, 63},
        {0, 63},
        13
    },
    {
        {0, -688128, 1966080},
        {-327680, -688128, 1638400},
        {-327680, -688128, 1966080},
        {255, 64},
        {224, 95},
        {224, 64},
        13
    },
    {
        {0, -688128, 1966080},
        {0, -688128, 1638400},
        {-327680, -688128, 1638400},
        {255, 64},
        {255, 95},
        {224, 95},
        13
    },
    {
        {327680, -688128, 1966080},
        {0, -688128, 1638400},
        {0, -688128, 1966080},
        {31, 64},
        {0, 95},
        {0, 64},
        13
    },
    {
        {327680, -688128, 1966080},
        {327680, -688128, 1638400},
        {0, -688128, 1638400},
        {31, 64},
        {31, 95},
        {0, 95},
        13
    },
    {
        {-327680, -1343488, 1310720},
        {-327680, -1015808, 983040},
        {-327680, -1343488, 983040},
        {127, 127},
        {96, 96},
        {127, 96},
        13
    },
    {
        {-327680, -1343488, 1310720},
        {-327680, -1015808, 1310720},
        {-327680, -1015808, 983040},
        {127, 127},
        {96, 127},
        {96, 96},
        13
    },
    {
        {-327680, -1343488, 1638400},
        {-327680, -1015808, 1310720},
        {-327680, -1343488, 1310720},
        {127, 159},
        {96, 128},
        {127, 128},
        13
    },
    {
        {-327680, -1343488, 1638400},
        {-327680, -1015808, 1638400},
        {-327680, -1015808, 1310720},
        {127, 159},
        {96, 159},
        {96, 128},
        13
    },
    {
        {-327680, -1343488, 1966080},
        {-327680, -1015808, 1638400},
        {-327680, -1343488, 1638400},
        {127, 191},
        {96, 160},
        {127, 160},
        13
    },
    {
        {-327680, -1343488, 1966080},
        {-327680, -1015808, 1966080},
        {-327680, -1015808, 1638400},
        {127, 191},
        {96, 191},
        {96, 160},
        13
    },
    {
        {-327680, -1343488, 2293760},
        {-327680, -1015808, 1966080},
        {-327680, -1343488, 1966080},
        {127, 223},
        {96, 192},
        {127, 192},
        13
    },
    {
        {-327680, -1343488, 2293760},
        {-327680, -1015808, 2293760},
        {-327680, -1015808, 1966080},
        {127, 223},
        {96, 223},
        {96, 192},
        13
    },
    {
        {-327680, -1015808, 2293760},
        {-327680, -688128, 1966080},
        {-327680, -1015808, 1966080},
        {95, 223},
        {64, 192},
        {95, 192},
        13
    },
    {
        {-327680, -1015808, 2293760},
        {-327680, -688128, 2293760},
        {-327680, -688128, 1966080},
        {95, 223},
        {64, 223},
        {64, 192},
        13
    },
    {
        {-327680, -1015808, 1966080},
        {-327680, -688128, 1638400},
        {-327680, -1015808, 1638400},
        {95, 191},
        {64, 160},
        {95, 160},
        13
    },
    {
        {-327680, -1015808, 1966080},
        {-327680, -688128, 1966080},
        {-327680, -688128, 1638400},
        {95, 191},
        {64, 191},
        {64, 160},
        13
    },
    {
        {-327680, -1015808, 1638400},
        {-327680, -688128, 1310720},
        {-327680, -1015808, 1310720},
        {95, 159},
        {64, 128},
        {95, 128},
        13
    },
    {
        {-327680, -1015808, 1638400},
        {-327680, -688128, 1638400},
        {-327680, -688128, 1310720},
        {95, 159},
        {64, 159},
        {64, 128},
        13
    },
    {
        {-327680, -1015808, 1310720},
        {-327680, -688128, 983040},
        {-327680, -1015808, 983040},
        {95, 127},
        {64, 96},
        {95, 96},
        13
    },
    {
        {-327680, -1015808, 1310720},
        {-327680, -688128, 1310720},
        {-327680, -688128, 983040},
        {95, 127},
        {64, 127},
        {64, 96},
        13
    },
    {
        {327680, -1015808, 1310720},
        {327680, -1343488, 983040},
        {327680, -1015808, 983040},
        {96, 127},
        {127, 96},
        {96, 96},
        13
    },
    {
        {327680, -1015808, 1310720},
        {327680, -1343488, 1310720},
        {327680, -1343488, 983040},
        {96, 127},
        {127, 127},
        {127, 96},
        13
    },
    {
        {327680, -1015808, 1638400},
        {327680, -1343488, 1310720},
        {327680, -1015808, 1310720},
        {96, 159},
        {127, 128},
        {96, 128},
        13
    },
    {
        {327680, -1015808, 1638400},
        {327680, -1343488, 1638400},
        {327680, -1343488, 1310720},
        {96, 159},
        {127, 159},
        {127, 128},
        13
    },
    {
        {327680, -1015808, 1966080},
        {327680, -1343488, 1638400},
        {327680, -1015808, 1638400},
        {96, 191},
        {127, 160},
        {96, 160},
        13
    },
    {
        {327680, -1015808, 1966080},
        {327680, -1343488, 1966080},
        {327680, -1343488, 1638400},
        {96, 191},
        {127, 191},
        {127, 160},
        13
    },
    {
        {327680, -1015808, 2293760},
        {327680, -1343488, 1966080},
        {327680, -1015808, 1966080},
        {96, 223},
        {127, 192},
        {96, 192},
        13
    },
    {
        {327680, -1015808, 2293760},
        {327680, -1343488, 2293760},
        {327680, -1343488, 1966080},
        {96, 223},
        {127, 223},
        {127, 192},
        13
    },
    {
        {327680, -688128, 2293760},
        {327680, -1015808, 1966080},
        {327680, -688128, 1966080},
        {64, 223},
        {95, 192},
        {64, 192},
        13
    },
    {
        {327680, -688128, 2293760},
        {327680, -1015808, 2293760},
        {327680, -1015808, 1966080},
        {64, 223},
        {95, 223},
        {95, 192},
        13
    },
    {
        {327680, -688128, 1966080},
        {327680, -1015808, 1638400},
        {327680, -688128, 1638400},
        {64, 191},
        {95, 160},
        {64, 160},
        13
    },
    {
        {327680, -688128, 1966080},
        {327680, -1015808, 1966080},
        {327680, -1015808, 1638400},
        {64, 191},
        {95, 191},
        {95, 160},
        13
    },
    {
        {327680, -688128, 1638400},
        {327680, -1015808, 1310720},
        {327680, -688128, 1310720},
        {64, 159},
        {95, 128},
        {64, 128},
        13
    },
    {
        {327680, -688128, 1638400},
        {327680, -1015808, 1638400},
        {327680, -1015808, 1310720},
        {64, 159},
        {95, 159},
        {95, 128},
        13
    },
    {
        {327680, -688128, 1310720},
        {327680, -1015808, 983040},
        {327680, -688128, 983040},
        {64, 127},
        {95, 96},
        {64, 96},
        13
    },
    {
        {327680, -688128, 1310720},
        {327680, -1015808, 1310720},
        {327680, -1015808, 983040},
        {64, 127},
        {95, 127},
        {95, 96},
        13
    },
    {
        {327680, -1343488, 983040},
        {0, -1343488, 1310720},
        {0, -1343488, 983040},
        {31, 159},
        {0, 128},
        {0, 159},
        10
    },
    {
        {327680, -1343488, 983040},
        {327680, -1343488, 1310720},
        {0, -1343488, 1310720},
        {31, 159},
        {31, 128},
        {0, 128},
        10
    },
    {
        {0, -1343488, 983040},
        {-327680, -1343488, 1310720},
        {-327680, -1343488, 983040},
        {255, 159},
        {224, 128},
        {224, 159},
        10
    },
    {
        {0, -1343488, 983040},
        {0, -1343488, 1310720},
        {-327680, -1343488, 1310720},
        {255, 159},
        {255, 128},
        {224, 128},
        10
    },
    {
        {0, -1343488, 1310720},
        {-327680, -1343488, 1638400},
        {-327680, -1343488, 1310720},
        {255, 127},
        {224, 96},
        {224, 127},
        10
    },
    {
        {0, -1343488, 1310720},
        {0, -1343488, 1638400},
        {-327680, -1343488, 1638400},
        {255, 127},
        {255, 96},
        {224, 96},
        10
    },
    {
        {0, -1343488, 1638400},
        {-327680, -1343488, 1966080},
        {-327680, -1343488, 1638400},
        {255, 95},
        {224, 64},
        {224, 95},
        13
    },
    {
        {0, -1343488, 1638400},
        {0, -1343488, 1966080},
        {-327680, -1343488, 1966080},
        {255, 95},
        {255, 64},
        {224, 64},
        13
    },
    {
        {0, -1343488, 1966080},
        {-327680, -1343488, 2293760},
        {-327680, -1343488, 1966080},
        {255, 63},
        {224, 32},
        {224, 63},
        13
    },
    {
        {0, -1343488, 1966080},
        {0, -1343488, 2293760},
        {-327680, -1343488, 2293760},
        {255, 63},
        {255, 32},
        {224, 32},
        13
    },
    {
        {327680, -1343488, 1310720},
        {0, -1343488, 1638400},
        {0, -1343488, 1310720},
        {31, 127},
        {0, 96},
        {0, 127},
        10
    },
    {
        {327680, -1343488, 1310720},
        {327680, -1343488, 1638400},
        {0, -1343488, 1638400},
        {31, 127},
        {31, 96},
        {0, 96},
        10
    },
    {
        {327680, -1343488, 1638400},
        {0, -1343488, 1966080},
        {0, -1343488, 1638400},
        {31, 95},
        {0, 64},
        {0, 95},
        13
    },
    {
        {327680, -1343488, 1638400},
        {327680, -1343488, 1966080},
        {0, -1343488, 1966080},
        {31, 95},
        {31, 64},
        {0, 64},
        13
    },
    {
        {327680, -1343488, 1966080},
        {0, -1343488, 2293760},
        {0, -1343488, 1966080},
        {31, 63},
        {0, 32},
        {0, 63},
        13
    },
    {
        {327680, -1343488, 1966080},
        {327680, -1343488, 2293760},
        {0, -1343488, 2293760},
        {31, 63},
        {31, 32},
        {0, 32},
        13
    },
    {
        {-327680, -688128, 2293760},
        {-327680, -1343488, 2260992},
        {-327680, -688128, 2260992},
        {47, 87},
        {40, 184},
        {40, 87},
        11
    },
    {
        {-327680, -688128, 2293760},
        {-327680, -1343488, 2293760},
        {-327680, -1343488, 2260992},
        {47, 87},
        {47, 184},
        {40, 184},
        11
    },
    {
        {-229376, -1343488, 2260992},
        {-327680, -688128, 2260992},
        {-327680, -1343488, 2260992},
        {199, 184},
        {176, 87},
        {176, 184},
        11
    },
    {
        {-229376, -1343488, 2260992},
        {-229376, -688128, 2260992},
        {-327680, -688128, 2260992},
        {199, 184},
        {199, 87},
        {176, 87},
        11
    },
    {
        {-229376, -688128, 2260992},
        {-327680, -688128, 2293760},
        {-327680, -688128, 2260992},
        {199, 215},
        {176, 208},
        {176, 215},
        11
    },
    {
        {-229376, -688128, 2260992},
        {-229376, -688128, 2293760},
        {-327680, -688128, 2293760},
        {199, 215},
        {199, 208},
        {176, 208},
        11
    },
    {
        {-229376, -1343488, 2293760},
        {-327680, -1343488, 2260992},
        {-327680, -1343488, 2293760},
        {199, 208},
        {176, 215},
        {176, 208},
        11
    },
    {
        {-229376, -1343488, 2293760},
        {-229376, -1343488, 2260992},
        {-327680, -1343488, 2260992},
        {199, 208},
        {199, 215},
        {176, 215},
        11
    },
    {
        {-229376, -688128, 2293760},
        {-327680, -1343488, 2293760},
        {-327680, -688128, 2293760},
        {199, 87},
        {176, 184},
        {176, 87},
        11
    },
    {
        {-229376, -688128, 2293760},
        {-229376, -1343488, 2293760},
        {-327680, -1343488, 2293760},
        {199, 87},
        {199, 184},
        {176, 184},
        11
    },
    {
        {-229376, -1343488, 2293760},
        {-229376, -688128, 2260992},
        {-229376, -1343488, 2260992},
        {47, 184},
        {40, 87},
        {40, 184},
        11
    },
    {
        {-229376, -1343488, 2293760},
        {-229376, -688128, 2293760},
        {-229376, -688128, 2260992},
        {47, 184},
        {47, 87},
        {40, 87},
        11
    },
    {
        {229376, -1146880, 2293760},
        {-229376, -688128, 2293760},
        {-229376, -1146880, 2293760},
        {63, 64},
        {0, 127},
        {0, 64},
        8
    },
    {
        {229376, -1146880, 2293760},
        {229376, -688128, 2293760},
        {-229376, -688128, 2293760},
        {63, 64},
        {63, 127},
        {0, 127},
        8
    },
    {
        {229376, -688128, 2293760},
        {229376, -1343488, 2260992},
        {229376, -688128, 2260992},
        {47, 87},
        {40, 184},
        {40, 87},
        11
    },
    {
        {229376, -688128, 2293760},
        {229376, -1343488, 2293760},
        {229376, -1343488, 2260992},
        {47, 87},
        {47, 184},
        {40, 184},
        11
    },
    {
        {327680, -1343488, 2260992},
        {229376, -688128, 2260992},
        {229376, -1343488, 2260992},
        {79, 184},
        {56, 87},
        {56, 184},
        11
    },
    {
        {327680, -1343488, 2260992},
        {327680, -688128, 2260992},
        {229376, -688128, 2260992},
        {79, 184},
        {79, 87},
        {56, 87},
        11
    },
    {
        {327680, -688128, 2260992},
        {229376, -688128, 2293760},
        {229376, -688128, 2260992},
        {79, 215},
        {56, 208},
        {56, 215},
        11
    },
    {
        {327680, -688128, 2260992},
        {327680, -688128, 2293760},
        {229376, -688128, 2293760},
        {79, 215},
        {79, 208},
        {56, 208},
        11
    },
    {
        {327680, -1343488, 2293760},
        {229376, -1343488, 2260992},
        {229376, -1343488, 2293760},
        {79, 208},
        {56, 215},
        {56, 208},
        11
    },
    {
        {327680, -1343488, 2293760},
        {327680, -1343488, 2260992},
        {229376, -1343488, 2260992},
        {79, 208},
        {79, 215},
        {56, 215},
        11
    },
    {
        {327680, -688128, 2293760},
        {229376, -1343488, 2293760},
        {229376, -688128, 2293760},
        {79, 87},
        {56, 184},
        {56, 87},
        11
    },
    {
        {327680, -688128, 2293760},
        {327680, -1343488, 2293760},
        {229376, -1343488, 2293760},
        {79, 87},
        {79, 184},
        {56, 184},
        11
    },
    {
        {327680, -1343488, 2293760},
        {327680, -688128, 2260992},
        {327680, -1343488, 2260992},
        {47, 184},
        {40, 87},
        {40, 184},
        11
    },
    {
        {327680, -1343488, 2293760},
        {327680, -688128, 2293760},
        {327680, -688128, 2260992},
        {47, 184},
        {47, 87},
        {40, 87},
        11
    },
    {
        {229376, -1343488, 2293760},
        {-229376, -1146880, 2293760},
        {-229376, -1343488, 2293760},
        {31, 124},
        {0, 143},
        {0, 124},
        5
    },
    {
        {229376, -1343488, 2293760},
        {229376, -1146880, 2293760},
        {-229376, -1146880, 2293760},
        {31, 124},
        {31, 143},
        {0, 143},
        5
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
            drawCross2(transformedGizmoPoints[i], 0xFFFFFF);
        };
        printf("\n");
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
                //Tri2 flatTri = {
                //    transformedTri.a,
                //    transformedTri.b,
                //    transformedTri.c,
                //    transformedTri.z
                //};
                //drawTri2(flatTri, colours[i%6]);
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
   

    }
}
