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

#define MOVEMENT_SPEED (10<<12)

#define ACCELERATION_CONSTANT (1<<12)
#define MAX_SPEED (3<<12)
#define JUMP_FORCE (10<<12)
#define FRICTION_CONSTANT (1<<12)
#define TERMINAL_VELOCITY (5<<12)
#define GRAVITY_CONSTANT (1<<10)

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




Camera mainCamera;
Player3 player;
char str_Buffer[256];
//int screenColor = 0xfa823c;
int screenColor = 0x000000;
int wallColor = 0x3c82fa;
int gteScaleFactor = 0;
bool drawOutlines = false;
int cameraHeight = 0;

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

    // This range check was supposed to speed things up but honestly, I think it is so much worse than just doing it on the GTE
    // We do still need to check if the triangle is too far away, otherwise large maps will loop and loop in on themselves.
    // But we can sort that out later once the maps start getting that big.

    //if(
    //    abs(cam->x - (tri.a.x>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->y - (tri.a.y>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->z - (tri.a.z>>GTE_SCALE_FACTOR)) > INT16_MAX ||
    //    abs(cam->x - (tri.b.x>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->y - (tri.b.y>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->z - (tri.b.z>>GTE_SCALE_FACTOR)) > INT16_MAX ||
    //    abs(cam->x - (tri.c.x>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->y - (tri.c.y>>GTE_SCALE_FACTOR)) > INT16_MAX || abs(cam->z - (tri.c.z>>GTE_SCALE_FACTOR)) > INT16_MAX
    //){
    //    // Out of range. Don't render
    //    return false;
    //}

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
    

    //if(MAC0 <= -1024){
    //    gte_setControlReg(GTE_TRX, currentTx);
    //    gte_setControlReg(GTE_TRY, currentTy);
    //    gte_setControlReg(GTE_TRZ, currentTz);
    //    return false;
    //}

    

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
            1, 337
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
            2, 150
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
            3, 56
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
            5, 49
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
            6, 26
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
            7, 15
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
            8, 10
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
            -1, 9
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
            -1, 11
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
            12, 14
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
            -2, 13
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
            16, 21
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
            -1, 17
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
            18, 20
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
            -2, 19
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
            -1, 22
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
            23, 25
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
            -2, 24
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
            27, 38
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
            28, 33
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
            -1, 29
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
            30, 32
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
            -2, 31
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
            -1, 34
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
            35, 37
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
            -2, 36
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
            39, 44
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
            -1, 40
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
            41, 43
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
            -2, 42
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
            -1, 45
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
            46, 48
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
            -2, 47
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
            50, 54
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
            51, -2
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
            52, -2
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
            53, -2
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
            55, -1
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
            57, 113
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
            58, 69
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
            59, 64
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
            -1, 60
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
            -1, 61
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
            62, -2
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
            63, -2
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
            -1, 65
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
            66, -1
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
            67, -2
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
            68, -2
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
            70, 73
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
            -1, 71
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
            72, -1
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
            74, 93
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
            75, 84
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
            76, 80
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
            77, 79
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
            -2, 78
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
            81, 83
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
            -2, 82
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
            85, 89
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
            86, 88
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
            -2, 87
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
            90, 92
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
            -2, 91
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
            94, 103
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
            95, 99
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
            96, 98
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
            -2, 97
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
            100, 102
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
            -2, 101
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
            104, 108
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
            105, 107
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
            -2, 106
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
            109, 111
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
            110, -1
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
            -1, 112
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
            114, 138
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
            115, 128
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
            116, 120
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
            -1, 117
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
            118, -2
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
            119, -2
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
            121, 123
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
            122, -1
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
            124, 126
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
            125, -1
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
            .y = -4096,
            .z = 0
        },
        .distance = 655360,
        .children = {
            129, 132
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
            130, -2
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
            131, -2
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
            133, 135
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
            -1, 134
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
            -1, 137
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
            139, 142
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
            140, 141
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
            143, 146
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
            144, -1
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
            -2, 145
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
            147, 149
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
            148, -1
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
            151, 247
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
            152, 169
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
            -1, 153
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
            154, 161
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
            155, 157
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
            156, -1
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
            158, -2
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
            159, -2
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
            160, -2
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
            .y = 0,
            .z = 4096
        },
        .distance = -327680,
        .children = {
            162, 166
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
            163, -2
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
            164, -2
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
            165, -2
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
            .y = 0,
            .z = 4096
        },
        .distance = -983040,
        .children = {
            167, -1
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
            168, -1
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
            .y = 0,
            .z = 4096
        },
        .distance = -983040,
        .children = {
            170, 241
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
            171, 202
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
            172, 183
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
            173, 174
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
            175, 178
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
            176, -1
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
            -2, 177
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
            179, -1
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
            180, 181
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
            -2, 182
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
            184, 193
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
            185, 188
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
            186, -1
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
            -2, 187
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
            189, -1
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
            190, 191
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
            -2, 192
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
            194, 197
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
            195, -1
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
            -2, 196
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
            198, -1
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
            199, 200
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
            -2, 201
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
            203, 222
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
            204, 213
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
            205, 208
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
            206, -1
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
            -2, 207
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
            209, -1
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
            210, 211
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
            -2, 212
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
            214, 217
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
            215, -1
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
            -2, 216
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
            218, -1
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
            219, 220
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
            -2, 221
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
            223, 232
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
            224, 227
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
            225, -1
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
            -2, 226
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
            228, -1
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
            229, 230
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
            -2, 231
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
            233, 236
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
            234, -1
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
            -2, 235
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
            237, -1
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
            238, 239
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
            -2, 240
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
            -1, 242
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
            243, -1
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
            244, -2
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
            245, -2
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
            246, -2
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
            248, 268
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
            -1, 249
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
            250, 259
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
            251, 257
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
            252, 255
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
            253, -2
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
            254, -2
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
            -2, 256
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
        .distance = -131072,
        .children = {
            258, -1
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
            260, 263
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
            -2, 261
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
            -2, 262
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
            -1, 264
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
            265, -1
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
            266, -2
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
            267, -2
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
            269, 280
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
            270, 275
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
            -1, 271
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 163840,
        .children = {
            -2, 272
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -163840,
        .children = {
            273, 274
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
            -1, 276
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
            277, -1
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
            278, -2
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
            279, -2
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
        .distance = -983040,
        .children = {
            281, 332
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
            282, 292
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
            283, 290
        }
    },
    {
        .normal = {
            .x = 4095,
            .y = 0,
            .z = 1
        },
        .distance = 1113907,
        .children = {
            -1, 284
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
            285, 287
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
            286, -2
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
            -2, 288
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
            -2, 289
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
        .distance = -131072,
        .children = {
            291, -1
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
            293, 330
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
            294, 297
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
            -1, 295
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
            296, -1
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
            298, 316
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
            299, 308
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
            300, 304
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
            301, 302
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
            -2, 303
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
            305, 306
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
            -2, 307
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
            309, 313
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
            310, 311
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
            -2, 312
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
            -2, 314
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
            -1, 315
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
            317, 319
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
            -2, 318
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
            320, 326
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
            -1, 321
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
            322, 325
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
            323, 324
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
        .distance = 655360,
        .children = {
            327, 328
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
        .distance = -917504,
        .children = {
            329, -1
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
            331, -1
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
            -1, 333
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
            334, -1
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
            -2, 335
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
            -2, 336
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
            .y = 0,
            .z = 4096
        },
        .distance = 655360,
        .children = {
            338, 489
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
            339, 392
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
            -1, 340
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
            341, 348
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
            342, 346
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
            343, -2
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
            344, -2
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
            345, -2
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
            347, -1
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
            349, 369
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
            350, 358
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
            351, 353
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
            352, -1
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
            354, -1
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
            355, 357
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
            356, -2
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
            359, 364
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
            360, -1
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
            361, 363
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
            362, -2
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
            365, -1
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
            366, 368
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
            367, -2
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
            370, 381
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
            371, 376
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
            372, -1
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
            373, 375
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
            374, -2
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
            377, -1
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
            378, 380
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
            379, -2
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
            382, 387
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
            383, -1
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
            384, 386
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
            385, -2
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
            388, -1
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
            389, 391
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
            390, -2
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
            393, 430
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
            394, 418
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
            395, 408
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
            396, 400
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
            -1, 397
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
            398, -2
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
            399, -2
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
            401, 406
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
            402, 404
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
            403, -1
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
            405, -1
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
            407, -1
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
            409, 412
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
            410, -2
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
            411, -2
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
            413, 415
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
            414, -1
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
            416, -1
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
            -1, 417
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
            419, 422
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
            420, 421
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
            423, 426
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
            424, -1
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
            -2, 425
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
            427, 429
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
            -1, 428
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
            431, 442
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
            432, 437
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
            433, -1
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
            -1, 434
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
            435, -2
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
            436, -2
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
            438, -1
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
            439, -1
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
            440, -2
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
            441, -2
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
        .distance = 983040,
        .children = {
            443, 466
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
            444, 455
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
            445, 450
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
            446, -1
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
            447, 449
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
            448, -2
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
            451, -1
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
            452, 454
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
            453, -2
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
            456, 461
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
            457, -1
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
            458, 460
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
            459, -2
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
            462, -1
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
            463, 465
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
            464, -2
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
            467, 478
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
            468, 473
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
            469, -1
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
            470, 472
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
            471, -2
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
            474, -1
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
            475, 477
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
            476, -2
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
            479, 484
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
            480, -1
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
            481, 483
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
            482, -2
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
            485, 487
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
            -1, 486
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
            488, -1
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
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2293760,
        .children = {
            490, 586
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
            491, 569
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
            492, 563
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
            493, 524
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
            494, 505
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
            495, 496
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
            497, 502
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
            -1, 498
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
            499, 500
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
            501, -2
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
            503, -1
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
            504, -2
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
            506, 515
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
            507, 512
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
            -1, 508
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
            509, 510
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
            511, -2
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
            513, -1
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
            514, -2
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
            516, 521
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
            -1, 517
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
            518, 519
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
            520, -2
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
            522, -1
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
            523, -2
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
            525, 544
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
            526, 535
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
            527, 532
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
            -1, 528
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
            529, 530
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
            531, -2
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
            533, -1
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
            534, -2
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
            536, 541
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
            -1, 537
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
            538, 539
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
            540, -2
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
            542, -1
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
            543, -2
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
            545, 554
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
            546, 551
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
            -1, 547
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
            548, 549
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
            550, -2
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
            552, -1
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
            553, -2
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
            555, 560
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
            -1, 556
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
            557, 558
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
            559, -2
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
            561, -1
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
            562, -2
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
            564, -1
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
            565, -1
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
            566, -2
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
            567, -2
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
            568, -2
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
            570, -1
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
            571, 578
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
            572, 574
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
            573, -1
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
            575, -2
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
            576, -2
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
            577, -2
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
            .y = 0,
            .z = 4096
        },
        .distance = -327680,
        .children = {
            579, 583
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
            580, -2
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
            581, -2
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
            582, -2
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
            .y = 0,
            .z = 4096
        },
        .distance = -983040,
        .children = {
            584, -1
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
            585, -1
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
            .y = 0,
            .z = 4096
        },
        .distance = -327680,
        .children = {
            587, 619
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
            588, 609
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
            589, 599
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
            590, 592
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
            591, -1
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
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4095,
            .y = 0,
            .z = 1
        },
        .distance = -1113907,
        .children = {
            593, -1
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
            594, 597
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
            595, -2
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
            596, -2
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
            -2, 598
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
        .distance = -1048576,
        .children = {
            600, 605
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
            -1, 601
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
            602, -1
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
            -2, 603
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
            -2, 604
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            606, -1
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
            -2, 607
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
            -2, 608
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
        .distance = -1048576,
        .children = {
            610, 615
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
            -1, 611
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
            612, -1
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
            -2, 613
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
            -2, 614
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            616, -1
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
            -2, 617
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
            -2, 618
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
            .y = 0,
            .z = 4096
        },
        .distance = -983040,
        .children = {
            620, 672
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
            621, 631
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
            622, 624
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
            623, -1
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
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4095,
            .y = 0,
            .z = -1
        },
        .distance = -1113907,
        .children = {
            625, -1
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
            626, 629
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
            627, -2
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
            628, -2
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
            -2, 630
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
        .distance = -327680,
        .children = {
            632, 634
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
            633, -1
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
            635, 657
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
            636, 647
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
            637, 642
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
            638, -1
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
            639, 640
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
            641, -2
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            643, -1
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
            644, 645
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
            646, -2
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
            648, 653
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
            649, -1
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
            650, 651
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
            652, -2
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
            654, 656
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
            -1, 655
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
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
            658, 669
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
            659, 665
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
            -1, 660
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
            661, 664
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
            662, 663
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -655360,
        .children = {
            666, 668
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
            667, -1
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
            670, -1
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
            -2, 671
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
        .distance = -327680,
        .children = {
            673, -1
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
            674, -1
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
            -2, 675
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
            -2, 676
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
BSPTree3 bsp_hitscan = {.nodes=bspNodes_hitscan, .numNodes = 677};

BSPNode3 bspNodes_player[] = {
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 622592,
        .children = {
            1, 531
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -32768,
        .children = {
            2, 269
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 622592,
        .children = {
            3, 137
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2162688,
        .children = {
            4, 67
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
            -1, 5
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            6, 9
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            -1, 7
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
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
        .distance = 4784128,
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
        .distance = 950272,
        .children = {
            10, 44
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3473408,
        .children = {
            11, 25
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4128768,
        .children = {
            12, 20
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            13, 18
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            14, 16
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            15, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 1015808,
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
        .distance = 688128,
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
        .distance = 1015808,
        .children = {
            19, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
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
        .distance = 3801088,
        .children = {
            21, 24
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            22, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            -1, 23
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4063232,
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
        .distance = 1015808,
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
        .distance = 2818048,
        .children = {
            26, 34
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3145728,
        .children = {
            27, 31
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            28, 29
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
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
        .distance = 3407872,
        .children = {
            30, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
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
        .distance = 1015808,
        .children = {
            32, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
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
        .distance = 3080192,
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
        .distance = 2490368,
        .children = {
            35, 39
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2752512,
        .children = {
            36, 37
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
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
        .distance = 1015808,
        .children = {
            38, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
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
        .distance = 2424832,
        .children = {
            40, 42
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            41, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
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
        .distance = 1015808,
        .children = {
            43, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
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
        .distance = 3407872,
        .children = {
            45, 56
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4063232,
        .children = {
            46, 54
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            47, 52
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            48, 49
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 4456448,
        .children = {
            -2, 50
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1112182,
        .children = {
            -2, 51
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = 1112182,
        .children = {
            -2, 53
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = 1112182,
        .children = {
            -2, 55
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = 2752512,
        .children = {
            57, 62
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3080192,
        .children = {
            58, 60
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1112182,
        .children = {
            -2, 59
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = 1112182,
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
        .distance = 884736,
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
        .distance = 2424832,
        .children = {
            63, 65
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1112182,
        .children = {
            -2, 64
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = 1112182,
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
        .distance = 884736,
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
        .distance = 1015808,
        .children = {
            -1, 68
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            69, 103
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            70, 89
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            71, 82
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1507328,
        .children = {
            72, 79
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2097152,
        .children = {
            73, 76
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -1, 74
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            75, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
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
        .distance = 1015808,
        .children = {
            77, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            -1, 78
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
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
        .distance = 1146880,
        .children = {
            -1, 80
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            81, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
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
        .distance = 851968,
        .children = {
            83, 86
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            -1, 84
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            85, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
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
        .distance = 1146880,
        .children = {
            -1, 87
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            88, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
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
        .distance = 1441792,
        .children = {
            90, 98
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1769472,
        .children = {
            91, 96
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2097152,
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
        .distance = 1112182,
        .children = {
            -2, 93
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = 1112182,
        .children = {
            -2, 95
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = 1112182,
        .children = {
            -2, 97
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = 1114112,
        .children = {
            99, 101
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1112182,
        .children = {
            -2, 100
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = 1112182,
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
        .distance = 884736,
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
        .distance = 196608,
        .children = {
            104, 110
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            105, 108
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            -1, 106
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            107, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
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
        .distance = 1112182,
        .children = {
            -2, 109
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
            111, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            112, 123
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            -1, 113
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            114, 119
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
            115, 117
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            116, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
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
        .distance = 688128,
        .children = {
            -1, 118
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1131034,
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
        .distance = 131072,
        .children = {
            -2, 120
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            121, -2
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
            -2, 122
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1204864,
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
        .distance = 688128,
        .children = {
            124, 134
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
            125, 132
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 688128,
        .children = {
            126, 129
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1204864,
        .children = {
            -2, 127
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1112182,
        .children = {
            -2, 128
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
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
        .distance = 950272,
        .children = {
            -2, 130
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            131, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = 688128,
        .children = {
            133, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1204864,
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
        .distance = -131072,
        .children = {
            135, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            136, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1112182,
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
        .distance = 294912,
        .children = {
            138, 194
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2424832,
        .children = {
            139, 148
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
            -1, 140
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            141, 146
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3407872,
        .children = {
            142, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4063232,
        .children = {
            143, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            144, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            145, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 4456448,
        .children = {
            147, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 1015808,
        .children = {
            149, 185
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 393216,
        .children = {
            -1, 150
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1605632,
        .children = {
            151, 169
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
            -1, 152
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
            153, 161
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1933312,
        .children = {
            154, 157
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1474560,
        .children = {
            155, -2
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
            -1, 156
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1507328,
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
        .distance = 1212416,
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
        .distance = 1507328,
        .children = {
            -1, 159
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1474560,
        .children = {
            160, -2
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
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1998848,
        .children = {
            162, 166
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
            163, 164
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
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
        .distance = 557056,
        .children = {
            -2, 165
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
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
        .distance = 557056,
        .children = {
            -2, 167
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
            -1, 168
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
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
        .distance = 819200,
        .children = {
            170, 179
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
            171, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1507328,
        .children = {
            -1, 172
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1277952,
        .children = {
            173, 176
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1212416,
        .children = {
            174, -2
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
            175, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1474560,
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
        .distance = 1212416,
        .children = {
            177, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1474560,
        .children = {
            178, -2
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
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            180, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1343488,
        .children = {
            181, 183
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
            182, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
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
        .distance = 360448,
        .children = {
            184, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
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
        .distance = 884736,
        .children = {
            186, 192
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            -2, 187
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
            188, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -2, 189
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
            190, -2
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
            191, -2
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
        .distance = -262144,
        .children = {
            193, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
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
        .distance = 2162688,
        .children = {
            195, 204
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
            -1, 196
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            197, 202
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3145728,
        .children = {
            198, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3801088,
        .children = {
            199, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            200, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            201, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 4456448,
        .children = {
            203, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 1507328,
        .children = {
            205, 207
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            206, -1
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
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1605632,
        .children = {
            208, 235
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1998848,
        .children = {
            209, 232
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2359296,
        .children = {
            -1, 210
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
        .children = {
            211, 230
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1474560,
        .children = {
            212, 213
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
        .distance = 2326528,
        .children = {
            214, 217
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
            215, 216
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
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
        .distance = 1015808,
        .children = {
            218, 224
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2228224,
        .children = {
            219, 223
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 262144,
        .children = {
            -2, 220
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1212416,
        .children = {
            -2, 221
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
            -2, 222
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1212416,
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
        .distance = 2228224,
        .children = {
            225, 229
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 262144,
        .children = {
            -2, 226
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            227, -2
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
            -2, 228
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
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
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
        .distance = 2326528,
        .children = {
            -1, 231
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
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
        .distance = 1212416,
        .children = {
            -2, 233
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            234, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
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
        .distance = 819200,
        .children = {
            236, 248
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 32768,
        .children = {
            237, 241
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            238, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1212416,
        .children = {
            -2, 239
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
            -1, 240
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
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
        .distance = 1277952,
        .children = {
            242, 243
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1212416,
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
        .distance = 884736,
        .children = {
            244, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            245, -1
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
            246, -2
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
            247, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1212416,
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
        .distance = 524288,
        .children = {
            249, 252
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
            -2, 250
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
            -2, 251
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
            253, -1
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
            -1, 254
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            255, 268
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
            256, 267
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
            257, 263
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
            258, 261
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
            259, -2
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
            260, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
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
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            262, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
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
        .distance = 196608,
        .children = {
            264, 266
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            265, -2
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
        .distance = 131072,
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
        .distance = 1015808,
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
        .distance = 131072,
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
        .distance = -622592,
        .children = {
            270, 398
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2162688,
        .children = {
            271, 279
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
            -1, 272
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            273, 277
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3407872,
        .children = {
            274, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4063232,
        .children = {
            275, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            276, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 4456448,
        .children = {
            278, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 884736,
        .children = {
            280, 396
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1507328,
        .children = {
            281, 282
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
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1277952,
        .children = {
            283, 347
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -393216,
        .children = {
            284, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            285, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1933312,
        .children = {
            286, 318
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2359296,
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
        .distance = 1474560,
        .children = {
            288, 290
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
            289, -1
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
        .distance = 2326528,
        .children = {
            291, 295
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
            292, 293
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
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
        .distance = -262144,
        .children = {
            294, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
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
        .distance = 557056,
        .children = {
            296, 317
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
            297, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1998848,
        .children = {
            298, 312
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            299, -2
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
            300, 306
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2228224,
        .children = {
            301, 305
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -262144,
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
        .distance = 1212416,
        .children = {
            -2, 303
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
            304, -2
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1212416,
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
        .distance = 2228224,
        .children = {
            307, 311
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -262144,
        .children = {
            308, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            309, -2
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
            310, -2
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
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
            313, 315
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            314, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1212416,
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
        .distance = 819200,
        .children = {
            316, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1605632,
        .children = {
            319, 333
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
            320, 325
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            321, 322
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1212416,
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
        .distance = 1212416,
        .children = {
            323, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1474560,
        .children = {
            324, -2
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            326, 327
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
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
        .distance = 819200,
        .children = {
            -2, 328
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1671168,
        .children = {
            329, 331
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
            -2, 330
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
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
            -2, 332
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
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
        .distance = 1146880,
        .children = {
            334, 339
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            335, 336
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1212416,
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
        .distance = 1212416,
        .children = {
            337, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1474560,
        .children = {
            338, -2
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            340, 341
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
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
        .distance = 819200,
        .children = {
            -2, 342
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1343488,
        .children = {
            343, 345
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
            -2, 344
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
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
            -2, 346
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
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
            348, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            349, 373
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            350, 355
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            351, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
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
        .distance = 950272,
        .children = {
            353, -2
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
            354, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1212416,
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
        .distance = 819200,
        .children = {
            356, 368
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
            357, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            358, 366
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            359, 364
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
            360, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -393216,
        .children = {
            361, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1212416,
        .children = {
            362, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1474560,
        .children = {
            363, -2
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -393216,
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
        .distance = -393216,
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
        .distance = 1015808,
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
        .distance = 950272,
        .children = {
            369, -2
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
            370, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -393216,
        .children = {
            371, -1
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
            -2, 372
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
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
        .distance = 1048576,
        .children = {
            -1, 374
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
            375, 379
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
            376, 377
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
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
        .distance = -262144,
        .children = {
            378, -1
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            380, 392
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
            381, -2
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
            382, 386
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
            383, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -262144,
        .children = {
            384, -2
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
            385, -2
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
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            387, 391
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -262144,
        .children = {
            388, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            389, -2
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
            -2, 390
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
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
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
        .distance = 131072,
        .children = {
            -2, 393
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
            -2, 394
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
            395, -2
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
        .distance = -262144,
        .children = {
            397, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
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
        .distance = 2162688,
        .children = {
            399, 455
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
            -1, 400
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            401, 452
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3473408,
        .children = {
            402, 427
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4128768,
        .children = {
            403, 415
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            404, 405
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = -950272,
        .children = {
            406, 412
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            407, 410
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            -2, 408
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
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
        .distance = 884736,
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
        .distance = -1112182,
        .children = {
            411, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = 4456448,
        .children = {
            -2, 413
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -2, 414
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
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
        .distance = -950272,
        .children = {
            416, 424
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4063232,
        .children = {
            417, 419
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            418, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = 3735552,
        .children = {
            420, 422
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
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
        .distance = 884736,
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
        .distance = -1112182,
        .children = {
            423, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = 3801088,
        .children = {
            425, 426
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
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
        .distance = -1015808,
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
        .distance = -950272,
        .children = {
            428, 442
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3080192,
        .children = {
            429, 434
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3407872,
        .children = {
            430, 432
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            431, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = -1112182,
        .children = {
            433, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = 2752512,
        .children = {
            435, 437
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            436, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = 2424832,
        .children = {
            438, 440
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            439, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = -1112182,
        .children = {
            441, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = 2490368,
        .children = {
            443, 450
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2818048,
        .children = {
            444, 448
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3145728,
        .children = {
            445, 447
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
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
        .distance = -1015808,
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
        .distance = -1015808,
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
        .distance = -1015808,
        .children = {
            -2, 449
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
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
        .distance = -1015808,
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
        .distance = 688128,
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
        .distance = -1146880,
        .children = {
            453, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            454, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 1015808,
        .children = {
            -1, 456
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 851968,
        .children = {
            457, 488
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            458, 472
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1769472,
        .children = {
            459, 464
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2097152,
        .children = {
            460, 462
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            461, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = -1112182,
        .children = {
            463, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = 1441792,
        .children = {
            465, 467
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            466, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = 1114112,
        .children = {
            468, 470
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            469, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = -1112182,
        .children = {
            471, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = 1179648,
        .children = {
            473, 485
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1507328,
        .children = {
            474, 482
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1146880,
        .children = {
            475, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1835008,
        .children = {
            476, 480
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            477, 478
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
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
        .distance = -1015808,
        .children = {
            -2, 479
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2097152,
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
        .distance = 688128,
        .children = {
            481, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
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
        .distance = -1146880,
        .children = {
            483, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -2, 484
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
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
        .distance = -1146880,
        .children = {
            486, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -2, 487
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
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
        .distance = -262144,
        .children = {
            489, -1
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
            490, 513
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            491, 502
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -720896,
        .children = {
            492, 497
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 786432,
        .children = {
            493, 495
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
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
        .distance = 884736,
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
        .distance = -1112182,
        .children = {
            496, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = -950272,
        .children = {
            498, 499
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
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
        .distance = -1146880,
        .children = {
            500, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -2, 501
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
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
        .distance = -720896,
        .children = {
            503, 508
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
            504, 506
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            505, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = -1112182,
        .children = {
            507, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = -950272,
        .children = {
            509, 510
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
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
        .distance = -1146880,
        .children = {
            511, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -2, 512
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
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
        .distance = -950272,
        .children = {
            514, 521
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            515, 517
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            516, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
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
        .distance = 688128,
        .children = {
            518, -2
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
            -2, 519
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -688128,
        .children = {
            -2, 520
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1204864,
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
        .distance = -1146880,
        .children = {
            522, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            523, 527
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            524, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -2, 525
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
            -2, 526
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1204864,
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
        .distance = -1015808,
        .children = {
            -2, 528
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -2, 529
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
            -2, 530
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1131034,
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
        .distance = -294912,
        .children = {
            532, 950
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 163840,
        .children = {
            533, 795
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 32768,
        .children = {
            534, 673
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 622592,
        .children = {
            535, 629
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2162688,
        .children = {
            536, 581
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            -1, 537
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            538, 579
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            539, 550
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            540, 541
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 1015808,
        .children = {
            542, 546
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            543, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            544, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
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
        .distance = 4456448,
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
        .distance = 294912,
        .children = {
            547, 549
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            -2, 548
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1053918,
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
        .distance = 4456448,
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
        .distance = 1015808,
        .children = {
            551, 572
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3080192,
        .children = {
            552, 559
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3735552,
        .children = {
            553, 556
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            554, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -1, 555
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4063232,
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
        .distance = 360448,
        .children = {
            557, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -1, 558
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3407872,
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
        .distance = 2424832,
        .children = {
            560, 569
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2490368,
        .children = {
            561, 566
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            562, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            563, 564
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
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
        .distance = 2752512,
        .children = {
            565, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
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
        .distance = 294912,
        .children = {
            567, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            568, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
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
        .distance = 294912,
        .children = {
            570, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
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
        .distance = 1081344,
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
        .distance = 294912,
        .children = {
            573, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1053918,
        .children = {
            574, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2424832,
        .children = {
            575, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2752512,
        .children = {
            576, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3407872,
        .children = {
            577, 578
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4063232,
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
        .distance = 3080192,
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
        .distance = 4456448,
        .children = {
            580, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 1146880,
        .children = {
            -1, 582
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            583, 615
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 229376,
        .children = {
            584, 607
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            585, 591
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            586, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1507328,
        .children = {
            587, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2097152,
        .children = {
            588, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            589, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
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
        .distance = 360448,
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
        .distance = 196608,
        .children = {
            -2, 592
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            593, 601
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -2, 594
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            595, 598
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
            596, -1
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
            -2, 597
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1131034,
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
            599, -1
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
            -2, 600
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
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
        .distance = 131072,
        .children = {
            -2, 602
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
            -2, 603
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -163840,
        .children = {
            604, -1
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
            -2, 605
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
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
        .distance = 262144,
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
        .distance = 131072,
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
        .distance = 65536,
        .children = {
            -2, 610
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
            -2, 611
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
            -2, 612
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -163840,
        .children = {
            613, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            614, -2
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
        .distance = 294912,
        .children = {
            616, 626
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            617, 624
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            618, 619
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1053918,
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
        .distance = 196608,
        .children = {
            620, 621
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1053918,
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
            622, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            623, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1053918,
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
            625, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
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
        .distance = 131072,
        .children = {
            -1, 627
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -163840,
        .children = {
            -2, 628
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
        .distance = 360448,
        .children = {
            630, 644
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            631, 635
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            632, 634
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            633, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            636, 640
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            637, 639
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            638, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            641, 643
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            642, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            645, 654
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            646, 650
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            647, 649
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            648, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            651, 653
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            652, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            655, 664
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            656, 660
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            657, 659
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            658, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            661, 663
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            662, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            665, 669
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            666, 668
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            667, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            670, 672
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            671, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -622592,
        .children = {
            674, 713
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            675, 684
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            676, 680
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            677, 679
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            678, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            681, 683
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            682, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            685, 694
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
            686, 690
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            687, 689
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            688, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            691, 693
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            692, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            695, 704
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
            696, 700
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            697, 699
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            698, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            701, 703
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            702, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            705, 709
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            706, 708
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            707, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            710, 712
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            711, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2162688,
        .children = {
            714, 756
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1146880,
        .children = {
            715, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            716, 725
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2490368,
        .children = {
            717, 724
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            718, 719
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = -1053918,
        .children = {
            -1, 720
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4128768,
        .children = {
            -2, 721
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3145728,
        .children = {
            722, 723
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3473408,
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
        .distance = 2818048,
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
        .distance = -1053918,
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
        .distance = 3735552,
        .children = {
            726, 739
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4063232,
        .children = {
            727, 738
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            728, 730
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            729, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 294912,
        .children = {
            731, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            732, 734
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            -2, 733
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
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
        .distance = -1081344,
        .children = {
            735, 737
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4128768,
        .children = {
            -2, 736
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
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
        .distance = 360448,
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
        .distance = 360448,
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
        .distance = 3080192,
        .children = {
            740, 750
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            741, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3407872,
        .children = {
            742, 746
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            743, 745
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            744, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3473408,
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
        .distance = 360448,
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
        .distance = -1081344,
        .children = {
            747, 749
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            748, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3145728,
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
        .distance = 360448,
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
        .distance = 2490368,
        .children = {
            751, 754
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            752, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            753, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2818048,
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
        .distance = 360448,
        .children = {
            755, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
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
        .distance = -1146880,
        .children = {
            757, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            758, 774
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            759, 769
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1507328,
        .children = {
            760, 767
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            761, 763
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2097152,
        .children = {
            -1, 762
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1053918,
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
        .distance = 294912,
        .children = {
            764, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1835008,
        .children = {
            765, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2097152,
        .children = {
            766, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
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
        .distance = -1015808,
        .children = {
            768, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1053918,
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
        .distance = 851968,
        .children = {
            770, 772
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            771, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1053918,
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
        .distance = -1015808,
        .children = {
            773, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1053918,
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
        .distance = 196608,
        .children = {
            775, 777
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            776, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1053918,
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
            778, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            779, 780
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
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
        .distance = 360448,
        .children = {
            781, 786
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
            782, 785
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1131034,
        .children = {
            783, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            784, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1053918,
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
        .distance = -1131034,
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
        .distance = 131072,
        .children = {
            787, 789
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            788, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1053918,
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
        .distance = -1015808,
        .children = {
            -2, 790
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            791, 794
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            -2, 792
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
            -2, 793
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -163840,
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 32768,
        .children = {
            796, 877
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 622592,
        .children = {
            797, 838
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2162688,
        .children = {
            798, 815
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            -1, 799
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -32768,
        .children = {
            800, 807
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            801, 805
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3735552,
        .children = {
            802, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            803, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            804, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 4456448,
        .children = {
            806, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 1015808,
        .children = {
            808, 813
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3407872,
        .children = {
            809, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4063232,
        .children = {
            810, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            811, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            812, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 4456448,
        .children = {
            814, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 1146880,
        .children = {
            -1, 816
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            817, 836
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 32768,
        .children = {
            818, 824
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -2, 819
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
            -2, 820
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
            -2, 821
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
            -2, 822
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -1, 823
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -163840,
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
        .distance = -32768,
        .children = {
            825, 831
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            -2, 826
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -2, 827
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
            -2, 828
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
            -2, 829
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -1, 830
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -163840,
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
        .distance = 458752,
        .children = {
            -2, 832
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, 833
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
            -2, 834
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -1, 835
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -163840,
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
        .distance = 131072,
        .children = {
            -1, 837
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
        .distance = 360448,
        .children = {
            839, 848
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -32768,
        .children = {
            840, 844
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            841, 843
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            842, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            845, 847
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            846, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -32768,
        .children = {
            849, 868
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 32768,
        .children = {
            850, 859
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            851, 855
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            852, 854
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            853, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            856, 858
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            857, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            860, 864
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            861, 863
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            862, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            865, 867
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            866, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            869, 873
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            870, 872
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            871, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            874, 876
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            875, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -622592,
        .children = {
            878, 917
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            879, 888
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -32768,
        .children = {
            880, 884
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            881, 883
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            882, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            885, 887
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            886, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -32768,
        .children = {
            889, 908
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 32768,
        .children = {
            890, 899
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
            891, 895
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            892, 894
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            893, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            896, 898
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            897, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            900, 904
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            901, 903
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            902, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            905, 907
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            906, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            909, 913
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            910, 912
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            911, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            914, 916
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            915, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2162688,
        .children = {
            918, 931
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1146880,
        .children = {
            919, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            920, 922
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            921, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 3473408,
        .children = {
            923, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -32768,
        .children = {
            924, 928
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3801088,
        .children = {
            925, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            926, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            927, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 4128768,
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
        .distance = 4718592,
        .children = {
            930, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = -1146880,
        .children = {
            932, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            933, 935
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -1, 934
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
        .distance = -32768,
        .children = {
            936, 944
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 851968,
        .children = {
            -2, 937
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -2, 938
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -163840,
        .children = {
            939, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 32768,
        .children = {
            940, 942
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            -2, 941
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            -2, 943
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
        .distance = 786432,
        .children = {
            -2, 945
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
            -2, 946
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -2, 947
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -163840,
        .children = {
            948, -1
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
            -2, 949
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
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
        .distance = 32768,
        .children = {
            951, 1223
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 622592,
        .children = {
            952, 1120
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2162688,
        .children = {
            953, 1023
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            954, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            -1, 955
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2490368,
        .children = {
            956, 1013
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            957, 978
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            958, 976
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            959, 964
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            960, 961
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 1081344,
        .children = {
            962, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
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
        .distance = 4456448,
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
        .distance = 3145728,
        .children = {
            965, 971
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4063231,
        .children = {
            966, 968
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, 967
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
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
        .distance = -360448,
        .children = {
            -2, 969
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -1, 970
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3473409,
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
        .distance = 2818048,
        .children = {
            972, 974
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, 973
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
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
        .distance = -360448,
        .children = {
            -2, 975
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
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
        .distance = 4456448,
        .children = {
            977, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 4390912,
        .children = {
            979, 990
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            980, 981
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 950272,
        .children = {
            982, 985
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            -2, 983
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            984, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1053918,
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
        .distance = -622592,
        .children = {
            986, 987
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
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
        .distance = 4456448,
        .children = {
            -2, 988
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, 989
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
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
        .distance = -622592,
        .children = {
            991, 997
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            992, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1053918,
        .children = {
            993, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2818049,
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
        .distance = 4063231,
        .children = {
            -2, 995
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3473409,
        .children = {
            -2, 996
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3145728,
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
        .distance = 3145728,
        .children = {
            998, 1007
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            -2, 999
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3801088,
        .children = {
            1000, 1002
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, 1001
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
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
        .distance = 3735552,
        .children = {
            1003, 1005
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, 1004
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
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
        .distance = 1112182,
        .children = {
            -2, 1006
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
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
        .distance = 950272,
        .children = {
            -2, 1008
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3080192,
        .children = {
            1009, 1011
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, 1010
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
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
        .distance = 1112182,
        .children = {
            -2, 1012
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
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
        .distance = 1015808,
        .children = {
            1014, 1017
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            1015, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            1016, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
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
        .distance = 950272,
        .children = {
            1018, 1020
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            1019, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1053918,
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
        .distance = -622592,
        .children = {
            -1, 1021
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, 1022
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
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
        .distance = -1015808,
        .children = {
            1024, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            -1, 1025
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
            1026, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            1027, 1085
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            1028, 1047
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1053918,
        .children = {
            1029, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            1030, 1039
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1441792,
        .children = {
            1031, 1038
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1769472,
        .children = {
            1032, 1036
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            1033, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2097152,
        .children = {
            1034, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            1035, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
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
        .distance = -688128,
        .children = {
            1037, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
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
        .distance = -688128,
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
        .distance = 1507328,
        .children = {
            1040, 1043
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1835008,
        .children = {
            -2, 1041
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            1042, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1769472,
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
        .distance = 1179648,
        .children = {
            1044, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            1045, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1441792,
        .children = {
            1046, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
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
        .distance = -622592,
        .children = {
            1048, 1066
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 786432,
        .children = {
            1049, 1051
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            -2, 1050
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1053918,
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
        .distance = 458752,
        .children = {
            1052, 1054
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            -2, 1053
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1053918,
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
        .distance = -360448,
        .children = {
            1055, 1061
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1056, 1058
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            -2, 1057
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1053918,
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
        .distance = 1015808,
        .children = {
            1059, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            1060, -2
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
            1062, 1065
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1131034,
        .children = {
            -2, 1063
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1064, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1053918,
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
        .distance = 1131034,
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
        .distance = 196608,
        .children = {
            1067, 1075
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 786432,
        .children = {
            1068, 1070
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            1069, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
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
        .distance = 458752,
        .children = {
            1071, 1073
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            1072, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
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
        .distance = 1015808,
        .children = {
            1074, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
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
        .distance = 1015808,
        .children = {
            1076, 1081
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
            1077, 1079
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            -2, 1078
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
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
        .distance = -688128,
        .children = {
            1080, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1131034,
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
        .distance = 131072,
        .children = {
            -2, 1082
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            -2, 1083
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
            -2, 1084
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1204864,
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
        .distance = -622592,
        .children = {
            1086, 1087
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
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
        .distance = 851968,
        .children = {
            1088, 1101
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1507328,
        .children = {
            1089, 1094
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1835008,
        .children = {
            1090, 1092
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, 1091
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
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
        .distance = 1112182,
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
        .distance = -884736,
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
        .distance = 1179648,
        .children = {
            1095, 1097
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, 1096
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
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
        .distance = 720896,
        .children = {
            1098, 1099
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
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
        .distance = -884736,
        .children = {
            1100, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
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
        .distance = 196608,
        .children = {
            1102, 1111
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            1103, 1107
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 720896,
        .children = {
            1104, 1105
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
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
        .distance = -884736,
        .children = {
            1106, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
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
        .distance = 720896,
        .children = {
            1108, 1109
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
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
        .distance = -884736,
        .children = {
            1110, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
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
        .distance = 131072,
        .children = {
            1112, 1116
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 720896,
        .children = {
            1113, 1114
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
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
        .distance = -884736,
        .children = {
            1115, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
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
        .distance = -688128,
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
        .distance = -131072,
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
        .distance = 688128,
        .children = {
            1119, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1204864,
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
        .distance = 2162688,
        .children = {
            1121, 1172
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1081344,
        .children = {
            1122, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2490368,
        .children = {
            1123, 1167
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            1124, 1126
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            1125, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 3080192,
        .children = {
            1127, 1163
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            1128, 1137
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            1129, 1131
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            1130, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = -1015808,
        .children = {
            1132, 1136
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
            -2, 1133
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            1134, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, 1135
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
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
        .distance = 360448,
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
        .distance = 3735552,
        .children = {
            1138, 1149
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
            1139, 1140
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
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
        .distance = 4063232,
        .children = {
            1141, 1143
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            1142, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
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
        .distance = -1015808,
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
        .distance = 3801088,
        .children = {
            1145, 1147
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            1146, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
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
        .distance = -950272,
        .children = {
            1148, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
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
        .distance = 3407872,
        .children = {
            1150, 1155
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
            1151, 1152
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
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
        .distance = -1015808,
        .children = {
            1153, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            1154, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
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
        .distance = 360448,
        .children = {
            1156, 1157
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
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
        .distance = -1015808,
        .children = {
            1158, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3145728,
        .children = {
            1159, 1161
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            1160, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
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
        .distance = -950272,
        .children = {
            1162, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
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
        .distance = 360448,
        .children = {
            1164, 1165
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
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
        .distance = -950272,
        .children = {
            1166, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
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
        .distance = -950272,
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
        .distance = 294912,
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
        .distance = -884736,
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
            1171, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
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
        .distance = 524288,
        .children = {
            1173, 1200
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, 1174
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1081344,
        .children = {
            1175, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1507328,
        .children = {
            1176, 1185
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1835008,
        .children = {
            1177, 1181
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
            1178, 1179
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
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
        .distance = -950272,
        .children = {
            1180, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
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
        .distance = 360448,
        .children = {
            1182, 1183
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
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
        .distance = -950272,
        .children = {
            1184, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
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
        .distance = 1179648,
        .children = {
            1186, 1190
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
            1187, 1188
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
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
        .distance = -950272,
        .children = {
            1189, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
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
        .distance = 851968,
        .children = {
            1191, 1195
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
            1192, 1193
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
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
        .distance = -950272,
        .children = {
            1194, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
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
        .distance = 294912,
        .children = {
            1196, 1199
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            -2, 1197
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, 1198
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
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
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
            1201, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            1202, 1203
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
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
        .distance = -1081344,
        .children = {
            1204, -1
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
            1205, 1210
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            1206, 1208
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            1207, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
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
            1209, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
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
        .distance = -1015808,
        .children = {
            1211, 1221
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            1212, 1218
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1213, 1215
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            1214, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
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
        .distance = -950272,
        .children = {
            -2, 1216
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
            1217, -2
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
            1219, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            1220, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
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
            -1, 1222
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -622592,
        .children = {
            1224, 1321
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            1225, 1246
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2162688,
        .children = {
            1226, 1238
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1081344,
        .children = {
            1227, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            1228, 1230
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            1229, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 3145728,
        .children = {
            1231, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3801088,
        .children = {
            1232, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4128768,
        .children = {
            1233, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            1234, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            1235, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, 1236
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            1237, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
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
        .distance = -1081344,
        .children = {
            1239, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1240, 1241
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
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
            1242, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            -2, 1243
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            -2, 1244
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, 1245
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
        .distance = 2162688,
        .children = {
            1247, 1280
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1081344,
        .children = {
            1248, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3145728,
        .children = {
            1249, 1267
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3801088,
        .children = {
            1250, 1260
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            1251, 1253
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            1252, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = -884736,
        .children = {
            1254, 1255
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
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
        .distance = 4128768,
        .children = {
            1256, 1258
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, 1257
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, 1259
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, 1261
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3473408,
        .children = {
            1262, 1264
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, 1263
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            -2, 1265
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
            -2, 1266
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
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
        .distance = 2818048,
        .children = {
            1268, 1272
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            1269, 1270
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
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
            -2, 1271
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
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
        .distance = -884736,
        .children = {
            -1, 1273
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2490368,
        .children = {
            1274, 1277
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            -2, 1275
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
            -2, 1276
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
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
        .distance = -950272,
        .children = {
            -2, 1278
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
            -2, 1279
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
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
        .distance = -1081344,
        .children = {
            1281, -1
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
            1282, 1309
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, 1283
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            1284, 1296
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            -2, 1285
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1835008,
        .children = {
            1286, 1288
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
            -2, 1287
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
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
        .distance = 1507328,
        .children = {
            1289, 1294
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1769472,
        .children = {
            1290, 1292
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
            -2, 1291
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
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
            -2, 1293
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
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
            -2, 1295
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
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
        .distance = 524288,
        .children = {
            1297, 1306
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            -2, 1298
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 851968,
        .children = {
            1299, 1304
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            1300, 1302
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, 1301
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, 1303
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
            -2, 1305
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
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
        .distance = -950272,
        .children = {
            -2, 1307
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, 1308
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
            1310, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            1311, 1312
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
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
        .distance = -1015808,
        .children = {
            1313, 1319
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
            1314, 1317
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            1315, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1316, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
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
            -2, 1318
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
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
            1320, -1
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
        .distance = 2162688,
        .children = {
            1322, 1396
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            1323, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2490368,
        .children = {
            1324, 1385
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1146880,
        .children = {
            1325, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            1326, 1355
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            1327, 1333
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            1328, 1329
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = 4128768,
        .children = {
            1330, 1331
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1053918,
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
        .distance = -1053918,
        .children = {
            -1, 1332
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2818048,
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
        .distance = 3145728,
        .children = {
            1334, 1349
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            1335, 1341
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            1336, 1337
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = -950272,
        .children = {
            1338, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            1339, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            1340, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
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
        .distance = 3801088,
        .children = {
            1342, 1347
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            1343, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -720896,
        .children = {
            1344, 1346
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            1345, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
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
        .distance = -1112182,
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
        .distance = -1112182,
        .children = {
            1348, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
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
        .distance = 2818048,
        .children = {
            1350, 1352
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            1351, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
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
        .distance = -950272,
        .children = {
            1353, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            1354, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
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
        .distance = 3473408,
        .children = {
            1356, 1372
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4128768,
        .children = {
            1357, 1363
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            1358, 1360
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            1359, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
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
        .distance = -688128,
        .children = {
            1361, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            -2, 1362
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
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
        .distance = 3801088,
        .children = {
            1364, 1368
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            1365, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            1366, 1367
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
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
        .distance = -360448,
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
        .distance = -688128,
        .children = {
            1369, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            1370, 1371
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
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
        .distance = -360448,
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
        .distance = 2818048,
        .children = {
            1373, 1382
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3145728,
        .children = {
            1374, 1378
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            1375, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            1376, 1377
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
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
        .distance = -360448,
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
        .distance = -688128,
        .children = {
            1379, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            1380, 1381
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
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
        .distance = -360448,
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
        .distance = -688128,
        .children = {
            1383, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            -2, 1384
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
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
        .distance = -1015808,
        .children = {
            1386, 1392
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            1387, 1390
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            -1, 1388
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            1389, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
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
        .distance = -622592,
        .children = {
            1391, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1053918,
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
        .distance = -688128,
        .children = {
            1393, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1146880,
        .children = {
            1394, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            -2, 1395
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
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
        .distance = -1015808,
        .children = {
            1397, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1146880,
        .children = {
            1398, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 851968,
        .children = {
            1399, 1432
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            1400, 1421
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            1401, 1415
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            1402, 1411
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            -1, 1403
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1835008,
        .children = {
            1404, 1406
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            1405, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
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
        .distance = 1507328,
        .children = {
            1407, 1409
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            1408, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
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
        .distance = -1112182,
        .children = {
            1410, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
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
        .distance = -1053918,
        .children = {
            -1, 1412
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1769472,
        .children = {
            1413, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            1414, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2097152,
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
        .distance = -688128,
        .children = {
            1416, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1507328,
        .children = {
            1417, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2097152,
        .children = {
            1418, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            1419, 1420
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
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
        .distance = -360448,
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
        .distance = -1015808,
        .children = {
            1422, 1430
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            1423, 1428
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            -1, 1424
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -720896,
        .children = {
            1425, 1427
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            1426, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
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
        .distance = -1112182,
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
        .distance = -622592,
        .children = {
            1429, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1053918,
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
        .distance = -360448,
        .children = {
            -2, 1431
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
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
        .distance = 196608,
        .children = {
            1433, 1456
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            1434, 1445
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            1435, 1443
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            1436, 1441
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            -1, 1437
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -720896,
        .children = {
            1438, 1440
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            1439, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
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
        .distance = -1112182,
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
        .distance = -622592,
        .children = {
            1442, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1053918,
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
        .distance = -360448,
        .children = {
            -2, 1444
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
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
        .distance = -1015808,
        .children = {
            1446, 1454
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            1447, 1452
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            -1, 1448
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -720896,
        .children = {
            1449, 1451
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            1450, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
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
        .distance = -1112182,
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
        .distance = -622592,
        .children = {
            1453, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1053918,
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
        .distance = -360448,
        .children = {
            -2, 1455
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
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
            1457, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            1458, 1474
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            1459, 1461
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1460, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1053918,
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
        .distance = -950272,
        .children = {
            1462, 1471
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1463, 1467
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -720896,
        .children = {
            1464, 1466
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            1465, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
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
        .distance = -1112182,
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
        .distance = -688128,
        .children = {
            -2, 1468
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
            -2, 1469
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -688128,
        .children = {
            -2, 1470
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1204864,
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
            -2, 1472
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            -2, 1473
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1204864,
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
        .distance = -688128,
        .children = {
            1475, -1
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
            -2, 1476
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            1477, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1131034,
        .children = {
            -2, -1
        }
    },
};
BSPTree3 bsp_player = {.nodes=bspNodes_player, .numNodes = 1478};

int numTris = 1048;
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
        {-983040, -327680, 655360},
        {-1048576, 0, 327680},
        {-1048576, -327680, 327680},
        {192, 224},
        {223, 255},
        {223, 224},
        14
    },
    {
        {-983040, -327680, 655360},
        {-983040, 0, 655360},
        {-1048576, 0, 327680},
        {192, 224},
        {192, 255},
        {223, 255},
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
        {327680, -1310720, 917504},
        {0, -1310720, 983040},
        {0, -1310720, 917504},
        {31, 171},
        {0, 166},
        {0, 171},
        11
    },
    {
        {327680, -1310720, 917504},
        {327680, -1310720, 983040},
        {0, -1310720, 983040},
        {31, 171},
        {31, 166},
        {0, 166},
        11
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
        {0, -1310720, 917504},
        {-327680, -1310720, 983040},
        {-327680, -1310720, 917504},
        {255, 171},
        {224, 166},
        {224, 171},
        11
    },
    {
        {0, -1310720, 917504},
        {0, -1310720, 983040},
        {-327680, -1310720, 983040},
        {255, 171},
        {255, 166},
        {224, 166},
        11
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
        {0, -688128, 917504},
        {-327680, -655360, 917504},
        {-327680, -688128, 917504},
        {255, 88},
        {176, 95},
        {176, 88},
        11
    },
    {
        {0, -688128, 917504},
        {0, -655360, 917504},
        {-327680, -655360, 917504},
        {255, 88},
        {255, 95},
        {176, 95},
        11
    },
    {
        {0, -655360, 917504},
        {-327680, -655360, 983040},
        {-327680, -655360, 917504},
        {255, 31},
        {176, 16},
        {176, 31},
        11
    },
    {
        {0, -655360, 917504},
        {0, -655360, 983040},
        {-327680, -655360, 983040},
        {255, 31},
        {255, 16},
        {176, 16},
        11
    },
    {
        {0, -688128, 983040},
        {-327680, -688128, 917504},
        {-327680, -688128, 983040},
        {255, 16},
        {176, 31},
        {176, 16},
        11
    },
    {
        {0, -688128, 983040},
        {0, -688128, 917504},
        {-327680, -688128, 917504},
        {255, 16},
        {255, 31},
        {176, 31},
        11
    },
    {
        {327680, -688128, 917504},
        {0, -655360, 917504},
        {0, -688128, 917504},
        {79, 88},
        {0, 95},
        {0, 88},
        11
    },
    {
        {327680, -688128, 917504},
        {327680, -655360, 917504},
        {0, -655360, 917504},
        {79, 88},
        {79, 95},
        {0, 95},
        11
    },
    {
        {327680, -655360, 917504},
        {0, -655360, 983040},
        {0, -655360, 917504},
        {79, 31},
        {0, 16},
        {0, 31},
        11
    },
    {
        {327680, -655360, 917504},
        {327680, -655360, 983040},
        {0, -655360, 983040},
        {79, 31},
        {79, 16},
        {0, 16},
        11
    },
    {
        {327680, -688128, 983040},
        {0, -688128, 917504},
        {0, -688128, 983040},
        {79, 16},
        {0, 31},
        {0, 16},
        11
    },
    {
        {327680, -688128, 983040},
        {327680, -688128, 917504},
        {0, -688128, 917504},
        {79, 16},
        {79, 31},
        {0, 31},
        11
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
    {
        {-983040, -655360, 655360},
        {-1048576, -327680, 327680},
        {-1048576, -655360, 327680},
        {192, 192},
        {223, 223},
        {223, 192},
        14
    },
    {
        {-983040, -655360, 655360},
        {-983040, -327680, 655360},
        {-1048576, -327680, 327680},
        {192, 192},
        {192, 223},
        {223, 223},
        14
    },
    {
        {-983040, -983040, 655360},
        {-1048576, -655360, 327680},
        {-1048576, -983040, 327680},
        {192, 160},
        {223, 191},
        {223, 160},
        14
    },
    {
        {-983040, -983040, 655360},
        {-983040, -655360, 655360},
        {-1048576, -655360, 327680},
        {192, 160},
        {192, 191},
        {223, 191},
        14
    },
    {
        {-983040, -1310720, 655360},
        {-1048576, -983040, 327680},
        {-1048576, -1310720, 327680},
        {192, 128},
        {223, 159},
        {223, 128},
        14
    },
    {
        {-983040, -1310720, 655360},
        {-983040, -983040, 655360},
        {-1048576, -983040, 327680},
        {192, 128},
        {192, 159},
        {223, 159},
        14
    },
    {
        {-983040, -1638400, 655360},
        {-1048576, -1310720, 327680},
        {-1048576, -1638400, 327680},
        {192, 96},
        {223, 127},
        {223, 96},
        14
    },
    {
        {-983040, -1638400, 655360},
        {-983040, -1310720, 655360},
        {-1048576, -1310720, 327680},
        {192, 96},
        {192, 127},
        {223, 127},
        14
    },
    {
        {-983040, -1966080, 655360},
        {-1048576, -1638400, 327680},
        {-1048576, -1966080, 327680},
        {192, 64},
        {223, 95},
        {223, 64},
        14
    },
    {
        {-983040, -1966080, 655360},
        {-983040, -1638400, 655360},
        {-1048576, -1638400, 327680},
        {192, 64},
        {192, 95},
        {223, 95},
        14
    },
    {
        {-1048576, -327680, -327680},
        {-983040, 0, -655360},
        {-983040, -327680, -655360},
        {32, 224},
        {63, 255},
        {63, 224},
        14
    },
    {
        {-1048576, -327680, -327680},
        {-1048576, 0, -327680},
        {-983040, 0, -655360},
        {32, 224},
        {32, 255},
        {63, 255},
        14
    },
    {
        {-1048576, -655360, -327680},
        {-983040, -327680, -655360},
        {-983040, -655360, -655360},
        {32, 192},
        {63, 223},
        {63, 192},
        14
    },
    {
        {-1048576, -655360, -327680},
        {-1048576, -327680, -327680},
        {-983040, -327680, -655360},
        {32, 192},
        {32, 223},
        {63, 223},
        14
    },
    {
        {-1048576, -983040, -327680},
        {-983040, -655360, -655360},
        {-983040, -983040, -655360},
        {32, 160},
        {63, 191},
        {63, 160},
        14
    },
    {
        {-1048576, -983040, -327680},
        {-1048576, -655360, -327680},
        {-983040, -655360, -655360},
        {32, 160},
        {32, 191},
        {63, 191},
        14
    },
    {
        {-1048576, -1310720, -327680},
        {-983040, -983040, -655360},
        {-983040, -1310720, -655360},
        {32, 128},
        {63, 159},
        {63, 128},
        14
    },
    {
        {-1048576, -1310720, -327680},
        {-1048576, -983040, -327680},
        {-983040, -983040, -655360},
        {32, 128},
        {32, 159},
        {63, 159},
        14
    },
    {
        {-1048576, -1638400, -327680},
        {-983040, -1310720, -655360},
        {-983040, -1638400, -655360},
        {32, 96},
        {63, 127},
        {63, 96},
        14
    },
    {
        {-1048576, -1638400, -327680},
        {-1048576, -1310720, -327680},
        {-983040, -1310720, -655360},
        {32, 96},
        {32, 127},
        {63, 127},
        14
    },
    {
        {-1048576, -1966080, -327680},
        {-983040, -1638400, -655360},
        {-983040, -1966080, -655360},
        {32, 64},
        {63, 95},
        {63, 64},
        14
    },
    {
        {-1048576, -1966080, -327680},
        {-1048576, -1638400, -327680},
        {-983040, -1638400, -655360},
        {32, 64},
        {32, 95},
        {63, 95},
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
        {983040, 0, 655360},
        {1048576, -327680, 327680},
        {1048576, 0, 327680},
        {192, 255},
        {223, 224},
        {223, 255},
        14
    },
    {
        {983040, 0, 655360},
        {983040, -327680, 655360},
        {1048576, -327680, 327680},
        {192, 255},
        {192, 224},
        {223, 224},
        14
    },
    {
        {983040, -327680, 655360},
        {1048576, -655360, 327680},
        {1048576, -327680, 327680},
        {192, 223},
        {223, 192},
        {223, 223},
        14
    },
    {
        {983040, -327680, 655360},
        {983040, -655360, 655360},
        {1048576, -655360, 327680},
        {192, 223},
        {192, 192},
        {223, 192},
        14
    },
    {
        {983040, -655360, 655360},
        {1048576, -983040, 327680},
        {1048576, -655360, 327680},
        {192, 191},
        {223, 160},
        {223, 191},
        14
    },
    {
        {983040, -655360, 655360},
        {983040, -983040, 655360},
        {1048576, -983040, 327680},
        {192, 191},
        {192, 160},
        {223, 160},
        14
    },
    {
        {983040, -983040, 655360},
        {1048576, -1310720, 327680},
        {1048576, -983040, 327680},
        {192, 159},
        {223, 128},
        {223, 159},
        14
    },
    {
        {983040, -983040, 655360},
        {983040, -1310720, 655360},
        {1048576, -1310720, 327680},
        {192, 159},
        {192, 128},
        {223, 128},
        14
    },
    {
        {983040, -1310720, 655360},
        {1048576, -1638400, 327680},
        {1048576, -1310720, 327680},
        {192, 127},
        {223, 96},
        {223, 127},
        14
    },
    {
        {983040, -1310720, 655360},
        {983040, -1638400, 655360},
        {1048576, -1638400, 327680},
        {192, 127},
        {192, 96},
        {223, 96},
        14
    },
    {
        {983040, -1638400, 655360},
        {1048576, -1966080, 327680},
        {1048576, -1638400, 327680},
        {192, 95},
        {223, 64},
        {223, 95},
        14
    },
    {
        {983040, -1638400, 655360},
        {983040, -1966080, 655360},
        {1048576, -1966080, 327680},
        {192, 95},
        {192, 64},
        {223, 64},
        14
    },
    {
        {-1114112, -4587520, 983040},
        {-1114112, -4653056, -983040},
        {-1114112, -4587520, -983040},
        {239, 159},
        {16, 144},
        {16, 159},
        11
    },
    {
        {-1114112, -4587520, 983040},
        {-1114112, -4653056, 983040},
        {-1114112, -4653056, -983040},
        {239, 159},
        {239, 144},
        {16, 144},
        11
    },
    {
        {1114112, -4653056, -983040},
        {-1114112, -4587520, -983040},
        {-1114112, -4653056, -983040},
        {15, 144},
        {240, 159},
        {240, 144},
        11
    },
    {
        {1114112, -4653056, -983040},
        {1114112, -4587520, -983040},
        {-1114112, -4587520, -983040},
        {15, 144},
        {15, 159},
        {240, 159},
        11
    },
    {
        {1114112, -4653056, 983040},
        {-1114112, -4653056, -983040},
        {-1114112, -4653056, 983040},
        {15, 16},
        {240, 239},
        {240, 16},
        11
    },
    {
        {1114112, -4653056, 983040},
        {1114112, -4653056, -983040},
        {-1114112, -4653056, -983040},
        {15, 16},
        {15, 239},
        {240, 239},
        11
    },
    {
        {1114112, -4587520, 983040},
        {-1114112, -4653056, 983040},
        {-1114112, -4587520, 983040},
        {15, 159},
        {240, 144},
        {240, 159},
        11
    },
    {
        {1114112, -4587520, 983040},
        {1114112, -4653056, 983040},
        {-1114112, -4653056, 983040},
        {15, 159},
        {15, 144},
        {240, 144},
        11
    },
    {
        {1114112, -4653056, 983040},
        {1114112, -4587520, -983040},
        {1114112, -4653056, -983040},
        {239, 144},
        {16, 159},
        {16, 144},
        11
    },
    {
        {1114112, -4653056, 983040},
        {1114112, -4587520, 983040},
        {1114112, -4587520, -983040},
        {239, 144},
        {239, 159},
        {16, 159},
        11
    },
    {
        {1048576, 0, -163840},
        {1048576, -163840, -327680},
        {1048576, 0, -327680},
        {15, 255},
        {0, 240},
        {0, 255},
        16
    },
    {
        {1048576, 0, -163840},
        {1048576, -163840, -163840},
        {1048576, -163840, -327680},
        {15, 255},
        {15, 240},
        {0, 240},
        16
    },
    {
        {1048576, -163840, -163840},
        {1048576, -327680, -327680},
        {1048576, -163840, -327680},
        {15, 239},
        {0, 224},
        {0, 239},
        16
    },
    {
        {1048576, -163840, -163840},
        {1048576, -327680, -163840},
        {1048576, -327680, -327680},
        {15, 239},
        {15, 224},
        {0, 224},
        16
    },
    {
        {1048576, -163840, 0},
        {1048576, -327680, -163840},
        {1048576, -163840, -163840},
        {31, 239},
        {16, 224},
        {16, 239},
        16
    },
    {
        {1048576, -163840, 0},
        {1048576, -327680, 0},
        {1048576, -327680, -163840},
        {31, 239},
        {31, 224},
        {16, 224},
        16
    },
    {
        {1048576, 0, 0},
        {1048576, -163840, -163840},
        {1048576, 0, -163840},
        {31, 255},
        {16, 240},
        {16, 255},
        16
    },
    {
        {1048576, 0, 0},
        {1048576, -163840, 0},
        {1048576, -163840, -163840},
        {31, 255},
        {31, 240},
        {16, 240},
        16
    },
    {
        {1048576, 0, 327680},
        {1048576, -65536, 262144},
        {1048576, 0, 262144},
        {63, 255},
        {57, 249},
        {57, 255},
        16
    },
    {
        {1048576, 0, 327680},
        {1048576, -65536, 327680},
        {1048576, -65536, 262144},
        {63, 255},
        {63, 249},
        {57, 249},
        16
    },
    {
        {1048576, 0, 262144},
        {1048576, -65536, 196608},
        {1048576, 0, 196608},
        {57, 255},
        {51, 249},
        {51, 255},
        16
    },
    {
        {1048576, 0, 262144},
        {1048576, -65536, 262144},
        {1048576, -65536, 196608},
        {57, 255},
        {57, 249},
        {51, 249},
        16
    },
    {
        {1048576, 0, 196608},
        {1048576, -65536, 131072},
        {1048576, 0, 131072},
        {50, 255},
        {44, 249},
        {44, 255},
        16
    },
    {
        {1048576, 0, 196608},
        {1048576, -65536, 196608},
        {1048576, -65536, 131072},
        {50, 255},
        {50, 249},
        {44, 249},
        16
    },
    {
        {1048576, 0, 131072},
        {1048576, -65536, 65536},
        {1048576, 0, 65536},
        {44, 255},
        {38, 249},
        {38, 255},
        16
    },
    {
        {1048576, 0, 131072},
        {1048576, -65536, 131072},
        {1048576, -65536, 65536},
        {44, 255},
        {44, 249},
        {38, 249},
        16
    },
    {
        {1048576, 0, 65536},
        {1048576, -65536, 0},
        {1048576, 0, 0},
        {37, 255},
        {32, 249},
        {32, 255},
        16
    },
    {
        {1048576, 0, 65536},
        {1048576, -65536, 65536},
        {1048576, -65536, 0},
        {37, 255},
        {37, 249},
        {32, 249},
        16
    },
    {
        {1048576, -65536, 65536},
        {1048576, -131072, 0},
        {1048576, -65536, 0},
        {37, 249},
        {32, 243},
        {32, 249},
        16
    },
    {
        {1048576, -65536, 65536},
        {1048576, -131072, 65536},
        {1048576, -131072, 0},
        {37, 249},
        {37, 243},
        {32, 243},
        16
    },
    {
        {1048576, -65536, 196608},
        {1048576, -131072, 131072},
        {1048576, -65536, 131072},
        {50, 249},
        {44, 243},
        {44, 249},
        16
    },
    {
        {1048576, -65536, 196608},
        {1048576, -131072, 196608},
        {1048576, -131072, 131072},
        {50, 249},
        {50, 243},
        {44, 243},
        16
    },
    {
        {1048576, -65536, 131072},
        {1048576, -131072, 65536},
        {1048576, -65536, 65536},
        {44, 249},
        {38, 243},
        {38, 249},
        16
    },
    {
        {1048576, -65536, 131072},
        {1048576, -131072, 131072},
        {1048576, -131072, 65536},
        {44, 249},
        {44, 243},
        {38, 243},
        16
    },
    {
        {1048576, -65536, 262144},
        {1048576, -131072, 196608},
        {1048576, -65536, 196608},
        {57, 249},
        {51, 243},
        {51, 249},
        16
    },
    {
        {1048576, -65536, 262144},
        {1048576, -131072, 262144},
        {1048576, -131072, 196608},
        {57, 249},
        {57, 243},
        {51, 243},
        16
    },
    {
        {1048576, -65536, 327680},
        {1048576, -131072, 262144},
        {1048576, -65536, 262144},
        {63, 249},
        {57, 243},
        {57, 249},
        16
    },
    {
        {1048576, -65536, 327680},
        {1048576, -131072, 327680},
        {1048576, -131072, 262144},
        {63, 249},
        {63, 243},
        {57, 243},
        16
    },
    {
        {1048576, -131072, 65536},
        {1048576, -196608, 0},
        {1048576, -131072, 0},
        {37, 242},
        {32, 236},
        {32, 242},
        16
    },
    {
        {1048576, -131072, 65536},
        {1048576, -196608, 65536},
        {1048576, -196608, 0},
        {37, 242},
        {37, 236},
        {32, 236},
        16
    },
    {
        {1048576, -131072, 196608},
        {1048576, -196608, 131072},
        {1048576, -131072, 131072},
        {50, 242},
        {44, 236},
        {44, 242},
        16
    },
    {
        {1048576, -131072, 196608},
        {1048576, -196608, 196608},
        {1048576, -196608, 131072},
        {50, 242},
        {50, 236},
        {44, 236},
        16
    },
    {
        {1048576, -131072, 131072},
        {1048576, -196608, 65536},
        {1048576, -131072, 65536},
        {44, 242},
        {38, 236},
        {38, 242},
        16
    },
    {
        {1048576, -131072, 131072},
        {1048576, -196608, 131072},
        {1048576, -196608, 65536},
        {44, 242},
        {44, 236},
        {38, 236},
        16
    },
    {
        {1048576, -131072, 262144},
        {1048576, -196608, 196608},
        {1048576, -131072, 196608},
        {57, 242},
        {51, 236},
        {51, 242},
        16
    },
    {
        {1048576, -131072, 262144},
        {1048576, -196608, 262144},
        {1048576, -196608, 196608},
        {57, 242},
        {57, 236},
        {51, 236},
        16
    },
    {
        {1048576, -131072, 327680},
        {1048576, -196608, 262144},
        {1048576, -131072, 262144},
        {63, 242},
        {57, 236},
        {57, 242},
        16
    },
    {
        {1048576, -131072, 327680},
        {1048576, -196608, 327680},
        {1048576, -196608, 262144},
        {63, 242},
        {63, 236},
        {57, 236},
        16
    },
    {
        {1048576, -196608, 65536},
        {1048576, -262144, 0},
        {1048576, -196608, 0},
        {37, 236},
        {32, 230},
        {32, 236},
        16
    },
    {
        {1048576, -196608, 65536},
        {1048576, -262144, 65536},
        {1048576, -262144, 0},
        {37, 236},
        {37, 230},
        {32, 230},
        16
    },
    {
        {1048576, -196608, 196608},
        {1048576, -262144, 131072},
        {1048576, -196608, 131072},
        {50, 236},
        {44, 230},
        {44, 236},
        16
    },
    {
        {1048576, -196608, 196608},
        {1048576, -262144, 196608},
        {1048576, -262144, 131072},
        {50, 236},
        {50, 230},
        {44, 230},
        16
    },
    {
        {1048576, -196608, 131072},
        {1048576, -262144, 65536},
        {1048576, -196608, 65536},
        {44, 236},
        {38, 230},
        {38, 236},
        16
    },
    {
        {1048576, -196608, 131072},
        {1048576, -262144, 131072},
        {1048576, -262144, 65536},
        {44, 236},
        {44, 230},
        {38, 230},
        16
    },
    {
        {1048576, -196608, 262144},
        {1048576, -262144, 196608},
        {1048576, -196608, 196608},
        {57, 236},
        {51, 230},
        {51, 236},
        16
    },
    {
        {1048576, -196608, 262144},
        {1048576, -262144, 262144},
        {1048576, -262144, 196608},
        {57, 236},
        {57, 230},
        {51, 230},
        16
    },
    {
        {1048576, -196608, 327680},
        {1048576, -262144, 262144},
        {1048576, -196608, 262144},
        {63, 236},
        {57, 230},
        {57, 236},
        16
    },
    {
        {1048576, -196608, 327680},
        {1048576, -262144, 327680},
        {1048576, -262144, 262144},
        {63, 236},
        {63, 230},
        {57, 230},
        16
    },
    {
        {1048576, -262144, 65536},
        {1048576, -327680, 0},
        {1048576, -262144, 0},
        {37, 229},
        {32, 224},
        {32, 229},
        16
    },
    {
        {1048576, -262144, 65536},
        {1048576, -327680, 65536},
        {1048576, -327680, 0},
        {37, 229},
        {37, 224},
        {32, 224},
        16
    },
    {
        {1048576, -262144, 196608},
        {1048576, -327680, 131072},
        {1048576, -262144, 131072},
        {50, 229},
        {44, 224},
        {44, 229},
        16
    },
    {
        {1048576, -262144, 196608},
        {1048576, -327680, 196608},
        {1048576, -327680, 131072},
        {50, 229},
        {50, 224},
        {44, 224},
        16
    },
    {
        {1048576, -262144, 131072},
        {1048576, -327680, 65536},
        {1048576, -262144, 65536},
        {44, 229},
        {38, 224},
        {38, 229},
        16
    },
    {
        {1048576, -262144, 131072},
        {1048576, -327680, 131072},
        {1048576, -327680, 65536},
        {44, 229},
        {44, 224},
        {38, 224},
        16
    },
    {
        {1048576, -262144, 262144},
        {1048576, -327680, 196608},
        {1048576, -262144, 196608},
        {57, 229},
        {51, 224},
        {51, 229},
        16
    },
    {
        {1048576, -262144, 262144},
        {1048576, -327680, 262144},
        {1048576, -327680, 196608},
        {57, 229},
        {57, 224},
        {51, 224},
        16
    },
    {
        {1048576, -262144, 327680},
        {1048576, -327680, 262144},
        {1048576, -262144, 262144},
        {63, 229},
        {57, 224},
        {57, 229},
        16
    },
    {
        {1048576, -262144, 327680},
        {1048576, -327680, 327680},
        {1048576, -327680, 262144},
        {63, 229},
        {63, 224},
        {57, 224},
        16
    },
};


#pragma endregion

//////////////////////////
// Controller Functions //
//////////////////////////
#pragma region Controller Funcs


// Functions for look controls
void lookLeft(void){
    mainCamera.yaw += 16;
}
void lookRight(void){
    mainCamera.yaw -= 16;
}
void lookUp(void){
    mainCamera.pitch -= 16;
    if(mainCamera.pitch<-1024){
        mainCamera.pitch = -1024;
    }
}
void lookDown(void){
    mainCamera.pitch += 16;
    if(mainCamera.pitch>1024){
        mainCamera.pitch = 1024;
    }
}

// Functions for move controls
void moveCameraForward(void){
    mainCamera.x -=  ((isin(mainCamera.yaw) * MOVEMENT_SPEED>>12)>>12);
    mainCamera.z +=  ((icos(mainCamera.yaw) * MOVEMENT_SPEED>>12)>>12);
}
void moveCameraBackward(void){
    mainCamera.x +=  ((isin(mainCamera.yaw) * MOVEMENT_SPEED>>12)>>12);
    mainCamera.z -=  ((icos(mainCamera.yaw) * MOVEMENT_SPEED>>12)>>12);
}
void moveCameraLeft(void){
    mainCamera.x -=  ((icos(mainCamera.yaw) * MOVEMENT_SPEED>>12)>>12);
    mainCamera.z += -((isin(mainCamera.yaw) * MOVEMENT_SPEED>>12)>>12);
}
void moveCameraRight(void){
    mainCamera.x +=  ((icos(mainCamera.yaw) * MOVEMENT_SPEED>>12)>>12);
    mainCamera.z -= -((isin(mainCamera.yaw) * MOVEMENT_SPEED>>12)>>12);
}
void moveCameraUp(void){
    cameraHeight -= 8;
    if(cameraHeight < -((PLAYER_BBOX_Y/2)>>GTE_SCALE_FACTOR)){
        cameraHeight = -((PLAYER_BBOX_Y/2)>>GTE_SCALE_FACTOR);
    }
}
void moveCameraDown(void){
    cameraHeight += 8;
    if(cameraHeight > ((PLAYER_BBOX_Y/2)>>GTE_SCALE_FACTOR)){
        cameraHeight = ((PLAYER_BBOX_Y/2)>>GTE_SCALE_FACTOR);
    }
}


// TODO: This overwrites the value rather than add onto it.
// So if you press two buttons, you only move in one direction.
// Maybe create a movement vector similar to what Source does?
// Functions for move controls
void movePlayerForward(void){
    player.velocity.x = -(isin(mainCamera.yaw) * MOVEMENT_SPEED)>>12;
    player.velocity.z =  (icos(mainCamera.yaw) * MOVEMENT_SPEED)>>12;
}
void movePlayerBackward(void){
    player.velocity.x =  (isin(mainCamera.yaw) * MOVEMENT_SPEED)>>12;
    player.velocity.z = -(icos(mainCamera.yaw) * MOVEMENT_SPEED)>>12;
}
void movePlayerLeft(void){
    player.velocity.x = -(icos(mainCamera.yaw) * MOVEMENT_SPEED)>>12;
    player.velocity.z = -(isin(mainCamera.yaw) * MOVEMENT_SPEED)>>12;
}
void movePlayerRight(void){
    player.velocity.x =  (icos(mainCamera.yaw) * MOVEMENT_SPEED)>>12;
    player.velocity.z =  (isin(mainCamera.yaw) * MOVEMENT_SPEED)>>12;
}

void playerJump(void){
    if(player.isGrounded || player.coyoteTimer > 0){
        player.velocity.y = -JUMP_FORCE;
        player.isGrounded = false;
        player.coyoteTimer = 0;
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
    initGPU();//
    
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
    controller_subscribeOnKeyHold(movePlayerLeft,         BUTTON_INDEX_LEFT    );
    controller_subscribeOnKeyHold(movePlayerRight,        BUTTON_INDEX_RIGHT   );
    controller_subscribeOnKeyHold(movePlayerForward,      BUTTON_INDEX_UP      );
    controller_subscribeOnKeyHold(movePlayerBackward,     BUTTON_INDEX_DOWN    );
    controller_subscribeOnKeyHold(playerJump,             BUTTON_INDEX_R2      );
    controller_subscribeOnKeyHold(NULL,                   BUTTON_INDEX_L2      );
    controller_subscribeOnKeyHold(lookLeft,               BUTTON_INDEX_SQUARE  );
    controller_subscribeOnKeyHold(lookRight,              BUTTON_INDEX_CIRCLE  );
    controller_subscribeOnKeyHold(lookUp,                 BUTTON_INDEX_TRIANGLE);
    controller_subscribeOnKeyHold(lookDown,               BUTTON_INDEX_X       );
    controller_subscribeOnKeyHold(moveCameraDown,         BUTTON_INDEX_L1      );
    controller_subscribeOnKeyHold(moveCameraUp,           BUTTON_INDEX_R1      );
    controller_subscribeOnKeyDown(toggleOutlines,         BUTTON_INDEX_SELECT  );


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
    mainCamera.y     = 0;
    mainCamera.z     = 0;
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
        if(!player.isGrounded){
            if(player.velocity.y + GRAVITY_CONSTANT > TERMINAL_VELOCITY){
                player.velocity.y = TERMINAL_VELOCITY;
            } else {
                player.velocity.y += GRAVITY_CONSTANT;
            }
        } else {
            // Apply friction if grounded
            if(player.velocity.x >= FRICTION_CONSTANT){
                player.velocity.x -= FRICTION_CONSTANT;
            } else if(player.velocity.x <= -FRICTION_CONSTANT){
                player.velocity.x += FRICTION_CONSTANT;
            } else {
                player.velocity.x = 0;
            }
            if(player.velocity.z >= FRICTION_CONSTANT){
                player.velocity.z -= FRICTION_CONSTANT;
            } else if(player.velocity.z <= -FRICTION_CONSTANT){
                player.velocity.z += FRICTION_CONSTANT;
            } else {
                player.velocity.z = 0;
            }
        }

        // Collide with the BSP tree
        Player3_move(&bsp_player, &player);
        //int playerColour = BSPTree3_pointContents(&bsp_player, 0, player.position) == -1 ? 0xFFFFFF : 0x000000;

        // Move camera to player position
        mainCamera.x     = (player.position.x)>>GTE_SCALE_FACTOR;
        mainCamera.z     = (player.position.z)>>GTE_SCALE_FACTOR;
        //mainCamera.y     = (player.position.y-(20<<12))>>GTE_SCALE_FACTOR; // the same height as the camera in the game
        mainCamera.y = ((player.position.y)>>GTE_SCALE_FACTOR) + cameraHeight;


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
        setTranslationMatrix(0, 0, 0);
        rotateCurrentMatrix(mainCamera.pitch, mainCamera.roll, mainCamera.yaw);
        

        // Render gizmo
        for (int i = 0; i<4; i++){
            transformVertex(&mainCamera, gizmoPoints[i], &transformedGizmoPoints[i]);
            drawCross2(transformedGizmoPoints[i], 0xFFFFFF);
        };
        drawLine2(transformedGizmoPoints[0], transformedGizmoPoints[1], 0x0000FF);
        drawLine2(transformedGizmoPoints[0], transformedGizmoPoints[2], 0x00FF00);
        drawLine2(transformedGizmoPoints[0], transformedGizmoPoints[3], 0xFF0000);



        // When rendering the world, we have an issue with getting too close to large triangles.
        // Looking at shallow angles causes them to disappear/see through walls.
        // This even happens when subdividing the wall.
        // Is it possible that the issue has to do with the MAC value?
        // Perhaps we are being too strict

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
                drawTri2_texturedFlat(transformedTri, &bspTextureInfo[ti].textureInfo, 20);
            }
        }

        // Crosshair
        drawCross2((Vector2){SCREEN_WIDTH/2, SCREEN_HEIGHT/2}, 0x0000FF);

        sprintf(str_Buffer, "Controls:\n D-Pad: Move\n Face Buttons: Look\n Select: Show wireframe\n R2: Jump\n\nCamera Offset: %d", cameraHeight);
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
