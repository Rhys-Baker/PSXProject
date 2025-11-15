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
//extern const uint8_t default_32Data[];
//extern const uint8_t default_32Palette[];
//TextureInfo default_32;


Camera mainCamera;
Player3 player;
char str_Buffer[256];
int screenColor = 0x000000;
int wallColor = 0x3c82fa;
int gteScaleFactor = 0;
bool drawOutlines = false;
int cameraHeight = 0;
int debugVariable = 0;
int drawnTris = 0;
int drawnQuads = 0;
int subbedQuads = 0;

// 3D direction Gizmo
Vector3 gizmoPoints[4] = {
    {0, 0, 0},
    {100<<12, 0, 0},
    {0, 100<<12, 0},
    {0, 0, 100<<12}
};
Vector2 transformedGizmoPoints[4];

bool needToPrintDebugInfo;

int imax(int a, int b){
    return a>b?a:b;
}
int imin(int a, int b){
    return a>b?b:a;
}

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
static void drawQuad2_texturedFlat(Quad2_texturedFlat quad, TextureInfo *texinfo){
    //int32_t xy0 = gp0_xy(quad.a.x, quad.a.y);
    //int32_t xy1 = gp0_xy(quad.b.x, quad.b.y);
    //int32_t xy2 = gp0_xy(quad.c.x, quad.c.y);
    //int32_t xy3 = gp0_xy(quad.d.x, quad.d.y);
    //int32_t uv0 = gp0_uv(texinfo->u + quad.auv.x, texinfo->v + quad.auv.y, texinfo->clut);
    //int32_t uv1 = gp0_uv(texinfo->u + quad.buv.x, texinfo->v + quad.buv.y, texinfo->page);
    //int32_t uv2 = gp0_uv(texinfo->u + quad.cuv.x, texinfo->v + quad.cuv.y, 0);
    //int32_t uv3 = gp0_uv(texinfo->u + quad.duv.x, texinfo->v + quad.duv.y, 0);

    // Only supports tiling textures that are powers of 2 
    // TODO: This assumes tiling. We might not necessarily want that.
    // Also this just BREAKS if the numbers are wrong. So don't let the numbers be wrong (must be powers of 2 >= 8)
    
    uint8_t bitmask_u = 0xFF << (31-__builtin_clz(texinfo->w));
    uint8_t bitmask_v = 0xFF << (31-__builtin_clz(texinfo->h));

    dmaPtr = allocatePacket(activeChain, quad.z, 10);
    dmaPtr[0] = gp0_texwindow(texinfo->u>>3, texinfo->v>>3, bitmask_u>>3, bitmask_v>>3);
    //dmaPtr[0] = gp0_texwindow(0, 4, 0b11100, 0b11100);
    //printf("%d %d\n", texinfo->u, bitmask_u);
    dmaPtr[1] = 0x808080 | gp0_quad(true, false);
    dmaPtr[2] = gp0_xy(quad.a.x, quad.a.y);
    dmaPtr[3] = gp0_uv(texinfo->u + quad.auv.x, texinfo->v + quad.auv.y, texinfo->clut);
    dmaPtr[4] = gp0_xy(quad.b.x, quad.b.y);
    dmaPtr[5] = gp0_uv(texinfo->u + quad.buv.x, texinfo->v + quad.buv.y, texinfo->page);
    dmaPtr[6] = gp0_xy(quad.c.x, quad.c.y);
    dmaPtr[7] = gp0_uv(texinfo->u + quad.cuv.x, texinfo->v + quad.cuv.y, 0);
    dmaPtr[8] = gp0_xy(quad.d.x, quad.d.y);
    dmaPtr[9] = gp0_uv(texinfo->u + quad.duv.x, texinfo->v + quad.duv.y, 0);

    //if(drawOutlines){
    //    drawLine2(activeChain, (Vector2){quad.a.x, quad.a.y},(Vector2){quad.b.x, quad.b.y}, 0xFFFFFF); // AB
    //    drawLine2(activeChain, (Vector2){quad.b.x, quad.b.y},(Vector2){quad.d.x, quad.d.y}, 0xFFFFFF); // BD
    //    drawLine2(activeChain, (Vector2){quad.d.x, quad.d.y},(Vector2){quad.c.x, quad.c.y}, 0xFFFFFF); // DC
    //    drawLine2(activeChain, (Vector2){quad.c.x, quad.c.y},(Vector2){quad.a.x, quad.a.y}, 0xFFFFFF); // CA
    //}
    return;
}

