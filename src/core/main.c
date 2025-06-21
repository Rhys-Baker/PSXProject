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

#define MAX_POLYGON_WIDTH 1023
#define MAX_POLYGON_HEIGHT 511


#define MOVEMENT_SPEED (ONE * 5 * MODEL_SCALE_MULTIPLIER)

#define ACCELERATION_CONSTANT (ONE * MODEL_SCALE_MULTIPLIER)
#define MAX_SPEED (ONE * 3 * MODEL_SCALE_MULTIPLIER)
#define JUMP_FORCE (ONE * 10 * MODEL_SCALE_MULTIPLIER)
#define FRICTION_CONSTANT (ONE * MODEL_SCALE_MULTIPLIER)
#define TERMINAL_VELOCITY (ONE * 5 * MODEL_SCALE_MULTIPLIER)
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
extern const uint8_t default_32Palette[];
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
void drawQuad2_texturedFlat(Quad2_texturedFlat quad, TextureInfo *texinfo){
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
        drawLine2((Vector2){quad.a.x, quad.a.y},(Vector2){quad.b.x, quad.b.y}, 0xFFFFFF); // AB
        drawLine2((Vector2){quad.b.x, quad.b.y},(Vector2){quad.d.x, quad.d.y}, 0xFFFFFF); // BD
        drawLine2((Vector2){quad.d.x, quad.d.y},(Vector2){quad.c.x, quad.c.y}, 0xFFFFFF); // DC
        drawLine2((Vector2){quad.c.x, quad.c.y},(Vector2){quad.a.x, quad.a.y}, 0xFFFFFF); // CA
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
bool transformQuad(Camera *cam, Quad3 quad, Quad2 *result){
    uint32_t currentTx;
    uint32_t currentTy;
    uint32_t currentTz;

    GTEVector16 verts[4] = {
        {(int16_t)((quad.a.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad.a.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad.a.z * MODEL_SCALE_MULTIPLIER)>>12)},
        {(int16_t)((quad.b.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad.b.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad.b.z * MODEL_SCALE_MULTIPLIER)>>12)},
        {(int16_t)((quad.c.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad.c.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad.c.z * MODEL_SCALE_MULTIPLIER)>>12)},
        {(int16_t)((quad.d.x * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad.d.y * MODEL_SCALE_MULTIPLIER)>>12), (int16_t)((quad.d.z * MODEL_SCALE_MULTIPLIER)>>12)}
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

    // Ensure the command has “gone to hardware” before we read back regs:
    __asm__ volatile ("" ::: "memory");

    gte_loadV0(&verts[3]);
    gte_command(GTE_CMD_RTPS | GTE_SF);

    // Ensure the command has “gone to hardware” before we read back regs:
    __asm__ volatile ("" ::: "memory");
    
    uint32_t xy1 = gte_getDataReg(GTE_SXY0);
    uint32_t xy2 = gte_getDataReg(GTE_SXY1);
    uint32_t xy3 = gte_getDataReg(GTE_SXY2);


    gte_command(GTE_CMD_AVSZ4 | GTE_SF);
    int zIndex = gte_getDataReg(GTE_OTZ);

    if(zIndex < 1 || zIndex >= ORDERING_TABLE_SIZE){
        return false;
    }
    
    // Save result
    result->a = (Vector2_16){xy0 & 0xFFFF, xy0 >> 16};
    result->b = (Vector2_16){xy1 & 0xFFFF, xy1 >> 16};
    result->c = (Vector2_16){xy2 & 0xFFFF, xy2 >> 16};
    result->d = (Vector2_16){xy3 & 0xFFFF, xy3 >> 16};
    result->z = zIndex;

    return true;
}
bool transformQuad_texturedFlat(Camera *cam, Quad3_texturedFlat quad, Quad2_texturedFlat *result){
    // Convert the textured_flat triangle to a regular triangle
    Quad3 _quad;
    _quad.a = quad.a;
    _quad.b = quad.b;
    _quad.c = quad.c;
    _quad.d = quad.d;

    // To store the result
    Quad2 _result = {
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
        0
    };

    bool ret = transformQuad(cam, _quad, &_result);

    result->a = _result.a;
    result->b = _result.b;
    result->c = _result.c;
    result->d = _result.d;

    result->z = _result.z;
    
    result->auv=quad.auv;
    result->buv=quad.buv;
    result->cuv=quad.cuv;
    result->duv=quad.duv;


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
    transformQuad_texturedFlat(cam, quad, &result);

    // Should do some world-space subdivisions here

    drawQuad2_texturedFlat(result, texinfo);
    drawnQuads++;

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
            .y = -4096,
            .z = 0
        },
        .distance = 2228224,
        .children = {
            1, 451
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
            -1, 2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -65536,
        .children = {
            3, 175
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
            4, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -65536,
        .children = {
            5, 74
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
            -1, 6
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
            7, 9
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
            8, -2
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
        .distance = 917504,
        .children = {
            10, 69
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
            11, 43
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
            12, 32
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
            13, 15
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
            -2, 14
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 393216,
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
        .distance = 589824,
        .children = {
            16, 22
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
            17, 20
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
            -2, 18
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
        .children = {
            19, -2
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
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
        .children = {
            21, -2
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
        .distance = 4194304,
        .children = {
            23, 27
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
            -2, 24
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
            -2, 25
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 262144,
        .children = {
            26, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1015360,
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
            -2, 28
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 262144,
        .children = {
            29, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3866623,
        .children = {
            30, 31
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1015360,
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
        .distance = 1015360,
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
            33, 34
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 393216,
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
        .distance = 589824,
        .children = {
            35, 40
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
            36, 38
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
        .children = {
            37, -2
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
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
        .children = {
            39, -2
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -2, 41
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 262144,
        .children = {
            42, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1015360,
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
        .distance = 589824,
        .children = {
            44, 53
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
            -1, 45
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
            46, 48
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
        .children = {
            47, -2
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
        .distance = 2359296,
        .children = {
            49, 51
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
        .children = {
            50, -2
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1048576,
        .children = {
            52, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
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
            54, 63
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
            55, 61
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 262144,
        .children = {
            56, -2
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
            57, 59
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
            58, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 393216,
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
        .distance = 393216,
        .children = {
            60, -2
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
        .distance = 393216,
        .children = {
            62, -2
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
        .distance = 262144,
        .children = {
            64, -1
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
            65, 66
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1015360,
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
            67, 68
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1015360,
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
        .distance = 1015360,
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
            -2, 70
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 589824,
        .children = {
            71, 73
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1065841,
        .children = {
            -2, 72
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
            75, 120
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
            76, 107
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
            77, 94
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
            78, 79
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
            -2, 80
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
            81, 85
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
            -2, 82
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
            -2, 83
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 589824,
        .children = {
            84, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1065841,
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
            -2, 86
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 589824,
        .children = {
            87, 90
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
            88, -1
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
            -2, 89
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
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
            91, 92
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1015360,
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
        .distance = 393216,
        .children = {
            93, -2
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
        .distance = -983040,
        .children = {
            95, 102
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
            -2, 96
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 589824,
        .children = {
            97, 100
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
        .children = {
            98, 99
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1065841,
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
        .distance = -1065841,
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
            -1, 101
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1015360,
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
        .distance = 393216,
        .children = {
            103, -2
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
            104, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 589824,
        .children = {
            105, -2
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
            -2, 106
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
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
            108, 115
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
            -2, 109
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 589824,
        .children = {
            110, 113
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
        .children = {
            111, 112
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1065841,
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
        .distance = -1065841,
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
            -1, 114
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1015360,
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
        .distance = 393216,
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
        .distance = -1114112,
        .children = {
            117, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 589824,
        .children = {
            118, -2
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
            -2, 119
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
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
            121, 147
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
            122, 128
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
            -2, 123
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
            124, 126
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 589824,
        .children = {
            125, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1065841,
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
        .distance = 589824,
        .children = {
            127, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1065841,
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
        .distance = 3014656,
        .children = {
            129, 139
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
            130, 133
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
        .children = {
            -2, 131
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 589824,
        .children = {
            -2, 132
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1015360,
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
        .distance = 262144,
        .children = {
            134, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 393216,
        .children = {
            135, -2
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
            136, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 589824,
        .children = {
            137, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
        .children = {
            138, -2
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            140, 142
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 589824,
        .children = {
            -2, 141
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1015360,
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
        .distance = 393216,
        .children = {
            143, -2
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
            144, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 589824,
        .children = {
            145, -2
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
            -2, 146
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
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
            148, 153
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 589824,
        .children = {
            149, -1
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
            -2, 150
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
            151, 152
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1065841,
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
        .distance = -1065841,
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
            154, 164
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 65536,
        .children = {
            155, 163
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 589824,
        .children = {
            156, 159
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
            157, -1
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
            -2, 158
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
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
            160, 161
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1015360,
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
        .distance = 393216,
        .children = {
            162, -2
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
        .distance = -983040,
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
        .distance = 65536,
        .children = {
            165, 174
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 589824,
        .children = {
            166, 169
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
            167, -1
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
            -2, 168
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
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
            170, 171
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1015360,
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
        .distance = 262144,
        .children = {
            172, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 393216,
        .children = {
            173, -2
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
        .distance = -983040,
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
            176, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 65536,
        .children = {
            177, 314
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
            -1, 178
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
            179, 291
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
            180, 182
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
            181, -1
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
            183, 228
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
            184, 187
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -720896,
        .children = {
            -2, 185
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
            -2, 186
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
            -1, -2
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
            188, 227
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
            189, 208
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -589824,
        .children = {
            190, 200
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
            191, 194
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -393216,
        .children = {
            -2, 192
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
            193, -2
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
            .y = 0,
            .z = 4096
        },
        .distance = -262144,
        .children = {
            195, 196
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
            197, 199
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
            -2, 198
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1015360,
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
        .distance = 1015360,
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
            201, 202
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
            -2, 203
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
            204, 206
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -720896,
        .children = {
            -2, 205
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
            .y = 0,
            .z = 4096
        },
        .distance = -720896,
        .children = {
            -2, 207
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
            .y = 0,
            .z = 4096
        },
        .distance = -589824,
        .children = {
            209, 210
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
        .distance = 393216,
        .children = {
            211, 222
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
            -2, 212
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 589824,
        .children = {
            213, 221
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 753664,
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
        .distance = 3997696,
        .children = {
            215, 216
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1065841,
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
        .distance = 1065841,
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
            218, -2
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
            219, 220
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1065841,
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
        .distance = 1065841,
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
            223, 224
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
            -2, 225
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
            226, -2
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
            -2, -1
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
            -1, -2
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
            229, 257
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
            230, 246
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
            231, -1
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
            232, 241
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -393216,
        .children = {
            233, 236
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
            -2, 234
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -262144,
        .children = {
            -1, 235
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1015360,
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
            -1, 237
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -589824,
        .children = {
            238, 239
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1015360,
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
        .distance = -720896,
        .children = {
            -2, 240
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
            .y = 0,
            .z = 4096
        },
        .distance = -393216,
        .children = {
            242, 243
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
            -1, 244
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -589824,
        .children = {
            -1, 245
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
            .y = 0,
            .z = 4096
        },
        .distance = -589824,
        .children = {
            -1, 247
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
            248, 255
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
            249, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 589824,
        .children = {
            250, 254
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
            251, -2
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
            252, 253
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1065841,
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
        .distance = 1065841,
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
            -1, -2
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
            256, -2
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 393216,
        .children = {
            258, 288
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
            259, -1
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
            260, 276
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -589824,
        .children = {
            261, 269
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
            262, 265
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -262144,
        .children = {
            -2, 263
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -393216,
        .children = {
            -2, 264
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
        .distance = -262144,
        .children = {
            -1, 266
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2686979,
        .children = {
            267, 268
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1015360,
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
        .distance = 1015360,
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
            270, 273
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
            .y = 0,
            .z = 4096
        },
        .distance = -720896,
        .children = {
            -2, 272
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            -1, 274
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
            275, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -720896,
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
        .distance = -589824,
        .children = {
            -1, 277
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 589824,
        .children = {
            278, 287
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
            279, 283
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 753664,
        .children = {
            280, 281
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1065841,
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
            282, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1065841,
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
        .distance = 753664,
        .children = {
            284, 285
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1065841,
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
            286, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1065841,
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
            289, -2
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
            290, -1
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
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            292, 309
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
            293, 303
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -589824,
        .children = {
            294, 300
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
            295, 298
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -262144,
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
        .distance = 1114112,
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
        .distance = -393216,
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
        .distance = -262144,
        .children = {
            -1, 299
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1015360,
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
            -1, 301
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
            302, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -720896,
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
        .distance = -589824,
        .children = {
            -1, 304
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
            305, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 589824,
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
        .distance = -851968,
        .children = {
            307, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1065841,
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
            -1, -2
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
            310, -2
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
            311, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 589824,
        .children = {
            312, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 753664,
        .children = {
            313, -2
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
        .distance = 3670016,
        .children = {
            315, 358
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
            316, -1
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
            317, 319
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
            318, -1
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
        .distance = -1048576,
        .children = {
            320, 357
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
            321, 337
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -589824,
        .children = {
            322, 323
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
        .distance = 4521984,
        .children = {
            -2, 324
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
            -2, 325
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -589824,
        .children = {
            326, 330
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
            -1, 327
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
            328, -2
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
            329, -2
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
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -753664,
        .children = {
            331, 336
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
            332, 334
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
            333, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1065841,
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
            335, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1065841,
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
        .distance = -1065841,
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
            -2, 338
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -589824,
        .children = {
            339, 352
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
            340, 346
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
            341, 343
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -262144,
        .children = {
            -1, 342
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1015360,
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
        .distance = -262144,
        .children = {
            -2, 344
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
            -2, 345
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -393216,
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
            347, 349
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -262144,
        .children = {
            -1, 348
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1015360,
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
        .distance = -262144,
        .children = {
            -2, 350
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
            -2, 351
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -393216,
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
            353, -1
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
            -2, 354
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
            355, 356
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -720896,
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
        .distance = -720896,
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
            359, -1
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
            360, 389
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
            361, 388
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -589824,
        .children = {
            362, 366
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
            -1, 363
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
            364, -2
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
            365, -2
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
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -589824,
        .children = {
            367, 377
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
            368, 375
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
            369, 372
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
            -1, 370
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -262144,
        .children = {
            -1, 371
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1015360,
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
        .distance = -262144,
        .children = {
            -2, 373
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
            -2, 374
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -393216,
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
            -1, 376
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -393216,
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
            378, -1
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
            379, 381
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1065841,
        .children = {
            380, -2
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
        .distance = 3342336,
        .children = {
            382, 387
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
            383, 385
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
            -2, 384
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -720896,
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
            -2, 386
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -720896,
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
            390, 426
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
            391, 422
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
            392, 403
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -589824,
        .children = {
            -1, 393
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
            -1, 394
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -589824,
        .children = {
            395, 398
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
            396, 397
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
        .distance = 2686976,
        .children = {
            399, 401
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1065841,
        .children = {
            400, -2
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
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1065841,
        .children = {
            402, -2
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
            .y = 0,
            .z = 4096
        },
        .distance = -589824,
        .children = {
            404, 417
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
            405, 411
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
            406, 408
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -262144,
        .children = {
            -1, 407
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1015360,
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
        .distance = -262144,
        .children = {
            -2, 409
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
            -2, 410
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -393216,
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
            412, 414
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -262144,
        .children = {
            -1, 413
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1015360,
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
        .distance = -262144,
        .children = {
            -2, 415
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
            -2, 416
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -393216,
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
            418, -1
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
            -2, 419
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
            420, 421
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -720896,
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
        .distance = -720896,
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
        .distance = -65536,
        .children = {
            -2, 423
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
            424, -1
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
            -2, 425
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -65536,
        .children = {
            427, 428
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
            -1, -2
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
            429, 450
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
            430, 440
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -589824,
        .children = {
            -1, 431
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -589824,
        .children = {
            432, 436
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
            -1, 433
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
            434, -2
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
            435, -2
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
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -753664,
        .children = {
            437, 439
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
            438, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1065841,
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
        .distance = -1065841,
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
        .distance = -589824,
        .children = {
            441, 447
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
            442, 444
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -262144,
        .children = {
            -1, 443
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1015360,
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
        .distance = -262144,
        .children = {
            -2, 445
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
            -2, 446
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -393216,
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
            448, -1
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
            -2, 449
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -720896,
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
            -1, 452
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
            453, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -65536,
        .children = {
            454, 918
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
            455, 625
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -425984,
        .children = {
            456, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 425984,
        .children = {
            -1, 457
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1572864,
        .children = {
            458, 549
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
            459, -1
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
            -1, 460
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -65536,
        .children = {
            461, 505
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2031616,
        .children = {
            462, 486
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2392064,
        .children = {
            -1, 463
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
            464, 466
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
            -1, 465
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
            -1, -2
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
            467, 471
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
            468, 469
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
            -1, -2
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
            -1, 470
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
        .distance = 425984,
        .children = {
            472, 485
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
            -2, 473
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
            474, -2
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
            -2, 475
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
            -2, 476
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 163840,
        .children = {
            477, 482
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
            478, -2
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
            -2, 479
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
            -2, 480
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
            -2, 481
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2195456,
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
            483, -2
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
            -2, 484
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
            -2, -1
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
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1900544,
        .children = {
            487, 497
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
            488, 491
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
            489, -2
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
            490, -2
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
            -1, -2
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
            492, 493
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
        .distance = 425984,
        .children = {
            494, -2
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
            495, -2
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
            -2, 496
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
        .distance = 262144,
        .children = {
            498, 503
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
            499, 501
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
            500, -2
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
            -1, -2
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
            -2, 502
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
            -2, 504
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
        .distance = 1900544,
        .children = {
            506, 535
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2392064,
        .children = {
            -1, 507
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
            508, 510
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
            509, -1
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
            -1, -2
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
            511, 515
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
            512, 513
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
            514, -1
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
        .distance = 425984,
        .children = {
            516, 534
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
            517, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2031616,
        .children = {
            518, 530
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
            519, -2
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
            -2, 520
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
            521, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -163840,
        .children = {
            522, 525
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
            523, -2
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
            -2, 524
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
            526, -2
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
            -2, 527
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
            528, -2
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
            -2, 529
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2195456,
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
            -2, 531
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
            532, -2
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
            533, -2
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
        .distance = -393216,
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
            536, 539
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
            -2, 537
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
            538, -2
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
            540, 548
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
            541, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1703936,
        .children = {
            542, 545
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
            543, -2
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
            544, -2
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
            546, -2
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
            547, -2
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
        .distance = 1638400,
        .children = {
            -1, 550
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
            551, 621
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -65536,
        .children = {
            552, 586
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
            553, 584
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1245184,
        .children = {
            554, 573
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
            555, 563
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
            556, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1376256,
        .children = {
            557, 560
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
            558, -2
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
            559, -2
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
            -1, -2
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
            561, -2
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
            562, -2
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
        .distance = 262144,
        .children = {
            564, 572
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
            -2, 565
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1376256,
        .children = {
            566, 569
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
            -2, 567
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
            568, -2
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
        .distance = 393216,
        .children = {
            570, -2
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
            -2, 571
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
            574, 578
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
            575, -2
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
            576, -2
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
            577, -2
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
            -1, -2
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
            579, 581
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
            -2, 580
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
            582, -2
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
            -2, 583
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
        .distance = 294912,
        .children = {
            -1, 585
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
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1245184,
        .children = {
            587, 602
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
            588, -1
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
            589, 592
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
            -2, 590
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
            591, -2
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
            593, 601
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
            594, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1376256,
        .children = {
            595, 598
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
            596, -2
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
            597, -2
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
            599, -2
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
            600, -2
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
            603, 604
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
            605, 607
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
            606, -2
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
        .distance = -393216,
        .children = {
            608, 619
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
            -2, 609
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
            610, 612
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
            611, -2
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
            -2, -1
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
            -2, 613
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
            614, 617
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
            -2, 615
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
            616, -2
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
            -2, 618
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
            -2, -1
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
            -2, 620
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
        .distance = -294912,
        .children = {
            622, -1
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
            -1, 623
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
            -1, 624
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
        .distance = 589824,
        .children = {
            626, 782
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
            627, 669
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 589824,
        .children = {
            628, 659
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
            629, 640
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
            630, 638
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
            631, 636
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
            632, 634
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
            633, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
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
            635, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
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
            637, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
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
            639, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
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
        .distance = 1572864,
        .children = {
            641, 646
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
            642, 644
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1065841,
        .children = {
            -2, 643
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
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1065841,
        .children = {
            -2, 645
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
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1376256,
        .children = {
            647, 651
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 753664,
        .children = {
            648, 649
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1065841,
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
            -2, 650
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1065841,
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
        .distance = 753664,
        .children = {
            652, 655
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
            653, 654
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1065841,
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
        .distance = 1065841,
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
            -2, 656
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
            657, 658
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1065841,
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
        .distance = 1065841,
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
            660, 666
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 65536,
        .children = {
            661, -2
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
            662, -2
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
            663, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 393216,
        .children = {
            664, -2
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
            -1, 665
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
            667, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 262144,
        .children = {
            668, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1015360,
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
            670, 752
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
            671, 685
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
            672, 676
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 262144,
        .children = {
            673, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 589824,
        .children = {
            674, -2
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
            675, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
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
            677, 680
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 589824,
        .children = {
            -2, 678
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 262144,
        .children = {
            679, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1015360,
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
        .distance = 589824,
        .children = {
            681, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 753664,
        .children = {
            682, 683
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1065841,
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
            -2, 684
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1065841,
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
        .distance = 262144,
        .children = {
            686, 740
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 589824,
        .children = {
            687, 724
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
            688, 702
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
            689, 694
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
            690, -2
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
            691, 692
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
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
        .distance = 720896,
        .children = {
            693, -2
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
        .distance = 1048576,
        .children = {
            695, 700
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
            696, 698
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
        .children = {
            697, -2
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
        .distance = 720896,
        .children = {
            -1, 699
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1169592,
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
            -2, 701
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1251205,
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
            703, 718
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
        .children = {
            704, 716
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
            705, 712
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1251205,
        .children = {
            -2, 706
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 753664,
        .children = {
            707, 709
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
            708, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1065841,
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
            710, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 263776,
        .children = {
            711, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1065841,
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
            -2, 713
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
            714, -2
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
            -2, 715
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1065841,
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
            717, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1065841,
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
        .distance = 720896,
        .children = {
            719, -2
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
            -2, 720
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
            721, 722
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1251205,
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
            723, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1251205,
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
            725, 735
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 393216,
        .children = {
            726, 729
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
            -2, 727
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
            -2, 728
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1169592,
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
            -2, 730
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
            -2, 731
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
            -2, 732
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
            -2, 733
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
            734, -2
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
        .distance = 917504,
        .children = {
            736, 739
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
            737, -2
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
            738, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1015360,
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
            741, 751
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
            -2, 742
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
            -2, 743
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
            -2, 744
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
            -2, 745
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -196608,
        .children = {
            -2, 746
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
            747, 748
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
            -2, 749
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
            750, -2
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
        .distance = 983040,
        .children = {
            753, 781
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
            754, 766
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
            -2, 755
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
            -2, 756
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
            -2, 757
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
            758, 765
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
            -2, 759
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
            -2, 760
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
            -2, 761
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
            762, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -196608,
        .children = {
            -2, 763
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
            764, -2
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
        .distance = 589824,
        .children = {
            -2, 767
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
            -2, 768
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
            -2, 769
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 65536,
        .children = {
            770, 776
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -196608,
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
            772, 773
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
            -2, 774
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
            775, -2
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
        .distance = -196608,
        .children = {
            -2, 777
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
            -2, 778
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
            -1, 779
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
            780, -2
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
        .distance = 393216,
        .children = {
            783, 842
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
            784, -1
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
            785, 804
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
            786, 802
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 65536,
        .children = {
            787, 795
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
            -2, 788
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 425984,
        .children = {
            -2, 789
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
            -2, 790
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
            -2, 791
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
            -2, 792
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
            793, -2
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
            -2, 794
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
        .distance = -589824,
        .children = {
            796, -2
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
            -2, 797
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
            798, -2
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
            799, -2
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
            -2, 800
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
            -2, 801
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
            .y = 0,
            .z = 4096
        },
        .distance = 589824,
        .children = {
            803, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1065841,
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
            805, 831
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
            806, 826
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
            807, 813
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 65536,
        .children = {
            808, 812
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
        .children = {
            809, 810
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            811, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1015360,
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
            814, 821
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 65536,
        .children = {
            815, 820
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 262144,
        .children = {
            816, 819
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
        .children = {
            817, 818
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
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1015360,
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
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 589824,
        .children = {
            822, 824
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
        .children = {
            823, -2
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            825, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1015360,
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
        .distance = 589824,
        .children = {
            827, 829
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
            -2, 828
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
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
            830, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1015360,
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
            832, 837
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 589824,
        .children = {
            833, 835
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
            -2, 834
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
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
            836, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1015360,
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
        .distance = 589824,
        .children = {
            838, 840
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
            -2, 839
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
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
            841, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1015360,
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
            843, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 65536,
        .children = {
            844, 859
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
        .children = {
            845, 858
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
            846, 855
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
            847, 849
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
            -2, 848
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
        .distance = 196608,
        .children = {
            850, -2
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
            851, 854
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
            852, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 163840,
        .children = {
            -2, 853
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
            856, -2
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
            857, -2
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
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 589824,
        .children = {
            860, 903
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -589824,
        .children = {
            861, 881
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -65536,
        .children = {
            862, 865
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
            863, -2
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
            864, -2
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
        .distance = -262144,
        .children = {
            866, 877
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
            867, 873
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
            868, -2
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
            869, 872
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
            870, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -163840,
        .children = {
            871, -2
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
        .distance = 917504,
        .children = {
            -2, 874
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
            875, -2
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
            -2, 876
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
        .distance = -262144,
        .children = {
            -2, 878
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
        .children = {
            879, -2
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
            -2, 880
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
            882, 893
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
            883, 887
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -753664,
        .children = {
            884, 886
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
            -2, 885
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1065841,
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
        .distance = -1065841,
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
            -2, 888
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
        .children = {
            889, -2
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
            890, 891
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1251205,
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
        .distance = -720896,
        .children = {
            -2, 892
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1251205,
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
            894, 896
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
        .children = {
            895, -2
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
            .y = 0,
            .z = 4096
        },
        .distance = 720896,
        .children = {
            897, 900
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
            898, -1
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
            -2, 899
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1251205,
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
            -2, 901
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
            -2, 902
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1169592,
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
            904, 905
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
        .distance = 262144,
        .children = {
            906, 908
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
            907, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1015360,
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
        .distance = 393216,
        .children = {
            909, 912
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
            -2, 910
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
            -2, 911
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1169592,
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
            -2, 913
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
            914, 917
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
            -2, 915
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
            -2, 916
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 262144,
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 65536,
        .children = {
            919, 1090
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
            920, -1
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
            921, 1012
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
            922, 955
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
            923, 936
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
            924, -1
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
            925, 931
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -720896,
        .children = {
            926, 930
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
            -2, 927
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -262144,
        .children = {
            -1, 928
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -589824,
        .children = {
            929, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1015360,
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
        .distance = -720896,
        .children = {
            932, 935
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
            -2, 933
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -262144,
        .children = {
            -1, 934
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1015360,
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
        .distance = 2031616,
        .children = {
            937, 946
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
            938, 944
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -589824,
        .children = {
            -1, 939
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
            940, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 589824,
        .children = {
            941, 943
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
            942, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1065841,
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
            -1, -2
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
            945, -2
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
        .distance = -917504,
        .children = {
            947, 953
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -589824,
        .children = {
            -1, 948
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
            949, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 589824,
        .children = {
            950, 952
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
            951, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1065841,
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
            -1, -2
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
            954, -2
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
        .distance = -589824,
        .children = {
            956, 975
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1245184,
        .children = {
            957, 966
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
            958, 962
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
            -2, 959
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
            960, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -262144,
        .children = {
            -1, 961
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1015360,
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
            -2, 963
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
            964, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -262144,
        .children = {
            -1, 965
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1015360,
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
            967, 971
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
            -2, 968
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
            969, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -262144,
        .children = {
            -1, 970
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1015360,
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
            -2, 972
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
            973, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -262144,
        .children = {
            -1, 974
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1015360,
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
            976, 988
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
            977, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1245184,
        .children = {
            978, 983
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
            979, 981
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -720896,
        .children = {
            -2, 980
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1048576,
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
        .distance = -720896,
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
        .distance = 1048576,
        .children = {
            984, 986
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
            985, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -720896,
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
        .distance = -720896,
        .children = {
            -2, 987
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
        .distance = 1376256,
        .children = {
            989, 997
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
            990, 995
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
            991, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 589824,
        .children = {
            992, 994
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
            993, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1065841,
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
            -1, -2
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
            996, -2
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
        .distance = 1048576,
        .children = {
            998, 1006
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
            999, 1004
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
            1000, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 589824,
        .children = {
            1001, 1003
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
            1002, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1065841,
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
            -1, -2
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
            1005, -2
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
        .distance = -917504,
        .children = {
            1007, 1010
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
            1008, -1
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
            1009, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1065841,
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
        .distance = 393216,
        .children = {
            1011, -2
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
        .distance = -589824,
        .children = {
            1013, 1039
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
            1014, 1038
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 589824,
        .children = {
            1015, 1018
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
            -2, 1016
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -262144,
        .children = {
            -1, 1017
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1015360,
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
        .distance = -393216,
        .children = {
            1019, 1033
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
            1020, 1028
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
            -2, 1021
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -262144,
        .children = {
            1022, 1026
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
            -2, 1023
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
            -1, 1024
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
            1025, -2
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
            -2, 1027
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
        .distance = -262144,
        .children = {
            1029, 1030
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
        .distance = -262144,
        .children = {
            1031, -2
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
            1032, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1015360,
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
            1034, 1037
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1169592,
        .children = {
            -2, 1035
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
            1036, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1015360,
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
        .distance = 1169592,
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
            -1, -2
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
            1040, 1085
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
            1041, 1055
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
            1042, 1051
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 589824,
        .children = {
            1043, 1044
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -720896,
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
            1045, 1049
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
            1046, 1047
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -720896,
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
        .distance = -720896,
        .children = {
            -2, 1048
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
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -720896,
        .children = {
            1050, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1169592,
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
        .distance = 393216,
        .children = {
            -2, 1052
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
            -2, 1053
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
            -2, 1054
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1251205,
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
        .distance = 393216,
        .children = {
            1056, 1064
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
            1057, 1061
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 753664,
        .children = {
            1058, 1059
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1065841,
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
            1060, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1065841,
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
            1062, -2
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
            1063, -1
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
        .distance = 589824,
        .children = {
            1065, 1077
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
            1066, 1071
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
            1067, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 753664,
        .children = {
            1068, 1069
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1065841,
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
            1070, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1065841,
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
        .distance = -720896,
        .children = {
            -2, 1072
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
            -2, 1073
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
            1074, 1076
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
            1075, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1251205,
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
        .distance = 1251205,
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
            1078, 1083
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
            1079, 1080
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
        .distance = -262144,
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
        .distance = 393216,
        .children = {
            1082, -2
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
        .distance = -917504,
        .children = {
            1084, -2
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
        .distance = 393216,
        .children = {
            -1, 1086
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 589824,
        .children = {
            -2, 1087
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
            -2, 1088
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
            -2, 1089
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
        .distance = -1179648,
        .children = {
            1091, -1
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
            1092, -1
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
            1093, 1149
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
            1094, 1136
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -589824,
        .children = {
            -1, 1095
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
            1096, 1130
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
            1097, 1106
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
            1098, 1103
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
            -1, 1099
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -589824,
        .children = {
            1100, 1101
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
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            1102, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1065841,
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
        .distance = -65536,
        .children = {
            -2, 1104
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
            -2, 1105
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
        .distance = 1703936,
        .children = {
            1107, 1116
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -589824,
        .children = {
            1108, 1113
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
            1109, 1111
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
            -1, 1110
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
        .distance = -393216,
        .children = {
            -2, 1112
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
        .distance = -1048576,
        .children = {
            1114, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1065841,
        .children = {
            1115, -2
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
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            1117, 1127
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
            -1, 1118
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
            1119, 1123
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -589824,
        .children = {
            1120, 1121
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
            .y = 0,
            .z = 4096
        },
        .distance = -851968,
        .children = {
            1122, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1065841,
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
        .distance = -589824,
        .children = {
            1124, 1125
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
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1065841,
        .children = {
            1126, -2
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
        .distance = -262144,
        .children = {
            -2, 1128
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -393216,
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
            1131, 1134
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
            -1, 1132
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
            1133, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1065841,
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
            -2, 1135
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
        .distance = -1048576,
        .children = {
            1137, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -589824,
        .children = {
            1138, 1141
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
            1139, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -262144,
        .children = {
            -1, 1140
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1015360,
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
            1142, 1147
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
            1143, 1145
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -720896,
        .children = {
            -2, 1144
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1048576,
        .children = {
            -2, 1146
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -720896,
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
            -2, 1148
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -720896,
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
            1150, 1169
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
            1151, 1164
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -393216,
        .children = {
            1152, 1155
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
            1153, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -262144,
        .children = {
            -1, 1154
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1015360,
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
            1156, 1160
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
            -1, 1157
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -589824,
        .children = {
            -1, 1158
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
            1159, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1065841,
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
        .distance = -589824,
        .children = {
            1161, 1162
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1015360,
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
            -2, 1163
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -720896,
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
        .distance = -65536,
        .children = {
            -2, 1165
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
            -2, 1166
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
            1167, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -753664,
        .children = {
            -2, 1168
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
            .y = 0,
            .z = 4096
        },
        .distance = -1048576,
        .children = {
            1170, 1229
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -589824,
        .children = {
            1171, 1186
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
            1172, 1178
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -65536,
        .children = {
            1173, 1174
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
            -1, 1175
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
            1176, -2
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
            1177, -2
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
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -65536,
        .children = {
            -2, 1179
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -720896,
        .children = {
            -2, 1180
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
            -2, 1181
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
            -2, 1182
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
            -2, 1183
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
            -2, 1184
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
            -2, 1185
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
        .distance = -262144,
        .children = {
            1187, 1196
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
            1188, 1189
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
            -2, 1190
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
            1191, 1195
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
            -2, 1192
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
            -2, 1193
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
            -2, 1194
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
        .distance = -589824,
        .children = {
            1197, 1207
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
            1198, 1199
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
        .distance = -262144,
        .children = {
            1200, 1204
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
            1201, -2
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
            1202, -2
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
            1203, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1015360,
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
            -2, 1205
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
            1206, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1169592,
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
            1208, 1220
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
            1209, 1214
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
            1210, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -753664,
        .children = {
            1211, 1213
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
            1212, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1065841,
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
        .distance = -1065841,
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
        .distance = -720896,
        .children = {
            -2, 1215
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
            -2, 1216
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
            1217, 1219
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
            -2, 1218
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1251205,
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
        .distance = -1251205,
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
            1221, 1223
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -720896,
        .children = {
            -2, 1222
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
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1048576,
        .children = {
            1224, 1226
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
            -2, 1225
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1251205,
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
        .distance = -720896,
        .children = {
            1227, -1
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
            -2, 1228
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1169592,
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
            1230, 1232
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -65536,
        .children = {
            -2, 1231
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
            1233, -1
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
BSPTree3 bsp_player = {.nodes=bspNodes_player, .numNodes = 1234};

int numTris = 8;
Tri3_texturedFlat tris[] = {
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
};
int numQuads = 520;
Quad3_texturedFlat quads[] = {
    {
        {0, 0, 0},
        {327680, 0, 0},
        {0, 0, -327680},
        {327680, 0, -327680},
        {255, 255},
        {224, 255},
        {255, 224},
        {224, 224},
        12
    },
    {
        {0, 0, -983040},
        {327680, 0, -983040},
        {0, -327680, -983040},
        {327680, -327680, -983040},
        {0, 255},
        {31, 255},
        {0, 224},
        {31, 224},
        16
    },
    {
        {327680, 0, -983040},
        {327680, 0, -917504},
        {327680, -327680, -983040},
        {327680, -327680, -917504},
        {16, 255},
        {31, 255},
        {16, 176},
        {31, 176},
        11
    },
    {
        {327680, 0, -917504},
        {655360, 0, -917504},
        {327680, -327680, -917504},
        {655360, -327680, -917504},
        {32, 255},
        {63, 255},
        {32, 224},
        {63, 224},
        15
    },
    {
        {688128, -327680, -983040},
        {655360, -327680, -917504},
        {688128, 0, -983040},
        {655360, 0, -917504},
        {0, 176},
        {15, 176},
        {0, 255},
        {15, 255},
        11
    },
    {
        {-688128, 0, -983040},
        {-655360, 0, -917504},
        {-688128, -327680, -983040},
        {-655360, -327680, -917504},
        {0, 255},
        {15, 255},
        {0, 176},
        {15, 176},
        11
    },
    {
        {-655360, 0, -917504},
        {-327680, 0, -917504},
        {-655360, -327680, -917504},
        {-327680, -327680, -917504},
        {192, 255},
        {223, 255},
        {192, 224},
        {223, 224},
        15
    },
    {
        {-327680, -327680, -983040},
        {-327680, -327680, -917504},
        {-327680, 0, -983040},
        {-327680, 0, -917504},
        {0, 176},
        {15, 176},
        {0, 255},
        {15, 255},
        11
    },
    {
        {-983040, 0, -655360},
        {-655360, 0, -983040},
        {-983040, -327680, -655360},
        {-655360, -327680, -983040},
        {0, 193},
        {0, 162},
        {31, 193},
        {31, 162},
        16
    },
    {
        {-1048576, -327680, -327680},
        {-1048576, -327680, 0},
        {-1048576, 0, -327680},
        {-1048576, 0, 0},
        {224, 224},
        {255, 224},
        {224, 255},
        {255, 255},
        16
    },
    {
        {327680, -327680, -983040},
        {327680, -327680, -917504},
        {327680, -655360, -983040},
        {327680, -655360, -917504},
        {0, 175},
        {15, 175},
        {0, 96},
        {15, 96},
        11
    },
    {
        {327680, -327680, -917504},
        {655360, -327680, -917504},
        {327680, -655360, -917504},
        {655360, -655360, -917504},
        {32, 223},
        {63, 223},
        {32, 192},
        {63, 192},
        6
    },
    {
        {688128, -655360, -983040},
        {655360, -655360, -917504},
        {688128, -327680, -983040},
        {655360, -327680, -917504},
        {0, 96},
        {15, 96},
        {0, 175},
        {15, 175},
        11
    },
    {
        {327680, -655360, -983040},
        {327680, -655360, -917504},
        {327680, -983040, -983040},
        {327680, -983040, -917504},
        {0, 95},
        {15, 95},
        {0, 16},
        {15, 16},
        11
    },
    {
        {327680, -655360, -917504},
        {655360, -655360, -917504},
        {327680, -983040, -917504},
        {655360, -983040, -917504},
        {32, 191},
        {63, 191},
        {32, 160},
        {63, 160},
        6
    },
    {
        {688128, -983040, -983040},
        {655360, -983040, -917504},
        {688128, -655360, -983040},
        {655360, -655360, -917504},
        {0, 16},
        {15, 16},
        {0, 95},
        {15, 95},
        11
    },
    {
        {327680, -983040, -983040},
        {327680, -983040, -917504},
        {327680, -1310720, -983040},
        {327680, -1310720, -917504},
        {0, 15},
        {15, 15},
        {0, 192},
        {15, 192},
        11
    },
    {
        {327680, -983040, -917504},
        {655360, -983040, -917504},
        {327680, -1310720, -917504},
        {655360, -1310720, -917504},
        {32, 159},
        {63, 159},
        {32, 128},
        {63, 128},
        9
    },
    {
        {688128, -1310720, -983040},
        {655360, -1310720, -917504},
        {688128, -983040, -983040},
        {655360, -983040, -917504},
        {0, 192},
        {15, 192},
        {0, 15},
        {15, 15},
        11
    },
    {
        {-688128, -327680, -983040},
        {-655360, -327680, -917504},
        {-688128, -655360, -983040},
        {-655360, -655360, -917504},
        {0, 175},
        {15, 175},
        {0, 96},
        {15, 96},
        11
    },
    {
        {-655360, -327680, -917504},
        {-327680, -327680, -917504},
        {-655360, -655360, -917504},
        {-327680, -655360, -917504},
        {192, 223},
        {223, 223},
        {192, 192},
        {223, 192},
        6
    },
    {
        {-327680, -655360, -983040},
        {-327680, -655360, -917504},
        {-327680, -327680, -983040},
        {-327680, -327680, -917504},
        {0, 96},
        {15, 96},
        {0, 175},
        {15, 175},
        11
    },
    {
        {-688128, -655360, -983040},
        {-655360, -655360, -917504},
        {-688128, -983040, -983040},
        {-655360, -983040, -917504},
        {0, 95},
        {15, 95},
        {0, 16},
        {15, 16},
        11
    },
    {
        {-655360, -655360, -917504},
        {-327680, -655360, -917504},
        {-655360, -983040, -917504},
        {-327680, -983040, -917504},
        {192, 191},
        {223, 191},
        {192, 160},
        {223, 160},
        6
    },
    {
        {-327680, -983040, -983040},
        {-327680, -983040, -917504},
        {-327680, -655360, -983040},
        {-327680, -655360, -917504},
        {0, 16},
        {15, 16},
        {0, 95},
        {15, 95},
        11
    },
    {
        {-688128, -983040, -983040},
        {-655360, -983040, -917504},
        {-688128, -1310720, -983040},
        {-655360, -1310720, -917504},
        {0, 15},
        {15, 15},
        {0, 192},
        {15, 192},
        11
    },
    {
        {-655360, -983040, -917504},
        {-327680, -983040, -917504},
        {-655360, -1310720, -917504},
        {-327680, -1310720, -917504},
        {192, 159},
        {223, 159},
        {192, 128},
        {223, 128},
        9
    },
    {
        {-327680, -1310720, -983040},
        {-327680, -1310720, -917504},
        {-327680, -983040, -983040},
        {-327680, -983040, -917504},
        {0, 192},
        {15, 192},
        {0, 15},
        {15, 15},
        11
    },
    {
        {-327680, 0, 0},
        {0, 0, 0},
        {-327680, 0, -327680},
        {0, 0, -327680},
        {255, 224},
        {255, 255},
        {224, 224},
        {224, 255},
        12
    },
    {
        {0, 0, 327680},
        {327680, 0, 327680},
        {0, 0, 0},
        {327680, 0, 0},
        {224, 255},
        {224, 224},
        {255, 255},
        {255, 224},
        12
    },
    {
        {-327680, 0, 327680},
        {0, 0, 327680},
        {-327680, 0, 0},
        {0, 0, 0},
        {224, 224},
        {255, 224},
        {224, 255},
        {255, 255},
        12
    },
    {
        {0, 0, 655360},
        {327680, 0, 655360},
        {0, 0, 327680},
        {327680, 0, 327680},
        {0, 192},
        {31, 192},
        {0, 223},
        {31, 223},
        1
    },
    {
        {-327680, 0, 655360},
        {0, 0, 655360},
        {-327680, 0, 327680},
        {0, 0, 327680},
        {224, 192},
        {255, 192},
        {224, 223},
        {255, 223},
        1
    },
    {
        {-327680, 0, 983040},
        {0, 0, 983040},
        {-327680, 0, 655360},
        {0, 0, 655360},
        {224, 160},
        {255, 160},
        {224, 191},
        {255, 191},
        1
    },
    {
        {0, 0, 983040},
        {327680, 0, 983040},
        {0, 0, 655360},
        {327680, 0, 655360},
        {0, 160},
        {31, 160},
        {0, 191},
        {31, 191},
        1
    },
    {
        {-983040, 0, 0},
        {-655360, 0, 0},
        {-983040, 0, -327680},
        {-655360, 0, -327680},
        {255, 160},
        {255, 191},
        {224, 160},
        {224, 191},
        1
    },
    {
        {-983040, 0, 327680},
        {-655360, 0, 327680},
        {-983040, 0, 0},
        {-655360, 0, 0},
        {31, 160},
        {31, 191},
        {0, 160},
        {0, 191},
        1
    },
    {
        {-655360, 0, 327680},
        {-327680, 0, 327680},
        {-655360, 0, 0},
        {-327680, 0, 0},
        {31, 192},
        {31, 223},
        {0, 192},
        {0, 223},
        1
    },
    {
        {-655360, 0, 0},
        {-327680, 0, 0},
        {-655360, 0, -327680},
        {-327680, 0, -327680},
        {255, 192},
        {255, 223},
        {224, 192},
        {224, 223},
        1
    },
    {
        {327680, 0, 0},
        {655360, 0, 0},
        {327680, 0, -327680},
        {655360, 0, -327680},
        {255, 32},
        {255, 63},
        {224, 32},
        {224, 63},
        1
    },
    {
        {327680, 0, 327680},
        {655360, 0, 327680},
        {327680, 0, 0},
        {655360, 0, 0},
        {31, 32},
        {31, 63},
        {0, 32},
        {0, 63},
        1
    },
    {
        {655360, 0, 327680},
        {983040, 0, 327680},
        {655360, 0, 0},
        {983040, 0, 0},
        {31, 64},
        {31, 95},
        {0, 64},
        {0, 95},
        1
    },
    {
        {655360, 0, 0},
        {983040, 0, 0},
        {655360, 0, -327680},
        {983040, 0, -327680},
        {255, 64},
        {255, 95},
        {224, 64},
        {224, 95},
        1
    },
    {
        {-327680, 0, -655360},
        {0, 0, -655360},
        {-327680, 0, -983040},
        {0, 0, -983040},
        {224, 64},
        {255, 64},
        {224, 95},
        {255, 95},
        1
    },
    {
        {-327680, 0, -327680},
        {0, 0, -327680},
        {-327680, 0, -655360},
        {0, 0, -655360},
        {224, 32},
        {255, 32},
        {224, 63},
        {255, 63},
        1
    },
    {
        {0, 0, -327680},
        {327680, 0, -327680},
        {0, 0, -655360},
        {327680, 0, -655360},
        {0, 32},
        {31, 32},
        {0, 63},
        {31, 63},
        1
    },
    {
        {0, 0, -655360},
        {327680, 0, -655360},
        {0, 0, -983040},
        {327680, 0, -983040},
        {0, 64},
        {31, 64},
        {0, 95},
        {31, 95},
        1
    },
    {
        {-1048576, 0, 327680},
        {-983040, 0, 327680},
        {-1048576, 0, 0},
        {-983040, 0, 0},
        {31, 153},
        {31, 159},
        {0, 153},
        {0, 159},
        1
    },
    {
        {-1048576, 0, 0},
        {-983040, 0, 0},
        {-1048576, 0, -327680},
        {-983040, 0, -327680},
        {255, 153},
        {255, 159},
        {224, 153},
        {224, 159},
        1
    },
    {
        {983040, 0, 0},
        {1048576, 0, 0},
        {983040, 0, -327680},
        {1048576, 0, -327680},
        {255, 96},
        {255, 101},
        {224, 96},
        {224, 101},
        1
    },
    {
        {983040, 0, 327680},
        {1048576, 0, 327680},
        {983040, 0, 0},
        {1048576, 0, 0},
        {31, 96},
        {31, 101},
        {0, 96},
        {0, 101},
        1
    },
    {
        {327680, 0, 917504},
        {655360, 0, 917504},
        {327680, 0, 655360},
        {655360, 0, 655360},
        {89, 32},
        {89, 63},
        {64, 32},
        {64, 63},
        10
    },
    {
        {327680, 0, 655360},
        {655360, 0, 655360},
        {327680, 0, 327680},
        {655360, 0, 327680},
        {63, 32},
        {63, 63},
        {32, 32},
        {32, 63},
        10
    },
    {
        {655360, 0, 655360},
        {983040, 0, 655360},
        {655360, 0, 327680},
        {983040, 0, 327680},
        {63, 64},
        {63, 95},
        {32, 64},
        {32, 95},
        10
    },
    {
        {-655360, 0, 655360},
        {-327680, 0, 655360},
        {-655360, 0, 327680},
        {-327680, 0, 327680},
        {63, 192},
        {63, 223},
        {32, 192},
        {32, 223},
        10
    },
    {
        {-983040, 0, 655360},
        {-655360, 0, 655360},
        {-983040, 0, 327680},
        {-655360, 0, 327680},
        {63, 160},
        {63, 191},
        {32, 160},
        {32, 191},
        10
    },
    {
        {-655360, 0, 917504},
        {-327680, 0, 917504},
        {-655360, 0, 655360},
        {-327680, 0, 655360},
        {89, 192},
        {89, 223},
        {64, 192},
        {64, 223},
        10
    },
    {
        {-655360, 0, -327680},
        {-327680, 0, -327680},
        {-655360, 0, -655360},
        {-327680, 0, -655360},
        {223, 192},
        {223, 223},
        {192, 192},
        {192, 223},
        10
    },
    {
        {-983040, 0, -327680},
        {-655360, 0, -327680},
        {-983040, 0, -655360},
        {-655360, 0, -655360},
        {223, 160},
        {223, 191},
        {192, 160},
        {192, 191},
        10
    },
    {
        {-655360, 0, -655360},
        {-327680, 0, -655360},
        {-655360, 0, -917504},
        {-327680, 0, -917504},
        {191, 192},
        {191, 223},
        {166, 192},
        {166, 223},
        10
    },
    {
        {327680, 0, -327680},
        {655360, 0, -327680},
        {327680, 0, -655360},
        {655360, 0, -655360},
        {223, 32},
        {223, 63},
        {192, 32},
        {192, 63},
        10
    },
    {
        {655360, 0, -327680},
        {983040, 0, -327680},
        {655360, 0, -655360},
        {983040, 0, -655360},
        {223, 64},
        {223, 95},
        {192, 64},
        {192, 95},
        10
    },
    {
        {327680, 0, -655360},
        {655360, 0, -655360},
        {327680, 0, -917504},
        {655360, 0, -917504},
        {191, 32},
        {191, 63},
        {166, 32},
        {166, 63},
        10
    },
    {
        {-983040, -327680, -655360},
        {-655360, -327680, -983040},
        {-983040, -655360, -655360},
        {-655360, -655360, -983040},
        {32, 193},
        {32, 162},
        {63, 193},
        {63, 162},
        16
    },
    {
        {-983040, -655360, -655360},
        {-655360, -655360, -983040},
        {-983040, -983040, -655360},
        {-655360, -983040, -983040},
        {64, 193},
        {64, 162},
        {95, 193},
        {95, 162},
        16
    },
    {
        {-983040, -983040, -655360},
        {-655360, -983040, -983040},
        {-983040, -1310720, -655360},
        {-655360, -1310720, -983040},
        {96, 193},
        {96, 162},
        {127, 193},
        {127, 162},
        16
    },
    {
        {-983040, -1966080, -655360},
        {-655360, -1966080, -983040},
        {-983040, -2293760, -655360},
        {-655360, -2293760, -983040},
        {192, 193},
        {192, 162},
        {223, 193},
        {223, 162},
        16
    },
    {
        {-983040, -2293760, -655360},
        {-655360, -2293760, -983040},
        {-983040, -2621440, -655360},
        {-655360, -2621440, -983040},
        {224, 193},
        {224, 162},
        {255, 193},
        {255, 162},
        16
    },
    {
        {-983040, -1638400, -655360},
        {-655360, -1638400, -983040},
        {-983040, -1966080, -655360},
        {-655360, -1966080, -983040},
        {160, 193},
        {160, 162},
        {191, 193},
        {191, 162},
        16
    },
    {
        {-983040, -1310720, -655360},
        {-655360, -1310720, -983040},
        {-983040, -1638400, -655360},
        {-655360, -1638400, -983040},
        {128, 193},
        {128, 162},
        {159, 193},
        {159, 162},
        16
    },
    {
        {-983040, -3276800, -655360},
        {-655360, -3276800, -983040},
        {-983040, -3604480, -655360},
        {-655360, -3604480, -983040},
        {64, 193},
        {64, 162},
        {95, 193},
        {95, 162},
        16
    },
    {
        {-983040, -3604480, -655360},
        {-655360, -3604480, -983040},
        {-983040, -3932160, -655360},
        {-655360, -3932160, -983040},
        {96, 193},
        {96, 162},
        {127, 193},
        {127, 162},
        16
    },
    {
        {-983040, -2949120, -655360},
        {-655360, -2949120, -983040},
        {-983040, -3276800, -655360},
        {-655360, -3276800, -983040},
        {32, 193},
        {32, 162},
        {63, 193},
        {63, 162},
        16
    },
    {
        {-983040, -2621440, -655360},
        {-655360, -2621440, -983040},
        {-983040, -2949120, -655360},
        {-655360, -2949120, -983040},
        {0, 193},
        {0, 162},
        {31, 193},
        {31, 162},
        16
    },
    {
        {-983040, -4259840, -655360},
        {-655360, -4259840, -983040},
        {-983040, -4587520, -655360},
        {-655360, -4587520, -983040},
        {160, 193},
        {160, 162},
        {191, 193},
        {191, 162},
        16
    },
    {
        {-983040, -3932160, -655360},
        {-655360, -3932160, -983040},
        {-983040, -4259840, -655360},
        {-655360, -4259840, -983040},
        {128, 193},
        {128, 162},
        {159, 193},
        {159, 162},
        16
    },
    {
        {-983040, 0, 655360},
        {-983040, -327680, 655360},
        {-655360, 0, 983040},
        {-655360, -327680, 983040},
        {0, 66},
        {31, 66},
        {0, 97},
        {31, 97},
        16
    },
    {
        {-983040, -327680, 655360},
        {-983040, -655360, 655360},
        {-655360, -327680, 983040},
        {-655360, -655360, 983040},
        {32, 66},
        {63, 66},
        {32, 97},
        {63, 97},
        16
    },
    {
        {-983040, -655360, 655360},
        {-983040, -983040, 655360},
        {-655360, -655360, 983040},
        {-655360, -983040, 983040},
        {64, 66},
        {95, 66},
        {64, 97},
        {95, 97},
        16
    },
    {
        {-983040, -983040, 655360},
        {-983040, -1310720, 655360},
        {-655360, -983040, 983040},
        {-655360, -1310720, 983040},
        {96, 66},
        {127, 66},
        {96, 97},
        {127, 97},
        16
    },
    {
        {-983040, -1310720, 655360},
        {-983040, -1638400, 655360},
        {-655360, -1310720, 983040},
        {-655360, -1638400, 983040},
        {128, 66},
        {159, 66},
        {128, 97},
        {159, 97},
        16
    },
    {
        {-983040, -1638400, 655360},
        {-983040, -1966080, 655360},
        {-655360, -1638400, 983040},
        {-655360, -1966080, 983040},
        {160, 66},
        {191, 66},
        {160, 97},
        {191, 97},
        16
    },
    {
        {-983040, -1966080, 655360},
        {-983040, -2293760, 655360},
        {-655360, -1966080, 983040},
        {-655360, -2293760, 983040},
        {192, 66},
        {223, 66},
        {192, 97},
        {223, 97},
        16
    },
    {
        {-983040, -2293760, 655360},
        {-983040, -2621440, 655360},
        {-655360, -2293760, 983040},
        {-655360, -2621440, 983040},
        {224, 66},
        {255, 66},
        {224, 97},
        {255, 97},
        16
    },
    {
        {-983040, -2621440, 655360},
        {-983040, -2949120, 655360},
        {-655360, -2621440, 983040},
        {-655360, -2949120, 983040},
        {0, 66},
        {31, 66},
        {0, 97},
        {31, 97},
        16
    },
    {
        {-983040, -2949120, 655360},
        {-983040, -3276800, 655360},
        {-655360, -2949120, 983040},
        {-655360, -3276800, 983040},
        {32, 66},
        {63, 66},
        {32, 97},
        {63, 97},
        16
    },
    {
        {-983040, -3276800, 655360},
        {-983040, -3604480, 655360},
        {-655360, -3276800, 983040},
        {-655360, -3604480, 983040},
        {64, 66},
        {95, 66},
        {64, 97},
        {95, 97},
        16
    },
    {
        {-983040, -3604480, 655360},
        {-983040, -3932160, 655360},
        {-655360, -3604480, 983040},
        {-655360, -3932160, 983040},
        {96, 66},
        {127, 66},
        {96, 97},
        {127, 97},
        16
    },
    {
        {-983040, -3932160, 655360},
        {-983040, -4259840, 655360},
        {-655360, -3932160, 983040},
        {-655360, -4259840, 983040},
        {128, 66},
        {159, 66},
        {128, 97},
        {159, 97},
        16
    },
    {
        {-983040, -4259840, 655360},
        {-983040, -4587520, 655360},
        {-655360, -4259840, 983040},
        {-655360, -4587520, 983040},
        {160, 66},
        {191, 66},
        {160, 97},
        {191, 97},
        16
    },
    {
        {655360, 0, -983040},
        {983040, 0, -655360},
        {655360, -327680, -983040},
        {983040, -327680, -655360},
        {0, 162},
        {0, 193},
        {31, 162},
        {31, 193},
        16
    },
    {
        {655360, -327680, -983040},
        {983040, -327680, -655360},
        {655360, -655360, -983040},
        {983040, -655360, -655360},
        {32, 162},
        {32, 193},
        {63, 162},
        {63, 193},
        16
    },
    {
        {655360, -655360, -983040},
        {983040, -655360, -655360},
        {655360, -983040, -983040},
        {983040, -983040, -655360},
        {64, 162},
        {64, 193},
        {95, 162},
        {95, 193},
        16
    },
    {
        {655360, -983040, -983040},
        {983040, -983040, -655360},
        {655360, -1310720, -983040},
        {983040, -1310720, -655360},
        {96, 162},
        {96, 193},
        {127, 162},
        {127, 193},
        16
    },
    {
        {655360, -1310720, -983040},
        {983040, -1310720, -655360},
        {655360, -1638400, -983040},
        {983040, -1638400, -655360},
        {128, 162},
        {128, 193},
        {159, 162},
        {159, 193},
        16
    },
    {
        {655360, -1638400, -983040},
        {983040, -1638400, -655360},
        {655360, -1966080, -983040},
        {983040, -1966080, -655360},
        {160, 162},
        {160, 193},
        {191, 162},
        {191, 193},
        16
    },
    {
        {655360, -1966080, -983040},
        {983040, -1966080, -655360},
        {655360, -2293760, -983040},
        {983040, -2293760, -655360},
        {192, 162},
        {192, 193},
        {223, 162},
        {223, 193},
        16
    },
    {
        {655360, -2293760, -983040},
        {983040, -2293760, -655360},
        {655360, -2621440, -983040},
        {983040, -2621440, -655360},
        {224, 162},
        {224, 193},
        {255, 162},
        {255, 193},
        16
    },
    {
        {655360, -2621440, -983040},
        {983040, -2621440, -655360},
        {655360, -2949120, -983040},
        {983040, -2949120, -655360},
        {0, 162},
        {0, 193},
        {31, 162},
        {31, 193},
        16
    },
    {
        {655360, -2949120, -983040},
        {983040, -2949120, -655360},
        {655360, -3276800, -983040},
        {983040, -3276800, -655360},
        {32, 162},
        {32, 193},
        {63, 162},
        {63, 193},
        16
    },
    {
        {655360, -3276800, -983040},
        {983040, -3276800, -655360},
        {655360, -3604480, -983040},
        {983040, -3604480, -655360},
        {64, 162},
        {64, 193},
        {95, 162},
        {95, 193},
        16
    },
    {
        {655360, -3604480, -983040},
        {983040, -3604480, -655360},
        {655360, -3932160, -983040},
        {983040, -3932160, -655360},
        {96, 162},
        {96, 193},
        {127, 162},
        {127, 193},
        16
    },
    {
        {655360, -3932160, -983040},
        {983040, -3932160, -655360},
        {655360, -4259840, -983040},
        {983040, -4259840, -655360},
        {128, 162},
        {128, 193},
        {159, 162},
        {159, 193},
        16
    },
    {
        {655360, -4259840, -983040},
        {983040, -4259840, -655360},
        {655360, -4587520, -983040},
        {983040, -4587520, -655360},
        {160, 162},
        {160, 193},
        {191, 162},
        {191, 193},
        16
    },
    {
        {655360, -327680, 983040},
        {983040, -327680, 655360},
        {655360, 0, 983040},
        {983040, 0, 655360},
        {31, 97},
        {31, 66},
        {0, 97},
        {0, 66},
        16
    },
    {
        {655360, -655360, 983040},
        {983040, -655360, 655360},
        {655360, -327680, 983040},
        {983040, -327680, 655360},
        {63, 97},
        {63, 66},
        {32, 97},
        {32, 66},
        16
    },
    {
        {655360, -983040, 983040},
        {983040, -983040, 655360},
        {655360, -655360, 983040},
        {983040, -655360, 655360},
        {95, 97},
        {95, 66},
        {64, 97},
        {64, 66},
        16
    },
    {
        {655360, -1310720, 983040},
        {983040, -1310720, 655360},
        {655360, -983040, 983040},
        {983040, -983040, 655360},
        {127, 97},
        {127, 66},
        {96, 97},
        {96, 66},
        16
    },
    {
        {655360, -1638400, 983040},
        {983040, -1638400, 655360},
        {655360, -1310720, 983040},
        {983040, -1310720, 655360},
        {159, 97},
        {159, 66},
        {128, 97},
        {128, 66},
        16
    },
    {
        {655360, -1966080, 983040},
        {983040, -1966080, 655360},
        {655360, -1638400, 983040},
        {983040, -1638400, 655360},
        {191, 97},
        {191, 66},
        {160, 97},
        {160, 66},
        16
    },
    {
        {655360, -2293760, 983040},
        {983040, -2293760, 655360},
        {655360, -1966080, 983040},
        {983040, -1966080, 655360},
        {223, 97},
        {223, 66},
        {192, 97},
        {192, 66},
        16
    },
    {
        {655360, -2621440, 983040},
        {983040, -2621440, 655360},
        {655360, -2293760, 983040},
        {983040, -2293760, 655360},
        {255, 97},
        {255, 66},
        {224, 97},
        {224, 66},
        16
    },
    {
        {655360, -2949120, 983040},
        {983040, -2949120, 655360},
        {655360, -2621440, 983040},
        {983040, -2621440, 655360},
        {31, 97},
        {31, 66},
        {0, 97},
        {0, 66},
        16
    },
    {
        {655360, -3276800, 983040},
        {983040, -3276800, 655360},
        {655360, -2949120, 983040},
        {983040, -2949120, 655360},
        {63, 97},
        {63, 66},
        {32, 97},
        {32, 66},
        16
    },
    {
        {655360, -3604480, 983040},
        {983040, -3604480, 655360},
        {655360, -3276800, 983040},
        {983040, -3276800, 655360},
        {95, 97},
        {95, 66},
        {64, 97},
        {64, 66},
        16
    },
    {
        {655360, -3932160, 983040},
        {983040, -3932160, 655360},
        {655360, -3604480, 983040},
        {983040, -3604480, 655360},
        {127, 97},
        {127, 66},
        {96, 97},
        {96, 66},
        16
    },
    {
        {655360, -4259840, 983040},
        {983040, -4259840, 655360},
        {655360, -3932160, 983040},
        {983040, -3932160, 655360},
        {159, 97},
        {159, 66},
        {128, 97},
        {128, 66},
        16
    },
    {
        {655360, -4587520, 983040},
        {983040, -4587520, 655360},
        {655360, -4259840, 983040},
        {983040, -4259840, 655360},
        {191, 97},
        {191, 66},
        {160, 97},
        {160, 66},
        16
    },
    {
        {-327680, 0, -983040},
        {0, 0, -983040},
        {-327680, -327680, -983040},
        {0, -327680, -983040},
        {224, 255},
        {255, 255},
        {224, 224},
        {255, 224},
        16
    },
    {
        {-327680, -327680, -983040},
        {0, -327680, -983040},
        {-327680, -655360, -983040},
        {0, -655360, -983040},
        {224, 223},
        {255, 223},
        {224, 192},
        {255, 192},
        0
    },
    {
        {0, -327680, -983040},
        {327680, -327680, -983040},
        {0, -655360, -983040},
        {327680, -655360, -983040},
        {0, 223},
        {31, 223},
        {0, 192},
        {31, 192},
        0
    },
    {
        {-1048576, -327680, 327680},
        {-983040, -327680, 655360},
        {-1048576, 0, 327680},
        {-983040, 0, 655360},
        {223, 224},
        {192, 224},
        {223, 255},
        {192, 255},
        14
    },
    {
        {-1048576, -327680, 0},
        {-1048576, -327680, 327680},
        {-1048576, 0, 0},
        {-1048576, 0, 327680},
        {0, 224},
        {31, 224},
        {0, 255},
        {31, 255},
        16
    },
    {
        {-1048576, -655360, -327680},
        {-1048576, -655360, 0},
        {-1048576, -327680, -327680},
        {-1048576, -327680, 0},
        {224, 192},
        {255, 192},
        {224, 223},
        {255, 223},
        15
    },
    {
        {-1048576, -655360, 0},
        {-1048576, -655360, 327680},
        {-1048576, -327680, 0},
        {-1048576, -327680, 327680},
        {0, 192},
        {31, 192},
        {0, 223},
        {31, 223},
        15
    },
    {
        {-1048576, -983040, -327680},
        {-1048576, -983040, 0},
        {-1048576, -655360, -327680},
        {-1048576, -655360, 0},
        {0, 160},
        {31, 160},
        {0, 191},
        {31, 191},
        6
    },
    {
        {-1048576, -983040, 0},
        {-1048576, -983040, 327680},
        {-1048576, -655360, 0},
        {-1048576, -655360, 327680},
        {32, 160},
        {63, 160},
        {32, 191},
        {63, 191},
        6
    },
    {
        {-1048576, -1310720, -327680},
        {-1048576, -1310720, 0},
        {-1048576, -983040, -327680},
        {-1048576, -983040, 0},
        {0, 128},
        {31, 128},
        {0, 159},
        {31, 159},
        6
    },
    {
        {-1048576, -1310720, 0},
        {-1048576, -1310720, 327680},
        {-1048576, -983040, 0},
        {-1048576, -983040, 327680},
        {32, 128},
        {63, 128},
        {32, 159},
        {63, 159},
        6
    },
    {
        {-1048576, -1638400, -327680},
        {-1048576, -1638400, 0},
        {-1048576, -1310720, -327680},
        {-1048576, -1310720, 0},
        {0, 96},
        {31, 96},
        {0, 127},
        {31, 127},
        6
    },
    {
        {-1048576, -1638400, 0},
        {-1048576, -1638400, 327680},
        {-1048576, -1310720, 0},
        {-1048576, -1310720, 327680},
        {32, 96},
        {63, 96},
        {32, 127},
        {63, 127},
        6
    },
    {
        {-1048576, -1966080, -327680},
        {-1048576, -1966080, 0},
        {-1048576, -1638400, -327680},
        {-1048576, -1638400, 0},
        {0, 64},
        {31, 64},
        {0, 95},
        {31, 95},
        9
    },
    {
        {-1048576, -1966080, 0},
        {-1048576, -1966080, 327680},
        {-1048576, -1638400, 0},
        {-1048576, -1638400, 327680},
        {32, 64},
        {63, 64},
        {32, 95},
        {63, 95},
        9
    },
    {
        {1048576, -1638400, -327680},
        {1048576, -1638400, 0},
        {1048576, -1966080, -327680},
        {1048576, -1966080, 0},
        {0, 95},
        {31, 95},
        {0, 64},
        {31, 64},
        9
    },
    {
        {1048576, -1310720, -327680},
        {1048576, -1310720, 0},
        {1048576, -1638400, -327680},
        {1048576, -1638400, 0},
        {0, 127},
        {31, 127},
        {0, 96},
        {31, 96},
        6
    },
    {
        {1048576, -983040, -327680},
        {1048576, -983040, 0},
        {1048576, -1310720, -327680},
        {1048576, -1310720, 0},
        {0, 159},
        {31, 159},
        {0, 128},
        {31, 128},
        6
    },
    {
        {1048576, -655360, -327680},
        {1048576, -655360, 0},
        {1048576, -983040, -327680},
        {1048576, -983040, 0},
        {0, 191},
        {31, 191},
        {0, 160},
        {31, 160},
        6
    },
    {
        {1048576, -327680, -327680},
        {1048576, -327680, 0},
        {1048576, -655360, -327680},
        {1048576, -655360, 0},
        {224, 223},
        {255, 223},
        {224, 192},
        {255, 192},
        15
    },
    {
        {1048576, -327680, 0},
        {1048576, -327680, 327680},
        {1048576, -655360, 0},
        {1048576, -655360, 327680},
        {0, 223},
        {31, 223},
        {0, 192},
        {31, 192},
        15
    },
    {
        {1048576, -655360, 0},
        {1048576, -655360, 327680},
        {1048576, -983040, 0},
        {1048576, -983040, 327680},
        {32, 191},
        {63, 191},
        {32, 160},
        {63, 160},
        6
    },
    {
        {1048576, -983040, 0},
        {1048576, -983040, 327680},
        {1048576, -1310720, 0},
        {1048576, -1310720, 327680},
        {32, 159},
        {63, 159},
        {32, 128},
        {63, 128},
        6
    },
    {
        {1048576, -1310720, 0},
        {1048576, -1310720, 327680},
        {1048576, -1638400, 0},
        {1048576, -1638400, 327680},
        {32, 127},
        {63, 127},
        {32, 96},
        {63, 96},
        6
    },
    {
        {1048576, -1638400, 0},
        {1048576, -1638400, 327680},
        {1048576, -1966080, 0},
        {1048576, -1966080, 327680},
        {32, 95},
        {63, 95},
        {32, 64},
        {63, 64},
        9
    },
    {
        {-1048576, -1966080, 327680},
        {-1048576, -2293760, 327680},
        {-983040, -1966080, 655360},
        {-983040, -2293760, 655360},
        {39, 63},
        {39, 32},
        {70, 63},
        {70, 32},
        7
    },
    {
        {-1048576, -2293760, 327680},
        {-1048576, -2621440, 327680},
        {-983040, -2293760, 655360},
        {-983040, -2621440, 655360},
        {39, 31},
        {39, 0},
        {70, 31},
        {70, 0},
        7
    },
    {
        {-1048576, -2621440, 327680},
        {-1048576, -2949120, 327680},
        {-983040, -2621440, 655360},
        {-983040, -2949120, 655360},
        {39, 255},
        {39, 224},
        {70, 255},
        {70, 224},
        7
    },
    {
        {-1048576, -2949120, 327680},
        {-1048576, -3276800, 327680},
        {-983040, -2949120, 655360},
        {-983040, -3276800, 655360},
        {39, 223},
        {39, 192},
        {70, 223},
        {70, 192},
        7
    },
    {
        {-1048576, -3276800, 327680},
        {-1048576, -3604480, 327680},
        {-983040, -3276800, 655360},
        {-983040, -3604480, 655360},
        {39, 191},
        {39, 160},
        {70, 191},
        {70, 160},
        7
    },
    {
        {-1048576, -3604480, 327680},
        {-1048576, -3932160, 327680},
        {-983040, -3604480, 655360},
        {-983040, -3932160, 655360},
        {39, 159},
        {39, 128},
        {70, 159},
        {70, 128},
        7
    },
    {
        {-1048576, -3932160, 327680},
        {-1048576, -4259840, 327680},
        {-983040, -3932160, 655360},
        {-983040, -4259840, 655360},
        {39, 127},
        {39, 96},
        {70, 127},
        {70, 96},
        7
    },
    {
        {-1048576, -4259840, 327680},
        {-1048576, -4587520, 327680},
        {-983040, -4259840, 655360},
        {-983040, -4587520, 655360},
        {39, 95},
        {39, 64},
        {70, 95},
        {70, 64},
        7
    },
    {
        {-1048576, -1966080, -327680},
        {-983040, -1966080, -655360},
        {-1048576, -2293760, -327680},
        {-983040, -2293760, -655360},
        {216, 63},
        {185, 63},
        {216, 32},
        {185, 32},
        7
    },
    {
        {-1048576, -2293760, -327680},
        {-983040, -2293760, -655360},
        {-1048576, -2621440, -327680},
        {-983040, -2621440, -655360},
        {216, 31},
        {185, 31},
        {216, 0},
        {185, 0},
        7
    },
    {
        {-1048576, -2621440, -327680},
        {-983040, -2621440, -655360},
        {-1048576, -2949120, -327680},
        {-983040, -2949120, -655360},
        {216, 255},
        {185, 255},
        {216, 224},
        {185, 224},
        7
    },
    {
        {-1048576, -2949120, -327680},
        {-983040, -2949120, -655360},
        {-1048576, -3276800, -327680},
        {-983040, -3276800, -655360},
        {216, 223},
        {185, 223},
        {216, 192},
        {185, 192},
        7
    },
    {
        {-1048576, -3276800, -327680},
        {-983040, -3276800, -655360},
        {-1048576, -3604480, -327680},
        {-983040, -3604480, -655360},
        {216, 191},
        {185, 191},
        {216, 160},
        {185, 160},
        7
    },
    {
        {-1048576, -3604480, -327680},
        {-983040, -3604480, -655360},
        {-1048576, -3932160, -327680},
        {-983040, -3932160, -655360},
        {216, 159},
        {185, 159},
        {216, 128},
        {185, 128},
        7
    },
    {
        {-1048576, -3932160, -327680},
        {-983040, -3932160, -655360},
        {-1048576, -4259840, -327680},
        {-983040, -4259840, -655360},
        {216, 127},
        {185, 127},
        {216, 96},
        {185, 96},
        7
    },
    {
        {-1048576, -4259840, -327680},
        {-983040, -4259840, -655360},
        {-1048576, -4587520, -327680},
        {-983040, -4587520, -655360},
        {216, 95},
        {185, 95},
        {216, 64},
        {185, 64},
        7
    },
    {
        {983040, -4259840, -655360},
        {1048576, -4259840, -327680},
        {983040, -4587520, -655360},
        {1048576, -4587520, -327680},
        {185, 95},
        {216, 95},
        {185, 64},
        {216, 64},
        7
    },
    {
        {983040, -4587520, 655360},
        {1048576, -4587520, 327680},
        {983040, -4259840, 655360},
        {1048576, -4259840, 327680},
        {70, 64},
        {39, 64},
        {70, 95},
        {39, 95},
        7
    },
    {
        {983040, -3932160, -655360},
        {1048576, -3932160, -327680},
        {983040, -4259840, -655360},
        {1048576, -4259840, -327680},
        {185, 127},
        {216, 127},
        {185, 96},
        {216, 96},
        7
    },
    {
        {983040, -4259840, 655360},
        {1048576, -4259840, 327680},
        {983040, -3932160, 655360},
        {1048576, -3932160, 327680},
        {70, 96},
        {39, 96},
        {70, 127},
        {39, 127},
        7
    },
    {
        {983040, -3932160, 655360},
        {1048576, -3932160, 327680},
        {983040, -3604480, 655360},
        {1048576, -3604480, 327680},
        {70, 128},
        {39, 128},
        {70, 159},
        {39, 159},
        7
    },
    {
        {983040, -3604480, 655360},
        {1048576, -3604480, 327680},
        {983040, -3276800, 655360},
        {1048576, -3276800, 327680},
        {70, 160},
        {39, 160},
        {70, 191},
        {39, 191},
        7
    },
    {
        {983040, -3276800, 655360},
        {1048576, -3276800, 327680},
        {983040, -2949120, 655360},
        {1048576, -2949120, 327680},
        {70, 192},
        {39, 192},
        {70, 223},
        {39, 223},
        7
    },
    {
        {983040, -2949120, 655360},
        {1048576, -2949120, 327680},
        {983040, -2621440, 655360},
        {1048576, -2621440, 327680},
        {70, 224},
        {39, 224},
        {70, 255},
        {39, 255},
        7
    },
    {
        {983040, -2621440, 655360},
        {1048576, -2621440, 327680},
        {983040, -2293760, 655360},
        {1048576, -2293760, 327680},
        {70, 0},
        {39, 0},
        {70, 31},
        {39, 31},
        7
    },
    {
        {983040, -2293760, 655360},
        {1048576, -2293760, 327680},
        {983040, -1966080, 655360},
        {1048576, -1966080, 327680},
        {70, 32},
        {39, 32},
        {70, 63},
        {39, 63},
        7
    },
    {
        {983040, -1966080, -655360},
        {1048576, -1966080, -327680},
        {983040, -2293760, -655360},
        {1048576, -2293760, -327680},
        {185, 63},
        {216, 63},
        {185, 32},
        {216, 32},
        7
    },
    {
        {983040, -2293760, -655360},
        {1048576, -2293760, -327680},
        {983040, -2621440, -655360},
        {1048576, -2621440, -327680},
        {185, 31},
        {216, 31},
        {185, 0},
        {216, 0},
        7
    },
    {
        {983040, -2621440, -655360},
        {1048576, -2621440, -327680},
        {983040, -2949120, -655360},
        {1048576, -2949120, -327680},
        {185, 255},
        {216, 255},
        {185, 224},
        {216, 224},
        7
    },
    {
        {983040, -2949120, -655360},
        {1048576, -2949120, -327680},
        {983040, -3276800, -655360},
        {1048576, -3276800, -327680},
        {185, 223},
        {216, 223},
        {185, 192},
        {216, 192},
        7
    },
    {
        {983040, -3276800, -655360},
        {1048576, -3276800, -327680},
        {983040, -3604480, -655360},
        {1048576, -3604480, -327680},
        {185, 191},
        {216, 191},
        {185, 160},
        {216, 160},
        7
    },
    {
        {983040, -3604480, -655360},
        {1048576, -3604480, -327680},
        {983040, -3932160, -655360},
        {1048576, -3932160, -327680},
        {185, 159},
        {216, 159},
        {185, 128},
        {216, 128},
        7
    },
    {
        {1048576, -1966080, 0},
        {1048576, -1966080, 327680},
        {1048576, -2293760, 0},
        {1048576, -2293760, 327680},
        {32, 63},
        {63, 63},
        {32, 32},
        {63, 32},
        3
    },
    {
        {1048576, -1966080, -327680},
        {1048576, -1966080, 0},
        {1048576, -2293760, -327680},
        {1048576, -2293760, 0},
        {0, 63},
        {31, 63},
        {0, 32},
        {31, 32},
        3
    },
    {
        {1048576, -2293760, -327680},
        {1048576, -2293760, 0},
        {1048576, -2621440, -327680},
        {1048576, -2621440, 0},
        {0, 31},
        {31, 31},
        {0, 0},
        {31, 0},
        3
    },
    {
        {1048576, -2293760, 0},
        {1048576, -2293760, 327680},
        {1048576, -2621440, 0},
        {1048576, -2621440, 327680},
        {32, 31},
        {63, 31},
        {32, 0},
        {63, 0},
        3
    },
    {
        {1048576, -2949120, -327680},
        {1048576, -2949120, 0},
        {1048576, -3276800, -327680},
        {1048576, -3276800, 0},
        {0, 223},
        {31, 223},
        {0, 192},
        {31, 192},
        3
    },
    {
        {1048576, -2949120, 0},
        {1048576, -2949120, 327680},
        {1048576, -3276800, 0},
        {1048576, -3276800, 327680},
        {32, 223},
        {63, 223},
        {32, 192},
        {63, 192},
        3
    },
    {
        {1048576, -2621440, -327680},
        {1048576, -2621440, 0},
        {1048576, -2949120, -327680},
        {1048576, -2949120, 0},
        {0, 255},
        {31, 255},
        {0, 224},
        {31, 224},
        3
    },
    {
        {1048576, -2621440, 0},
        {1048576, -2621440, 327680},
        {1048576, -2949120, 0},
        {1048576, -2949120, 327680},
        {32, 255},
        {63, 255},
        {32, 224},
        {63, 224},
        3
    },
    {
        {1048576, -3604480, -327680},
        {1048576, -3604480, 0},
        {1048576, -3932160, -327680},
        {1048576, -3932160, 0},
        {0, 159},
        {31, 159},
        {0, 128},
        {31, 128},
        3
    },
    {
        {1048576, -3604480, 0},
        {1048576, -3604480, 327680},
        {1048576, -3932160, 0},
        {1048576, -3932160, 327680},
        {32, 159},
        {63, 159},
        {32, 128},
        {63, 128},
        3
    },
    {
        {1048576, -3276800, -327680},
        {1048576, -3276800, 0},
        {1048576, -3604480, -327680},
        {1048576, -3604480, 0},
        {0, 191},
        {31, 191},
        {0, 160},
        {31, 160},
        3
    },
    {
        {1048576, -3276800, 0},
        {1048576, -3276800, 327680},
        {1048576, -3604480, 0},
        {1048576, -3604480, 327680},
        {32, 191},
        {63, 191},
        {32, 160},
        {63, 160},
        3
    },
    {
        {1048576, -4259840, -327680},
        {1048576, -4259840, 0},
        {1048576, -4587520, -327680},
        {1048576, -4587520, 0},
        {0, 95},
        {31, 95},
        {0, 64},
        {31, 64},
        3
    },
    {
        {1048576, -4259840, 0},
        {1048576, -4259840, 327680},
        {1048576, -4587520, 0},
        {1048576, -4587520, 327680},
        {32, 95},
        {63, 95},
        {32, 64},
        {63, 64},
        3
    },
    {
        {1048576, -3932160, -327680},
        {1048576, -3932160, 0},
        {1048576, -4259840, -327680},
        {1048576, -4259840, 0},
        {0, 127},
        {31, 127},
        {0, 96},
        {31, 96},
        3
    },
    {
        {1048576, -3932160, 0},
        {1048576, -3932160, 327680},
        {1048576, -4259840, 0},
        {1048576, -4259840, 327680},
        {32, 127},
        {63, 127},
        {32, 96},
        {63, 96},
        3
    },
    {
        {-1048576, -2293760, 0},
        {-1048576, -2293760, 327680},
        {-1048576, -1966080, 0},
        {-1048576, -1966080, 327680},
        {32, 32},
        {63, 32},
        {32, 63},
        {63, 63},
        3
    },
    {
        {-1048576, -2293760, -327680},
        {-1048576, -2293760, 0},
        {-1048576, -1966080, -327680},
        {-1048576, -1966080, 0},
        {0, 32},
        {31, 32},
        {0, 63},
        {31, 63},
        3
    },
    {
        {-1048576, -2621440, -327680},
        {-1048576, -2621440, 0},
        {-1048576, -2293760, -327680},
        {-1048576, -2293760, 0},
        {0, 0},
        {31, 0},
        {0, 31},
        {31, 31},
        3
    },
    {
        {-1048576, -2949120, -327680},
        {-1048576, -2949120, 0},
        {-1048576, -2621440, -327680},
        {-1048576, -2621440, 0},
        {0, 224},
        {31, 224},
        {0, 255},
        {31, 255},
        3
    },
    {
        {-1048576, -3276800, -327680},
        {-1048576, -3276800, 0},
        {-1048576, -2949120, -327680},
        {-1048576, -2949120, 0},
        {0, 192},
        {31, 192},
        {0, 223},
        {31, 223},
        3
    },
    {
        {-1048576, -3604480, -327680},
        {-1048576, -3604480, 0},
        {-1048576, -3276800, -327680},
        {-1048576, -3276800, 0},
        {0, 160},
        {31, 160},
        {0, 191},
        {31, 191},
        3
    },
    {
        {-1048576, -3932160, -327680},
        {-1048576, -3932160, 0},
        {-1048576, -3604480, -327680},
        {-1048576, -3604480, 0},
        {0, 128},
        {31, 128},
        {0, 159},
        {31, 159},
        3
    },
    {
        {-1048576, -4259840, -327680},
        {-1048576, -4259840, 0},
        {-1048576, -3932160, -327680},
        {-1048576, -3932160, 0},
        {0, 96},
        {31, 96},
        {0, 127},
        {31, 127},
        3
    },
    {
        {-1048576, -4587520, -327680},
        {-1048576, -4587520, 0},
        {-1048576, -4259840, -327680},
        {-1048576, -4259840, 0},
        {0, 64},
        {31, 64},
        {0, 95},
        {31, 95},
        3
    },
    {
        {-1048576, -4587520, 0},
        {-1048576, -4587520, 327680},
        {-1048576, -4259840, 0},
        {-1048576, -4259840, 327680},
        {32, 64},
        {63, 64},
        {32, 95},
        {63, 95},
        3
    },
    {
        {-1048576, -4259840, 0},
        {-1048576, -4259840, 327680},
        {-1048576, -3932160, 0},
        {-1048576, -3932160, 327680},
        {32, 96},
        {63, 96},
        {32, 127},
        {63, 127},
        3
    },
    {
        {-1048576, -3932160, 0},
        {-1048576, -3932160, 327680},
        {-1048576, -3604480, 0},
        {-1048576, -3604480, 327680},
        {32, 128},
        {63, 128},
        {32, 159},
        {63, 159},
        3
    },
    {
        {-1048576, -3604480, 0},
        {-1048576, -3604480, 327680},
        {-1048576, -3276800, 0},
        {-1048576, -3276800, 327680},
        {32, 160},
        {63, 160},
        {32, 191},
        {63, 191},
        3
    },
    {
        {-1048576, -3276800, 0},
        {-1048576, -3276800, 327680},
        {-1048576, -2949120, 0},
        {-1048576, -2949120, 327680},
        {32, 192},
        {63, 192},
        {32, 223},
        {63, 223},
        3
    },
    {
        {-1048576, -2949120, 0},
        {-1048576, -2949120, 327680},
        {-1048576, -2621440, 0},
        {-1048576, -2621440, 327680},
        {32, 224},
        {63, 224},
        {32, 255},
        {63, 255},
        3
    },
    {
        {-1048576, -2621440, 0},
        {-1048576, -2621440, 327680},
        {-1048576, -2293760, 0},
        {-1048576, -2293760, 327680},
        {32, 0},
        {63, 0},
        {32, 31},
        {63, 31},
        3
    },
    {
        {0, -983040, -983040},
        {327680, -983040, -983040},
        {0, -1310720, -983040},
        {327680, -1310720, -983040},
        {128, 0},
        {128, 31},
        {159, 0},
        {159, 31},
        7
    },
    {
        {-327680, -983040, -983040},
        {0, -983040, -983040},
        {-327680, -1310720, -983040},
        {0, -1310720, -983040},
        {128, 224},
        {128, 255},
        {159, 224},
        {159, 255},
        7
    },
    {
        {0, -655360, -983040},
        {327680, -655360, -983040},
        {0, -983040, -983040},
        {327680, -983040, -983040},
        {64, 0},
        {64, 31},
        {95, 0},
        {95, 31},
        7
    },
    {
        {-327680, -655360, -983040},
        {0, -655360, -983040},
        {-327680, -983040, -983040},
        {0, -983040, -983040},
        {64, 224},
        {64, 255},
        {95, 224},
        {95, 255},
        7
    },
    {
        {0, -1638400, -983040},
        {327680, -1638400, -983040},
        {0, -1966080, -983040},
        {327680, -1966080, -983040},
        {32, 95},
        {63, 95},
        {32, 64},
        {63, 64},
        16
    },
    {
        {-327680, -1638400, -983040},
        {0, -1638400, -983040},
        {-327680, -1966080, -983040},
        {0, -1966080, -983040},
        {0, 95},
        {31, 95},
        {0, 64},
        {31, 64},
        16
    },
    {
        {-327680, -1310720, -983040},
        {0, -1310720, -983040},
        {-327680, -1638400, -983040},
        {0, -1638400, -983040},
        {0, 127},
        {31, 127},
        {0, 96},
        {31, 96},
        0
    },
    {
        {0, -1310720, -983040},
        {327680, -1310720, -983040},
        {0, -1638400, -983040},
        {327680, -1638400, -983040},
        {32, 127},
        {63, 127},
        {32, 96},
        {63, 96},
        0
    },
    {
        {0, -1966080, -983040},
        {327680, -1966080, -983040},
        {0, -2293760, -983040},
        {327680, -2293760, -983040},
        {32, 63},
        {63, 63},
        {32, 32},
        {63, 32},
        3
    },
    {
        {-327680, -1966080, -983040},
        {0, -1966080, -983040},
        {-327680, -2293760, -983040},
        {0, -2293760, -983040},
        {0, 63},
        {31, 63},
        {0, 32},
        {31, 32},
        3
    },
    {
        {-327680, -2293760, -983040},
        {0, -2293760, -983040},
        {-327680, -2621440, -983040},
        {0, -2621440, -983040},
        {0, 31},
        {31, 31},
        {0, 0},
        {31, 0},
        3
    },
    {
        {0, -2293760, -983040},
        {327680, -2293760, -983040},
        {0, -2621440, -983040},
        {327680, -2621440, -983040},
        {32, 31},
        {63, 31},
        {32, 0},
        {63, 0},
        3
    },
    {
        {-327680, -2621440, -983040},
        {0, -2621440, -983040},
        {-327680, -2949120, -983040},
        {0, -2949120, -983040},
        {0, 255},
        {31, 255},
        {0, 224},
        {31, 224},
        3
    },
    {
        {0, -2949120, -983040},
        {327680, -2949120, -983040},
        {0, -3276800, -983040},
        {327680, -3276800, -983040},
        {32, 223},
        {63, 223},
        {32, 192},
        {63, 192},
        3
    },
    {
        {-327680, -2949120, -983040},
        {0, -2949120, -983040},
        {-327680, -3276800, -983040},
        {0, -3276800, -983040},
        {0, 223},
        {31, 223},
        {0, 192},
        {31, 192},
        3
    },
    {
        {0, -2621440, -983040},
        {327680, -2621440, -983040},
        {0, -2949120, -983040},
        {327680, -2949120, -983040},
        {32, 255},
        {63, 255},
        {32, 224},
        {63, 224},
        3
    },
    {
        {-327680, -3276800, -983040},
        {0, -3276800, -983040},
        {-327680, -3604480, -983040},
        {0, -3604480, -983040},
        {0, 191},
        {31, 191},
        {0, 160},
        {31, 160},
        3
    },
    {
        {0, -3604480, -983040},
        {327680, -3604480, -983040},
        {0, -3932160, -983040},
        {327680, -3932160, -983040},
        {32, 159},
        {63, 159},
        {32, 128},
        {63, 128},
        3
    },
    {
        {-327680, -3604480, -983040},
        {0, -3604480, -983040},
        {-327680, -3932160, -983040},
        {0, -3932160, -983040},
        {0, 159},
        {31, 159},
        {0, 128},
        {31, 128},
        3
    },
    {
        {0, -3276800, -983040},
        {327680, -3276800, -983040},
        {0, -3604480, -983040},
        {327680, -3604480, -983040},
        {32, 191},
        {63, 191},
        {32, 160},
        {63, 160},
        3
    },
    {
        {-327680, -3932160, -983040},
        {0, -3932160, -983040},
        {-327680, -4259840, -983040},
        {0, -4259840, -983040},
        {0, 127},
        {31, 127},
        {0, 96},
        {31, 96},
        3
    },
    {
        {0, -4259840, -983040},
        {327680, -4259840, -983040},
        {0, -4587520, -983040},
        {327680, -4587520, -983040},
        {32, 95},
        {63, 95},
        {32, 64},
        {63, 64},
        3
    },
    {
        {-327680, -4259840, -983040},
        {0, -4259840, -983040},
        {-327680, -4587520, -983040},
        {0, -4587520, -983040},
        {0, 95},
        {31, 95},
        {0, 64},
        {31, 64},
        3
    },
    {
        {0, -3932160, -983040},
        {327680, -3932160, -983040},
        {0, -4259840, -983040},
        {327680, -4259840, -983040},
        {32, 127},
        {63, 127},
        {32, 96},
        {63, 96},
        3
    },
    {
        {-688128, -1310720, -983040},
        {-655360, -1310720, -917504},
        {-688128, -1638400, -983040},
        {-655360, -1638400, -917504},
        {0, 191},
        {15, 191},
        {0, 112},
        {15, 112},
        11
    },
    {
        {-655360, -1310720, -917504},
        {-327680, -1310720, -917504},
        {-655360, -1638400, -917504},
        {-327680, -1638400, -917504},
        {192, 127},
        {223, 127},
        {192, 96},
        {223, 96},
        4
    },
    {
        {-327680, -1638400, -983040},
        {-327680, -1638400, -917504},
        {-327680, -1310720, -983040},
        {-327680, -1310720, -917504},
        {0, 112},
        {15, 112},
        {0, 191},
        {15, 191},
        11
    },
    {
        {-688128, -1638400, -983040},
        {-655360, -1638400, -917504},
        {-688128, -1966080, -983040},
        {-655360, -1966080, -917504},
        {0, 111},
        {15, 111},
        {0, 32},
        {15, 32},
        11
    },
    {
        {-655360, -1638400, -917504},
        {-327680, -1638400, -917504},
        {-655360, -1966080, -917504},
        {-327680, -1966080, -917504},
        {192, 95},
        {223, 95},
        {192, 64},
        {223, 64},
        4
    },
    {
        {-327680, -1966080, -983040},
        {-327680, -1966080, -917504},
        {-327680, -1638400, -983040},
        {-327680, -1638400, -917504},
        {0, 32},
        {15, 32},
        {0, 111},
        {15, 111},
        11
    },
    {
        {327680, -1310720, -983040},
        {327680, -1310720, -917504},
        {327680, -1638400, -983040},
        {327680, -1638400, -917504},
        {0, 191},
        {15, 191},
        {0, 112},
        {15, 112},
        11
    },
    {
        {327680, -1310720, -917504},
        {655360, -1310720, -917504},
        {327680, -1638400, -917504},
        {655360, -1638400, -917504},
        {32, 127},
        {63, 127},
        {32, 96},
        {63, 96},
        4
    },
    {
        {688128, -1638400, -983040},
        {655360, -1638400, -917504},
        {688128, -1310720, -983040},
        {655360, -1310720, -917504},
        {0, 112},
        {15, 112},
        {0, 191},
        {15, 191},
        11
    },
    {
        {327680, -1638400, -983040},
        {327680, -1638400, -917504},
        {327680, -1966080, -983040},
        {327680, -1966080, -917504},
        {0, 111},
        {15, 111},
        {0, 32},
        {15, 32},
        11
    },
    {
        {327680, -1638400, -917504},
        {655360, -1638400, -917504},
        {327680, -1966080, -917504},
        {655360, -1966080, -917504},
        {32, 95},
        {63, 95},
        {32, 64},
        {63, 64},
        4
    },
    {
        {688128, -1966080, -983040},
        {655360, -1966080, -917504},
        {688128, -1638400, -983040},
        {655360, -1638400, -917504},
        {0, 32},
        {15, 32},
        {0, 111},
        {15, 111},
        11
    },
    {
        {-688128, -1966080, -983040},
        {-655360, -1966080, -917504},
        {-688128, -2293760, -983040},
        {-655360, -2293760, -917504},
        {0, 31},
        {15, 31},
        {0, 208},
        {15, 208},
        11
    },
    {
        {-655360, -1966080, -917504},
        {-327680, -1966080, -917504},
        {-655360, -2293760, -917504},
        {-327680, -2293760, -917504},
        {192, 63},
        {223, 63},
        {192, 32},
        {223, 32},
        15
    },
    {
        {-327680, -2293760, -983040},
        {-327680, -2293760, -917504},
        {-327680, -1966080, -983040},
        {-327680, -1966080, -917504},
        {0, 208},
        {15, 208},
        {0, 31},
        {15, 31},
        11
    },
    {
        {-688128, -2293760, -983040},
        {-655360, -2293760, -917504},
        {-688128, -2621440, -983040},
        {-655360, -2621440, -917504},
        {0, 207},
        {15, 207},
        {0, 128},
        {15, 128},
        11
    },
    {
        {-655360, -2293760, -917504},
        {-327680, -2293760, -917504},
        {-655360, -2621440, -917504},
        {-327680, -2621440, -917504},
        {192, 31},
        {223, 31},
        {192, 0},
        {223, 0},
        6
    },
    {
        {-327680, -2621440, -983040},
        {-327680, -2621440, -917504},
        {-327680, -2293760, -983040},
        {-327680, -2293760, -917504},
        {0, 128},
        {15, 128},
        {0, 207},
        {15, 207},
        11
    },
    {
        {-688128, -2621440, -983040},
        {-655360, -2621440, -917504},
        {-688128, -2949120, -983040},
        {-655360, -2949120, -917504},
        {0, 127},
        {15, 127},
        {0, 48},
        {15, 48},
        11
    },
    {
        {-655360, -2621440, -917504},
        {-327680, -2621440, -917504},
        {-655360, -2949120, -917504},
        {-327680, -2949120, -917504},
        {192, 255},
        {223, 255},
        {192, 224},
        {223, 224},
        6
    },
    {
        {-327680, -2949120, -983040},
        {-327680, -2949120, -917504},
        {-327680, -2621440, -983040},
        {-327680, -2621440, -917504},
        {0, 48},
        {15, 48},
        {0, 127},
        {15, 127},
        11
    },
    {
        {-688128, -2949120, -983040},
        {-655360, -2949120, -917504},
        {-688128, -3276800, -983040},
        {-655360, -3276800, -917504},
        {0, 47},
        {15, 47},
        {0, 224},
        {15, 224},
        11
    },
    {
        {-655360, -2949120, -917504},
        {-327680, -2949120, -917504},
        {-655360, -3276800, -917504},
        {-327680, -3276800, -917504},
        {192, 223},
        {223, 223},
        {192, 192},
        {223, 192},
        9
    },
    {
        {-327680, -3276800, -983040},
        {-327680, -3276800, -917504},
        {-327680, -2949120, -983040},
        {-327680, -2949120, -917504},
        {0, 224},
        {15, 224},
        {0, 47},
        {15, 47},
        11
    },
    {
        {327680, -2949120, -983040},
        {327680, -2949120, -917504},
        {327680, -3276800, -983040},
        {327680, -3276800, -917504},
        {0, 47},
        {15, 47},
        {0, 224},
        {15, 224},
        11
    },
    {
        {327680, -2949120, -917504},
        {655360, -2949120, -917504},
        {327680, -3276800, -917504},
        {655360, -3276800, -917504},
        {32, 223},
        {63, 223},
        {32, 192},
        {63, 192},
        9
    },
    {
        {688128, -3276800, -983040},
        {655360, -3276800, -917504},
        {688128, -2949120, -983040},
        {655360, -2949120, -917504},
        {0, 224},
        {15, 224},
        {0, 47},
        {15, 47},
        11
    },
    {
        {327680, -1966080, -983040},
        {327680, -1966080, -917504},
        {327680, -2293760, -983040},
        {327680, -2293760, -917504},
        {16, 31},
        {31, 31},
        {16, 208},
        {31, 208},
        11
    },
    {
        {327680, -1966080, -917504},
        {655360, -1966080, -917504},
        {327680, -2293760, -917504},
        {655360, -2293760, -917504},
        {32, 63},
        {63, 63},
        {32, 32},
        {63, 32},
        15
    },
    {
        {688128, -2293760, -983040},
        {655360, -2293760, -917504},
        {688128, -1966080, -983040},
        {655360, -1966080, -917504},
        {0, 208},
        {15, 208},
        {0, 31},
        {15, 31},
        11
    },
    {
        {327680, -2293760, -983040},
        {327680, -2293760, -917504},
        {327680, -2621440, -983040},
        {327680, -2621440, -917504},
        {0, 207},
        {15, 207},
        {0, 128},
        {15, 128},
        11
    },
    {
        {327680, -2293760, -917504},
        {655360, -2293760, -917504},
        {327680, -2621440, -917504},
        {655360, -2621440, -917504},
        {32, 31},
        {63, 31},
        {32, 0},
        {63, 0},
        6
    },
    {
        {688128, -2621440, -983040},
        {655360, -2621440, -917504},
        {688128, -2293760, -983040},
        {655360, -2293760, -917504},
        {0, 128},
        {15, 128},
        {0, 207},
        {15, 207},
        11
    },
    {
        {327680, -2621440, -983040},
        {327680, -2621440, -917504},
        {327680, -2949120, -983040},
        {327680, -2949120, -917504},
        {0, 127},
        {15, 127},
        {0, 48},
        {15, 48},
        11
    },
    {
        {327680, -2621440, -917504},
        {655360, -2621440, -917504},
        {327680, -2949120, -917504},
        {655360, -2949120, -917504},
        {32, 255},
        {63, 255},
        {32, 224},
        {63, 224},
        6
    },
    {
        {688128, -2949120, -983040},
        {655360, -2949120, -917504},
        {688128, -2621440, -983040},
        {655360, -2621440, -917504},
        {0, 48},
        {15, 48},
        {0, 127},
        {15, 127},
        11
    },
    {
        {327680, -3604480, -983040},
        {327680, -3604480, -917504},
        {327680, -3932160, -983040},
        {327680, -3932160, -917504},
        {0, 143},
        {15, 143},
        {0, 64},
        {15, 64},
        11
    },
    {
        {327680, -3604480, -917504},
        {655360, -3604480, -917504},
        {327680, -3932160, -917504},
        {655360, -3932160, -917504},
        {32, 159},
        {63, 159},
        {32, 128},
        {63, 128},
        4
    },
    {
        {688128, -3932160, -983040},
        {655360, -3932160, -917504},
        {688128, -3604480, -983040},
        {655360, -3604480, -917504},
        {0, 64},
        {15, 64},
        {0, 143},
        {15, 143},
        11
    },
    {
        {327680, -3276800, -983040},
        {327680, -3276800, -917504},
        {327680, -3604480, -983040},
        {327680, -3604480, -917504},
        {0, 223},
        {15, 223},
        {0, 144},
        {15, 144},
        11
    },
    {
        {327680, -3276800, -917504},
        {655360, -3276800, -917504},
        {327680, -3604480, -917504},
        {655360, -3604480, -917504},
        {32, 191},
        {63, 191},
        {32, 160},
        {63, 160},
        4
    },
    {
        {688128, -3604480, -983040},
        {655360, -3604480, -917504},
        {688128, -3276800, -983040},
        {655360, -3276800, -917504},
        {0, 144},
        {15, 144},
        {0, 223},
        {15, 223},
        11
    },
    {
        {327680, -4259840, -983040},
        {327680, -4259840, -917504},
        {327680, -4587520, -983040},
        {327680, -4587520, -917504},
        {0, 239},
        {15, 239},
        {0, 160},
        {15, 160},
        11
    },
    {
        {327680, -4259840, -917504},
        {655360, -4259840, -917504},
        {327680, -4587520, -917504},
        {655360, -4587520, -917504},
        {32, 95},
        {63, 95},
        {32, 64},
        {63, 64},
        4
    },
    {
        {688128, -4587520, -983040},
        {655360, -4587520, -917504},
        {688128, -4259840, -983040},
        {655360, -4259840, -917504},
        {0, 160},
        {15, 160},
        {0, 239},
        {15, 239},
        11
    },
    {
        {327680, -3932160, -983040},
        {327680, -3932160, -917504},
        {327680, -4259840, -983040},
        {327680, -4259840, -917504},
        {0, 63},
        {15, 63},
        {0, 240},
        {15, 240},
        11
    },
    {
        {327680, -3932160, -917504},
        {655360, -3932160, -917504},
        {327680, -4259840, -917504},
        {655360, -4259840, -917504},
        {32, 127},
        {63, 127},
        {32, 96},
        {63, 96},
        4
    },
    {
        {688128, -4259840, -983040},
        {655360, -4259840, -917504},
        {688128, -3932160, -983040},
        {655360, -3932160, -917504},
        {0, 240},
        {15, 240},
        {0, 63},
        {15, 63},
        11
    },
    {
        {-688128, -3604480, -983040},
        {-655360, -3604480, -917504},
        {-688128, -3932160, -983040},
        {-655360, -3932160, -917504},
        {0, 143},
        {15, 143},
        {0, 64},
        {15, 64},
        11
    },
    {
        {-655360, -3604480, -917504},
        {-327680, -3604480, -917504},
        {-655360, -3932160, -917504},
        {-327680, -3932160, -917504},
        {192, 159},
        {223, 159},
        {192, 128},
        {223, 128},
        4
    },
    {
        {-327680, -3932160, -983040},
        {-327680, -3932160, -917504},
        {-327680, -3604480, -983040},
        {-327680, -3604480, -917504},
        {0, 64},
        {15, 64},
        {0, 143},
        {15, 143},
        11
    },
    {
        {-688128, -3276800, -983040},
        {-655360, -3276800, -917504},
        {-688128, -3604480, -983040},
        {-655360, -3604480, -917504},
        {0, 223},
        {15, 223},
        {0, 144},
        {15, 144},
        11
    },
    {
        {-655360, -3276800, -917504},
        {-327680, -3276800, -917504},
        {-655360, -3604480, -917504},
        {-327680, -3604480, -917504},
        {192, 191},
        {223, 191},
        {192, 160},
        {223, 160},
        4
    },
    {
        {-327680, -3604480, -983040},
        {-327680, -3604480, -917504},
        {-327680, -3276800, -983040},
        {-327680, -3276800, -917504},
        {0, 144},
        {15, 144},
        {0, 223},
        {15, 223},
        11
    },
    {
        {-688128, -4259840, -983040},
        {-655360, -4259840, -917504},
        {-688128, -4587520, -983040},
        {-655360, -4587520, -917504},
        {0, 239},
        {15, 239},
        {0, 160},
        {15, 160},
        11
    },
    {
        {-655360, -4259840, -917504},
        {-327680, -4259840, -917504},
        {-655360, -4587520, -917504},
        {-327680, -4587520, -917504},
        {192, 95},
        {223, 95},
        {192, 64},
        {223, 64},
        4
    },
    {
        {-327680, -4587520, -983040},
        {-327680, -4587520, -917504},
        {-327680, -4259840, -983040},
        {-327680, -4259840, -917504},
        {0, 160},
        {15, 160},
        {0, 239},
        {15, 239},
        11
    },
    {
        {-688128, -3932160, -983040},
        {-655360, -3932160, -917504},
        {-688128, -4259840, -983040},
        {-655360, -4259840, -917504},
        {0, 63},
        {15, 63},
        {0, 240},
        {15, 240},
        11
    },
    {
        {-655360, -3932160, -917504},
        {-327680, -3932160, -917504},
        {-655360, -4259840, -917504},
        {-327680, -4259840, -917504},
        {192, 127},
        {223, 127},
        {192, 96},
        {223, 96},
        4
    },
    {
        {-327680, -4259840, -983040},
        {-327680, -4259840, -917504},
        {-327680, -3932160, -983040},
        {-327680, -3932160, -917504},
        {0, 240},
        {15, 240},
        {0, 63},
        {15, 63},
        11
    },
    {
        {327680, -4259840, 917504},
        {327680, -4259840, 983040},
        {327680, -4587520, 917504},
        {327680, -4587520, 983040},
        {208, 239},
        {223, 239},
        {208, 160},
        {223, 160},
        11
    },
    {
        {327680, -4587520, 917504},
        {655360, -4587520, 917504},
        {327680, -4259840, 917504},
        {655360, -4259840, 917504},
        {32, 64},
        {63, 64},
        {32, 95},
        {63, 95},
        4
    },
    {
        {655360, -4587520, 917504},
        {688128, -4587520, 983040},
        {655360, -4259840, 917504},
        {688128, -4259840, 983040},
        {208, 160},
        {223, 160},
        {208, 239},
        {223, 239},
        11
    },
    {
        {327680, -3932160, 917504},
        {327680, -3932160, 983040},
        {327680, -4259840, 917504},
        {327680, -4259840, 983040},
        {208, 63},
        {223, 63},
        {208, 240},
        {223, 240},
        11
    },
    {
        {327680, -4259840, 917504},
        {655360, -4259840, 917504},
        {327680, -3932160, 917504},
        {655360, -3932160, 917504},
        {32, 96},
        {63, 96},
        {32, 127},
        {63, 127},
        4
    },
    {
        {655360, -4259840, 917504},
        {688128, -4259840, 983040},
        {655360, -3932160, 917504},
        {688128, -3932160, 983040},
        {208, 240},
        {223, 240},
        {208, 63},
        {223, 63},
        11
    },
    {
        {327680, -3604480, 917504},
        {327680, -3604480, 983040},
        {327680, -3932160, 917504},
        {327680, -3932160, 983040},
        {208, 143},
        {223, 143},
        {208, 64},
        {223, 64},
        11
    },
    {
        {327680, -3932160, 917504},
        {655360, -3932160, 917504},
        {327680, -3604480, 917504},
        {655360, -3604480, 917504},
        {32, 128},
        {63, 128},
        {32, 159},
        {63, 159},
        4
    },
    {
        {655360, -3932160, 917504},
        {688128, -3932160, 983040},
        {655360, -3604480, 917504},
        {688128, -3604480, 983040},
        {208, 64},
        {223, 64},
        {208, 143},
        {223, 143},
        11
    },
    {
        {327680, -3276800, 917504},
        {327680, -3276800, 983040},
        {327680, -3604480, 917504},
        {327680, -3604480, 983040},
        {208, 223},
        {223, 223},
        {208, 144},
        {223, 144},
        11
    },
    {
        {327680, -3604480, 917504},
        {655360, -3604480, 917504},
        {327680, -3276800, 917504},
        {655360, -3276800, 917504},
        {32, 160},
        {63, 160},
        {32, 191},
        {63, 191},
        4
    },
    {
        {655360, -3604480, 917504},
        {688128, -3604480, 983040},
        {655360, -3276800, 917504},
        {688128, -3276800, 983040},
        {208, 144},
        {223, 144},
        {208, 223},
        {223, 223},
        11
    },
    {
        {327680, -2949120, 917504},
        {327680, -2949120, 983040},
        {327680, -3276800, 917504},
        {327680, -3276800, 983040},
        {208, 47},
        {223, 47},
        {208, 224},
        {223, 224},
        11
    },
    {
        {327680, -3276800, 917504},
        {655360, -3276800, 917504},
        {327680, -2949120, 917504},
        {655360, -2949120, 917504},
        {32, 192},
        {63, 192},
        {32, 223},
        {63, 223},
        9
    },
    {
        {655360, -3276800, 917504},
        {688128, -3276800, 983040},
        {655360, -2949120, 917504},
        {688128, -2949120, 983040},
        {208, 224},
        {223, 224},
        {208, 47},
        {223, 47},
        11
    },
    {
        {327680, -2621440, 917504},
        {327680, -2621440, 983040},
        {327680, -2949120, 917504},
        {327680, -2949120, 983040},
        {208, 127},
        {223, 127},
        {208, 48},
        {223, 48},
        11
    },
    {
        {327680, -2949120, 917504},
        {655360, -2949120, 917504},
        {327680, -2621440, 917504},
        {655360, -2621440, 917504},
        {32, 224},
        {63, 224},
        {32, 255},
        {63, 255},
        6
    },
    {
        {655360, -2949120, 917504},
        {688128, -2949120, 983040},
        {655360, -2621440, 917504},
        {688128, -2621440, 983040},
        {208, 48},
        {223, 48},
        {208, 127},
        {223, 127},
        11
    },
    {
        {327680, -2293760, 917504},
        {327680, -2293760, 983040},
        {327680, -2621440, 917504},
        {327680, -2621440, 983040},
        {208, 207},
        {223, 207},
        {208, 128},
        {223, 128},
        11
    },
    {
        {327680, -2621440, 917504},
        {655360, -2621440, 917504},
        {327680, -2293760, 917504},
        {655360, -2293760, 917504},
        {32, 0},
        {63, 0},
        {32, 31},
        {63, 31},
        6
    },
    {
        {655360, -2621440, 917504},
        {688128, -2621440, 983040},
        {655360, -2293760, 917504},
        {688128, -2293760, 983040},
        {208, 128},
        {223, 128},
        {208, 207},
        {223, 207},
        11
    },
    {
        {327680, -1966080, 917504},
        {327680, -1966080, 983040},
        {327680, -2293760, 917504},
        {327680, -2293760, 983040},
        {224, 31},
        {239, 31},
        {224, 208},
        {239, 208},
        11
    },
    {
        {327680, -2293760, 917504},
        {655360, -2293760, 917504},
        {327680, -1966080, 917504},
        {655360, -1966080, 917504},
        {32, 32},
        {63, 32},
        {32, 63},
        {63, 63},
        15
    },
    {
        {655360, -2293760, 917504},
        {688128, -2293760, 983040},
        {655360, -1966080, 917504},
        {688128, -1966080, 983040},
        {208, 208},
        {223, 208},
        {208, 31},
        {223, 31},
        11
    },
    {
        {327680, -1638400, 917504},
        {327680, -1638400, 983040},
        {327680, -1966080, 917504},
        {327680, -1966080, 983040},
        {208, 111},
        {223, 111},
        {208, 32},
        {223, 32},
        11
    },
    {
        {327680, -1966080, 917504},
        {655360, -1966080, 917504},
        {327680, -1638400, 917504},
        {655360, -1638400, 917504},
        {32, 64},
        {63, 64},
        {32, 95},
        {63, 95},
        4
    },
    {
        {655360, -1966080, 917504},
        {688128, -1966080, 983040},
        {655360, -1638400, 917504},
        {688128, -1638400, 983040},
        {208, 32},
        {223, 32},
        {208, 111},
        {223, 111},
        11
    },
    {
        {327680, -1310720, 917504},
        {327680, -1310720, 983040},
        {327680, -1638400, 917504},
        {327680, -1638400, 983040},
        {208, 191},
        {223, 191},
        {208, 112},
        {223, 112},
        11
    },
    {
        {327680, -1638400, 917504},
        {655360, -1638400, 917504},
        {327680, -1310720, 917504},
        {655360, -1310720, 917504},
        {32, 96},
        {63, 96},
        {32, 127},
        {63, 127},
        4
    },
    {
        {655360, -1638400, 917504},
        {688128, -1638400, 983040},
        {655360, -1310720, 917504},
        {688128, -1310720, 983040},
        {208, 112},
        {223, 112},
        {208, 191},
        {223, 191},
        11
    },
    {
        {327680, -983040, 917504},
        {327680, -983040, 983040},
        {327680, -1310720, 917504},
        {327680, -1310720, 983040},
        {208, 15},
        {223, 15},
        {208, 192},
        {223, 192},
        11
    },
    {
        {327680, -1310720, 917504},
        {655360, -1310720, 917504},
        {327680, -983040, 917504},
        {655360, -983040, 917504},
        {32, 128},
        {63, 128},
        {32, 159},
        {63, 159},
        9
    },
    {
        {655360, -1310720, 917504},
        {688128, -1310720, 983040},
        {655360, -983040, 917504},
        {688128, -983040, 983040},
        {208, 192},
        {223, 192},
        {208, 15},
        {223, 15},
        11
    },
    {
        {-655360, -4259840, 917504},
        {-688128, -4259840, 983040},
        {-655360, -4587520, 917504},
        {-688128, -4587520, 983040},
        {208, 239},
        {223, 239},
        {208, 160},
        {223, 160},
        11
    },
    {
        {-655360, -4587520, 917504},
        {-327680, -4587520, 917504},
        {-655360, -4259840, 917504},
        {-327680, -4259840, 917504},
        {192, 64},
        {223, 64},
        {192, 95},
        {223, 95},
        4
    },
    {
        {-327680, -4587520, 917504},
        {-327680, -4587520, 983040},
        {-327680, -4259840, 917504},
        {-327680, -4259840, 983040},
        {208, 160},
        {223, 160},
        {208, 239},
        {223, 239},
        11
    },
    {
        {-655360, -3932160, 917504},
        {-688128, -3932160, 983040},
        {-655360, -4259840, 917504},
        {-688128, -4259840, 983040},
        {208, 63},
        {223, 63},
        {208, 240},
        {223, 240},
        11
    },
    {
        {-655360, -4259840, 917504},
        {-327680, -4259840, 917504},
        {-655360, -3932160, 917504},
        {-327680, -3932160, 917504},
        {192, 96},
        {223, 96},
        {192, 127},
        {223, 127},
        4
    },
    {
        {-327680, -4259840, 917504},
        {-327680, -4259840, 983040},
        {-327680, -3932160, 917504},
        {-327680, -3932160, 983040},
        {208, 240},
        {223, 240},
        {208, 63},
        {223, 63},
        11
    },
    {
        {-655360, -3604480, 917504},
        {-688128, -3604480, 983040},
        {-655360, -3932160, 917504},
        {-688128, -3932160, 983040},
        {208, 143},
        {223, 143},
        {208, 64},
        {223, 64},
        11
    },
    {
        {-655360, -3932160, 917504},
        {-327680, -3932160, 917504},
        {-655360, -3604480, 917504},
        {-327680, -3604480, 917504},
        {192, 128},
        {223, 128},
        {192, 159},
        {223, 159},
        4
    },
    {
        {-327680, -3932160, 917504},
        {-327680, -3932160, 983040},
        {-327680, -3604480, 917504},
        {-327680, -3604480, 983040},
        {208, 64},
        {223, 64},
        {208, 143},
        {223, 143},
        11
    },
    {
        {-655360, -3276800, 917504},
        {-688128, -3276800, 983040},
        {-655360, -3604480, 917504},
        {-688128, -3604480, 983040},
        {208, 223},
        {223, 223},
        {208, 144},
        {223, 144},
        11
    },
    {
        {-655360, -3604480, 917504},
        {-327680, -3604480, 917504},
        {-655360, -3276800, 917504},
        {-327680, -3276800, 917504},
        {192, 160},
        {223, 160},
        {192, 191},
        {223, 191},
        4
    },
    {
        {-327680, -3604480, 917504},
        {-327680, -3604480, 983040},
        {-327680, -3276800, 917504},
        {-327680, -3276800, 983040},
        {208, 144},
        {223, 144},
        {208, 223},
        {223, 223},
        11
    },
    {
        {-655360, -2949120, 917504},
        {-688128, -2949120, 983040},
        {-655360, -3276800, 917504},
        {-688128, -3276800, 983040},
        {208, 47},
        {223, 47},
        {208, 224},
        {223, 224},
        11
    },
    {
        {-655360, -3276800, 917504},
        {-327680, -3276800, 917504},
        {-655360, -2949120, 917504},
        {-327680, -2949120, 917504},
        {192, 192},
        {223, 192},
        {192, 223},
        {223, 223},
        9
    },
    {
        {-327680, -3276800, 917504},
        {-327680, -3276800, 983040},
        {-327680, -2949120, 917504},
        {-327680, -2949120, 983040},
        {208, 224},
        {223, 224},
        {208, 47},
        {223, 47},
        11
    },
    {
        {-655360, -2621440, 917504},
        {-688128, -2621440, 983040},
        {-655360, -2949120, 917504},
        {-688128, -2949120, 983040},
        {208, 127},
        {223, 127},
        {208, 48},
        {223, 48},
        11
    },
    {
        {-655360, -2949120, 917504},
        {-327680, -2949120, 917504},
        {-655360, -2621440, 917504},
        {-327680, -2621440, 917504},
        {192, 224},
        {223, 224},
        {192, 255},
        {223, 255},
        6
    },
    {
        {-327680, -2949120, 917504},
        {-327680, -2949120, 983040},
        {-327680, -2621440, 917504},
        {-327680, -2621440, 983040},
        {208, 48},
        {223, 48},
        {208, 127},
        {223, 127},
        11
    },
    {
        {-655360, -2293760, 917504},
        {-688128, -2293760, 983040},
        {-655360, -2621440, 917504},
        {-688128, -2621440, 983040},
        {208, 207},
        {223, 207},
        {208, 128},
        {223, 128},
        11
    },
    {
        {-655360, -2621440, 917504},
        {-327680, -2621440, 917504},
        {-655360, -2293760, 917504},
        {-327680, -2293760, 917504},
        {192, 0},
        {223, 0},
        {192, 31},
        {223, 31},
        6
    },
    {
        {-327680, -2621440, 917504},
        {-327680, -2621440, 983040},
        {-327680, -2293760, 917504},
        {-327680, -2293760, 983040},
        {208, 128},
        {223, 128},
        {208, 207},
        {223, 207},
        11
    },
    {
        {-655360, -1966080, 917504},
        {-688128, -1966080, 983040},
        {-655360, -2293760, 917504},
        {-688128, -2293760, 983040},
        {208, 31},
        {223, 31},
        {208, 208},
        {223, 208},
        11
    },
    {
        {-655360, -2293760, 917504},
        {-327680, -2293760, 917504},
        {-655360, -1966080, 917504},
        {-327680, -1966080, 917504},
        {192, 32},
        {223, 32},
        {192, 63},
        {223, 63},
        15
    },
    {
        {-327680, -2293760, 917504},
        {-327680, -2293760, 983040},
        {-327680, -1966080, 917504},
        {-327680, -1966080, 983040},
        {208, 208},
        {223, 208},
        {208, 31},
        {223, 31},
        11
    },
    {
        {-655360, -1638400, 917504},
        {-688128, -1638400, 983040},
        {-655360, -1966080, 917504},
        {-688128, -1966080, 983040},
        {208, 111},
        {223, 111},
        {208, 32},
        {223, 32},
        11
    },
    {
        {-655360, -1966080, 917504},
        {-327680, -1966080, 917504},
        {-655360, -1638400, 917504},
        {-327680, -1638400, 917504},
        {192, 64},
        {223, 64},
        {192, 95},
        {223, 95},
        4
    },
    {
        {-327680, -1966080, 917504},
        {-327680, -1966080, 983040},
        {-327680, -1638400, 917504},
        {-327680, -1638400, 983040},
        {208, 32},
        {223, 32},
        {208, 111},
        {223, 111},
        11
    },
    {
        {-655360, -1310720, 917504},
        {-688128, -1310720, 983040},
        {-655360, -1638400, 917504},
        {-688128, -1638400, 983040},
        {208, 191},
        {223, 191},
        {208, 112},
        {223, 112},
        11
    },
    {
        {-655360, -1638400, 917504},
        {-327680, -1638400, 917504},
        {-655360, -1310720, 917504},
        {-327680, -1310720, 917504},
        {192, 96},
        {223, 96},
        {192, 127},
        {223, 127},
        4
    },
    {
        {-327680, -1638400, 917504},
        {-327680, -1638400, 983040},
        {-327680, -1310720, 917504},
        {-327680, -1310720, 983040},
        {208, 112},
        {223, 112},
        {208, 191},
        {223, 191},
        11
    },
    {
        {-655360, -983040, 917504},
        {-688128, -983040, 983040},
        {-655360, -1310720, 917504},
        {-688128, -1310720, 983040},
        {208, 15},
        {223, 15},
        {208, 192},
        {223, 192},
        11
    },
    {
        {-655360, -1310720, 917504},
        {-327680, -1310720, 917504},
        {-655360, -983040, 917504},
        {-327680, -983040, 917504},
        {192, 128},
        {223, 128},
        {192, 159},
        {223, 159},
        9
    },
    {
        {-327680, -1310720, 917504},
        {-327680, -1310720, 983040},
        {-327680, -983040, 917504},
        {-327680, -983040, 983040},
        {208, 192},
        {223, 192},
        {208, 15},
        {223, 15},
        11
    },
    {
        {-655360, -655360, 917504},
        {-688128, -655360, 983040},
        {-655360, -983040, 917504},
        {-688128, -983040, 983040},
        {208, 95},
        {223, 95},
        {208, 16},
        {223, 16},
        11
    },
    {
        {-655360, -983040, 917504},
        {-327680, -983040, 917504},
        {-655360, -655360, 917504},
        {-327680, -655360, 917504},
        {192, 160},
        {223, 160},
        {192, 191},
        {223, 191},
        6
    },
    {
        {-327680, -983040, 917504},
        {-327680, -983040, 983040},
        {-327680, -655360, 917504},
        {-327680, -655360, 983040},
        {208, 16},
        {223, 16},
        {208, 95},
        {223, 95},
        11
    },
    {
        {-655360, -327680, 917504},
        {-688128, -327680, 983040},
        {-655360, -655360, 917504},
        {-688128, -655360, 983040},
        {208, 175},
        {223, 175},
        {208, 96},
        {223, 96},
        11
    },
    {
        {-655360, -655360, 917504},
        {-327680, -655360, 917504},
        {-655360, -327680, 917504},
        {-327680, -327680, 917504},
        {192, 192},
        {223, 192},
        {192, 223},
        {223, 223},
        6
    },
    {
        {-327680, -655360, 917504},
        {-327680, -655360, 983040},
        {-327680, -327680, 917504},
        {-327680, -327680, 983040},
        {208, 96},
        {223, 96},
        {208, 175},
        {223, 175},
        11
    },
    {
        {-655360, 0, 917504},
        {-688128, 0, 983040},
        {-655360, -327680, 917504},
        {-688128, -327680, 983040},
        {208, 255},
        {223, 255},
        {208, 176},
        {223, 176},
        11
    },
    {
        {-655360, -327680, 917504},
        {-327680, -327680, 917504},
        {-655360, 0, 917504},
        {-327680, 0, 917504},
        {192, 224},
        {223, 224},
        {192, 255},
        {223, 255},
        15
    },
    {
        {-327680, -327680, 917504},
        {-327680, -327680, 983040},
        {-327680, 0, 917504},
        {-327680, 0, 983040},
        {208, 176},
        {223, 176},
        {208, 255},
        {223, 255},
        11
    },
    {
        {327680, 0, 917504},
        {327680, 0, 983040},
        {327680, -327680, 917504},
        {327680, -327680, 983040},
        {224, 255},
        {239, 255},
        {224, 176},
        {239, 176},
        11
    },
    {
        {327680, -327680, 917504},
        {655360, -327680, 917504},
        {327680, 0, 917504},
        {655360, 0, 917504},
        {32, 224},
        {63, 224},
        {32, 255},
        {63, 255},
        15
    },
    {
        {655360, -327680, 917504},
        {688128, -327680, 983040},
        {655360, 0, 917504},
        {688128, 0, 983040},
        {208, 176},
        {223, 176},
        {208, 255},
        {223, 255},
        11
    },
    {
        {327680, -327680, 917504},
        {327680, -327680, 983040},
        {327680, -655360, 917504},
        {327680, -655360, 983040},
        {208, 175},
        {223, 175},
        {208, 96},
        {223, 96},
        11
    },
    {
        {327680, -655360, 917504},
        {655360, -655360, 917504},
        {327680, -327680, 917504},
        {655360, -327680, 917504},
        {32, 192},
        {63, 192},
        {32, 223},
        {63, 223},
        6
    },
    {
        {655360, -655360, 917504},
        {688128, -655360, 983040},
        {655360, -327680, 917504},
        {688128, -327680, 983040},
        {208, 96},
        {223, 96},
        {208, 175},
        {223, 175},
        11
    },
    {
        {327680, -655360, 917504},
        {327680, -655360, 983040},
        {327680, -983040, 917504},
        {327680, -983040, 983040},
        {208, 95},
        {223, 95},
        {208, 16},
        {223, 16},
        11
    },
    {
        {327680, -983040, 917504},
        {655360, -983040, 917504},
        {327680, -655360, 917504},
        {655360, -655360, 917504},
        {32, 160},
        {63, 160},
        {32, 191},
        {63, 191},
        6
    },
    {
        {655360, -983040, 917504},
        {688128, -983040, 983040},
        {655360, -655360, 917504},
        {688128, -655360, 983040},
        {208, 16},
        {223, 16},
        {208, 95},
        {223, 95},
        11
    },
    {
        {0, -1638400, 917504},
        {327680, -1638400, 917504},
        {0, -1310720, 917504},
        {327680, -1310720, 917504},
        {32, 96},
        {63, 96},
        {32, 127},
        {63, 127},
        0
    },
    {
        {0, -1310720, 917504},
        {327680, -1310720, 917504},
        {0, -1310720, 983040},
        {327680, -1310720, 983040},
        {0, 171},
        {31, 171},
        {0, 166},
        {31, 166},
        11
    },
    {
        {-327680, -1638400, 917504},
        {0, -1638400, 917504},
        {-327680, -1310720, 917504},
        {0, -1310720, 917504},
        {0, 96},
        {31, 96},
        {0, 127},
        {31, 127},
        0
    },
    {
        {-327680, -1310720, 917504},
        {0, -1310720, 917504},
        {-327680, -1310720, 983040},
        {0, -1310720, 983040},
        {224, 171},
        {255, 171},
        {224, 166},
        {255, 166},
        11
    },
    {
        {-327680, -1966080, 917504},
        {0, -1966080, 917504},
        {-327680, -1638400, 917504},
        {0, -1638400, 917504},
        {0, 64},
        {31, 64},
        {0, 95},
        {31, 95},
        16
    },
    {
        {-327680, -2293760, 917504},
        {0, -2293760, 917504},
        {-327680, -1966080, 917504},
        {0, -1966080, 917504},
        {0, 32},
        {31, 32},
        {0, 63},
        {31, 63},
        3
    },
    {
        {-327680, -2621440, 917504},
        {0, -2621440, 917504},
        {-327680, -2293760, 917504},
        {0, -2293760, 917504},
        {0, 0},
        {31, 0},
        {0, 31},
        {31, 31},
        3
    },
    {
        {-327680, -2949120, 917504},
        {0, -2949120, 917504},
        {-327680, -2621440, 917504},
        {0, -2621440, 917504},
        {0, 224},
        {31, 224},
        {0, 255},
        {31, 255},
        3
    },
    {
        {-327680, -3276800, 917504},
        {0, -3276800, 917504},
        {-327680, -2949120, 917504},
        {0, -2949120, 917504},
        {0, 192},
        {31, 192},
        {0, 223},
        {31, 223},
        3
    },
    {
        {-327680, -3604480, 917504},
        {0, -3604480, 917504},
        {-327680, -3276800, 917504},
        {0, -3276800, 917504},
        {0, 160},
        {31, 160},
        {0, 191},
        {31, 191},
        3
    },
    {
        {-327680, -3932160, 917504},
        {0, -3932160, 917504},
        {-327680, -3604480, 917504},
        {0, -3604480, 917504},
        {0, 128},
        {31, 128},
        {0, 159},
        {31, 159},
        3
    },
    {
        {-327680, -4259840, 917504},
        {0, -4259840, 917504},
        {-327680, -3932160, 917504},
        {0, -3932160, 917504},
        {0, 96},
        {31, 96},
        {0, 127},
        {31, 127},
        3
    },
    {
        {-327680, -4587520, 917504},
        {0, -4587520, 917504},
        {-327680, -4259840, 917504},
        {0, -4259840, 917504},
        {0, 64},
        {31, 64},
        {0, 95},
        {31, 95},
        3
    },
    {
        {0, -4587520, 917504},
        {327680, -4587520, 917504},
        {0, -4259840, 917504},
        {327680, -4259840, 917504},
        {32, 64},
        {63, 64},
        {32, 95},
        {63, 95},
        3
    },
    {
        {0, -4259840, 917504},
        {327680, -4259840, 917504},
        {0, -3932160, 917504},
        {327680, -3932160, 917504},
        {32, 96},
        {63, 96},
        {32, 127},
        {63, 127},
        3
    },
    {
        {0, -3932160, 917504},
        {327680, -3932160, 917504},
        {0, -3604480, 917504},
        {327680, -3604480, 917504},
        {32, 128},
        {63, 128},
        {32, 159},
        {63, 159},
        3
    },
    {
        {0, -3604480, 917504},
        {327680, -3604480, 917504},
        {0, -3276800, 917504},
        {327680, -3276800, 917504},
        {32, 160},
        {63, 160},
        {32, 191},
        {63, 191},
        3
    },
    {
        {0, -3276800, 917504},
        {327680, -3276800, 917504},
        {0, -2949120, 917504},
        {327680, -2949120, 917504},
        {32, 192},
        {63, 192},
        {32, 223},
        {63, 223},
        3
    },
    {
        {0, -2949120, 917504},
        {327680, -2949120, 917504},
        {0, -2621440, 917504},
        {327680, -2621440, 917504},
        {32, 224},
        {63, 224},
        {32, 255},
        {63, 255},
        3
    },
    {
        {0, -2621440, 917504},
        {327680, -2621440, 917504},
        {0, -2293760, 917504},
        {327680, -2293760, 917504},
        {32, 0},
        {63, 0},
        {32, 31},
        {63, 31},
        3
    },
    {
        {0, -2293760, 917504},
        {327680, -2293760, 917504},
        {0, -1966080, 917504},
        {327680, -1966080, 917504},
        {32, 32},
        {63, 32},
        {32, 63},
        {63, 63},
        3
    },
    {
        {0, -1966080, 917504},
        {327680, -1966080, 917504},
        {0, -1638400, 917504},
        {327680, -1638400, 917504},
        {32, 64},
        {63, 64},
        {32, 95},
        {63, 95},
        16
    },
    {
        {-229376, -458752, 983040},
        {229376, -458752, 983040},
        {-229376, 0, 983040},
        {229376, 0, 983040},
        {0, 192},
        {63, 192},
        {0, 255},
        {63, 255},
        8
    },
    {
        {-327680, 0, 950272},
        {-327680, 0, 983040},
        {-327680, -655360, 950272},
        {-327680, -655360, 983040},
        {232, 255},
        {239, 255},
        {232, 96},
        {239, 96},
        11
    },
    {
        {-327680, -655360, 950272},
        {-229376, -655360, 950272},
        {-327680, 0, 950272},
        {-229376, 0, 950272},
        {176, 96},
        {199, 96},
        {176, 255},
        {199, 255},
        11
    },
    {
        {-327680, 0, 950272},
        {-229376, 0, 950272},
        {-327680, 0, 983040},
        {-229376, 0, 983040},
        {176, 23},
        {199, 23},
        {176, 16},
        {199, 16},
        11
    },
    {
        {-327680, -655360, 983040},
        {-229376, -655360, 983040},
        {-327680, -655360, 950272},
        {-229376, -655360, 950272},
        {176, 16},
        {199, 16},
        {176, 23},
        {199, 23},
        11
    },
    {
        {-327680, 0, 983040},
        {-229376, 0, 983040},
        {-327680, -655360, 983040},
        {-229376, -655360, 983040},
        {176, 255},
        {199, 255},
        {176, 96},
        {199, 96},
        11
    },
    {
        {-229376, -655360, 950272},
        {-229376, -655360, 983040},
        {-229376, 0, 950272},
        {-229376, 0, 983040},
        {232, 96},
        {239, 96},
        {232, 255},
        {239, 255},
        11
    },
    {
        {229376, 0, 950272},
        {229376, 0, 983040},
        {229376, -655360, 950272},
        {229376, -655360, 983040},
        {232, 255},
        {239, 255},
        {232, 96},
        {239, 96},
        11
    },
    {
        {229376, -655360, 950272},
        {327680, -655360, 950272},
        {229376, 0, 950272},
        {327680, 0, 950272},
        {56, 96},
        {79, 96},
        {56, 255},
        {79, 255},
        11
    },
    {
        {229376, 0, 950272},
        {327680, 0, 950272},
        {229376, 0, 983040},
        {327680, 0, 983040},
        {56, 23},
        {79, 23},
        {56, 16},
        {79, 16},
        11
    },
    {
        {229376, -655360, 983040},
        {327680, -655360, 983040},
        {229376, -655360, 950272},
        {327680, -655360, 950272},
        {56, 16},
        {79, 16},
        {56, 23},
        {79, 23},
        11
    },
    {
        {229376, 0, 983040},
        {327680, 0, 983040},
        {229376, -655360, 983040},
        {327680, -655360, 983040},
        {56, 255},
        {79, 255},
        {56, 96},
        {79, 96},
        11
    },
    {
        {327680, -655360, 950272},
        {327680, -655360, 983040},
        {327680, 0, 950272},
        {327680, 0, 983040},
        {232, 96},
        {239, 96},
        {232, 255},
        {239, 255},
        11
    },
    {
        {-229376, -655360, 983040},
        {229376, -655360, 983040},
        {-229376, -458752, 983040},
        {229376, -458752, 983040},
        {0, 192},
        {31, 192},
        {0, 210},
        {31, 210},
        5
    },
    {
        {-327680, -688128, 1310720},
        {0, -688128, 1310720},
        {-327680, -688128, 983040},
        {0, -688128, 983040},
        {224, 128},
        {255, 128},
        {224, 159},
        {255, 159},
        13
    },
    {
        {0, -688128, 1310720},
        {327680, -688128, 1310720},
        {0, -688128, 983040},
        {327680, -688128, 983040},
        {0, 128},
        {31, 128},
        {0, 159},
        {31, 159},
        13
    },
    {
        {-327680, -688128, 917504},
        {0, -688128, 917504},
        {-327680, -655360, 917504},
        {0, -655360, 917504},
        {176, 88},
        {255, 88},
        {176, 95},
        {255, 95},
        11
    },
    {
        {-327680, -655360, 917504},
        {0, -655360, 917504},
        {-327680, -655360, 983040},
        {0, -655360, 983040},
        {176, 31},
        {255, 31},
        {176, 16},
        {255, 16},
        11
    },
    {
        {-327680, -688128, 983040},
        {0, -688128, 983040},
        {-327680, -688128, 917504},
        {0, -688128, 917504},
        {176, 16},
        {255, 16},
        {176, 31},
        {255, 31},
        11
    },
    {
        {0, -688128, 917504},
        {327680, -688128, 917504},
        {0, -655360, 917504},
        {327680, -655360, 917504},
        {0, 88},
        {79, 88},
        {0, 95},
        {79, 95},
        11
    },
    {
        {0, -655360, 917504},
        {327680, -655360, 917504},
        {0, -655360, 983040},
        {327680, -655360, 983040},
        {0, 31},
        {79, 31},
        {0, 16},
        {79, 16},
        11
    },
    {
        {0, -688128, 983040},
        {327680, -688128, 983040},
        {0, -688128, 917504},
        {327680, -688128, 917504},
        {0, 16},
        {79, 16},
        {0, 31},
        {79, 31},
        11
    },
    {
        {-327680, -688128, 1638400},
        {0, -688128, 1638400},
        {-327680, -688128, 1310720},
        {0, -688128, 1310720},
        {224, 96},
        {255, 96},
        {224, 127},
        {255, 127},
        13
    },
    {
        {0, -688128, 1638400},
        {327680, -688128, 1638400},
        {0, -688128, 1310720},
        {327680, -688128, 1310720},
        {0, 96},
        {31, 96},
        {0, 127},
        {31, 127},
        13
    },
    {
        {-327680, -688128, 2293760},
        {0, -688128, 2293760},
        {-327680, -688128, 1966080},
        {0, -688128, 1966080},
        {224, 32},
        {255, 32},
        {224, 63},
        {255, 63},
        13
    },
    {
        {0, -688128, 2293760},
        {327680, -688128, 2293760},
        {0, -688128, 1966080},
        {327680, -688128, 1966080},
        {0, 32},
        {31, 32},
        {0, 63},
        {31, 63},
        13
    },
    {
        {-327680, -688128, 1966080},
        {0, -688128, 1966080},
        {-327680, -688128, 1638400},
        {0, -688128, 1638400},
        {224, 64},
        {255, 64},
        {224, 95},
        {255, 95},
        13
    },
    {
        {0, -688128, 1966080},
        {327680, -688128, 1966080},
        {0, -688128, 1638400},
        {327680, -688128, 1638400},
        {0, 64},
        {31, 64},
        {0, 95},
        {31, 95},
        13
    },
    {
        {-327680, -1343488, 983040},
        {-327680, -1343488, 1310720},
        {-327680, -1015808, 983040},
        {-327680, -1015808, 1310720},
        {127, 96},
        {127, 127},
        {96, 96},
        {96, 127},
        13
    },
    {
        {-327680, -1343488, 1310720},
        {-327680, -1343488, 1638400},
        {-327680, -1015808, 1310720},
        {-327680, -1015808, 1638400},
        {127, 128},
        {127, 159},
        {96, 128},
        {96, 159},
        13
    },
    {
        {-327680, -1343488, 1638400},
        {-327680, -1343488, 1966080},
        {-327680, -1015808, 1638400},
        {-327680, -1015808, 1966080},
        {127, 160},
        {127, 191},
        {96, 160},
        {96, 191},
        13
    },
    {
        {-327680, -1343488, 1966080},
        {-327680, -1343488, 2293760},
        {-327680, -1015808, 1966080},
        {-327680, -1015808, 2293760},
        {127, 192},
        {127, 223},
        {96, 192},
        {96, 223},
        13
    },
    {
        {-327680, -1015808, 1966080},
        {-327680, -1015808, 2293760},
        {-327680, -688128, 1966080},
        {-327680, -688128, 2293760},
        {95, 192},
        {95, 223},
        {64, 192},
        {64, 223},
        13
    },
    {
        {-327680, -1015808, 1638400},
        {-327680, -1015808, 1966080},
        {-327680, -688128, 1638400},
        {-327680, -688128, 1966080},
        {95, 160},
        {95, 191},
        {64, 160},
        {64, 191},
        13
    },
    {
        {-327680, -1015808, 1310720},
        {-327680, -1015808, 1638400},
        {-327680, -688128, 1310720},
        {-327680, -688128, 1638400},
        {95, 128},
        {95, 159},
        {64, 128},
        {64, 159},
        13
    },
    {
        {-327680, -1015808, 983040},
        {-327680, -1015808, 1310720},
        {-327680, -688128, 983040},
        {-327680, -688128, 1310720},
        {95, 96},
        {95, 127},
        {64, 96},
        {64, 127},
        13
    },
    {
        {327680, -1015808, 983040},
        {327680, -1015808, 1310720},
        {327680, -1343488, 983040},
        {327680, -1343488, 1310720},
        {96, 96},
        {96, 127},
        {127, 96},
        {127, 127},
        13
    },
    {
        {327680, -1015808, 1310720},
        {327680, -1015808, 1638400},
        {327680, -1343488, 1310720},
        {327680, -1343488, 1638400},
        {96, 128},
        {96, 159},
        {127, 128},
        {127, 159},
        13
    },
    {
        {327680, -1015808, 1638400},
        {327680, -1015808, 1966080},
        {327680, -1343488, 1638400},
        {327680, -1343488, 1966080},
        {96, 160},
        {96, 191},
        {127, 160},
        {127, 191},
        13
    },
    {
        {327680, -1015808, 1966080},
        {327680, -1015808, 2293760},
        {327680, -1343488, 1966080},
        {327680, -1343488, 2293760},
        {96, 192},
        {96, 223},
        {127, 192},
        {127, 223},
        13
    },
    {
        {327680, -688128, 1966080},
        {327680, -688128, 2293760},
        {327680, -1015808, 1966080},
        {327680, -1015808, 2293760},
        {64, 192},
        {64, 223},
        {95, 192},
        {95, 223},
        13
    },
    {
        {327680, -688128, 1638400},
        {327680, -688128, 1966080},
        {327680, -1015808, 1638400},
        {327680, -1015808, 1966080},
        {64, 160},
        {64, 191},
        {95, 160},
        {95, 191},
        13
    },
    {
        {327680, -688128, 1310720},
        {327680, -688128, 1638400},
        {327680, -1015808, 1310720},
        {327680, -1015808, 1638400},
        {64, 128},
        {64, 159},
        {95, 128},
        {95, 159},
        13
    },
    {
        {327680, -688128, 983040},
        {327680, -688128, 1310720},
        {327680, -1015808, 983040},
        {327680, -1015808, 1310720},
        {64, 96},
        {64, 127},
        {95, 96},
        {95, 127},
        13
    },
    {
        {0, -1343488, 983040},
        {327680, -1343488, 983040},
        {0, -1343488, 1310720},
        {327680, -1343488, 1310720},
        {0, 159},
        {31, 159},
        {0, 128},
        {31, 128},
        10
    },
    {
        {-327680, -1343488, 983040},
        {0, -1343488, 983040},
        {-327680, -1343488, 1310720},
        {0, -1343488, 1310720},
        {224, 159},
        {255, 159},
        {224, 128},
        {255, 128},
        10
    },
    {
        {-327680, -1343488, 1310720},
        {0, -1343488, 1310720},
        {-327680, -1343488, 1638400},
        {0, -1343488, 1638400},
        {224, 127},
        {255, 127},
        {224, 96},
        {255, 96},
        10
    },
    {
        {-327680, -1343488, 1638400},
        {0, -1343488, 1638400},
        {-327680, -1343488, 1966080},
        {0, -1343488, 1966080},
        {224, 95},
        {255, 95},
        {224, 64},
        {255, 64},
        13
    },
    {
        {-327680, -1343488, 1966080},
        {0, -1343488, 1966080},
        {-327680, -1343488, 2293760},
        {0, -1343488, 2293760},
        {224, 63},
        {255, 63},
        {224, 32},
        {255, 32},
        13
    },
    {
        {0, -1343488, 1310720},
        {327680, -1343488, 1310720},
        {0, -1343488, 1638400},
        {327680, -1343488, 1638400},
        {0, 127},
        {31, 127},
        {0, 96},
        {31, 96},
        10
    },
    {
        {0, -1343488, 1638400},
        {327680, -1343488, 1638400},
        {0, -1343488, 1966080},
        {327680, -1343488, 1966080},
        {0, 95},
        {31, 95},
        {0, 64},
        {31, 64},
        13
    },
    {
        {0, -1343488, 1966080},
        {327680, -1343488, 1966080},
        {0, -1343488, 2293760},
        {327680, -1343488, 2293760},
        {0, 63},
        {31, 63},
        {0, 32},
        {31, 32},
        13
    },
    {
        {-327680, -688128, 2260992},
        {-327680, -688128, 2293760},
        {-327680, -1343488, 2260992},
        {-327680, -1343488, 2293760},
        {40, 87},
        {47, 87},
        {40, 184},
        {47, 184},
        11
    },
    {
        {-327680, -1343488, 2260992},
        {-229376, -1343488, 2260992},
        {-327680, -688128, 2260992},
        {-229376, -688128, 2260992},
        {176, 184},
        {199, 184},
        {176, 87},
        {199, 87},
        11
    },
    {
        {-327680, -688128, 2260992},
        {-229376, -688128, 2260992},
        {-327680, -688128, 2293760},
        {-229376, -688128, 2293760},
        {176, 215},
        {199, 215},
        {176, 208},
        {199, 208},
        11
    },
    {
        {-327680, -1343488, 2293760},
        {-229376, -1343488, 2293760},
        {-327680, -1343488, 2260992},
        {-229376, -1343488, 2260992},
        {176, 208},
        {199, 208},
        {176, 215},
        {199, 215},
        11
    },
    {
        {-327680, -688128, 2293760},
        {-229376, -688128, 2293760},
        {-327680, -1343488, 2293760},
        {-229376, -1343488, 2293760},
        {176, 87},
        {199, 87},
        {176, 184},
        {199, 184},
        11
    },
    {
        {-229376, -1343488, 2260992},
        {-229376, -1343488, 2293760},
        {-229376, -688128, 2260992},
        {-229376, -688128, 2293760},
        {40, 184},
        {47, 184},
        {40, 87},
        {47, 87},
        11
    },
    {
        {-229376, -1146880, 2293760},
        {229376, -1146880, 2293760},
        {-229376, -688128, 2293760},
        {229376, -688128, 2293760},
        {0, 64},
        {63, 64},
        {0, 127},
        {63, 127},
        8
    },
    {
        {229376, -688128, 2260992},
        {229376, -688128, 2293760},
        {229376, -1343488, 2260992},
        {229376, -1343488, 2293760},
        {40, 87},
        {47, 87},
        {40, 184},
        {47, 184},
        11
    },
    {
        {229376, -1343488, 2260992},
        {327680, -1343488, 2260992},
        {229376, -688128, 2260992},
        {327680, -688128, 2260992},
        {56, 184},
        {79, 184},
        {56, 87},
        {79, 87},
        11
    },
    {
        {229376, -688128, 2260992},
        {327680, -688128, 2260992},
        {229376, -688128, 2293760},
        {327680, -688128, 2293760},
        {56, 215},
        {79, 215},
        {56, 208},
        {79, 208},
        11
    },
    {
        {229376, -1343488, 2293760},
        {327680, -1343488, 2293760},
        {229376, -1343488, 2260992},
        {327680, -1343488, 2260992},
        {56, 208},
        {79, 208},
        {56, 215},
        {79, 215},
        11
    },
    {
        {229376, -688128, 2293760},
        {327680, -688128, 2293760},
        {229376, -1343488, 2293760},
        {327680, -1343488, 2293760},
        {56, 87},
        {79, 87},
        {56, 184},
        {79, 184},
        11
    },
    {
        {327680, -1343488, 2260992},
        {327680, -1343488, 2293760},
        {327680, -688128, 2260992},
        {327680, -688128, 2293760},
        {40, 184},
        {47, 184},
        {40, 87},
        {47, 87},
        11
    },
    {
        {-229376, -1343488, 2293760},
        {229376, -1343488, 2293760},
        {-229376, -1146880, 2293760},
        {229376, -1146880, 2293760},
        {0, 124},
        {31, 124},
        {0, 143},
        {31, 143},
        5
    },
    {
        {-1048576, -655360, 327680},
        {-983040, -655360, 655360},
        {-1048576, -327680, 327680},
        {-983040, -327680, 655360},
        {223, 192},
        {192, 192},
        {223, 223},
        {192, 223},
        14
    },
    {
        {-1048576, -983040, 327680},
        {-983040, -983040, 655360},
        {-1048576, -655360, 327680},
        {-983040, -655360, 655360},
        {223, 160},
        {192, 160},
        {223, 191},
        {192, 191},
        14
    },
    {
        {-1048576, -1310720, 327680},
        {-983040, -1310720, 655360},
        {-1048576, -983040, 327680},
        {-983040, -983040, 655360},
        {223, 128},
        {192, 128},
        {223, 159},
        {192, 159},
        14
    },
    {
        {-1048576, -1638400, 327680},
        {-983040, -1638400, 655360},
        {-1048576, -1310720, 327680},
        {-983040, -1310720, 655360},
        {223, 96},
        {192, 96},
        {223, 127},
        {192, 127},
        14
    },
    {
        {-1048576, -1966080, 327680},
        {-983040, -1966080, 655360},
        {-1048576, -1638400, 327680},
        {-983040, -1638400, 655360},
        {223, 64},
        {192, 64},
        {223, 95},
        {192, 95},
        14
    },
    {
        {-983040, -327680, -655360},
        {-1048576, -327680, -327680},
        {-983040, 0, -655360},
        {-1048576, 0, -327680},
        {63, 224},
        {32, 224},
        {63, 255},
        {32, 255},
        14
    },
    {
        {-983040, -655360, -655360},
        {-1048576, -655360, -327680},
        {-983040, -327680, -655360},
        {-1048576, -327680, -327680},
        {63, 192},
        {32, 192},
        {63, 223},
        {32, 223},
        14
    },
    {
        {-983040, -983040, -655360},
        {-1048576, -983040, -327680},
        {-983040, -655360, -655360},
        {-1048576, -655360, -327680},
        {63, 160},
        {32, 160},
        {63, 191},
        {32, 191},
        14
    },
    {
        {-983040, -1310720, -655360},
        {-1048576, -1310720, -327680},
        {-983040, -983040, -655360},
        {-1048576, -983040, -327680},
        {63, 128},
        {32, 128},
        {63, 159},
        {32, 159},
        14
    },
    {
        {-983040, -1638400, -655360},
        {-1048576, -1638400, -327680},
        {-983040, -1310720, -655360},
        {-1048576, -1310720, -327680},
        {63, 96},
        {32, 96},
        {63, 127},
        {32, 127},
        14
    },
    {
        {-983040, -1966080, -655360},
        {-1048576, -1966080, -327680},
        {-983040, -1638400, -655360},
        {-1048576, -1638400, -327680},
        {63, 64},
        {32, 64},
        {63, 95},
        {32, 95},
        14
    },
    {
        {983040, -1638400, -655360},
        {1048576, -1638400, -327680},
        {983040, -1966080, -655360},
        {1048576, -1966080, -327680},
        {63, 95},
        {32, 95},
        {63, 64},
        {32, 64},
        14
    },
    {
        {983040, -1310720, -655360},
        {1048576, -1310720, -327680},
        {983040, -1638400, -655360},
        {1048576, -1638400, -327680},
        {63, 127},
        {32, 127},
        {63, 96},
        {32, 96},
        14
    },
    {
        {983040, -983040, -655360},
        {1048576, -983040, -327680},
        {983040, -1310720, -655360},
        {1048576, -1310720, -327680},
        {63, 159},
        {32, 159},
        {63, 128},
        {32, 128},
        14
    },
    {
        {983040, -655360, -655360},
        {1048576, -655360, -327680},
        {983040, -983040, -655360},
        {1048576, -983040, -327680},
        {63, 191},
        {32, 191},
        {63, 160},
        {32, 160},
        14
    },
    {
        {983040, -327680, -655360},
        {1048576, -327680, -327680},
        {983040, -655360, -655360},
        {1048576, -655360, -327680},
        {63, 223},
        {32, 223},
        {63, 192},
        {32, 192},
        14
    },
    {
        {983040, 0, -655360},
        {1048576, 0, -327680},
        {983040, -327680, -655360},
        {1048576, -327680, -327680},
        {63, 255},
        {32, 255},
        {63, 224},
        {32, 224},
        14
    },
    {
        {1048576, 0, 327680},
        {983040, 0, 655360},
        {1048576, -327680, 327680},
        {983040, -327680, 655360},
        {223, 255},
        {192, 255},
        {223, 224},
        {192, 224},
        14
    },
    {
        {1048576, -327680, 327680},
        {983040, -327680, 655360},
        {1048576, -655360, 327680},
        {983040, -655360, 655360},
        {223, 223},
        {192, 223},
        {223, 192},
        {192, 192},
        14
    },
    {
        {1048576, -655360, 327680},
        {983040, -655360, 655360},
        {1048576, -983040, 327680},
        {983040, -983040, 655360},
        {223, 191},
        {192, 191},
        {223, 160},
        {192, 160},
        14
    },
    {
        {1048576, -983040, 327680},
        {983040, -983040, 655360},
        {1048576, -1310720, 327680},
        {983040, -1310720, 655360},
        {223, 159},
        {192, 159},
        {223, 128},
        {192, 128},
        14
    },
    {
        {1048576, -1310720, 327680},
        {983040, -1310720, 655360},
        {1048576, -1638400, 327680},
        {983040, -1638400, 655360},
        {223, 127},
        {192, 127},
        {223, 96},
        {192, 96},
        14
    },
    {
        {1048576, -1638400, 327680},
        {983040, -1638400, 655360},
        {1048576, -1966080, 327680},
        {983040, -1966080, 655360},
        {223, 95},
        {192, 95},
        {223, 64},
        {192, 64},
        14
    },
    {
        {-1114112, -4587520, -983040},
        {-1114112, -4587520, 983040},
        {-1114112, -4653056, -983040},
        {-1114112, -4653056, 983040},
        {16, 159},
        {239, 159},
        {16, 144},
        {239, 144},
        11
    },
    {
        {-1114112, -4653056, -983040},
        {1114112, -4653056, -983040},
        {-1114112, -4587520, -983040},
        {1114112, -4587520, -983040},
        {240, 144},
        {15, 144},
        {240, 159},
        {15, 159},
        11
    },
    {
        {-1114112, -4653056, 983040},
        {1114112, -4653056, 983040},
        {-1114112, -4653056, -983040},
        {1114112, -4653056, -983040},
        {240, 16},
        {15, 16},
        {240, 239},
        {15, 239},
        11
    },
    {
        {-1114112, -4587520, 983040},
        {1114112, -4587520, 983040},
        {-1114112, -4653056, 983040},
        {1114112, -4653056, 983040},
        {240, 159},
        {15, 159},
        {240, 144},
        {15, 144},
        11
    },
    {
        {1114112, -4653056, -983040},
        {1114112, -4653056, 983040},
        {1114112, -4587520, -983040},
        {1114112, -4587520, 983040},
        {16, 144},
        {239, 144},
        {16, 159},
        {239, 159},
        11
    },
    {
        {1048576, 0, -327680},
        {1048576, 0, -163840},
        {1048576, -163840, -327680},
        {1048576, -163840, -163840},
        {0, 255},
        {15, 255},
        {0, 240},
        {15, 240},
        16
    },
    {
        {1048576, -163840, -327680},
        {1048576, -163840, -163840},
        {1048576, -327680, -327680},
        {1048576, -327680, -163840},
        {0, 239},
        {15, 239},
        {0, 224},
        {15, 224},
        16
    },
    {
        {1048576, -163840, -163840},
        {1048576, -163840, 0},
        {1048576, -327680, -163840},
        {1048576, -327680, 0},
        {16, 239},
        {31, 239},
        {16, 224},
        {31, 224},
        16
    },
    {
        {1048576, 0, -163840},
        {1048576, 0, 0},
        {1048576, -163840, -163840},
        {1048576, -163840, 0},
        {16, 255},
        {31, 255},
        {16, 240},
        {31, 240},
        16
    },
    {
        {1048576, 0, 262144},
        {1048576, 0, 327680},
        {1048576, -65536, 262144},
        {1048576, -65536, 327680},
        {57, 255},
        {63, 255},
        {57, 249},
        {63, 249},
        16
    },
    {
        {1048576, 0, 196608},
        {1048576, 0, 262144},
        {1048576, -65536, 196608},
        {1048576, -65536, 262144},
        {51, 255},
        {57, 255},
        {51, 249},
        {57, 249},
        16
    },
    {
        {1048576, 0, 131072},
        {1048576, 0, 196608},
        {1048576, -65536, 131072},
        {1048576, -65536, 196608},
        {44, 255},
        {50, 255},
        {44, 249},
        {50, 249},
        16
    },
    {
        {1048576, 0, 65536},
        {1048576, 0, 131072},
        {1048576, -65536, 65536},
        {1048576, -65536, 131072},
        {38, 255},
        {44, 255},
        {38, 249},
        {44, 249},
        16
    },
    {
        {1048576, 0, 0},
        {1048576, 0, 65536},
        {1048576, -65536, 0},
        {1048576, -65536, 65536},
        {32, 255},
        {37, 255},
        {32, 249},
        {37, 249},
        16
    },
    {
        {1048576, -65536, 0},
        {1048576, -65536, 65536},
        {1048576, -131072, 0},
        {1048576, -131072, 65536},
        {32, 249},
        {37, 249},
        {32, 243},
        {37, 243},
        16
    },
    {
        {1048576, -65536, 131072},
        {1048576, -65536, 196608},
        {1048576, -131072, 131072},
        {1048576, -131072, 196608},
        {44, 249},
        {50, 249},
        {44, 243},
        {50, 243},
        16
    },
    {
        {1048576, -65536, 65536},
        {1048576, -65536, 131072},
        {1048576, -131072, 65536},
        {1048576, -131072, 131072},
        {38, 249},
        {44, 249},
        {38, 243},
        {44, 243},
        16
    },
    {
        {1048576, -65536, 196608},
        {1048576, -65536, 262144},
        {1048576, -131072, 196608},
        {1048576, -131072, 262144},
        {51, 249},
        {57, 249},
        {51, 243},
        {57, 243},
        16
    },
    {
        {1048576, -65536, 262144},
        {1048576, -65536, 327680},
        {1048576, -131072, 262144},
        {1048576, -131072, 327680},
        {57, 249},
        {63, 249},
        {57, 243},
        {63, 243},
        16
    },
    {
        {1048576, -131072, 0},
        {1048576, -131072, 65536},
        {1048576, -196608, 0},
        {1048576, -196608, 65536},
        {32, 242},
        {37, 242},
        {32, 236},
        {37, 236},
        16
    },
    {
        {1048576, -131072, 131072},
        {1048576, -131072, 196608},
        {1048576, -196608, 131072},
        {1048576, -196608, 196608},
        {44, 242},
        {50, 242},
        {44, 236},
        {50, 236},
        16
    },
    {
        {1048576, -131072, 65536},
        {1048576, -131072, 131072},
        {1048576, -196608, 65536},
        {1048576, -196608, 131072},
        {38, 242},
        {44, 242},
        {38, 236},
        {44, 236},
        16
    },
    {
        {1048576, -131072, 196608},
        {1048576, -131072, 262144},
        {1048576, -196608, 196608},
        {1048576, -196608, 262144},
        {51, 242},
        {57, 242},
        {51, 236},
        {57, 236},
        16
    },
    {
        {1048576, -131072, 262144},
        {1048576, -131072, 327680},
        {1048576, -196608, 262144},
        {1048576, -196608, 327680},
        {57, 242},
        {63, 242},
        {57, 236},
        {63, 236},
        16
    },
    {
        {1048576, -196608, 0},
        {1048576, -196608, 65536},
        {1048576, -262144, 0},
        {1048576, -262144, 65536},
        {32, 236},
        {37, 236},
        {32, 230},
        {37, 230},
        16
    },
    {
        {1048576, -196608, 131072},
        {1048576, -196608, 196608},
        {1048576, -262144, 131072},
        {1048576, -262144, 196608},
        {44, 236},
        {50, 236},
        {44, 230},
        {50, 230},
        16
    },
    {
        {1048576, -196608, 65536},
        {1048576, -196608, 131072},
        {1048576, -262144, 65536},
        {1048576, -262144, 131072},
        {38, 236},
        {44, 236},
        {38, 230},
        {44, 230},
        16
    },
    {
        {1048576, -196608, 196608},
        {1048576, -196608, 262144},
        {1048576, -262144, 196608},
        {1048576, -262144, 262144},
        {51, 236},
        {57, 236},
        {51, 230},
        {57, 230},
        16
    },
    {
        {1048576, -196608, 262144},
        {1048576, -196608, 327680},
        {1048576, -262144, 262144},
        {1048576, -262144, 327680},
        {57, 236},
        {63, 236},
        {57, 230},
        {63, 230},
        16
    },
    {
        {1048576, -262144, 0},
        {1048576, -262144, 65536},
        {1048576, -327680, 0},
        {1048576, -327680, 65536},
        {32, 229},
        {37, 229},
        {32, 224},
        {37, 224},
        16
    },
    {
        {1048576, -262144, 131072},
        {1048576, -262144, 196608},
        {1048576, -327680, 131072},
        {1048576, -327680, 196608},
        {44, 229},
        {50, 229},
        {44, 224},
        {50, 224},
        16
    },
    {
        {1048576, -262144, 65536},
        {1048576, -262144, 131072},
        {1048576, -327680, 65536},
        {1048576, -327680, 131072},
        {38, 229},
        {44, 229},
        {38, 224},
        {44, 224},
        16
    },
    {
        {1048576, -262144, 196608},
        {1048576, -262144, 262144},
        {1048576, -327680, 196608},
        {1048576, -327680, 262144},
        {51, 229},
        {57, 229},
        {51, 224},
        {57, 224},
        16
    },
    {
        {1048576, -262144, 262144},
        {1048576, -262144, 327680},
        {1048576, -327680, 262144},
        {1048576, -327680, 327680},
        {57, 229},
        {63, 229},
        {57, 224},
        {63, 224},
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
    mainCamera.x -=  (isin(mainCamera.yaw)>>12);
    mainCamera.z +=  (icos(mainCamera.yaw)>>12);
}
void moveCameraBackward(void){
    mainCamera.x +=  (isin(mainCamera.yaw)>>12);
    mainCamera.z -=  (icos(mainCamera.yaw)>>12);
}
void moveCameraLeft(void){
    mainCamera.x -=  (icos(mainCamera.yaw)>>12);
    mainCamera.z += -(isin(mainCamera.yaw)>>12);
}
void moveCameraRight(void){
    mainCamera.x +=  (icos(mainCamera.yaw)>>12);
    mainCamera.z -= -(isin(mainCamera.yaw)>>12);
}
void moveCameraUp(void){
    cameraHeight -= 8<<12;
    if(cameraHeight < -((PLAYER_BBOX_Y/2))){
        cameraHeight = -((PLAYER_BBOX_Y/2));
    }
}
void moveCameraDown(void){
    cameraHeight += 8<<12;
    if(cameraHeight > ((PLAYER_BBOX_Y/2))){
        cameraHeight = ((PLAYER_BBOX_Y/2));
    }
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
    controller_subscribeOnKeyHold(movePlayerLeft,         BUTTON_INDEX_LEFT    );
    controller_subscribeOnKeyHold(movePlayerRight,        BUTTON_INDEX_RIGHT   );
    controller_subscribeOnKeyHold(movePlayerForward,      BUTTON_INDEX_UP      );
    controller_subscribeOnKeyHold(movePlayerBackward,     BUTTON_INDEX_DOWN    );
    controller_subscribeOnKeyHold(incrementDebugVariable, BUTTON_INDEX_R2      );
    controller_subscribeOnKeyHold(decrementDebugVariable, BUTTON_INDEX_L2      );
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

    int t = 4;
    
    uint8_t bitmask_u = 0xFF << (31-__builtin_clz(bspTextureInfo[t].textureInfo.w));
    uint8_t bitmask_v = 0xFF << (31-__builtin_clz(bspTextureInfo[t].textureInfo.h));

    // Init camera
    mainCamera.x     = 0;
    mainCamera.y     = 0;
    mainCamera.z     = 0;
    mainCamera.pitch = 0;
    mainCamera.roll  = 0;
    mainCamera.yaw   = 0;

    resetPlayer();


    printf("Player:\n x: %d\n y: %d\n z: %d\n",
        player.position.x, player.position.y, player.position.z
    );
    player.velocity.x = 0;
    player.velocity.y = GRAVITY_CONSTANT;
    player.velocity.z = 0;

    Player3_move(&bsp_player, &player);

    printf("Player:\n x: %d\n y: %d\n z: %d\n",
        player.position.x, player.position.y, player.position.z
    );



    debug("Start of main loop\n");
    // Main loop. Runs every frame, forever
    for(;;){

        drawnQuads = 0;

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

        // Move camera to player position
        mainCamera.x     = (player.position.x);
        mainCamera.z     = (player.position.z);
        mainCamera.y = ((player.position.y)) + (cameraHeight);


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
        setTranslationMatrix(0, 0, 0);
        
        // Translate and Rotate camera
        rotateCurrentMatrix(mainCamera.pitch, mainCamera.roll, mainCamera.yaw);
        gte_setV0(-(mainCamera.x>>12), -(mainCamera.y>>12), -(mainCamera.z>>12));
        translateCurrentMatrixByV0();
        gte_setControlReg(GTE_TRZ, gte_getControlReg(GTE_TRZ) - debugVariable);

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
                continue; // Don't render empty brushes.
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
        
        for(int i=0; i<numQuads; i++){
            int32_t ti = quads[i].textureIndex;
            if(ti == -1){
                continue; // Don't render empty brushes.
            }
            if(ti > numTextures){
                printf(
                    "Texture index %d is out of range! (numTextures: %d)\n",
                    ti, numTextures
                );
                continue;
            }
            fullRenderQuad3_texturedFlat(quads[i], &mainCamera, &bspTextureInfo[ti].textureInfo);
        }

        // Crosshair
        drawCross2((Vector2){SCREEN_WIDTH/2, SCREEN_HEIGHT/2}, 0x0000FF);

        sprintf(str_Buffer, "Player:\n X: %d\n Y: %d\n Z: %d\n\nCamera:\n yaw: %d\n sin: %d\n cos: %d, Quads: %d",
            player.position.x, player.position.y, player.position.z,
            mainCamera.yaw, isin(mainCamera.yaw), icos(mainCamera.yaw),
            drawnQuads
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
