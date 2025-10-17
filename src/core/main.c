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
#include "world.h"

#include "registers.h"
#include "system.h"
#pragma endregion

#define MAX_POLYGON_WIDTH 1023
#define MAX_POLYGON_HEIGHT 511


#define MOVEMENT_SPEED (ONE * 8 * MODEL_SCALE_MULTIPLIER)

#define ACCELERATION_CONSTANT (ONE * MODEL_SCALE_MULTIPLIER)
#define MAX_SPEED (ONE * 3 * MODEL_SCALE_MULTIPLIER)
#define JUMP_FORCE (ONE * 18 * MODEL_SCALE_MULTIPLIER)
#define FRICTION_CONSTANT (ONE * MODEL_SCALE_MULTIPLIER)
#define TERMINAL_VELOCITY (ONE * 200 * MODEL_SCALE_MULTIPLIER)
#define GRAVITY_CONSTANT (ONE * MODEL_SCALE_MULTIPLIER)

#define UNIT_SIZE (16) // Define unit sizes12
#define PLAYER_BBOX_X (1 * UNIT_SIZE * ONE * MODEL_SCALE_MULTIPLIER)
#define PLAYER_BBOX_Y (4 * UNIT_SIZE * ONE * MODEL_SCALE_MULTIPLIER)
#define PLAYER_BBOX_Z (1 * UNIT_SIZE * ONE * MODEL_SCALE_MULTIPLIER)


// Built-in debug textures
extern const uint8_t fontData[];
extern const uint8_t fontPalette[];
TextureInfo font;
extern const uint8_t default_32Data[];
//extern const uint8_t default_32Palette[];
TextureInfo default_32;


Camera mainCamera;
Player3 player;
char str_Buffer[256];
int screenColor = 0x000000;
int wallColor = 0x3c82fa;
int gteScaleFactor = 0;
bool drawOutlines = false;
int cameraHeight = 0;
int debugVariable = 0;
int drawnQuads = 0;


int timerValueA, timerValueB, timerValueC, timerValueD;
int subTimerValueA, subTimerValueB, subTimerValueC, subTimerValueD;
int subTimerTotalA, subTimerTotalB, subTimerTotalC, subTimerTotalD;
int subTimerAvgA,   subTimerAvgB,   subTimerAvgC,   subTimerAvgD;


// 3D direction Gizmo
Vector3 gizmoPoints[4] = {
    {0, 0, 0},
    {100<<12, 0, 0},
    {0, 100<<12, 0},
    {0, 0, 100<<12}
};
Vector2 transformedGizmoPoints[4];


