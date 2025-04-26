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

#define PLAYER_BBOX_X (64 * ONE)
#define PLAYER_BBOX_Y (128 * ONE)
#define PLAYER_BBOX_Z (64 * ONE)


// Include texture data files
extern const uint8_t fontData[];
extern const uint8_t fontPalette[];
TextureInfo font;

extern const uint8_t filth_128Data[];
TextureInfo filth_128;

extern const uint8_t default_32Data[];
TextureInfo default_32;

Camera mainCamera;
Player3 player;
char str_Buffer[256];
int screenColor = 0xfa823c;
int wallColor = 0x3c82fa;
int gteScaleFactor = 0;
int delayFactor = 0;

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
    int32_t uv0 = gp0_uv(tri.auv.x + texinfo->u, tri.auv.y + texinfo->v, texinfo->clut);
    int32_t uv1 = gp0_uv(tri.buv.x + texinfo->u, tri.buv.y + texinfo->v, texinfo->page);
    int32_t uv2 = gp0_uv(tri.cuv.x + texinfo->u, tri.cuv.y + texinfo->v, 0);

    dmaPtr = allocatePacket(activeChain, tri.z, 8);
    dmaPtr[0] = gp0_texwindow(0, 0, ~0b00011, ~0b00011);
    dmaPtr[1] = 0x808080 | gp0_triangle(true, false);
    dmaPtr[2] = xy0;
    dmaPtr[3] = uv0;
    dmaPtr[4] = xy1;
    dmaPtr[5] = uv1;
    dmaPtr[6] = xy2;
    dmaPtr[7] = uv2;
    

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

    if(zIndex < 1 || zIndex >= ORDERING_TABLE_SIZE){
        gte_setTranslationVector(currentTx, currentTy, currentTz);
        return false;
    }

    // Save result
    result->a = (Vector2_16){xy0 & 0xFFFF, xy0 >> 16};
    result->b = (Vector2_16){xy1 & 0xFFFF, xy1 >> 16};
    result->c = (Vector2_16){xy2 & 0xFFFF, xy2 >> 16};
    result->z = zIndex;

    // Restore the translation and rotation back to the initial state as to not clobber any other models.
    gte_setTranslationVector(currentTx, currentTy, currentTz);
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

