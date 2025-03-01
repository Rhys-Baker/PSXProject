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

#define ACCELERATION_CONSTANT (1<<12)
#define MAX_SPEED (3<<12)
#define JUMP_FORCE (10<<12)
#define FRICTION_CONSTANT (1<<8)
#define TERMINAL_VELOCITY (5<<12)
#define GRAVITY_CONSTANT (1<<11)


// Include texture data files
extern const uint8_t fontData[];
extern const uint8_t fontPalette[];
TextureInfo font;

extern const uint8_t filth_128Data[];
TextureInfo *filth_128;

Camera mainCamera;
Player2 player;
char str_Buffer[256];
int screenColor = 0xfa823c;
int wallColor = 0x3c82fa;

// 3D direction Gizmo
Vector3 gizmoPoints[4] = {
    {0, 0, 0},
    {100, 0, 0},
    {0, 100, 0},
    {0, 0, 100}
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

    dmaPtr = allocatePacket(activeChain, ORDERING_TABLE_SIZE - 1, 3);
    dmaPtr[0] = colour | gp0_line(false, false);
    dmaPtr[1] = gp0_xy(x-2, y-2);
    dmaPtr[2] = gp0_xy(x+2, y+2);

    dmaPtr = allocatePacket(activeChain, ORDERING_TABLE_SIZE - 1, 3);
    dmaPtr[0] = colour | gp0_line(false, false);
    dmaPtr[1] = gp0_xy(x+2, y-2);
    dmaPtr[2] = gp0_xy(x-2, y+2);
}
void drawLine2(Vector2 a, Vector2 b, uint32_t colour){
    dmaPtr = allocatePacket(activeChain, ORDERING_TABLE_SIZE - 1, 3);
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
    int32_t distX = abs(cam->x - point.x);
    int32_t distY = abs(cam->y - point.y);
    int32_t distZ = abs(cam->z - point.z);
    
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
    vert.x = (int16_t)point.x;
    vert.y = (int16_t)point.y;
    vert.z = (int16_t)point.z;
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
int transformTri(Camera *cam, Tri3 tri, Tri2 *result){
    uint32_t xy0, xy1, xy2;

    // Range check. Is it too big to be drawn?
    if(
        abs(cam->x - tri.a.x) > INT16_MAX || abs(cam->y - tri.a.y) > INT16_MAX || abs(cam->z - tri.a.z) > INT16_MAX ||
        abs(cam->x - tri.b.x) > INT16_MAX || abs(cam->y - tri.b.y) > INT16_MAX || abs(cam->z - tri.b.z) > INT16_MAX ||
        abs(cam->x - tri.c.x) > INT16_MAX || abs(cam->y - tri.c.y) > INT16_MAX || abs(cam->z - tri.c.z) > INT16_MAX
    ){
        // Out of range. Don't render
        return 1;
    }

    // Save the current matrices so we don't clobber them.
    Vector3 currentT;
    gte_getTranslationVector(&currentT.x, &currentT.y, &currentT.z);

    // Translate model
    updateTranslationMatrix(cam->x, cam->y, cam->z);
    // Rotate model
    rotateCurrentMatrix(0, 0, 0);

    GTEVector16 verts[3] = {
        {(int16_t)tri.a.x, (int16_t)tri.a.y, (int16_t)tri.a.z},
        {(int16_t)tri.b.x, (int16_t)tri.b.y, (int16_t)tri.b.z},
        {(int16_t)tri.c.x, (int16_t)tri.c.y, (int16_t)tri.c.z}
    };

    gte_loadV0(&verts[0]);
    gte_loadV1(&verts[1]);
    gte_loadV2(&verts[2]);
    gte_command(GTE_CMD_RTPT | GTE_SF);
    gte_command(GTE_CMD_NCLIP);
    if(gte_getMAC0() <= 0){
        return 2;
    }
    xy0 = gte_getSXY0();
    xy1 = gte_getSXY1();
    xy2 = gte_getSXY2();

    gte_command(GTE_CMD_AVSZ3 | GTE_SF);
    int zIndex = gte_getOTZ();

    if(zIndex < 0 || zIndex >= ORDERING_TABLE_SIZE){
        return 3;
    }

    // Save result
    result->a = (Vector2){xy0 & 0xFFFF, xy0 >> 16};
    result->b = (Vector2){xy1 & 0xFFFF, xy1 >> 16};
    result->c = (Vector2){xy2 & 0xFFFF, xy2 >> 16};
    result->z = zIndex;

    // Restore matrices.
    gte_setTranslationVector(currentT.x, currentT.y, currentT.z);

    return 0;
}
int transformQuad(Camera *cam, Quad3 quad, Quad2 *result){
    uint32_t xy0, xy1, xy2, xy3;
    uint32_t sz0, sz1, sz2, sz3;

    // Range check. Is it too big to be drawn?
    if(
        abs(cam->x - quad.a.x) > INT16_MAX || abs(cam->y - quad.a.y) > INT16_MAX || abs(cam->z - quad.a.z) > INT16_MAX ||
        abs(cam->x - quad.b.x) > INT16_MAX || abs(cam->y - quad.b.y) > INT16_MAX || abs(cam->z - quad.b.z) > INT16_MAX ||
        abs(cam->x - quad.c.x) > INT16_MAX || abs(cam->y - quad.c.y) > INT16_MAX || abs(cam->z - quad.c.z) > INT16_MAX ||
        abs(cam->x - quad.d.x) > INT16_MAX || abs(cam->y - quad.d.y) > INT16_MAX || abs(cam->z - quad.d.z) > INT16_MAX
    ){
        // Out of range. Don't render
        return 1;
    }

    // Save the current matrices so we don't clobber them.
    Vector3 currentT;
    gte_getTranslationVector(&currentT.x, &currentT.y, &currentT.z);

    // Translate model
    updateTranslationMatrix(cam->x, cam->y, cam->z);
    // Rotate model
    rotateCurrentMatrix(0, 0, 0);

    GTEVector16 verts[4] = {
        {(int16_t)quad.a.x, (int16_t)quad.a.y, (int16_t)quad.a.z},
        {(int16_t)quad.b.x, (int16_t)quad.b.y, (int16_t)quad.b.z},
        {(int16_t)quad.c.x, (int16_t)quad.c.y, (int16_t)quad.c.z},
        {(int16_t)quad.d.x, (int16_t)quad.d.y, (int16_t)quad.d.z}
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
        return 2;
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
        return 3;
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

    return 0;
}


#pragma endregion



///////////////////////////////////////////////
// BSP Tree Definition and Shape Definitions //
///////////////////////////////////////////////
#pragma region BSP Tree

Quad3 quads[] = {
    // Floor Quad
    {
        {-512, 0,  512},
        { 512, 0,  512},
        {-512, 0, -512},
        { 512, 0, -512}
    },
    // Ceiling Quad
    {
        {-512, -1024, -512},
        { 512, -1024, -512},
        {-512, -1024,  512},
        { 512, -1024,  512}
    },
    // Left Quad
    {
        {-512, -1024, -512},
        {-512, -1024,  512},
        {-512,     0, -512},
        {-512,     0,  512},
    },
    // Right Quad
    {
        { 512, -1024,  512},
        { 512, -1024, -512},
        { 512,     0,  512},
        { 512,     0, -512},
    },
    // Far Quad
    {
        {-512, -1024,  512},
        { 512, -1024,  512},
        {-512,     0,  512},
        { 512,     0,  512},
    },
    // Near Quad
    {
        { 512, -1024, -512},
        {-512, -1024, -512},
        { 512,     0, -512},
        {-512,     0, -512},
    }
};

BSPNode3 bspNodes[] = {
    // Floor
    {
        .normal = {
            .x=0,
            .y=ONE,
            .z=0
        },
        .distance = 0,
        .children = {
            1, -2
        }
    },

    // Ceiling
    {
        .normal = {
            .x=0,
            .y=-ONE,
            .z=0
        },
        .distance = -1024,
        .children = {
            2, -2
        }
    },

    // Left
    {
        .normal = {
            .x=ONE,
            .y=0,
            .z=0
        },
        .distance = -512,
        .children = {
            3, -2
        }
    },

    // Right
    {
        .normal = {
            .x=-ONE,
            .y=0,
            .z=0
        },
        .distance = -512,
        .children = {
            4, -2
        }
    },

    // Near
    {
        .normal = {
            .x=0,
            .y=0,
            .z=-ONE
        },
        .distance = -512,
        .children = {
            5, -2
        }
    },

    // Far
    {
        .normal = {
            .x=0,
            .y=0,
            .z=ONE
        },
        .distance = -512,
        .children = {
            -1, -2
        }
    }
};

BSPTree3 bspTree = {
    .nodes = bspNodes,
    .numNodes = 6
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
void moveForward(void){
    mainCamera.x -=  (isin(mainCamera.yaw) * MOVEMENT_SPEED)>>12;
    mainCamera.z +=  (icos(mainCamera.yaw) * MOVEMENT_SPEED)>>12;
}
void moveBackward(void){
    mainCamera.x +=  (isin(mainCamera.yaw) * MOVEMENT_SPEED)>>12;
    mainCamera.z -=  (icos(mainCamera.yaw) * MOVEMENT_SPEED)>>12;
}
void moveLeft(void){
    mainCamera.x -=  (icos(mainCamera.yaw) * MOVEMENT_SPEED)>>12;
    mainCamera.z += -(isin(mainCamera.yaw) * MOVEMENT_SPEED)>>12;
}
void moveRight(void){
    mainCamera.x +=  (icos(mainCamera.yaw) * MOVEMENT_SPEED)>>12;
    mainCamera.z -= -(isin(mainCamera.yaw) * MOVEMENT_SPEED)>>12;
}

void moveUp(void){
    mainCamera.y -= MOVEMENT_SPEED;
}
void moveDown(void){
    mainCamera.y += MOVEMENT_SPEED;
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
    // TODO: Fill the screen with black / Add a loading screen here?
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
    controller_subscribeOnKeyHold(moveLeft,       BUTTON_INDEX_LEFT    );
    controller_subscribeOnKeyHold(moveRight,      BUTTON_INDEX_RIGHT   );
    controller_subscribeOnKeyHold(moveForward,    BUTTON_INDEX_UP      );
    controller_subscribeOnKeyHold(moveBackward,   BUTTON_INDEX_DOWN    );
    controller_subscribeOnKeyHold(moveUp,         BUTTON_INDEX_R2      );
    controller_subscribeOnKeyHold(moveDown,       BUTTON_INDEX_L2      );
    controller_subscribeOnKeyHold(lookLeft,       BUTTON_INDEX_L1      );
    controller_subscribeOnKeyHold(lookRight,      BUTTON_INDEX_R1      );


    // Init camera
    mainCamera.x     = 0;
    mainCamera.y     = 0;
    mainCamera.z     = -1000;
    mainCamera.pitch = 0;
    mainCamera.roll  = 0;
    mainCamera.yaw   = 0;

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
        rotateCurrentMatrix(mainCamera.roll, mainCamera.yaw, mainCamera.pitch);
        setTranslationMatrix(0, 0, 0);
        

        //model_renderTextured(&filth, filth_128, &mainCamera, 0, 0, 0, 0, 0, 0);

        for (int i = 0; i<4; i++){
            transformVertex(&mainCamera, gizmoPoints[i], &transformedGizmoPoints[i]);
        };
        drawLine2(transformedGizmoPoints[0], transformedGizmoPoints[1], 0x0000FF);
        drawLine2(transformedGizmoPoints[0], transformedGizmoPoints[2], 0x00FF00);
        drawLine2(transformedGizmoPoints[0], transformedGizmoPoints[3], 0xFF0000);
        
        //Tri3 tri;
        //tri.a = quads[0].a;
        //tri.b = quads[0].b;
        //tri.c = quads[0].c;
        //Tri2 transformedTri;
        //int result = transformTri(&mainCamera, tri, &transformedTri);
        //drawTri2(transformedTri, 0x00FF00);

        uint32_t colours[6] = {
            0x0000FF,
            0x00FF00,
            0xFF0000,
            0x00FFFF,
            0xFF00FF,
            0xFFFF00
        };

        Quad2 transformedQuad;
        for(int i = 0; i<6; i++){
            if(!transformQuad(&mainCamera, quads[i], &transformedQuad)){
                drawQuad2(transformedQuad, colours[i]);
            } else {
                debug("No.");
            }
        }
        
        printf("\n");

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
   }
    __builtin_unreachable();
}