//////////////////////////////
// Drawing Helper Functions //
//////////////////////////////
#pragma region Drawing Helpers
static void drawCross2(DMAChain *chain, Vector2 p, uint32_t colour){
    int32_t x, y;
    x = p.x;
    y = p.y;

    dmaPtr = allocatePacket(chain, 0, 3);
    dmaPtr[0] = colour | gp0_line(false, false);
    dmaPtr[1] = gp0_xy(x-2, y-2);
    dmaPtr[2] = gp0_xy(x+2, y+2);

    dmaPtr = allocatePacket(chain, 0, 3);
    dmaPtr[0] = colour | gp0_line(false, false);
    dmaPtr[1] = gp0_xy(x+2, y-2);
    dmaPtr[2] = gp0_xy(x-2, y+2);
}
static void drawLine2(DMAChain *chain, Vector2 a, Vector2 b, uint32_t colour){
    dmaPtr = allocatePacket(chain, 0, 3);
    dmaPtr[0] = colour | gp0_line(false, false);
    dmaPtr[1] = gp0_xy(a.x, a.y);
    dmaPtr[2] = gp0_xy(b.x, b.y);
}
static void drawTri2(DMAChain *chain, Tri2 tri, uint32_t colour){
    dmaPtr = allocatePacket(chain, tri.z, 4);
    dmaPtr[0] = colour | gp0_triangle(false, false);
    dmaPtr[1] = gp0_xy(tri.a.x, tri.a.y);
    dmaPtr[2] = gp0_xy(tri.b.x, tri.b.y);
    dmaPtr[3] = gp0_xy(tri.c.x, tri.c.y);
}
static void drawTri2_texturedFlat(DMAChain *chain, Tri2_texturedFlat tri, TextureInfo *texinfo, int max_recursion){

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
            activeChain,
            (Tri2_texturedFlat) {
                tri.a, va, vc,
                tri.z,
                tri.auv, ta, tc
            },
            texinfo,
            max_recursion
        );
        drawTri2_texturedFlat(
            activeChain,
            (Tri2_texturedFlat) {
                va, tri.b, vb,
                tri.z,
                ta, tri.buv, tb
            },
            texinfo,
            max_recursion
        );
        drawTri2_texturedFlat(
            activeChain,
            (Tri2_texturedFlat) {
                vb, tri.c, vc,
                tri.z,
                tb, tri.cuv, tc
            },
            texinfo,
            max_recursion
        );
        drawTri2_texturedFlat(
            activeChain,
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

    dmaPtr = allocatePacket(chain, tri.z, 8);
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
        drawLine2(activeChain, (Vector2){tri.a.x, tri.a.y},(Vector2){tri.b.x, tri.b.y}, 0xFFFFFF); // AB
        drawLine2(activeChain, (Vector2){tri.b.x, tri.b.y},(Vector2){tri.c.x, tri.c.y}, 0xFFFFFF); // BC
        drawLine2(activeChain, (Vector2){tri.c.x, tri.c.y},(Vector2){tri.a.x, tri.a.y}, 0xFFFFFF); // CA
    }

}
static void drawQuad2(DMAChain *chain, Quad2 quad, uint32_t colour){    
    dmaPtr = allocatePacket(activeChain, quad.z, 5);
    dmaPtr[0] = colour | gp0_shadedQuad(false, false, false);
    dmaPtr[1] = gp0_xy(quad.a.x, quad.a.y);
    dmaPtr[2] = gp0_xy(quad.b.x, quad.b.y);
    dmaPtr[3] = gp0_xy(quad.c.x, quad.c.y);
    dmaPtr[4] = gp0_xy(quad.d.x, quad.d.y);
}
static void drawQuad2_texturedFlat(DMAChain *chain, Quad2_texturedFlat quad, TextureInfo *texinfo){
    int32_t xy0 = gp0_xy(quad.a.x, quad.a.y);
    int32_t xy1 = gp0_xy(quad.b.x, quad.b.y);
    int32_t xy2 = gp0_xy(quad.c.x, quad.c.y);
    int32_t xy3 = gp0_xy(quad.d.x, quad.d.y);
    int32_t uv0 = gp0_uv(texinfo->u + quad.auv.x, texinfo->v + quad.auv.y, texinfo->clut);
    int32_t uv1 = gp0_uv(texinfo->u + quad.buv.x, texinfo->v + quad.buv.y, texinfo->page);
    int32_t uv2 = gp0_uv(texinfo->u + quad.cuv.x, texinfo->v + quad.cuv.y, 0);
    int32_t uv3 = gp0_uv(texinfo->u + quad.duv.x, texinfo->v + quad.duv.y, 0);

    // Only supports tiling textures that are powers of 2 
    // TODO: This assumes tiling. We might not necessarily want that. Perhaps add an
    // Also this just BREAKS if the numbers are wrong. So don't let the numbers be wrong (must be powers of 2 >= 8)
    
    uint8_t bitmask_u = 0xFF << (31-__builtin_clz(texinfo->w));
    uint8_t bitmask_v = 0xFF << (31-__builtin_clz(texinfo->h));

    dmaPtr = allocatePacket(activeChain, quad.z, 10);
    dmaPtr[0] = gp0_texwindow(texinfo->u>>3, texinfo->v>>3, bitmask_u>>3, bitmask_v>>3);
    //dmaPtr[0] = gp0_texwindow(0, 4, 0b11100, 0b11100);
    //printf("%d %d\n", texinfo->u, bitmask_u);
    dmaPtr[1] = 0x808080 | gp0_quad(true, false);
    dmaPtr[2] = xy0;
    dmaPtr[3] = uv0;
    dmaPtr[4] = xy1;
    dmaPtr[5] = uv1;
    dmaPtr[6] = xy2;
    dmaPtr[7] = uv2;
    dmaPtr[8] = xy3;
    dmaPtr[9] = uv3;

    if(drawOutlines){
        drawLine2(activeChain, (Vector2){quad.a.x, quad.a.y},(Vector2){quad.b.x, quad.b.y}, 0xFFFFFF); // AB
        drawLine2(activeChain, (Vector2){quad.b.x, quad.b.y},(Vector2){quad.d.x, quad.d.y}, 0xFFFFFF); // BD
        drawLine2(activeChain, (Vector2){quad.d.x, quad.d.y},(Vector2){quad.c.x, quad.c.y}, 0xFFFFFF); // DC
        drawLine2(activeChain, (Vector2){quad.c.x, quad.c.y},(Vector2){quad.a.x, quad.a.y}, 0xFFFFFF); // CA
    }
    return;
}