BSPNode3 bspNodes_hitscan[] = {
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -262144,
        .children = {
            1, 11
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
            2, 7
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
            3, -1
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
            -1, 4
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
            5, -1
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
            -1, 6
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 3932160,
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
            8, -1
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
            -1, 9
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
            10, -1
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
        .distance = -2031616,
        .children = {
            12, 46
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
            13, 17
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
            -1, 14
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
            -1, 15
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
            16, -1
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
            18, 42
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
            19, 31
        }
    },
    {
        .normal = {
            .x = -1790,
            .y = -1989,
            .z = 3100
        },
        .distance = 1438584,
        .children = {
            -1, 20
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -1989,
            .z = 3580
        },
        .distance = 636541,
        .children = {
            -1, 21
        }
    },
    {
        .normal = {
            .x = 1790,
            .y = -1989,
            .z = 3100
        },
        .distance = -165500,
        .children = {
            -1, 22
        }
    },
    {
        .normal = {
            .x = -1790,
            .y = 1989,
            .z = 3100
        },
        .distance = 165500,
        .children = {
            23, -1
        }
    },
    {
        .normal = {
            .x = 3100,
            .y = -1989,
            .z = -1790
        },
        .distance = -752637,
        .children = {
            -1, 24
        }
    },
    {
        .normal = {
            .x = 3100,
            .y = -1989,
            .z = 1790
        },
        .distance = -752637,
        .children = {
            -1, 25
        }
    },
    {
        .normal = {
            .x = 3580,
            .y = -1989,
            .z = 0
        },
        .distance = -967543,
        .children = {
            -1, 26
        }
    },
    {
        .normal = {
            .x = 3580,
            .y = 1989,
            .z = 0
        },
        .distance = -2240627,
        .children = {
            27, -1
        }
    },
    {
        .normal = {
            .x = 3100,
            .y = 1989,
            .z = -1790
        },
        .distance = -2025720,
        .children = {
            28, -1
        }
    },
    {
        .normal = {
            .x = 3100,
            .y = 1989,
            .z = 1790
        },
        .distance = -2025720,
        .children = {
            29, -1
        }
    },
    {
        .normal = {
            .x = 1790,
            .y = 1989,
            .z = 3100
        },
        .distance = -1438584,
        .children = {
            30, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 1989,
            .z = 3580
        },
        .distance = -636541,
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
        .distance = -1638400,
        .children = {
            -1, 32
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -196608,
        .children = {
            33, -1
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
            -1, 34
        }
    },
    {
        .normal = {
            .x = -2048,
            .y = 0,
            .z = 3547
        },
        .distance = 1114112,
        .children = {
            -1, 35
        }
    },
    {
        .normal = {
            .x = 3547,
            .y = 0,
            .z = -2048
        },
        .distance = -1785771,
        .children = {
            36, -1
        }
    },
    {
        .normal = {
            .x = 2048,
            .y = 0,
            .z = 3547
        },
        .distance = -1114112,
        .children = {
            37, -1
        }
    },
    {
        .normal = {
            .x = -2048,
            .y = 0,
            .z = 3547
        },
        .distance = 720896,
        .children = {
            38, -1
        }
    },
    {
        .normal = {
            .x = 2048,
            .y = 0,
            .z = 3547
        },
        .distance = -720896,
        .children = {
            -1, 39
        }
    },
    {
        .normal = {
            .x = 3547,
            .y = 0,
            .z = -2048
        },
        .distance = -1392555,
        .children = {
            -1, 40
        }
    },
    {
        .normal = {
            .x = 3547,
            .y = 0,
            .z = 2048
        },
        .distance = -1392555,
        .children = {
            -1, 41
        }
    },
    {
        .normal = {
            .x = 3547,
            .y = 0,
            .z = 2048
        },
        .distance = -1785771,
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
        .distance = -786432,
        .children = {
            -1, 43
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
            44, -1
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
            -1, 45
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
            -2, -1
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
            47, 51
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -4784128,
        .children = {
            48, -1
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
            -1, 49
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
            50, -1
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
            52, -1
        }
    },
    {
        .normal = {
            .x = -1790,
            .y = -1989,
            .z = 3100
        },
        .distance = 1438584,
        .children = {
            -1, 53
        }
    },
    {
        .normal = {
            .x = 3580,
            .y = 1989,
            .z = 0
        },
        .distance = -2240627,
        .children = {
            54, -1
        }
    },
    {
        .normal = {
            .x = 3100,
            .y = 1989,
            .z = -1790
        },
        .distance = -2025720,
        .children = {
            55, -1
        }
    },
    {
        .normal = {
            .x = 3100,
            .y = 1989,
            .z = 1790
        },
        .distance = -2025720,
        .children = {
            56, -1
        }
    },
    {
        .normal = {
            .x = 1790,
            .y = 1989,
            .z = 3100
        },
        .distance = -1438584,
        .children = {
            -2, -1
        }
    },
};
BSPTree3 bsp_hitscan = {.nodes=bspNodes_hitscan, .numNodes = 57};

BSPNode3 bspNodes_player[] = {
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -393216,
        .children = {
            1, 11
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
            2, 7
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
            3, -1
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
            -1, 4
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
            5, -1
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
            -1, 6
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 4063232,
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
            -1, 8
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
            -1, 9
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
            10, -1
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -2293759,
        .children = {
            12, 95
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
            13, 18
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
            -1, 14
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
            15, -1
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
            -1, 16
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
            17, -1
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
            -1, 19
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
            20, -1
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
            21, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1572863,
        .children = {
            -1, 22
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 983042,
        .children = {
            23, 37
        }
    },
    {
        .normal = {
            .x = 1790,
            .y = -1989,
            .z = 3100
        },
        .distance = 118321,
        .children = {
            -1, 24
        }
    },
    {
        .normal = {
            .x = 3100,
            .y = -1989,
            .z = 1790
        },
        .distance = -468812,
        .children = {
            -1, 25
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -1989,
            .z = 3580
        },
        .distance = 878428,
        .children = {
            -1, 26
        }
    },
    {
        .normal = {
            .x = 3100,
            .y = 1989,
            .z = 1790
        },
        .distance = -2309545,
        .children = {
            27, -1
        }
    },
    {
        .normal = {
            .x = 1790,
            .y = 1989,
            .z = 3100
        },
        .distance = -1722409,
        .children = {
            28, -1
        }
    },
    {
        .normal = {
            .x = 3580,
            .y = 1989,
            .z = 0
        },
        .distance = -2482513,
        .children = {
            29, -1
        }
    },
    {
        .normal = {
            .x = 3100,
            .y = -1989,
            .z = -1790
        },
        .distance = -468812,
        .children = {
            -1, 30
        }
    },
    {
        .normal = {
            .x = 3547,
            .y = 0,
            .z = -2047
        },
        .distance = -2095892,
        .children = {
            31, -1
        }
    },
    {
        .normal = {
            .x = -2048,
            .y = 0,
            .z = 3547
        },
        .distance = 1424232,
        .children = {
            -1, 32
        }
    },
    {
        .normal = {
            .x = -1790,
            .y = -1989,
            .z = 3100
        },
        .distance = 1722409,
        .children = {
            -1, 33
        }
    },
    {
        .normal = {
            .x = 3580,
            .y = -1989,
            .z = 0
        },
        .distance = -725657,
        .children = {
            -1, 34
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 1989,
            .z = 3580
        },
        .distance = -878428,
        .children = {
            35, -1
        }
    },
    {
        .normal = {
            .x = 3100,
            .y = 1989,
            .z = -1790
        },
        .distance = -2309545,
        .children = {
            36, -1
        }
    },
    {
        .normal = {
            .x = -1790,
            .y = 1989,
            .z = 3100
        },
        .distance = -118322,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 1790,
            .y = 1989,
            .z = 3100
        },
        .distance = -1722409,
        .children = {
            38, -1
        }
    },
    {
        .normal = {
            .x = 3547,
            .y = 0,
            .z = -2047
        },
        .distance = -2095892,
        .children = {
            39, -1
        }
    },
    {
        .normal = {
            .x = -2048,
            .y = 0,
            .z = 3547
        },
        .distance = 1424232,
        .children = {
            -1, 40
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -2162688,
        .children = {
            41, 92
        }
    },
    {
        .normal = {
            .x = 2048,
            .y = 0,
            .z = 3547
        },
        .distance = -1424231,
        .children = {
            42, -1
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
            43, 90
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
            44, 88
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1376256,
        .children = {
            45, 47
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
            -1, 46
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
            .x = 1790,
            .y = -1989,
            .z = 3100
        },
        .distance = 118321,
        .children = {
            -1, 48
        }
    },
    {
        .normal = {
            .x = 3100,
            .y = -1989,
            .z = 1790
        },
        .distance = -468812,
        .children = {
            -1, 49
        }
    },
    {
        .normal = {
            .x = 3100,
            .y = -1989,
            .z = -1790
        },
        .distance = -468812,
        .children = {
            -1, 50
        }
    },
    {
        .normal = {
            .x = -1790,
            .y = 1989,
            .z = 3100
        },
        .distance = -118322,
        .children = {
            51, -1
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
            52, 54
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
            53, -1
        }
    },
    {
        .normal = {
            .x = 2048,
            .y = 0,
            .z = 3547
        },
        .distance = -410777,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1507328,
        .children = {
            55, 61
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
            56, -2
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
            57, -1
        }
    },
    {
        .normal = {
            .x = 2048,
            .y = 0,
            .z = 3547
        },
        .distance = -410777,
        .children = {
            -1, 58
        }
    },
    {
        .normal = {
            .x = 3547,
            .y = 0,
            .z = 2048
        },
        .distance = -1082435,
        .children = {
            -1, 59
        }
    },
    {
        .normal = {
            .x = 3547,
            .y = 0,
            .z = -2048
        },
        .distance = -1082435,
        .children = {
            -1, 60
        }
    },
    {
        .normal = {
            .x = -2048,
            .y = 0,
            .z = 3547
        },
        .distance = 410777,
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
            62, 86
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
            63, 65
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
            64, -2
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 3547,
            .y = 0,
            .z = -2048
        },
        .distance = -1213506,
        .children = {
            66, 68
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
            67, -2
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = -2048,
            .y = 0,
            .z = 3547
        },
        .distance = 541848,
        .children = {
            69, 84
        }
    },
    {
        .normal = {
            .x = 3547,
            .y = 0,
            .z = 2048
        },
        .distance = -1213506,
        .children = {
            70, 72
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
            71, -2
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
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2047,
            .y = 0,
            .z = 3547
        },
        .distance = -1293157,
        .children = {
            73, 82
        }
    },
    {
        .normal = {
            .x = 3547,
            .y = 0,
            .z = 2047
        },
        .distance = -1964820,
        .children = {
            74, 80
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
            75, -2
        }
    },
    {
        .normal = {
            .x = 2048,
            .y = 0,
            .z = 3547
        },
        .distance = -541848,
        .children = {
            76, 77
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
            -2, 78
        }
    },
    {
        .normal = {
            .x = 3547,
            .y = 0,
            .z = -2047
        },
        .distance = -1964820,
        .children = {
            79, -1
        }
    },
    {
        .normal = {
            .x = -2047,
            .y = 0,
            .z = 3547
        },
        .distance = 1293157,
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
            81, -2
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
            83, -2
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
            85, -2
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
            87, -2
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
            89, -1
        }
    },
    {
        .normal = {
            .x = -2048,
            .y = 0,
            .z = 3547
        },
        .distance = 410777,
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
            91, -1
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
            .y = -4096,
            .z = 0
        },
        .distance = 458752,
        .children = {
            93, -1
        }
    },
    {
        .normal = {
            .x = 2048,
            .y = 0,
            .z = 3547
        },
        .distance = -1424231,
        .children = {
            94, -1
        }
    },
    {
        .normal = {
            .x = 3547,
            .y = 0,
            .z = 2047
        },
        .distance = -2095892,
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
        .distance = -4915200,
        .children = {
            96, -1
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
            97, -1
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
            -1, 98
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
            99, -1
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
            -1, -2
        }
    },
};
BSPTree3 bsp_player = {.nodes=bspNodes_player, .numNodes = 100};

int numTris = 262;
Tri3_texturedFlat tris[] = {
    {
        {-262144, 0, 1769472},
        {-262144, 0, 2031616},
        {-262144, -2162688, 2031616},
        {0, 81},
        {64, 81},
        {64, 0}
},
    {
        {-262144, 0, 1769472},
        {-262144, -2162688, 2031616},
        {-262144, -2162688, 1769472},
        {0, 81},
        {64, 0},
        {0, 0}
},
    {
        {-262144, 65536, -262144},
        {-262144, 65536, 262144},
        {-262144, -65536, 262144},
        {0, 32},
        {128, 32},
        {128, 0}
},
    {
        {-262144, 65536, -262144},
        {-262144, -65536, 262144},
        {-262144, -65536, -262144},
        {0, 32},
        {128, 0},
        {0, 0}
},
    {
        {262144, -65536, 262144},
        {-262144, -65536, 262144},
        {-262144, 65536, 262144},
        {128, 0},
        {0, 0},
        {0, 32}
},
    {
        {262144, -65536, 262144},
        {-262144, 65536, 262144},
        {262144, 65536, 262144},
        {128, 0},
        {0, 32},
        {128, 32}
},
    {
        {-262144, -2162688, 1769472},
        {3932160, -2162688, 1769472},
        {3932160, 0, 1769472},
        {0, 0},
        {64, 0},
        {64, 81}
},
    {
        {-262144, -2162688, 1769472},
        {3932160, 0, 1769472},
        {-262144, 0, 1769472},
        {0, 0},
        {64, 81},
        {0, 81}
},
    {
        {3932160, -2162688, 2031616},
        {-262144, -2162688, 2031616},
        {-262144, 0, 2031616},
        {64, 0},
        {0, 0},
        {0, 81}
},
    {
        {3932160, -2162688, 2031616},
        {-262144, 0, 2031616},
        {3932160, 0, 2031616},
        {64, 0},
        {0, 81},
        {64, 81}
},
    {
        {3932160, 0, 1769472},
        {3932160, 0, 2031616},
        {-262144, 0, 2031616},
        {64, 64},
        {64, 0},
        {0, 0}
},
    {
        {3932160, 0, 1769472},
        {-262144, 0, 2031616},
        {-262144, 0, 1769472},
        {64, 64},
        {0, 0},
        {0, 64}
},
    {
        {3932160, -2162688, 2031616},
        {3932160, -2162688, 1769472},
        {-262144, -2162688, 1769472},
        {64, 0},
        {64, 64},
        {0, 64}
},
    {
        {3932160, -2162688, 2031616},
        {-262144, -2162688, 1769472},
        {-262144, -2162688, 2031616},
        {64, 0},
        {0, 64},
        {0, 0}
},
    {
        {3932160, -2162688, 2031616},
        {3932160, 0, 2031616},
        {3932160, 0, 1769472},
        {64, 0},
        {64, 81},
        {0, 81}
},
    {
        {3932160, -2162688, 2031616},
        {3932160, 0, 1769472},
        {3932160, -2162688, 1769472},
        {64, 0},
        {0, 81},
        {0, 0}
},
    {
        {-262144, -65536, -262144},
        {262144, -65536, -262144},
        {262144, 65536, -262144},
        {0, 0},
        {128, 0},
        {128, 32}
},
    {
        {-262144, -65536, -262144},
        {262144, 65536, -262144},
        {-262144, 65536, -262144},
        {0, 0},
        {128, 32},
        {0, 32}
},
    {
        {262144, -65536, -262144},
        {262144, -65536, 262144},
        {262144, 65536, 262144},
        {0, 0},
        {128, 0},
        {128, 32}
},
    {
        {262144, -65536, -262144},
        {262144, 65536, 262144},
        {262144, 65536, -262144},
        {0, 0},
        {128, 32},
        {0, 32}
},
    {
        {-262144, 65536, 262144},
        {-262144, 65536, -262144},
        {262144, 65536, -262144},
        {0, 0},
        {0, 128},
        {128, 128}
},
    {
        {-262144, 65536, 262144},
        {262144, 65536, -262144},
        {262144, 65536, 262144},
        {0, 0},
        {128, 128},
        {128, 0}
},
    {
        {-262144, -65536, -262144},
        {-262144, -65536, 262144},
        {262144, -65536, 262144},
        {0, 128},
        {0, 0},
        {128, 0}
},
    {
        {-262144, -65536, -262144},
        {262144, -65536, 262144},
        {262144, -65536, -262144},
        {0, 128},
        {128, 0},
        {128, 128}
},
    {
        {-2031616, 65536, -262144},
        {-2031616, 65536, 262144},
        {-2031616, -65536, 52680},
        {0, 32},
        {128, 32},
        {76, 0}
},
    {
        {-2031616, 65536, -262144},
        {-2031616, -65536, 52680},
        {-2031616, -65536, -52680},
        {0, 32},
        {76, 0},
        {51, 0}
},
    {
        {-2031616, 65536, -262144},
        {-2031616, -65536, -52680},
        {-2031616, -65536, -113511},
        {0, 32},
        {51, 0},
        {36, 0}
},
    {
        {-2031616, 65536, -262144},
        {-2031616, -65536, -113511},
        {-2031616, -65536, -196608},
        {0, 32},
        {36, 0},
        {16, 0}
},
    {
        {-2031616, 65536, -262144},
        {-2031616, -65536, -196608},
        {-2031616, -65536, -262144},
        {0, 32},
        {16, 0},
        {0, 0}
},
    {
        {-2031616, 65536, 262144},
        {-2031616, -65536, 262144},
        {-2031616, -65536, 196608},
        {16, 32},
        {16, 0},
        {0, 0}
},
    {
        {-2031616, 65536, 262144},
        {-2031616, -65536, 196608},
        {-2031616, -65536, 113511},
        {37, 32},
        {21, 0},
        {0, 0}
},
    {
        {-2031616, 65536, 262144},
        {-2031616, -65536, 113511},
        {-2031616, -65536, 52680},
        {52, 32},
        {15, 0},
        {0, 0}
},
    {
        {-2031616, -720896, -52680},
        {-2031616, -65536, -52680},
        {-2031616, -65536, 52680},
        {0, 0},
        {0, 160},
        {21, 160}
},
    {
        {-2031616, -720896, -52680},
        {-2031616, -65536, 52680},
        {-2031616, -720896, 52680},
        {0, 0},
        {21, 160},
        {21, 0}
},
    {
        {-589824, -327680, 1769472},
        {-1114112, -327680, 1769472},
        {-1114112, -1245184, 1769472},
        {128, 224},
        {0, 224},
        {0, 0}
},
    {
        {-589824, -327680, 1769472},
        {-1114112, -1245184, 1769472},
        {-589824, -1245184, 1769472},
        {128, 224},
        {0, 0},
        {128, 0}
},
    {
        {-1114112, -327680, 1769472},
        {-2031616, -327680, 1769472},
        {-2031616, -1245184, 1769472},
        {224, 224},
        {0, 224},
        {0, 0}
},
    {
        {-1114112, -327680, 1769472},
        {-2031616, -1245184, 1769472},
        {-1114112, -1245184, 1769472},
        {224, 224},
        {0, 0},
        {224, 0}
},
    {
        {-589824, -1245184, 1769472},
        {-1114112, -1245184, 1769472},
        {-1114112, -2162688, 1769472},
        {128, 224},
        {0, 224},
        {0, 0}
},
    {
        {-589824, -1245184, 1769472},
        {-1114112, -2162688, 1769472},
        {-589824, -2162688, 1769472},
        {128, 224},
        {0, 0},
        {128, 0}
},
    {
        {-1114112, -1245184, 1769472},
        {-2031616, -1245184, 1769472},
        {-2031616, -2162688, 1769472},
        {224, 224},
        {0, 224},
        {0, 0}
},
    {
        {-1114112, -1245184, 1769472},
        {-2031616, -2162688, 1769472},
        {-1114112, -2162688, 1769472},
        {224, 224},
        {0, 0},
        {224, 0}
},
    {
        {-1114112, -327680, 1769472},
        {-1114112, 0, 1769472},
        {-2031616, 0, 1769472},
        {224, 0},
        {224, 80},
        {0, 80}
},
    {
        {-1114112, -327680, 1769472},
        {-2031616, 0, 1769472},
        {-2031616, -327680, 1769472},
        {224, 0},
        {0, 80},
        {0, 0}
},
    {
        {-589824, -327680, 1769472},
        {-589824, 0, 1769472},
        {-1114112, 0, 1769472},
        {128, 0},
        {128, 80},
        {0, 80}
},
    {
        {-589824, -327680, 1769472},
        {-1114112, 0, 1769472},
        {-1114112, -327680, 1769472},
        {128, 0},
        {0, 80},
        {0, 0}
},
    {
        {-589824, -327680, 2031616},
        {-589824, -327680, 1769472},
        {-589824, -1245184, 1769472},
        {64, 224},
        {0, 224},
        {0, 0}
},
    {
        {-589824, -327680, 2031616},
        {-589824, -1245184, 1769472},
        {-589824, -1245184, 2031616},
        {64, 224},
        {0, 0},
        {64, 0}
},
    {
        {-589824, -1245184, 2031616},
        {-589824, -1245184, 1769472},
        {-589824, -2162688, 1769472},
        {64, 224},
        {0, 224},
        {0, 0}
},
    {
        {-589824, -1245184, 2031616},
        {-589824, -2162688, 1769472},
        {-589824, -2162688, 2031616},
        {64, 224},
        {0, 0},
        {64, 0}
},
    {
        {-589824, 0, 2031616},
        {-589824, 0, 1769472},
        {-589824, -327680, 1769472},
        {64, 80},
        {0, 80},
        {0, 0}
},
    {
        {-589824, 0, 2031616},
        {-589824, -327680, 1769472},
        {-589824, -327680, 2031616},
        {64, 80},
        {0, 0},
        {64, 0}
},
    {
        {-1114112, -327680, 2031616},
        {-589824, -327680, 2031616},
        {-589824, -1245184, 2031616},
        {0, 224},
        {128, 224},
        {128, 0}
},
    {
        {-1114112, -327680, 2031616},
        {-589824, -1245184, 2031616},
        {-1114112, -1245184, 2031616},
        {0, 224},
        {128, 0},
        {0, 0}
},
    {
        {-1114112, -1245184, 2031616},
        {-2031616, -1245184, 2031616},
        {-2031616, -327680, 2031616},
        {224, 0},
        {0, 0},
        {0, 224}
},
    {
        {-1114112, -1245184, 2031616},
        {-2031616, -327680, 2031616},
        {-1114112, -327680, 2031616},
        {224, 0},
        {0, 224},
        {224, 224}
},
    {
        {-1114112, -1245184, 2031616},
        {-589824, -1245184, 2031616},
        {-589824, -2162688, 2031616},
        {0, 224},
        {128, 224},
        {128, 0}
},
    {
        {-1114112, -1245184, 2031616},
        {-589824, -2162688, 2031616},
        {-1114112, -2162688, 2031616},
        {0, 224},
        {128, 0},
        {0, 0}
},
    {
        {-1114112, -2162688, 2031616},
        {-2031616, -2162688, 2031616},
        {-2031616, -1245184, 2031616},
        {224, 0},
        {0, 0},
        {0, 224}
},
    {
        {-1114112, -2162688, 2031616},
        {-2031616, -1245184, 2031616},
        {-1114112, -1245184, 2031616},
        {224, 0},
        {0, 224},
        {224, 224}
},
    {
        {-1114112, -327680, 2031616},
        {-2031616, -327680, 2031616},
        {-2031616, 0, 2031616},
        {224, 0},
        {0, 0},
        {0, 80}
},
    {
        {-1114112, -327680, 2031616},
        {-2031616, 0, 2031616},
        {-1114112, 0, 2031616},
        {224, 0},
        {0, 80},
        {224, 80}
},
    {
        {-1114112, -327680, 2031616},
        {-1114112, 0, 2031616},
        {-589824, 0, 2031616},
        {0, 0},
        {0, 80},
        {128, 80}
},
    {
        {-1114112, -327680, 2031616},
        {-589824, 0, 2031616},
        {-589824, -327680, 2031616},
        {0, 0},
        {128, 80},
        {128, 0}
},
    {
        {-2031616, 0, 2031616},
        {-2031616, 0, 1769472},
        {-1114112, 0, 1769472},
        {0, 0},
        {0, 64},
        {224, 64}
},
    {
        {-2031616, 0, 2031616},
        {-1114112, 0, 1769472},
        {-1114112, 0, 2031616},
        {0, 0},
        {224, 64},
        {224, 0}
},
    {
        {-1114112, 0, 2031616},
        {-1114112, 0, 1769472},
        {-589824, 0, 1769472},
        {0, 0},
        {0, 64},
        {128, 64}
},
    {
        {-1114112, 0, 2031616},
        {-589824, 0, 1769472},
        {-589824, 0, 2031616},
        {0, 0},
        {128, 64},
        {128, 0}
},
    {
        {-2031616, -2162688, 1769472},
        {-2031616, -2162688, 2031616},
        {-1114112, -2162688, 2031616},
        {0, 64},
        {0, 0},
        {224, 0}
},
    {
        {-2031616, -2162688, 1769472},
        {-1114112, -2162688, 2031616},
        {-1114112, -2162688, 1769472},
        {0, 64},
        {224, 0},
        {224, 64}
},
    {
        {-1114112, -2162688, 1769472},
        {-1114112, -2162688, 2031616},
        {-589824, -2162688, 2031616},
        {0, 64},
        {0, 0},
        {128, 0}
},
    {
        {-1114112, -2162688, 1769472},
        {-589824, -2162688, 2031616},
        {-589824, -2162688, 1769472},
        {0, 64},
        {128, 0},
        {128, 64}
},
    {
        {-1114112, -65536, 262144},
        {-786432, -65536, 262144},
        {-786432, -65536, -262144},
        {0, 0},
        {80, 0},
        {80, 128}
},
    {
        {-1114112, -65536, 262144},
        {-786432, -65536, -262144},
        {-1114112, -65536, -262144},
        {0, 0},
        {80, 128},
        {0, 128}
},
    {
        {-1114112, -65536, 262144},
        {-1114112, -65536, -262144},
        {-1638400, -65536, -52680},
        {128, 0},
        {128, 128},
        {0, 76}
},
    {
        {-1114112, -65536, 262144},
        {-1638400, -65536, -52680},
        {-1638400, -65536, 52680},
        {128, 0},
        {0, 76},
        {0, 51}
},
    {
        {-1114112, -65536, 262144},
        {-1638400, -65536, 52680},
        {-1638400, -65536, 113511},
        {128, 0},
        {0, 51},
        {0, 36}
},
    {
        {-1114112, -65536, 262144},
        {-1638400, -65536, 113511},
        {-1638400, -65536, 196608},
        {128, 0},
        {0, 36},
        {0, 16}
},
    {
        {-1114112, -65536, 262144},
        {-1638400, -65536, 196608},
        {-1638400, -65536, 262144},
        {128, 0},
        {0, 16},
        {0, 0}
},
    {
        {-1114112, -65536, -262144},
        {-1638400, -65536, -262144},
        {-1638400, -65536, -196608},
        {128, 16},
        {0, 16},
        {0, 0}
},
    {
        {-1114112, -65536, -262144},
        {-1638400, -65536, -196608},
        {-1638400, -65536, -113511},
        {128, 37},
        {0, 21},
        {0, 0}
},
    {
        {-1114112, -65536, -262144},
        {-1638400, -65536, -113511},
        {-1638400, -65536, -52680},
        {128, 52},
        {0, 15},
        {0, 0}
},
    {
        {-1887689, -65536, 196608},
        {-2031616, -65536, 196608},
        {-2031616, -65536, 262144},
        {35, 16},
        {0, 16},
        {0, 0}
},
    {
        {-1887689, -65536, 196608},
        {-2031616, -65536, 262144},
        {-1638400, -65536, 262144},
        {35, 16},
        {0, 0},
        {96, 0}
},
    {
        {-1887689, -65536, 196608},
        {-1638400, -65536, 262144},
        {-1782327, -65536, 196608},
        {0, 16},
        {61, 0},
        {25, 16}
},
    {
        {-1638400, -65536, 262144},
        {-1638400, -65536, 196608},
        {-1782327, -65536, 196608},
        {36, 0},
        {36, 16},
        {0, 16}
},
    {
        {-1978935, -65536, 143927},
        {-2031616, -65536, 113511},
        {-2031616, -65536, 196608},
        {12, 12},
        {0, 20},
        {0, 0}
},
    {
        {-1978935, -65536, 143927},
        {-2031616, -65536, 196608},
        {-1887689, -65536, 196608},
        {12, 12},
        {0, 0},
        {35, 0}
},
    {
        {-1691081, -65536, 143927},
        {-1782327, -65536, 196608},
        {-1638400, -65536, 196608},
        {23, 12},
        {0, 0},
        {36, 0}
},
    {
        {-1691081, -65536, 143927},
        {-1638400, -65536, 196608},
        {-1638400, -65536, 113511},
        {0, 12},
        {13, 0},
        {13, 20}
},
    {
        {-1638400, -65536, -52680},
        {-1638400, -65536, -113511},
        {-1691081, -65536, -143927},
        {13, 0},
        {13, 15},
        {0, 23}
},
    {
        {-1691081, -65536, 143927},
        {-1638400, -65536, 113511},
        {-1638400, -65536, 52680},
        {0, 0},
        {13, 8},
        {13, 23}
},
    {
        {-2031616, -65536, -113511},
        {-2031616, -65536, -52680},
        {-1978935, -65536, -143927},
        {0, 15},
        {0, 0},
        {12, 23}
},
    {
        {-1691081, -65536, -143927},
        {-1638400, -65536, -113511},
        {-1638400, -65536, -196608},
        {0, 8},
        {13, 0},
        {13, 21}
},
    {
        {-1691081, -65536, -143927},
        {-1638400, -65536, -196608},
        {-1782327, -65536, -196608},
        {23, 0},
        {36, 13},
        {0, 13}
},
    {
        {-1978935, -65536, -143927},
        {-1887689, -65536, -196608},
        {-2031616, -65536, -196608},
        {12, 0},
        {35, 13},
        {0, 13}
},
    {
        {-1978935, -65536, -143927},
        {-2031616, -65536, -196608},
        {-2031616, -65536, -113511},
        {12, 8},
        {0, 21},
        {0, 0}
},
    {
        {-2031616, -65536, 52680},
        {-2031616, -65536, 113511},
        {-1978935, -65536, 143927},
        {0, 23},
        {0, 8},
        {12, 0}
},
    {
        {-1782327, -65536, -196608},
        {-1638400, -65536, -196608},
        {-1638400, -65536, -262144},
        {0, 0},
        {36, 0},
        {36, 16}
},
    {
        {-1782327, -65536, -196608},
        {-1638400, -65536, -262144},
        {-2031616, -65536, -262144},
        {60, 0},
        {96, 16},
        {0, 16}
},
    {
        {-1782327, -65536, -196608},
        {-2031616, -65536, -262144},
        {-1887689, -65536, -196608},
        {60, 0},
        {0, 16},
        {35, 0}
},
    {
        {-2031616, -65536, -262144},
        {-2031616, -65536, -196608},
        {-1887689, -65536, -196608},
        {0, 16},
        {0, 0},
        {35, 0}
},
    {
        {-1507328, -720896, 87801},
        {-1595129, -720896, 239878},
        {-1638400, -720896, 113511},
        {26, 29},
        {8, 0},
        {0, 24}
},
    {
        {-1507328, -720896, 87801},
        {-1638400, -720896, 113511},
        {-1638400, -720896, 52680},
        {26, 5},
        {0, 0},
        {0, 12}
},
    {
        {-1507328, -720896, 87801},
        {-1638400, -720896, 52680},
        {-1638400, -720896, -52680},
        {26, 0},
        {0, 7},
        {0, 28}
},
    {
        {-1507328, -720896, 87801},
        {-1638400, -720896, -52680},
        {-1507328, -720896, -87801},
        {26, 0},
        {0, 28},
        {26, 35}
},
    {
        {-1638400, -720896, -113511},
        {-1638400, -720896, -196608},
        {-1595129, -720896, -239878},
        {0, 0},
        {0, 16},
        {8, 24}
},
    {
        {-1638400, -720896, -113511},
        {-1595129, -720896, -239878},
        {-1507328, -720896, -87801},
        {0, 5},
        {8, 29},
        {26, 0}
},
    {
        {-1638400, -720896, -113511},
        {-1507328, -720896, -87801},
        {-1638400, -720896, -52680},
        {0, 12},
        {26, 7},
        {0, 0}
},
    {
        {-1638400, -720896, 196608},
        {-1638400, -720896, 113511},
        {-1595129, -720896, 239878},
        {0, 8},
        {0, 24},
        {8, 0}
},
    {
        {-1638400, -720896, 196608},
        {-1595129, -720896, 239878},
        {-1638400, -720896, 264860},
        {0, 13},
        {8, 5},
        {0, 0}
},
    {
        {-1638400, -720896, -264860},
        {-1595129, -720896, -239878},
        {-1638400, -720896, -196608},
        {0, 13},
        {8, 8},
        {0, 0}
},
    {
        {-1782327, -720896, 196608},
        {-1638400, -720896, 196608},
        {-1638400, -720896, 264860},
        {0, 13},
        {28, 13},
        {28, 0}
},
    {
        {-1782327, -720896, 196608},
        {-1638400, -720896, 264860},
        {-1747206, -720896, 327680},
        {0, 25},
        {28, 12},
        {7, 0}
},
    {
        {-1782327, -720896, 196608},
        {-1747206, -720896, 327680},
        {-1922809, -720896, 327680},
        {28, 25},
        {35, 0},
        {0, 0}
},
    {
        {-1782327, -720896, 196608},
        {-1922809, -720896, 327680},
        {-1887689, -720896, 196608},
        {28, 25},
        {0, 0},
        {7, 25}
},
    {
        {-1887689, -720896, 196608},
        {-1922809, -720896, 327680},
        {-2031616, -720896, 264860},
        {28, 25},
        {21, 0},
        {0, 12}
},
    {
        {-1887689, -720896, 196608},
        {-2031616, -720896, 264860},
        {-2031616, -720896, 196608},
        {28, 13},
        {0, 0},
        {0, 13}
},
    {
        {-1978935, -720896, 143927},
        {-1887689, -720896, 196608},
        {-2031616, -720896, 196608},
        {10, 10},
        {28, 0},
        {0, 0}
},
    {
        {-1978935, -720896, 143927},
        {-2031616, -720896, 196608},
        {-2031616, -720896, 113511},
        {10, 10},
        {0, 0},
        {0, 16}
},
    {
        {-1691081, -720896, 143927},
        {-1638400, -720896, 113511},
        {-1638400, -720896, 196608},
        {0, 10},
        {10, 16},
        {10, 0}
},
    {
        {-1691081, -720896, 143927},
        {-1638400, -720896, 196608},
        {-1782327, -720896, 196608},
        {18, 10},
        {28, 0},
        {0, 0}
},
    {
        {-1691081, -720896, -143927},
        {-1638400, -720896, -113511},
        {-1638400, -720896, -52680},
        {0, 18},
        {10, 12},
        {10, 0}
},
    {
        {-1638400, -720896, 52680},
        {-1638400, -720896, 113511},
        {-1691081, -720896, 143927},
        {10, 18},
        {10, 6},
        {0, 0}
},
    {
        {-1978935, -720896, -143927},
        {-2031616, -720896, -52680},
        {-2031616, -720896, -113511},
        {10, 18},
        {0, 0},
        {0, 12}
},
    {
        {-1691081, -720896, -143927},
        {-1782327, -720896, -196608},
        {-1638400, -720896, -196608},
        {18, 0},
        {0, 10},
        {28, 10}
},
    {
        {-1691081, -720896, -143927},
        {-1638400, -720896, -196608},
        {-1638400, -720896, -113511},
        {0, 6},
        {10, 16},
        {10, 0}
},
    {
        {-2031616, -720896, -196608},
        {-1887689, -720896, -196608},
        {-1978935, -720896, -143927},
        {0, 10},
        {28, 10},
        {10, 0}
},
    {
        {-2031616, -720896, -196608},
        {-1978935, -720896, -143927},
        {-2031616, -720896, -113511},
        {0, 16},
        {10, 6},
        {0, 0}
},
    {
        {-1978935, -720896, 143927},
        {-2031616, -720896, 113511},
        {-2031616, -720896, 52680},
        {10, 0},
        {0, 6},
        {0, 18}
},
    {
        {-1887689, -720896, -196608},
        {-2031616, -720896, -196608},
        {-2031616, -720896, -264860},
        {28, 0},
        {0, 0},
        {0, 13}
},
    {
        {-1887689, -720896, -196608},
        {-2031616, -720896, -264860},
        {-1922809, -720896, -327680},
        {28, 0},
        {0, 13},
        {21, 26}
},
    {
        {-1887689, -720896, -196608},
        {-1922809, -720896, -327680},
        {-1747206, -720896, -327680},
        {7, 0},
        {0, 26},
        {35, 26}
},
    {
        {-1887689, -720896, -196608},
        {-1747206, -720896, -327680},
        {-1782327, -720896, -196608},
        {0, 0},
        {28, 26},
        {21, 0}
},
    {
        {-1782327, -720896, -196608},
        {-1747206, -720896, -327680},
        {-1638400, -720896, -264860},
        {0, 0},
        {7, 26},
        {28, 13}
},
    {
        {-1782327, -720896, -196608},
        {-1638400, -720896, -264860},
        {-1638400, -720896, -196608},
        {0, 0},
        {28, 13},
        {28, 0}
},
    {
        {-1922809, -720896, 327680},
        {-1835008, -1310720, 0},
        {-2031616, -827291, 196608},
        {21, 90},
        {39, 0},
        {0, 73}
},
    {
        {-1922809, -720896, 327680},
        {-2031616, -827291, 196608},
        {-2031616, -720896, 264860},
        {21, 17},
        {0, 0},
        {0, 17}
},
    {
        {-1835008, -1310720, 0},
        {-1922809, -720896, 327680},
        {-1747206, -720896, 327680},
        {18, 0},
        {0, 128},
        {35, 128}
},
    {
        {-1638400, -720896, 264860},
        {-1595129, -720896, 239878},
        {-1835008, -1310720, 0},
        {38, 90},
        {46, 90},
        {0, 0}
},
    {
        {-1638400, -720896, 264860},
        {-1835008, -1310720, 0},
        {-1747206, -720896, 327680},
        {38, 90},
        {0, 0},
        {17, 90}
},
    {
        {-1638400, -720896, -264860},
        {-1747206, -720896, -327680},
        {-1835008, -1310720, 0},
        {38, 90},
        {17, 90},
        {0, 0}
},
    {
        {-1638400, -720896, -264860},
        {-1835008, -1310720, 0},
        {-1595129, -720896, -239878},
        {38, 90},
        {0, 0},
        {46, 90}
},
    {
        {-1595129, -720896, -239878},
        {-1835008, -1310720, 0},
        {-1507328, -720896, -87801},
        {0, 97},
        {47, 0},
        {29, 97}
},
    {
        {-1835008, -1310720, 0},
        {-1595129, -720896, 239878},
        {-1507328, -720896, 87801},
        {0, 0},
        {46, 97},
        {17, 97}
},
    {
        {-1835008, -1310720, 0},
        {-1507328, -720896, 87801},
        {-1507328, -720896, -87801},
        {18, 0},
        {35, 128},
        {0, 128}
},
    {
        {-2031616, -956825, -52680},
        {-2031616, -956825, 52680},
        {-1835008, -1310720, 0},
        {0, 77},
        {21, 77},
        {11, 0}
},
    {
        {-2031616, -827291, 196608},
        {-1835008, -1310720, 0},
        {-2031616, -956825, 52680},
        {38, 80},
        {0, 0},
        {10, 58}
},
    {
        {-2031616, -827291, -196608},
        {-2031616, -956825, -52680},
        {-1835008, -1310720, 0},
        {0, 80},
        {28, 58},
        {39, 0}
},
    {
        {-2031616, -827291, -196608},
        {-1835008, -1310720, 0},
        {-1922809, -720896, -327680},
        {0, 73},
        {39, 0},
        {21, 90}
},
    {
        {-2031616, -827291, -196608},
        {-1922809, -720896, -327680},
        {-2031616, -720896, -264860},
        {0, 0},
        {21, 17},
        {0, 17}
},
    {
        {-1747206, -720896, -327680},
        {-1922809, -720896, -327680},
        {-1835008, -1310720, 0},
        {35, 128},
        {0, 128},
        {18, 0}
},
    {
        {-1638400, -720896, 52680},
        {-1638400, -65536, 52680},
        {-1638400, -65536, -52680},
        {21, 0},
        {21, 160},
        {0, 160}
},
    {
        {-1638400, -720896, 52680},
        {-1638400, -65536, -52680},
        {-1638400, -720896, -52680},
        {21, 0},
        {0, 160},
        {0, 0}
},
    {
        {-1887689, -65536, -196608},
        {-1887689, -720896, -196608},
        {-1782327, -720896, -196608},
        {0, 160},
        {0, 0},
        {21, 0}
},
    {
        {-1887689, -65536, -196608},
        {-1782327, -720896, -196608},
        {-1782327, -65536, -196608},
        {0, 160},
        {21, 0},
        {21, 160}
},
    {
        {-1887689, -720896, 196608},
        {-1887689, -65536, 196608},
        {-1782327, -65536, 196608},
        {0, 0},
        {0, 160},
        {21, 160}
},
    {
        {-1887689, -720896, 196608},
        {-1782327, -65536, 196608},
        {-1782327, -720896, 196608},
        {0, 0},
        {21, 160},
        {21, 0}
},
    {
        {-1978935, -720896, 143927},
        {-1978935, -65536, 143927},
        {-1887689, -65536, 196608},
        {0, 0},
        {0, 160},
        {19, 160}
},
    {
        {-1978935, -720896, 143927},
        {-1887689, -65536, 196608},
        {-1887689, -720896, 196608},
        {0, 0},
        {19, 160},
        {19, 0}
},
    {
        {-1978935, -720896, 143927},
        {-2031616, -720896, 52680},
        {-2031616, -65536, 52680},
        {19, 0},
        {0, 0},
        {0, 160}
},
    {
        {-1978935, -720896, 143927},
        {-2031616, -65536, 52680},
        {-1978935, -65536, 143927},
        {19, 0},
        {0, 160},
        {19, 160}
},
    {
        {-1978935, -65536, -143927},
        {-1978935, -720896, -143927},
        {-1887689, -720896, -196608},
        {0, 160},
        {0, 0},
        {19, 0}
},
    {
        {-1978935, -65536, -143927},
        {-1887689, -720896, -196608},
        {-1887689, -65536, -196608},
        {0, 160},
        {19, 0},
        {19, 160}
},
    {
        {-1782327, -720896, -196608},
        {-1691081, -720896, -143927},
        {-1691081, -65536, -143927},
        {0, 0},
        {19, 0},
        {19, 160}
},
    {
        {-1782327, -720896, -196608},
        {-1691081, -65536, -143927},
        {-1782327, -65536, -196608},
        {0, 0},
        {19, 160},
        {0, 160}
},
    {
        {-1691081, -720896, 143927},
        {-1782327, -720896, 196608},
        {-1782327, -65536, 196608},
        {19, 0},
        {0, 0},
        {0, 160}
},
    {
        {-1691081, -720896, 143927},
        {-1782327, -65536, 196608},
        {-1691081, -65536, 143927},
        {19, 0},
        {0, 160},
        {19, 160}
},
    {
        {-1691081, -720896, -143927},
        {-1638400, -720896, -52680},
        {-1638400, -65536, -52680},
        {0, 0},
        {19, 0},
        {19, 160}
},
    {
        {-1691081, -720896, -143927},
        {-1638400, -65536, -52680},
        {-1691081, -65536, -143927},
        {0, 0},
        {19, 160},
        {0, 160}
},
    {
        {-1638400, -720896, 52680},
        {-1691081, -720896, 143927},
        {-1691081, -65536, 143927},
        {0, 0},
        {19, 0},
        {19, 160}
},
    {
        {-1638400, -720896, 52680},
        {-1691081, -65536, 143927},
        {-1638400, -65536, 52680},
        {0, 0},
        {19, 160},
        {0, 160}
},
    {
        {-2031616, -65536, -52680},
        {-2031616, -720896, -52680},
        {-1978935, -720896, -143927},
        {19, 160},
        {19, 0},
        {0, 0}
},
    {
        {-2031616, -65536, -52680},
        {-1978935, -720896, -143927},
        {-1978935, -65536, -143927},
        {19, 160},
        {0, 0},
        {0, 160}
},
    {
        {-786432, 65536, -262144},
        {-786432, -65536, -262144},
        {-786432, -65536, 262144},
        {0, 32},
        {0, 0},
        {128, 0}
},
    {
        {-786432, 65536, -262144},
        {-786432, -65536, 262144},
        {-786432, 65536, 262144},
        {0, 32},
        {128, 0},
        {128, 32}
},
    {
        {-1638400, -65536, -262144},
        {-1114112, -65536, -262144},
        {-1114112, 65536, -262144},
        {0, 0},
        {128, 0},
        {128, 32}
},
    {
        {-1638400, -65536, -262144},
        {-1114112, 65536, -262144},
        {-2031616, 65536, -262144},
        {96, 0},
        {224, 32},
        {0, 32}
},
    {
        {-1638400, -65536, -262144},
        {-2031616, 65536, -262144},
        {-2031616, -65536, -262144},
        {96, 0},
        {0, 32},
        {0, 0}
},
    {
        {-1114112, 65536, -262144},
        {-1114112, -65536, -262144},
        {-786432, -65536, -262144},
        {0, 32},
        {0, 0},
        {80, 0}
},
    {
        {-1114112, 65536, -262144},
        {-786432, -65536, -262144},
        {-786432, 65536, -262144},
        {0, 32},
        {80, 0},
        {80, 32}
},
    {
        {-1638400, -65536, 262144},
        {-2031616, -65536, 262144},
        {-2031616, 65536, 262144},
        {96, 0},
        {0, 0},
        {0, 32}
},
    {
        {-1638400, -65536, 262144},
        {-2031616, 65536, 262144},
        {-1114112, 65536, 262144},
        {96, 0},
        {0, 32},
        {224, 32}
},
    {
        {-1638400, -65536, 262144},
        {-1114112, 65536, 262144},
        {-1114112, -65536, 262144},
        {0, 0},
        {128, 32},
        {128, 0}
},
    {
        {-1114112, 65536, 262144},
        {-786432, 65536, 262144},
        {-786432, -65536, 262144},
        {0, 32},
        {80, 32},
        {80, 0}
},
    {
        {-1114112, 65536, 262144},
        {-786432, -65536, 262144},
        {-1114112, -65536, 262144},
        {0, 32},
        {80, 0},
        {0, 0}
},
    {
        {-1114112, 65536, -262144},
        {-1114112, 65536, 262144},
        {-2031616, 65536, 262144},
        {224, 128},
        {224, 0},
        {0, 0}
},
    {
        {-1114112, 65536, -262144},
        {-2031616, 65536, 262144},
        {-2031616, 65536, -262144},
        {224, 128},
        {0, 0},
        {0, 128}
},
    {
        {-786432, 65536, -262144},
        {-786432, 65536, 262144},
        {-1114112, 65536, 262144},
        {80, 128},
        {80, 0},
        {0, 0}
},
    {
        {-786432, 65536, -262144},
        {-1114112, 65536, 262144},
        {-1114112, 65536, -262144},
        {80, 128},
        {0, 0},
        {0, 128}
},
    {
        {-2031616, -327680, 1769472},
        {-2949120, -327680, 1769472},
        {-2949120, -1245184, 1769472},
        {224, 224},
        {0, 224},
        {0, 0}
},
    {
        {-2031616, -327680, 1769472},
        {-2949120, -1245184, 1769472},
        {-2031616, -1245184, 1769472},
        {224, 224},
        {0, 0},
        {224, 0}
},
    {
        {-3866624, -327680, 1769472},
        {-4784128, -327680, 1769472},
        {-4784128, -1245184, 1769472},
        {224, 224},
        {0, 224},
        {0, 0}
},
    {
        {-3866624, -327680, 1769472},
        {-4784128, -1245184, 1769472},
        {-3866624, -1245184, 1769472},
        {224, 224},
        {0, 0},
        {224, 0}
},
    {
        {-2949120, -327680, 1769472},
        {-3866624, -327680, 1769472},
        {-3866624, -1245184, 1769472},
        {224, 224},
        {0, 224},
        {0, 0}
},
    {
        {-2949120, -327680, 1769472},
        {-3866624, -1245184, 1769472},
        {-2949120, -1245184, 1769472},
        {224, 224},
        {0, 0},
        {224, 0}
},
    {
        {-2031616, -1245184, 1769472},
        {-2949120, -1245184, 1769472},
        {-2949120, -2162688, 1769472},
        {224, 224},
        {0, 224},
        {0, 0}
},
    {
        {-2031616, -1245184, 1769472},
        {-2949120, -2162688, 1769472},
        {-2031616, -2162688, 1769472},
        {224, 224},
        {0, 0},
        {224, 0}
},
    {
        {-3866624, -1245184, 1769472},
        {-4784128, -1245184, 1769472},
        {-4784128, -2162688, 1769472},
        {224, 224},
        {0, 224},
        {0, 0}
},
    {
        {-3866624, -1245184, 1769472},
        {-4784128, -2162688, 1769472},
        {-3866624, -2162688, 1769472},
        {224, 224},
        {0, 0},
        {224, 0}
},
    {
        {-2949120, -1245184, 1769472},
        {-3866624, -1245184, 1769472},
        {-3866624, -2162688, 1769472},
        {224, 224},
        {0, 224},
        {0, 0}
},
    {
        {-2949120, -1245184, 1769472},
        {-3866624, -2162688, 1769472},
        {-2949120, -2162688, 1769472},
        {224, 224},
        {0, 0},
        {224, 0}
},
    {
        {-2949120, -327680, 1769472},
        {-2949120, 0, 1769472},
        {-3866624, 0, 1769472},
        {224, 0},
        {224, 80},
        {0, 80}
},
    {
        {-2949120, -327680, 1769472},
        {-3866624, 0, 1769472},
        {-3866624, -327680, 1769472},
        {224, 0},
        {0, 80},
        {0, 0}
},
    {
        {-3866624, -327680, 1769472},
        {-3866624, 0, 1769472},
        {-4784128, 0, 1769472},
        {224, 0},
        {224, 80},
        {0, 80}
},
    {
        {-3866624, -327680, 1769472},
        {-4784128, 0, 1769472},
        {-4784128, -327680, 1769472},
        {224, 0},
        {0, 80},
        {0, 0}
},
    {
        {-2031616, -327680, 1769472},
        {-2031616, 0, 1769472},
        {-2949120, 0, 1769472},
        {224, 0},
        {224, 80},
        {0, 80}
},
    {
        {-2031616, -327680, 1769472},
        {-2949120, 0, 1769472},
        {-2949120, -327680, 1769472},
        {224, 0},
        {0, 80},
        {0, 0}
},
    {
        {-4784128, -327680, 1769472},
        {-4784128, -327680, 2031616},
        {-4784128, -1245184, 2031616},
        {0, 224},
        {64, 224},
        {64, 0}
},
    {
        {-4784128, -327680, 1769472},
        {-4784128, -1245184, 2031616},
        {-4784128, -1245184, 1769472},
        {0, 224},
        {64, 0},
        {0, 0}
},
    {
        {-4784128, -1245184, 1769472},
        {-4784128, -1245184, 2031616},
        {-4784128, -2162688, 2031616},
        {0, 224},
        {64, 224},
        {64, 0}
},
    {
        {-4784128, -1245184, 1769472},
        {-4784128, -2162688, 2031616},
        {-4784128, -2162688, 1769472},
        {0, 224},
        {64, 0},
        {0, 0}
},
    {
        {-4784128, 0, 1769472},
        {-4784128, 0, 2031616},
        {-4784128, -327680, 2031616},
        {0, 80},
        {64, 80},
        {64, 0}
},
    {
        {-4784128, 0, 1769472},
        {-4784128, -327680, 2031616},
        {-4784128, -327680, 1769472},
        {0, 80},
        {64, 0},
        {0, 0}
},
    {
        {-2949120, -327680, 2031616},
        {-2031616, -327680, 2031616},
        {-2031616, -1245184, 2031616},
        {0, 224},
        {224, 224},
        {224, 0}
},
    {
        {-2949120, -327680, 2031616},
        {-2031616, -1245184, 2031616},
        {-2949120, -1245184, 2031616},
        {0, 224},
        {224, 0},
        {0, 0}
},
    {
        {-3866624, -1245184, 2031616},
        {-4784128, -1245184, 2031616},
        {-4784128, -327680, 2031616},
        {224, 0},
        {0, 0},
        {0, 224}
},
    {
        {-3866624, -1245184, 2031616},
        {-4784128, -327680, 2031616},
        {-3866624, -327680, 2031616},
        {224, 0},
        {0, 224},
        {224, 224}
},
    {
        {-3866624, -327680, 2031616},
        {-2949120, -327680, 2031616},
        {-2949120, -1245184, 2031616},
        {0, 224},
        {224, 224},
        {224, 0}
},
    {
        {-3866624, -327680, 2031616},
        {-2949120, -1245184, 2031616},
        {-3866624, -1245184, 2031616},
        {0, 224},
        {224, 0},
        {0, 0}
},
    {
        {-2949120, -1245184, 2031616},
        {-2031616, -1245184, 2031616},
        {-2031616, -2162688, 2031616},
        {0, 224},
        {224, 224},
        {224, 0}
},
    {
        {-2949120, -1245184, 2031616},
        {-2031616, -2162688, 2031616},
        {-2949120, -2162688, 2031616},
        {0, 224},
        {224, 0},
        {0, 0}
},
    {
        {-3866624, -2162688, 2031616},
        {-4784128, -2162688, 2031616},
        {-4784128, -1245184, 2031616},
        {224, 0},
        {0, 0},
        {0, 224}
},
    {
        {-3866624, -2162688, 2031616},
        {-4784128, -1245184, 2031616},
        {-3866624, -1245184, 2031616},
        {224, 0},
        {0, 224},
        {224, 224}
},
    {
        {-3866624, -1245184, 2031616},
        {-2949120, -1245184, 2031616},
        {-2949120, -2162688, 2031616},
        {0, 224},
        {224, 224},
        {224, 0}
},
    {
        {-3866624, -1245184, 2031616},
        {-2949120, -2162688, 2031616},
        {-3866624, -2162688, 2031616},
        {0, 224},
        {224, 0},
        {0, 0}
},
    {
        {-3866624, -327680, 2031616},
        {-3866624, 0, 2031616},
        {-2949120, 0, 2031616},
        {0, 0},
        {0, 80},
        {224, 80}
},
    {
        {-3866624, -327680, 2031616},
        {-2949120, 0, 2031616},
        {-2949120, -327680, 2031616},
        {0, 0},
        {224, 80},
        {224, 0}
},
    {
        {-3866624, -327680, 2031616},
        {-4784128, -327680, 2031616},
        {-4784128, 0, 2031616},
        {224, 0},
        {0, 0},
        {0, 80}
},
    {
        {-3866624, -327680, 2031616},
        {-4784128, 0, 2031616},
        {-3866624, 0, 2031616},
        {224, 0},
        {0, 80},
        {224, 80}
},
    {
        {-2949120, -327680, 2031616},
        {-2949120, 0, 2031616},
        {-2031616, 0, 2031616},
        {0, 0},
        {0, 80},
        {224, 80}
},
    {
        {-2949120, -327680, 2031616},
        {-2031616, 0, 2031616},
        {-2031616, -327680, 2031616},
        {0, 0},
        {224, 80},
        {224, 0}
},
    {
        {-2949120, 0, 1769472},
        {-2949120, 0, 2031616},
        {-3866624, 0, 2031616},
        {224, 64},
        {224, 0},
        {0, 0}
},
    {
        {-2949120, 0, 1769472},
        {-3866624, 0, 2031616},
        {-3866624, 0, 1769472},
        {224, 64},
        {0, 0},
        {0, 64}
},
    {
        {-3866624, 0, 1769472},
        {-3866624, 0, 2031616},
        {-4784128, 0, 2031616},
        {224, 64},
        {224, 0},
        {0, 0}
},
    {
        {-3866624, 0, 1769472},
        {-4784128, 0, 2031616},
        {-4784128, 0, 1769472},
        {224, 64},
        {0, 0},
        {0, 64}
},
    {
        {-2031616, 0, 1769472},
        {-2031616, 0, 2031616},
        {-2949120, 0, 2031616},
        {224, 64},
        {224, 0},
        {0, 0}
},
    {
        {-2031616, 0, 1769472},
        {-2949120, 0, 2031616},
        {-2949120, 0, 1769472},
        {224, 64},
        {0, 0},
        {0, 64}
},
    {
        {-2949120, -2162688, 2031616},
        {-2949120, -2162688, 1769472},
        {-3866624, -2162688, 1769472},
        {224, 0},
        {224, 64},
        {0, 64}
},
    {
        {-2949120, -2162688, 2031616},
        {-3866624, -2162688, 1769472},
        {-3866624, -2162688, 2031616},
        {224, 0},
        {0, 64},
        {0, 0}
},
    {
        {-3866624, -2162688, 2031616},
        {-3866624, -2162688, 1769472},
        {-4784128, -2162688, 1769472},
        {224, 0},
        {224, 64},
        {0, 64}
},
    {
        {-3866624, -2162688, 2031616},
        {-4784128, -2162688, 1769472},
        {-4784128, -2162688, 2031616},
        {224, 0},
        {0, 64},
        {0, 0}
},
    {
        {-2031616, -2162688, 2031616},
        {-2031616, -2162688, 1769472},
        {-2949120, -2162688, 1769472},
        {224, 0},
        {224, 64},
        {0, 64}
},
    {
        {-2031616, -2162688, 2031616},
        {-2949120, -2162688, 1769472},
        {-2949120, -2162688, 2031616},
        {224, 0},
        {0, 64},
        {0, 0}
},
    {
        {-2162688, -720896, -87801},
        {-2074886, -720896, -239878},
        {-2031616, -720896, -113511},
        {0, 0},
        {17, 29},
        {25, 5}
},
    {
        {-2162688, -720896, -87801},
        {-2031616, -720896, -113511},
        {-2031616, -720896, -52680},
        {0, 7},
        {25, 12},
        {25, 0}
},
    {
        {-2162688, -720896, -87801},
        {-2031616, -720896, -52680},
        {-2031616, -720896, 52680},
        {0, 28},
        {25, 21},
        {25, 0}
},
    {
        {-2162688, -720896, -87801},
        {-2031616, -720896, 52680},
        {-2162688, -720896, 87801},
        {0, 35},
        {25, 7},
        {0, 0}
},
    {
        {-2031616, -720896, 113511},
        {-2031616, -720896, 196608},
        {-2074886, -720896, 239878},
        {8, 24},
        {8, 8},
        {0, 0}
},
    {
        {-2031616, -720896, 113511},
        {-2074886, -720896, 239878},
        {-2162688, -720896, 87801},
        {25, 24},
        {17, 0},
        {0, 29}
},
    {
        {-2031616, -720896, 113511},
        {-2162688, -720896, 87801},
        {-2031616, -720896, 52680},
        {25, 0},
        {0, 5},
        {25, 12}
},
    {
        {-2031616, -720896, -196608},
        {-2031616, -720896, -113511},
        {-2074886, -720896, -239878},
        {8, 16},
        {8, 0},
        {0, 24}
},
    {
        {-2031616, -720896, -196608},
        {-2074886, -720896, -239878},
        {-2031616, -720896, -264860},
        {8, 0},
        {0, 8},
        {8, 13}
},
    {
        {-2074886, -720896, 239878},
        {-2031616, -720896, 196608},
        {-2031616, -720896, 264860},
        {0, 5},
        {8, 13},
        {8, 0}
},
    {
        {-2074886, -720896, 239878},
        {-2031616, -720896, 264860},
        {-2031616, -827291, 196608},
        {0, 17},
        {8, 17},
        {8, 0}
},
    {
        {-2162688, -720896, 87801},
        {-2031616, -956825, 52680},
        {-2031616, -956825, -52680},
        {28, 51},
        {21, 0},
        {0, 0}
},
    {
        {-2162688, -720896, 87801},
        {-2031616, -956825, -52680},
        {-2162688, -720896, -87801},
        {35, 51},
        {7, 0},
        {0, 51}
},
    {
        {-2162688, -720896, 87801},
        {-2074886, -720896, 239878},
        {-2031616, -827291, 196608},
        {0, 17},
        {29, 17},
        {21, 0}
},
    {
        {-2162688, -720896, 87801},
        {-2031616, -827291, 196608},
        {-2031616, -956825, 52680},
        {7, 39},
        {28, 22},
        {0, 0}
},
    {
        {-2162688, -720896, -87801},
        {-2031616, -956825, -52680},
        {-2031616, -827291, -196608},
        {21, 39},
        {28, 0},
        {0, 22}
},
    {
        {-2162688, -720896, -87801},
        {-2031616, -827291, -196608},
        {-2074886, -720896, -239878},
        {29, 17},
        {8, 0},
        {0, 17}
},
    {
        {-2031616, -720896, -264860},
        {-2074886, -720896, -239878},
        {-2031616, -827291, -196608},
        {8, 17},
        {0, 17},
        {8, 0}
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
void decrementScaleFactor(void){
    gteScaleFactor --;
    if(gteScaleFactor < 0){
        gteScaleFactor = 0;
    }
}
void incrementDelayFactor(void){
    delayFactor ++;
    if(delayFactor > 255){
        delayFactor = 255;
    }
}
void decrementDelayFactor(void){
    delayFactor --;
    if(delayFactor < 0){
        delayFactor = 0;
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
        controller_subscribeOnKeyDown(decrementDelayFactor, BUTTON_INDEX_L1      );
        controller_subscribeOnKeyDown(incrementDelayFactor, BUTTON_INDEX_R1      );
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
        controller_subscribeOnKeyDown(decrementDelayFactor, BUTTON_INDEX_L1      );
        controller_subscribeOnKeyDown(incrementDelayFactor, BUTTON_INDEX_R1      );
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
    uploadTexture(&default_32, default_32Data, SCREEN_WIDTH+64, 0, 32, 32); // Default checkerboard pink and black pattern for missing textures
    
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
    
    Model filth;
    model_load("FILTH.MDL;1", &filth);
    uploadTexture(&filth_128, filth_128Data, SCREEN_WIDTH, 256, 128, 128);


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
        uint32_t playerColour = 0x000000;
        int32_t bspResult = BSPTree3_pointContents(&bsp_player, 0, player.position);
        playerColour = bspResult == -1 ? 0x000000 : 0xFFFFFF;


        #pragma endregion



        for (int i = 0; i<256 * delayFactor; i++){
            printf("%d ", i);
        }
        printf("\n");


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
        Tri2_texturedFlat transformedTri;
        for(int i = 0; i<numTris; i++){
            if(
                transformTri_texturedFlat(&mainCamera, tris[i], &transformedTri)
            ){
                drawTri2_texturedFlat(transformedTri, &default_32, 5);
            }
        }

        //Tri2 transformedTri;
        //for(int i = 0; i<numTris; i++){
        //    Tri3 tri3;
        //    tri3.a = tris[i].a;tri3.b = tris[i].b;tri3.c = tris[i].c;
        //    if(
        //        transformTri(&mainCamera, tri3, &transformedTri)
        //    ){
        //        drawTri2(transformedTri, colours[i%6]);
        //    }
        //}
        




        Vector3 playerPoints[] = {
            {
                player.position.x - PLAYER_BBOX_X / 2,
                player.position.y - PLAYER_BBOX_Y / 2,
                player.position.z - PLAYER_BBOX_Z / 2
            },
            {
                player.position.x + PLAYER_BBOX_X / 2,
                player.position.y - PLAYER_BBOX_Y / 2,
                player.position.z - PLAYER_BBOX_Z / 2
            },
            {
                player.position.x - PLAYER_BBOX_X / 2,
                player.position.y + PLAYER_BBOX_Y / 2,
                player.position.z - PLAYER_BBOX_Z / 2
            },
            {
                player.position.x + PLAYER_BBOX_X / 2,
                player.position.y + PLAYER_BBOX_Y / 2,
                player.position.z - PLAYER_BBOX_Z / 2
            },
            {
                player.position.x - PLAYER_BBOX_X / 2,
                player.position.y - PLAYER_BBOX_Y / 2,
                player.position.z + PLAYER_BBOX_Z / 2
            },
            {
                player.position.x + PLAYER_BBOX_X / 2,
                player.position.y - PLAYER_BBOX_Y / 2,
                player.position.z + PLAYER_BBOX_Z / 2
            },
            {
                player.position.x - PLAYER_BBOX_X / 2,
                player.position.y + PLAYER_BBOX_Y / 2,
                player.position.z + PLAYER_BBOX_Z / 2
            },
            {
                player.position.x + PLAYER_BBOX_X / 2,
                player.position.y + PLAYER_BBOX_Y / 2,
                player.position.z + PLAYER_BBOX_Z / 2
            }
        };
        Vector2 transformedPlayerPoints[4];
        bool pointTransformed[4];

        for (int i = 0; i<8; i++){
            pointTransformed[i] = transformVertex(&mainCamera, playerPoints[i], &transformedPlayerPoints[i]);
        }
        
        for (int i = 0; i<8; i++){
            drawCross2(transformedPlayerPoints[i], playerColour);
        }
        for (int i = 1; i<7; i++){
            drawLine2(transformedPlayerPoints[i-1], transformedPlayerPoints[i], playerColour);
            drawLine2(transformedPlayerPoints[i], transformedPlayerPoints[i+1], playerColour);
            drawLine2(transformedPlayerPoints[i+1], transformedPlayerPoints[i-1], playerColour);
        }

        sprintf(str_Buffer, 
            "%s Mode\n"
            "Delay Factor: %d\n",
            controlCamera ? "Camera" : "Player",
            delayFactor
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
   

        debug("\n***\n\n"); // Add a separator between frames to make it easier to read debug output
    }
}