bool transformVertex(Camera *cam, Vector3 point, Vector2 *result){
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

void transformAndSortTri(Tri3 *tri, uint32_t *primitive, Camera *cam){
    // TODO: This block needs to have like, all of this stuff be pre-processed to the entire model. It shouldn't need to be scaled so much
    gte_loadV0(&(GTEVector16){(int16_t)((tri->a.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((tri->a.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((tri->a.z * MODEL_SCALE_MULTIPLIER)>>12)});
    gte_loadV1(&(GTEVector16){(int16_t)((tri->b.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((tri->b.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((tri->b.z * MODEL_SCALE_MULTIPLIER)>>12)});
    gte_loadV2(&(GTEVector16){(int16_t)((tri->c.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((tri->c.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((tri->c.z * MODEL_SCALE_MULTIPLIER)>>12)});

    gte_command(GTE_CMD_RTPT | GTE_SF);
    gte_command(GTE_CMD_NCLIP);
    
    primitive[3] = gte_getDataReg(GTE_SXY0);
    primitive[5] = gte_getDataReg(GTE_SXY1);
    primitive[7] = gte_getDataReg(GTE_SXY2);

    int MAC0;
    __asm__ volatile("mfc2 %0, $24\n" : "=r"(MAC0));
    if(MAC0 <= 0){
        return;
    }
    if(gte_getControlReg(GTE_FLAG) & GTE_FLAG_DIVIDE_OVERFLOW){
        return;
    }

    gte_command(GTE_CMD_AVSZ3 | GTE_SF);

    int zIndex;
    __asm__ volatile("mfc2 %0, $7\n" : "=r"(zIndex));
    if(zIndex < 1 || zIndex >= ORDERING_TABLE_SIZE){
        return;
    }

    sortPacket(activeChain, zIndex, 8, primitive);
    drawnTris++;
}

void transformAndSortQuad(Quad3 *quad, uint32_t *primitive, Camera *cam){
    //subTimerValueA = TIMER_VALUE(0);
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^[ 1 ]^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//
    // Transform the quad initially

    // TODO: This block needs to have like, all of this stuff be pre-processed to the entire model. It shouldn't need to be scaled so much
    gte_loadV0(&(GTEVector16){(int16_t)((quad->a.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->a.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->a.z * MODEL_SCALE_MULTIPLIER)>>12)});
    gte_loadV1(&(GTEVector16){(int16_t)((quad->b.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->b.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->b.z * MODEL_SCALE_MULTIPLIER)>>12)});
    gte_loadV2(&(GTEVector16){(int16_t)((quad->c.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->c.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->c.z * MODEL_SCALE_MULTIPLIER)>>12)});
    
    //subTimerValueB = TIMER_VALUE(0);
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

    primitive[3] = gte_getDataReg(GTE_SXY0);
    

    // Ensure the command has “gone to hardware” before we read back regs:
    //__asm__ volatile ("" ::: "memory");

    gte_loadV0(&(GTEVector16){(int16_t)((quad->d.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->d.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->d.z * MODEL_SCALE_MULTIPLIER)>>12)});
    gte_command(GTE_CMD_RTPS | GTE_SF);

    // Ensure the command has “gone to hardware” before we read back regs:
    //__asm__ volatile ("" ::: "memory");

    primitive[5] = gte_getDataReg(GTE_SXY0);
    primitive[7] = gte_getDataReg(GTE_SXY1);
    primitive[9] = gte_getDataReg(GTE_SXY2);

    gte_command(GTE_CMD_AVSZ4 | GTE_SF);

    int zIndex;
    __asm__ volatile("mfc2 %0, $7\n" : "=r"(zIndex));
    if(zIndex < 1 || zIndex >= ORDERING_TABLE_SIZE){
        return;
    }
    

    //subTimerValueC = TIMER_VALUE(0);
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^[ 3 ]^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//

    sortPacket(activeChain, zIndex, 10, primitive);

    drawnQuads++;
    //subTimerValueD = TIMER_VALUE(0);
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^[ 4 ]^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//
}

// TODO: This feels terrible, optimise it?
bool recursiveSubdivideAndSort_screenspace(int depth, int zIndex, Vector2_16 A, Vector2_16 B, Vector2_16 C, Vector2_16 D, Vector2_16 UVA, Vector2_16 UVB, Vector2_16 UVC, Vector2_16 UVD, int16_t clut, int16_t texpage){
    if(!depth) return false;
    // Check if it is too big, if it isn't the sort it right away
    Vector2_16 max = {imax(imax(A.x, B.x), imax(C.x, D.x)), imax(imax(A.y, B.y), imax(C.y, D.y))};
    Vector2_16 min = {imin(imin(A.x, B.x), imin(C.x, D.x)), imin(imin(A.y, B.y), imin(C.y, D.y))};
    
    if(!((max.x - min.x) > 1023 || (max.y - min.y) > 511)){
        dmaPtr = allocatePacket(activeChain, zIndex, 9);
        dmaPtr[0] = 0x808080 | gp0_quad(true, false);
        
        dmaPtr[1] = gp0_xy(A.x, A.y); // XY0
        dmaPtr[2] = gp0_uv(UVA.x, UVA.y, clut); // UV0
        dmaPtr[3] = gp0_xy(B.x, B.y); // XY1
        dmaPtr[4] = gp0_uv(UVB.x, UVB.y, texpage); // UV1
        dmaPtr[5] = gp0_xy(C.x, C.y); // XY2
        dmaPtr[6] = gp0_uv(UVC.x, UVC.y, 0); // UV2
        dmaPtr[7] = gp0_xy(D.x, D.y); // XY3
        dmaPtr[8] = gp0_uv(UVD.x, UVD.y, 0); // UV3

        drawnQuads++;
        subbedQuads++;
        return true;
    }

    // Get the midpoints along the lines and the center point
    Vector2_16 a = {(A.x + B.x) / 2, (A.y + B.y) / 2};
    Vector2_16 b = {(B.x + D.x) / 2, (B.y + D.y) / 2};
    Vector2_16 c = {(D.x + C.x) / 2, (D.y + C.y) / 2};
    Vector2_16 d = {(C.x + A.x) / 2, (C.y + A.y) / 2};
    Vector2_16 M = {(A.x + B.x + C.x + D.x) / 4, (A.y + B.y + C.y + D.y) / 4}; // Better

    Vector2_16 UVa = {(UVA.x + UVB.x) / 2, (UVA.y + UVB.y) / 2};
    Vector2_16 UVb = {(UVB.x + UVD.x) / 2, (UVB.y + UVD.y) / 2};
    Vector2_16 UVc = {(UVD.x + UVC.x) / 2, (UVD.y + UVC.y) / 2};
    Vector2_16 UVd = {(UVC.x + UVA.x) / 2, (UVC.y + UVA.y) / 2};
    Vector2_16 UVM = {(UVA.x + UVB.x + UVC.x + UVD.x) / 4, (UVA.y + UVB.y + UVC.y + UVD.y) / 4};
    
    //printf(
    //    "A: (%d %d)\n"
    //    "B: (%d %d)\n"
    //    "C: (%d %d)\n"
    //    "D: (%d %d)\n"
    //    "a: (%d %d)\n"
    //    "b: (%d %d)\n"
    //    "c: (%d %d)\n"
    //    "d: (%d %d)\n"
    //    "M: (%d %d)\n",
    //    A.x, A.y,
    //    B.x, B.y,
    //    C.x, C.y,
    //    D.x, D.y,
    //    a.x, a.y,
    //    b.x, b.y,
    //    c.x, c.y,
    //    d.x, d.y,
    //    M.x, M.y
    //);

    // A->a->d->M
    recursiveSubdivideAndSort_screenspace(depth - 1, zIndex, A, a, d, M, UVA, UVa, UVd, UVM, clut, texpage);
    // a->B->M->b
    recursiveSubdivideAndSort_screenspace(depth - 1, zIndex, a, B, M, b, UVa, UVB, UVM, UVb, clut, texpage);
    // d->M->D->c
    recursiveSubdivideAndSort_screenspace(depth - 1, zIndex, d, M, C, c, UVd, UVM, UVC, UVc, clut, texpage);
    // M->b->c->C
    recursiveSubdivideAndSort_screenspace(depth - 1, zIndex, M, b, c, D, UVM, UVb, UVc, UVD, clut, texpage);
}

bool recursiveSubdivideAndSort_worldspace(int depth, Quad3 *quad, Vector2 *UVA, Vector2 *UVB, Vector2 *UVC, Vector2 *UVD, int16_t texpage){

}

// Handles transforming and sorting quads but also allocates subdivided quads
void transformAndSortQuadWithSubdivision(Quad3 *quad, uint32_t *primitive, Camera *cam){
    // TODO: This block needs to have like, all of this stuff be pre-processed to the entire model. It shouldn't need to be scaled so much
    gte_loadV0(&(GTEVector16){(int16_t)((quad->a.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->a.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->a.z * MODEL_SCALE_MULTIPLIER)>>12)});
    gte_loadV1(&(GTEVector16){(int16_t)((quad->b.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->b.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->b.z * MODEL_SCALE_MULTIPLIER)>>12)});
    gte_loadV2(&(GTEVector16){(int16_t)((quad->c.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->c.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->c.z * MODEL_SCALE_MULTIPLIER)>>12)});
    
    gte_command(GTE_CMD_RTPT | GTE_SF);
    gte_command(GTE_CMD_NCLIP);
    
    
    int MAC0;
    __asm__ volatile("mfc2 %0, $24\n" : "=r"(MAC0));
    if(MAC0 <= 0){
        return;
    }
    if(gte_getControlReg(GTE_FLAG) & GTE_FLAG_DIVIDE_OVERFLOW){
        return;
    }

    primitive[3] = gte_getDataReg(GTE_SXY0);

    gte_loadV0(&(GTEVector16){(int16_t)((quad->d.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->d.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad->d.z * MODEL_SCALE_MULTIPLIER)>>12)});
    gte_command(GTE_CMD_RTPS | GTE_SF);

    primitive[5] = gte_getDataReg(GTE_SXY0);
    primitive[7] = gte_getDataReg(GTE_SXY1);
    primitive[9] = gte_getDataReg(GTE_SXY2);

    gte_command(GTE_CMD_AVSZ4 | GTE_SF);

    int zIndex;
    __asm__ volatile("mfc2 %0, $7\n" : "=r"(zIndex));
    if(zIndex < 1 || zIndex >= ORDERING_TABLE_SIZE){
        return;
    }


    // Right before sorting, we need to check if the quad is too big to actually be rendered.
    // Get the width and height
    Vector2_16 A = {(int16_t)(primitive[3] & 0xFFFF),(int16_t)((primitive[3])>>16)};
    Vector2_16 B = {(int16_t)(primitive[5] & 0xFFFF),(int16_t)((primitive[5])>>16)};
    Vector2_16 C = {(int16_t)(primitive[7] & 0xFFFF),(int16_t)((primitive[7])>>16)};
    Vector2_16 D = {(int16_t)(primitive[9] & 0xFFFF),(int16_t)((primitive[9])>>16)};

    int maxX = imax(imax(A.x, B.x), imax(C.x, D.x));
    int minX = imin(imin(A.x, B.x), imin(C.x, D.x));
    int maxY = imax(imax(A.y, B.y), imax(C.y, D.y));
    int minY = imin(imin(A.y, B.y), imin(C.y, D.y));

    if(!((maxX - minX) > 1023 || (maxY - minY) > 511)){
        // Sort the primitive if its a valid size
        sortPacket(activeChain, zIndex, 10, primitive);
        drawnQuads++;
        return;
    }

    //printf("Attempting recursive subdivision\n");

    // Extract UV info
    Vector2_16 UVa  = {primitive[4]  & 0xFF, (primitive[4]  & 0xFF00) >> 8};
    Vector2_16 UVb  = {primitive[6]  & 0xFF, (primitive[6]  & 0xFF00) >> 8};
    Vector2_16 UVc  = {primitive[8]  & 0xFF, (primitive[8]  & 0xFF00) >> 8};
    Vector2_16 UVd  = {primitive[10] & 0xFF, (primitive[10] & 0xFF00) >> 8};
    int16_t clut    = primitive[4] >> 16;
    int16_t texpage = primitive[6] >> 16;

    recursiveSubdivideAndSort_screenspace(5, zIndex, A, B, C, D, UVa, UVb, UVc, UVd, clut, texpage);
    dmaPtr = allocatePacket(activeChain, zIndex, 1); // Add the texture window after (runs before the other primitives)
    dmaPtr[0] = primitive[1]; // Texwindow
    
}


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

#define CAMERA_SPEED_SLOW 8
#define CAMERA_SPEED_FAST 16
int cameraSpeed = CAMERA_SPEED_SLOW;

// Functions for move controls
void moveCameraForward(void){
    mainCamera.x -=  (isin(mainCamera.yaw) * cameraSpeed);
    mainCamera.z +=  (icos(mainCamera.yaw) * cameraSpeed);
}
void moveCameraBackward(void){
    mainCamera.x +=  (isin(mainCamera.yaw) * cameraSpeed);
    mainCamera.z -=  (icos(mainCamera.yaw) * cameraSpeed);
}
void moveCameraLeft(void){
    mainCamera.x -=  (icos(mainCamera.yaw) * cameraSpeed);
    mainCamera.z += -(isin(mainCamera.yaw) * cameraSpeed);
}
void moveCameraRight(void){
    mainCamera.x +=  (icos(mainCamera.yaw) * cameraSpeed);
    mainCamera.z -= -(isin(mainCamera.yaw) * cameraSpeed);
}
void moveCameraUp(void){
    mainCamera.y -= cameraSpeed<<12;
}
void moveCameraDown(void){
    mainCamera.y += cameraSpeed<<12;
}
void cameraSpeedUp(void){
    cameraSpeed = CAMERA_SPEED_FAST;
}
void cameraSlowDown(void){
    cameraSpeed = CAMERA_SPEED_SLOW;
}

void incrementDebugVariable(void){
    debugVariable++;
}
void decrementDebugVariable(void){
    debugVariable--;
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
    player.position = (Vector3){0, -(512<<12), 0};
    player.velocity = (Vector3){0, 0, 0};
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
    // controller_subscribeOnKeyHold(movePlayerLeft,         BUTTON_INDEX_LEFT    );
    // controller_subscribeOnKeyHold(movePlayerRight,        BUTTON_INDEX_RIGHT   );
    // controller_subscribeOnKeyHold(movePlayerForward,      BUTTON_INDEX_UP      );
    // controller_subscribeOnKeyHold(movePlayerBackward,     BUTTON_INDEX_DOWN    );
    controller_subscribeOnKeyHold(moveCameraLeft,         BUTTON_INDEX_LEFT    );
    controller_subscribeOnKeyHold(moveCameraRight,        BUTTON_INDEX_RIGHT   );
    controller_subscribeOnKeyHold(moveCameraForward,      BUTTON_INDEX_UP      );
    controller_subscribeOnKeyHold(moveCameraBackward,     BUTTON_INDEX_DOWN    );
    controller_subscribeOnKeyDown(cameraSpeedUp,          BUTTON_INDEX_R2      );
    controller_subscribeOnKeyUp  (cameraSlowDown,         BUTTON_INDEX_R2      );
    controller_subscribeOnKeyHold(lookLeft,               BUTTON_INDEX_SQUARE  );
    controller_subscribeOnKeyHold(lookRight,              BUTTON_INDEX_CIRCLE  );
    controller_subscribeOnKeyHold(lookUp,                 BUTTON_INDEX_TRIANGLE);
    controller_subscribeOnKeyHold(lookDown,               BUTTON_INDEX_X       );
    controller_subscribeOnKeyHold(moveCameraDown,         BUTTON_INDEX_L1      );
    controller_subscribeOnKeyHold(moveCameraUp,           BUTTON_INDEX_R1      );
    controller_subscribeOnKeyDown(toggleOutlines,         BUTTON_INDEX_SELECT  );
    controller_subscribeOnKeyDown(playerJump,             BUTTON_INDEX_START   );


    // Load all the necessary textures from disc
    printf("Loading textures from disc...\n");
    for(int i = 0; i<numTextures; i++){
        int bytesLoaded = texture_loadTIM(bspTextureInfo[i].name, &bspTextureInfo[i].textureInfo);
        if(bytesLoaded < 0){
            printf("Error loading texture: %d", bytesLoaded);
        }
    }

    // Finally, manually load the default_32 texture for testing
    //uploadTexture(&default_32, default_32Data, SCREEN_WIDTH, 0, 32, 32);

    int t = 4;
    
    uint8_t bitmask_u = 0xFF << (31-__builtin_clz(bspTextureInfo[t].textureInfo.w));
    uint8_t bitmask_v = 0xFF << (31-__builtin_clz(bspTextureInfo[t].textureInfo.h));

    // Init camera
    mainCamera.x     = 0;
    mainCamera.y     = -(300<<12);
    mainCamera.z     = 0;
    mainCamera.pitch = 0;
    mainCamera.roll  = 0;
    mainCamera.yaw   = 0;

    // resetPlayer();


    // printf("Player:\n x: %d\n y: %d\n z: %d\n",
    //     player.position.x, player.position.y, player.position.z
    // );
    // player.velocity.x = 0;
    // player.velocity.y = GRAVITY_CONSTANT;
    // player.velocity.z = 0;

    // Player3_move(&bsp_player, &player);

    // printf("Player:\n x: %d\n y: %d\n z: %d\n",
    //     player.position.x, player.position.y, player.position.z
    // );


    int timerValueA, timerValueB, timerValueC, timerValueD;
    timerValueA = timerValueB = timerValueC = timerValueD = 0;

    int timerIndex = 0;
    int timerAverage;
    int timeframe[32];
    for (int i=0; i<32; i++){
        timeframe[i] = 0;
    }

    debug("Start of main loop\n");

    // Main loop. Runs every frame, forever
    for(;;){
        drawnTris = 0;
        drawnQuads = 0;
        subbedQuads = 0;
        // Reset the timer value to zero at the start of the loop.
        TIMER_CTRL(1) = (
            TIMER_CTRL_ENABLE_SYNC |
            TIMER_CTRL_SYNC_PAUSE_ONCE |
            TIMER_CTRL_IRQ_REPEAT |
            TIMER_CTRL_EXT_CLOCK
        );
        

        ///////////////////////////
        //       Game logic      //
        ///////////////////////////
        //debug("Game Logic\n");
        #pragma region Game logic
        // Poll the controllers and run their assoicated functions
        controller_update();
        

        // Apply gravity if not grounded
        // if(!player.isGrounded){
        //     if(player.velocity.y + GRAVITY_CONSTANT > TERMINAL_VELOCITY){
        //         player.velocity.y = TERMINAL_VELOCITY;
        //     } else {
        //         player.velocity.y += GRAVITY_CONSTANT;
        //     }
        // } else {
        //     // Apply friction if grounded
        //     if(player.velocity.x >= FRICTION_CONSTANT){
        //         player.velocity.x -= FRICTION_CONSTANT;
        //     } else if(player.velocity.x <= -FRICTION_CONSTANT){
        //         player.velocity.x += FRICTION_CONSTANT;
        //     } else {
        //         player.velocity.x = 0;
        //     }
        //     if(player.velocity.z >= FRICTION_CONSTANT){
        //         player.velocity.z -= FRICTION_CONSTANT;
        //     } else if(player.velocity.z <= -FRICTION_CONSTANT){
        //         player.velocity.z += FRICTION_CONSTANT;
        //     } else {
        //         player.velocity.z = 0;
        //     }
        // }

        // // Collide with the BSP tree
        // Player3_move(&bsp_player, &player);

        // // Move camera to player position
        // mainCamera.x     = (player.position.x);
        // mainCamera.z     = (player.position.z);
        // mainCamera.y = ((player.position.y)) + (cameraHeight);

        timerValueA = TIMER_VALUE(1);
        #pragma endregion


        ///////////////////////////
        //       Rendering       //
        ///////////////////////////
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
        gte_setV0(-(mainCamera.x>>12), -(mainCamera.y>>12), -(mainCamera.z>>12));
        translateCurrentMatrixByV0();
        gte_setControlReg(GTE_TRZ, gte_getControlReg(GTE_TRZ) - debugVariable);

        // Render gizmo
        // for (int i = 0; i<4; i++){
        //     transformVertex(&mainCamera, gizmoPoints[i], &transformedGizmoPoints[i]);
        //     drawCross2(activeChain, transformedGizmoPoints[i], 0xFFFFFF);
        // };
        // drawLine2(activeChain, transformedGizmoPoints[0], transformedGizmoPoints[1], 0x0000FF);
        // drawLine2(activeChain, transformedGizmoPoints[0], transformedGizmoPoints[2], 0x00FF00);
        // drawLine2(activeChain, transformedGizmoPoints[0], transformedGizmoPoints[3], 0xFF0000);


        nextQuadSub = quadPrims[usingSecondFrame][0];
        for(int i=0; i<numTris; i++){
            transformAndSortTri(&tris[i], &triPrims[usingSecondFrame][i*9], &mainCamera);
        }
        for(int i=0; i<numQuads; i++){
            //transformAndSortQuad(&quads[i], &quadPrims[usingSecondFrame][i*11], &mainCamera);
            transformAndSortQuadWithSubdivision(&quads[i], &quadPrims[usingSecondFrame][i*11], &mainCamera);
        }

        // Crosshair
        // drawCross2(activeChain, (Vector2){SCREEN_WIDTH/2, SCREEN_HEIGHT/2}, 0x0000FF);
        
        

        // Framerate cheatsheet:
        //  60fps <  263 hblanks
        //  30fps <  526 hblanks
        //  15fps < 1052 hblanks
        sprintf(str_Buffer, "Quads: %d (%d)",
            drawnQuads, subbedQuads
        );
        printString(activeChain, &font, 10, 10, str_Buffer);
        
        // Draw a plain background
        dmaPtr = allocatePacket(activeChain, ORDERING_TABLE_SIZE -1 , 3);
        dmaPtr[0] = screenColor | gp0_vramFill();
        dmaPtr[1] = gp0_xy(bufferX, bufferY);
        dmaPtr[2] = gp0_xy(SCREEN_WIDTH, SCREEN_HEIGHT);
        
        timerValueB = TIMER_VALUE(1);
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


        timerValueC = TIMER_VALUE(1);

        timeframe[timerIndex] = timerValueC; 
        timerIndex = (timerIndex + 1) % 32;
        timerAverage = 0;
        for(int i=0; i<32; i++){
            timerAverage += timeframe[i];
        }
        timerAverage = (timerAverage >> 5);

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