bool transformVertex(Camera *cam, Vector3 point, Vector2 *result){
    //int32_t distX = abs((cam->x>>10) - (point.x>>10));
    //int32_t distY = abs((cam->y>>10) - (point.y>>10));
    //int32_t distZ = abs((cam->z>>10) - (point.z>>10));
    //
    //if(distX > INT16_MAX || distY > INT16_MAX || distZ > INT16_MAX){
    //    return false;
    //}
    // Save the current translation vector
    //int32_t currentTx = gte_getControlReg(GTE_TRX);
    //int32_t currentTy = gte_getControlReg(GTE_TRY);
    //int32_t currentTz = gte_getControlReg(GTE_TRZ);
    // Translate model
    //updateTranslationMatrix(cam->x, cam->y, cam->z);
    // Rotate model
    //rotateCurrentMatrix(0, 0, 0);

    GTEVector16 vert;
    vert.x = (int16_t)((point.x * MODEL_SCALE_MULTIPLIER)>>12);
    vert.y = (int16_t)((point.y * MODEL_SCALE_MULTIPLIER)>>12);
    vert.z = (int16_t)((point.z * MODEL_SCALE_MULTIPLIER)>>12);
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
    //gte_setControlReg(GTE_TRX, currentTx);
    //gte_setControlReg(GTE_TRY, currentTy);
    //gte_setControlReg(GTE_TRZ, currentTz);
    return true;
}
bool transformTri(Camera *cam, Tri3 tri, Tri2 *result){
    uint32_t currentTx;
    uint32_t currentTy;
    uint32_t currentTz;

    GTEVector16 verts[3] = {
        {(int16_t)((tri.a.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((tri.a.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((tri.a.z * MODEL_SCALE_MULTIPLIER)>>12)},
        {(int16_t)((tri.b.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((tri.b.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((tri.b.z * MODEL_SCALE_MULTIPLIER)>>12)},
        {(int16_t)((tri.c.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((tri.c.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((tri.c.z * MODEL_SCALE_MULTIPLIER)>>12)}
    };

    gte_loadV0(&verts[0]);
    gte_loadV1(&verts[1]);
    gte_loadV2(&verts[2]);
    gte_command(GTE_CMD_RTPT | GTE_SF);
    gte_command(GTE_CMD_NCLIP);

    // Ensure the command has “gone to hardware” before we read back regs:
    __asm__ volatile ("" ::: "memory");

    int MAC0 = gte_getDataReg(GTE_MAC0);
    uint32_t flags = gte_getControlReg(GTE_FLAG);
    bool clip = flags & GTE_FLAG_DIVIDE_OVERFLOW;
    
    
    if(MAC0 <= 0){
        return false;
    }
    if(clip){
        return false;
    }
    uint32_t xy0 = gte_getDataReg(GTE_SXY0);
    uint32_t xy1 = gte_getDataReg(GTE_SXY1);
    uint32_t xy2 = gte_getDataReg(GTE_SXY2);

    gte_command(GTE_CMD_AVSZ3 | GTE_SF);
    int zIndex = gte_getDataReg(GTE_OTZ);

    if(zIndex < 1 || zIndex >= ORDERING_TABLE_SIZE){
        return false;
    }
    
    // Save result
    result->a = (Vector2_16){xy0 & 0xFFFF, xy0 >> 16};
    result->b = (Vector2_16){xy1 & 0xFFFF, xy1 >> 16};
    result->c = (Vector2_16){xy2 & 0xFFFF, xy2 >> 16};
    result->z = zIndex;

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
static inline bool transformQuad(Camera *cam, Quad3 *quad, Quad2 *result){
    gte_loadV0(&(GTEVector16){(int16_t)((quad->a.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->a.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->a.z * MODEL_SCALE_MULTIPLIER)>>12)});
    gte_loadV1(&(GTEVector16){(int16_t)((quad->b.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->b.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->b.z * MODEL_SCALE_MULTIPLIER)>>12)});
    gte_loadV2(&(GTEVector16){(int16_t)((quad->c.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->c.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->c.z * MODEL_SCALE_MULTIPLIER)>>12)});
    gte_command(GTE_CMD_RTPT | GTE_SF);
    gte_command(GTE_CMD_NCLIP);

    // Ensure the command has “gone to hardware” before we read back regs:
    __asm__ volatile ("" ::: "memory");

    if(gte_getDataReg(GTE_MAC0) <= 0){
        printf("MAC0\n");
        return false;
    }
    if(gte_getControlReg(GTE_FLAG) & GTE_FLAG_DIVIDE_OVERFLOW){
        printf("Flag\n");
        return false;
    }

    uint32_t xy0 = gte_getDataReg(GTE_SXY0);
    result->a = (Vector2_16){xy0 & 0xFFFF, xy0 >> 16};

    // Ensure the command has “gone to hardware” before we read back regs:
    __asm__ volatile ("" ::: "memory");

    gte_loadV0(&(GTEVector16){(int16_t)((quad->d.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->d.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->d.z * MODEL_SCALE_MULTIPLIER)>>12)});
    gte_command(GTE_CMD_RTPS | GTE_SF);

    // Ensure the command has “gone to hardware” before we read back regs:
    __asm__ volatile ("" ::: "memory");

    gte_command(GTE_CMD_AVSZ4 | GTE_SF);
    int zIndex = gte_getDataReg(GTE_OTZ);

    if(zIndex < 1 || zIndex >= ORDERING_TABLE_SIZE){
        printf("Z: %d\n", zIndex);
        return false;
    }
    
    
    uint32_t xy1 = gte_getDataReg(GTE_SXY0);
    uint32_t xy2 = gte_getDataReg(GTE_SXY1);
    uint32_t xy3 = gte_getDataReg(GTE_SXY2);

    result->b = (Vector2_16){xy1 & 0xFFFF, xy1 >> 16};
    result->c = (Vector2_16){xy2 & 0xFFFF, xy2 >> 16};
    result->d = (Vector2_16){xy3 & 0xFFFF, xy3 >> 16};
    result->z = zIndex;

    return true;
}
static inline bool transformQuad_texturedFlat(Camera *cam, Quad3_texturedFlat *quad, Quad2_texturedFlat *result){
    
    
    bool ret = true;

    
    #pragma region transformQuad

    gte_loadV0(&(GTEVector16){(int16_t)((quad->a.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->a.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->a.z * MODEL_SCALE_MULTIPLIER)>>12)});
    gte_loadV1(&(GTEVector16){(int16_t)((quad->b.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->b.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->b.z * MODEL_SCALE_MULTIPLIER)>>12)});
    gte_loadV2(&(GTEVector16){(int16_t)((quad->c.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->c.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->c.z * MODEL_SCALE_MULTIPLIER)>>12)});
    
    
    gte_command(GTE_CMD_RTPT | GTE_SF);
    gte_command(GTE_CMD_NCLIP);
    

    // Ensure the command has “gone to hardware” before we read back regs:
    __asm__ volatile ("" ::: "memory");

    if(gte_getDataReg(GTE_MAC0) <= 0){
        ret = false;
        goto exit;
    }
    if(gte_getControlReg(GTE_FLAG) & GTE_FLAG_DIVIDE_OVERFLOW){
        ret = false;
        goto exit;
    }

    uint32_t xy0 = gte_getDataReg(GTE_SXY0);
    result->a = (Vector2_16){xy0 & 0xFFFF, xy0 >> 16};

    // Ensure the command has “gone to hardware” before we read back regs:
    __asm__ volatile ("" ::: "memory");

    gte_loadV0(&(GTEVector16){(int16_t)((quad->d.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->d.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->d.z * MODEL_SCALE_MULTIPLIER)>>12)});
    gte_command(GTE_CMD_RTPS | GTE_SF);

    // Ensure the command has “gone to hardware” before we read back regs:
    __asm__ volatile ("" ::: "memory");

    gte_command(GTE_CMD_AVSZ4 | GTE_SF);
    int zIndex = gte_getDataReg(GTE_OTZ);

    if(zIndex < 1 || zIndex >= ORDERING_TABLE_SIZE){
        ret = false;
        goto exit;
    }
    
    uint32_t xy1 = gte_getDataReg(GTE_SXY0);
    uint32_t xy2 = gte_getDataReg(GTE_SXY1);
    uint32_t xy3 = gte_getDataReg(GTE_SXY2);

    result->b = (Vector2_16){xy1 & 0xFFFF, xy1 >> 16};
    result->c = (Vector2_16){xy2 & 0xFFFF, xy2 >> 16};
    result->d = (Vector2_16){xy3 & 0xFFFF, xy3 >> 16};
    result->z = zIndex;

    #pragma endregion

exit:

    result->auv=quad->auv;
    result->buv=quad->buv;
    result->cuv=quad->cuv;
    result->duv=quad->duv;

    
    return ret;
}

// A--1--B
// | /| /|
// |/ |/ |
// 4--m--2
// | /| /|
// |/ |/ |
// C--3--D

// In:
// A->B->C->D 
// Out:
// A->1->4->m
// 1->B->m->2
// 4->m->C->3
// m->2->3->D
void subdivideQuad3(Quad3_texturedFlat quad, Quad3_texturedFlat childQuads[4]){
    Vector3 VA, VB, VC, VD;
    Vector2 VAu,VBu,VCu,VDu;
    Vector3 V1, V2, V3, V4;
    Vector2 V1u,V2u,V3u,V4u;
    Vector3 Vm;
    Vector2 Vmu;

    VA = quad.a; VB = quad.b; VC = quad.c; VD = quad.d;
    VAu=quad.auv;VBu=quad.buv;VCu=quad.cuv;VDu=quad.duv;

    V1 = (Vector3){(VA.x + VB.x)>>1,(VA.y + VB.y)>>1,(VA.z + VB.z)>>1};
    V1u= (Vector2){(VAu.x+VBu.x)>>1,(VAu.y+VBu.y)>>1};
    V2 = (Vector3){(VB.x + VD.x)>>1,(VB.y + VD.y)>>1,(VB.z + VD.z)>>1};
    V2u= (Vector2){(VBu.x+VDu.x)>>1,(VBu.y+VDu.y)>>1};
    V3 = (Vector3){(VC.x + VD.x)>>1,(VC.y + VD.y)>>1,(VC.z + VD.z)>>1};
    V3u= (Vector2){(VCu.x+VDu.x)>>1,(VCu.y+VDu.y)>>1};
    V4 = (Vector3){(VA.x + VC.x)>>1,(VA.y + VC.y)>>1,(VA.z + VC.z)>>1};
    V4u= (Vector2){(VAu.x+VCu.x)>>1,(VAu.y+VCu.y)>>1};

    Vm = (Vector3){
        (VA.x + VB.x + VC.x + VD.x) >>2,
        (VA.y + VB.y + VC.y + VD.y) >>2,
        (VA.z + VB.z + VC.z + VD.z) >>2
    };
    Vmu= (Vector2){
        (VAu.x + VBu.x + VCu.x + VDu.x) >>2,
        (VAu.y + VBu.y + VCu.y + VDu.y) >>2,
    };

    childQuads[0]=(Quad3_texturedFlat){
        VA, V1, V4, Vm,
        VAu,V1u,V4u,Vmu,
        quad.textureIndex
    };
    childQuads[1]=(Quad3_texturedFlat){
        V1, VB, Vm, V2,
        V1u,VBu,Vmu,V2u,
        quad.textureIndex
    };
    childQuads[2]=(Quad3_texturedFlat){
        V4, Vm, VC, V3,
        V4u,Vmu,VCu,V3u,
        quad.textureIndex
    };
    childQuads[3]=(Quad3_texturedFlat){
        Vm, V2, V3, VD,
        Vmu,V2u,V3u,VDu,
        quad.textureIndex
    };
}

void fullRenderQuad3_texturedFlat(Quad3_texturedFlat quad, Camera *cam, TextureInfo *texinfo){    
    // Transform the quad initially
    Quad2_texturedFlat result;
    bool ret = transformQuad_texturedFlat(cam, &quad, &result);

    if(!ret) return;
    // Should do some world-space subdivisions here
    drawQuad2_texturedFlat(activeChain, result, texinfo);
    drawnQuads++;

}

void fullRenderQuad3_texturedFlat_Optimised(Quad3_texturedFlat *quad, Camera *cam, TextureInfo *texinfo){    
    subTimerValueA = TIMER_VALUE(0);
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^[ 1 ]^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//
    // Transform the quad initially
   
    // TODO: This block needs to have like, all of this stuff be pre-processed to the entire model. It shouldn't need to be scaled so much
    gte_loadV0(&(GTEVector16){(int16_t)((quad->a.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->a.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->a.z * MODEL_SCALE_MULTIPLIER)>>12)});
    gte_loadV1(&(GTEVector16){(int16_t)((quad->b.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->b.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->b.z * MODEL_SCALE_MULTIPLIER)>>12)});
    gte_loadV2(&(GTEVector16){(int16_t)((quad->c.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->c.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->c.z * MODEL_SCALE_MULTIPLIER)>>12)});
    
    subTimerValueB = TIMER_VALUE(0);
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^[ 2 ]^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//

    gte_command(GTE_CMD_RTPT | GTE_SF);
    gte_command(GTE_CMD_NCLIP);
    

    // Ensure the command has “gone to hardware” before we read back regs:
    //__asm__ volatile ("" ::: "memory");
    
    int MAC0;
    __asm__ volatile("mfc2 %0, $24\n" : "=r"(MAC0));
    if(MAC0 <= 0){
        return;
    }
    if(gte_getControlReg(GTE_FLAG) & GTE_FLAG_DIVIDE_OVERFLOW){
        return;
    }

    uint32_t xy0 = gte_getDataReg(GTE_SXY0);

    // Ensure the command has “gone to hardware” before we read back regs:
    //__asm__ volatile ("" ::: "memory");

    gte_loadV0(&(GTEVector16){(int16_t)((quad->d.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->d.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->d.z * MODEL_SCALE_MULTIPLIER)>>12)});
    gte_command(GTE_CMD_RTPS | GTE_SF);

    // Ensure the command has “gone to hardware” before we read back regs:
    //__asm__ volatile ("" ::: "memory");

    uint32_t xy1 = gte_getDataReg(GTE_SXY0);
    uint32_t xy2 = gte_getDataReg(GTE_SXY1);
    uint32_t xy3 = gte_getDataReg(GTE_SXY2);

    gte_command(GTE_CMD_AVSZ4 | GTE_SF);

    int zIndex;
    __asm__ volatile("mfc2 %0, $7\n" : "=r"(zIndex));
    if(zIndex < 1 || zIndex >= ORDERING_TABLE_SIZE){
        return;
    }
    
    subTimerValueC = TIMER_VALUE(0);
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^[ 3 ]^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//

    dmaPtr = allocatePacket(activeChain, zIndex, 10);
    dmaPtr[0] = gp0_texwindow(texinfo->u>>3, texinfo->v>>3, (0xFF << (31-__builtin_clz(texinfo->w)))>>3, (0xFF << (31-__builtin_clz(texinfo->h)))>>3);
    dmaPtr[1] = 0x808080 | gp0_quad(true, false);
    dmaPtr[2] = xy0;
    dmaPtr[3] = gp0_uv(texinfo->u + quad->auv.x, texinfo->v + quad->auv.y, texinfo->clut);
    dmaPtr[4] = xy1;
    dmaPtr[5] = gp0_uv(texinfo->u + quad->buv.x, texinfo->v + quad->buv.y, texinfo->page);
    dmaPtr[6] = xy2;
    dmaPtr[7] = gp0_uv(texinfo->u + quad->cuv.x, texinfo->v + quad->cuv.y, 0);
    dmaPtr[8] = xy3;
    dmaPtr[9] = gp0_uv(texinfo->u + quad->duv.x, texinfo->v + quad->duv.y, 0);

    
    drawnQuads++;
    subTimerValueD = TIMER_VALUE(0);
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^[ 4 ]^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//
}
#pragma endregion

Quad3_texturedFlat quad3Array[1024];
Quad2_texturedFlat quad2Array[1024];

struct {Quad3 quad[6]} cube;


// Gets called once at the start of main.
void initHardware(void){
    // Enable display blanking if not already.
    // Prevents logo from appearing while loading.
    GPU_GP1 = gp1_dispBlank(true);

    // Initialise the serial port for printing
    initSerialIO(115200);
    //initSPU();
    initIRQ();
    //initControllerBus();
    //initCDROM();
    //initFilesystem();
    initGPU();//
    
    setupGTE(SCREEN_WIDTH, SCREEN_HEIGHT);
    // Upload textures
    uploadIndexedTexture(&font, fontData, 960, 0, FONT_WIDTH, FONT_HEIGHT, 
        fontPalette, 960, FONT_HEIGHT, GP0_COLOR_4BPP);
    uploadTexture(&default_32, default_32Data, SCREEN_WIDTH, 0, 32, 32);
    
    // Point to the relevant DMA chain for this frame, then swap the active frame.
    activeChain = &dmaChains[usingSecondFrame];
    usingSecondFrame = !usingSecondFrame;
    // Reset the ordering table to a blank state.
    clearOrderingTable((activeChain->orderingTable), ORDERING_TABLE_SIZE);
    activeChain->nextPacket = activeChain->data;
   

    // Initialise an array of 1024 quads
    int xScale = ONE * 100;
    int yScale = ONE * 90;
    for (int y=0; y<32; y++){
        for(int x=0; x<32; x++){
            quad3Array[y*32 + x] = (Quad3_texturedFlat){
                .a = {.x=-(xScale * 16) + (xScale * x),          .y=-(yScale * 16) + (yScale * y),          .z=0},
                .b = {.x=-(xScale * 16) + (xScale * x) + xScale, .y=-(yScale * 16) + (yScale * y),          .z=0},
                .c = {.x=-(xScale * 16) + (xScale * x),          .y=-(yScale * 16) + (yScale * y) + yScale, .z=0},
                .d = {.x=-(xScale * 16) + (xScale * x) + xScale, .y=-(yScale * 16) + (yScale * y) + yScale, .z=0},

                .auv = {.x = 0,  .y = 0},
                .buv = {.x = 32, .y = 0},
                .cuv = {.x = 0,  .y = 32},
                .duv = {.x = 32, .y = 32},

                .textureIndex = 0
            };
        }
    }
    

    // IMPORTANT?
    // Create a preprocessing step that does the following:
    // (int16_t)((quad->a.x * MODEL_SCALE_MULTIPLIER)>>12)
    // to models that will be passed to the GTE.
    // Currently, this is done every frame.
    // If they are stored in memory, they can be fed in directly.

    
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

    mainCamera.x = 0;
    mainCamera.y = 0;
    mainCamera.z = -(ONE * 2);

    mainCamera.pitch = 0;
    mainCamera.roll = 0;
    mainCamera.yaw = 0;


    debug("Start of main loop\n");
    // Main loop. Runs every frame, forever
    int avgTime;
    for(;;){
        drawnQuads = 0;


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
        setTranslationMatrix(0, 0, 0);

        // Translate and Rotate camera
        rotateCurrentMatrix(mainCamera.pitch, mainCamera.roll, mainCamera.yaw);
        gte_setV0(-(mainCamera.x), -(mainCamera.y), -(mainCamera.z));
        translateCurrentMatrixByV0();
        gte_setControlReg(GTE_TRZ, gte_getControlReg(GTE_TRZ) - debugVariable);
        


        //for(int i=0; i<1024; i++){
        //    Quad2_texturedFlat rT;
        //    if(transformQuad_texturedFlat(&mainCamera, &quad3Array[i], &rT)){
        //        drawQuad2_texturedFlat(activeChain, rT, &default_32);
        //    }
        //}


        
        
        

        #pragma region Transform
        // Transform
        subTimerTotalA = 0;
        subTimerTotalB = 0;
        subTimerTotalC = 0;
        subTimerTotalD = 0;
        TIMER_CTRL(1) = (
            TIMER_CTRL_IRQ_REPEAT |
            TIMER_CTRL_EXT_CLOCK
        );
        for(int i=0; i<1024; i++){
            TIMER_CTRL(0) = (
                TIMER_CTRL_EXT_CLOCK | 
                TIMER_CTRL_IRQ_REPEAT
            );

            //fullRenderQuad3_texturedFlat(quad3Array[i], &mainCamera, &default_32);
            fullRenderQuad3_texturedFlat_Optimised(&quad3Array[i], &mainCamera, &default_32);
            
            subTimerTotalA += subTimerValueA;
            subTimerTotalB += subTimerValueB - subTimerValueA;
            subTimerTotalC += subTimerValueC - subTimerValueB;
            subTimerTotalD += subTimerValueD - subTimerValueC;
        }
        timerValueA = TIMER_VALUE(1);

        subTimerAvgA = (subTimerTotalA / 1024);
        subTimerAvgB = (subTimerTotalB / 1024);
        subTimerAvgC = (subTimerTotalC / 1024);
        subTimerAvgD = (subTimerTotalD / 1024);
        #pragma endregion
        

        


        sprintf(str_Buffer,
            "Timer: %d (%d %d %d)\n"
            "Subtimers: %d\n"
            " %d\n %d\n %d\n %d",
            timerValueA, timerValueB-timerValueA, timerValueC-timerValueB, timerValueD-timerValueC,
            subTimerAvgA + subTimerAvgB + subTimerAvgC + subTimerAvgD,
            subTimerAvgA, subTimerAvgB, subTimerAvgC, subTimerAvgD
        );
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


        
        timerValueB = TIMER_VALUE(1);
        // This will wait for the GPU to be ready,
        waitForGP0Ready();
        
        // Give DMA a pointer to the last item in the ordering table.
        // We don't need to add a terminator, as it is already done for us by the OTC.
        sendLinkedList(&(activeChain->orderingTable)[ORDERING_TABLE_SIZE - 1]);
        waitForVblank();

        timerValueC = TIMER_VALUE(1);

        // Swap the frame buffers.
        bufferY = usingSecondFrame ? 0 : SCREEN_HEIGHT;
        GPU_GP1 = gp1_fbOffset(bufferX, bufferY);

        // Point to the relevant DMA chain for this frame, then swap the active frame.
        activeChain = &dmaChains[usingSecondFrame];
        usingSecondFrame = !usingSecondFrame;
        
        // Reset the ordering table to a blank state.
        clearOrderingTable((activeChain->orderingTable), ORDERING_TABLE_SIZE);
        activeChain->nextPacket = activeChain->data;
        
        timerValueD = TIMER_VALUE(1);
        #pragma endregion
   

    }
}
