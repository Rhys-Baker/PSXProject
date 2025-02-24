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

Player2 player;
char str_Buffer[256];
int screenColor = 0xfa823c;
int wallColor = 0x3c82fa;


//////////////////////////////
// Drawing Helper Functions //
//////////////////////////////
#pragma region Drawing Helpers
void drawCross(Vector2 p, uint32_t colour){
    int32_t x, y;
    x = p.x>>12;
    y = p.y>>12;

    dmaPtr = allocatePacket(activeChain, ORDERING_TABLE_SIZE - 1, 3);
    dmaPtr[0] = colour | gp0_line(false, false);
    dmaPtr[1] = gp0_xy(x-2, y-2);
    dmaPtr[2] = gp0_xy(x+2, y+2);

    dmaPtr = allocatePacket(activeChain, ORDERING_TABLE_SIZE - 1, 3);
    dmaPtr[0] = colour | gp0_line(false, false);
    dmaPtr[1] = gp0_xy(x+2, y-2);
    dmaPtr[2] = gp0_xy(x-2, y+2);
}
void drawLine(Vector2 a, Vector2 b, uint32_t colour){
    dmaPtr = allocatePacket(activeChain, ORDERING_TABLE_SIZE - 1, 3);
    dmaPtr[0] = colour | gp0_line(false, false);
    dmaPtr[1] = gp0_xy(a.x>>12, a.y>>12);
    dmaPtr[2] = gp0_xy(b.x>>12, b.y>>12);
}
void drawRect(Rectangle rect, uint32_t colour){
    int minx = min(min(rect.A.x, rect.B.x), min(rect.C.x, rect.D.x));
    int miny = min(min(rect.A.y, rect.B.y), min(rect.C.y, rect.D.y));

    int maxx = max(max(rect.A.x, rect.B.x), max(rect.C.x, rect.D.x));
    int maxy = max(max(rect.A.y, rect.B.y), max(rect.C.y, rect.D.y));


    dmaPtr = allocatePacket(activeChain, ORDERING_TABLE_SIZE - 1, 3);
    dmaPtr[0] = colour | gp0_rectangle(false, true, false);
    dmaPtr[1] = gp0_xy(minx, miny);
    dmaPtr[2] = gp0_xy(maxx - minx, maxy-miny);

}
void drawTri(Triangle tri, uint32_t colour){
    dmaPtr = allocatePacket(activeChain, ORDERING_TABLE_SIZE - 1, 4);
    dmaPtr[0] = colour | gp0_triangle(false, false);
    dmaPtr[1] = gp0_xy(tri.A.x, tri.A.y);
    dmaPtr[2] = gp0_xy(tri.B.x, tri.B.y);
    dmaPtr[3] = gp0_xy(tri.C.x, tri.C.y);
}
#pragma endregion



///////////////////////////////////////////////
// BSP Tree Definition and Shape Definitions //
///////////////////////////////////////////////
#pragma region BSP Tree

const int numTris = 14;
const int numRects = 3;
const Triangle mapTris[] = {
{
    {1, 0}, {320, 0}, {320, 1}
},
{
    {1, 0}, {320, 1}, {1, 1}
},
{
    {1, 100}, {1, 40}, {140, 40}
},
{
    {1, 100}, {140, 40}, {140, 100}
},
{
    {180, 1}, {220, 1}, {220, 60}
},
{
    {180, 1}, {220, 60}, {180, 60}
},
{
    {220, 120}, {300, 120}, {300, 160}
},
{
    {220, 120}, {300, 160}, {220, 160}
},
{
    {300, 1}, {319, 1}, {319, 80}
},
{
    {300, 1}, {319, 80}, {300, 80}
},
{
    {319, 240}, {1, 240}, {1, 239}
},
{
    {319, 240}, {1, 239}, {319, 239}
},
{
    {320, 1}, {320, 240}, {319, 240}
},
{
    {320, 1}, {319, 240}, {319, 1}
},
};

const Rectangle mapRects[] = {
{
    {0, 0}, {1, 0}, {1, 240}, {0, 240}
},
{
    {1, 239}, {1, 200}, {100, 200}, {100, 239}
},
{
    {220, 160}, {260, 160}, {260, 239}, {220, 239}
},
};

BSPNode2 bspNodes[] = {
    {
        .normal = { .x = 4096, .y = 0},
        .distance = 4096,
        .children = {
            1, -2
        }
    },
    {
        .normal = { .x = 0, .y = 4096},
        .distance = 4096,
        .children = {
            2, -2
        }
    },
    {
        .normal = { .x = 4096, .y = 0},
        .distance = 1306624,
        .children = {
            -2, 3
        }
    },
    {
        .normal = { .x = 0, .y = 4096},
        .distance = 978944,
        .children = {
            -2, 4
        }
    },
    {
        .normal = { .x = 0, .y = 4096},
        .distance = 655360,
        .children = {
            15, 5
        }
    },
    {
        .normal = { .x = 4096, .y = 0},
        .distance = 1228800,
        .children = {
            14, 6
        }
    },
    {
        .normal = { .x = 0, .y = 4096},
        .distance = 491520,
        .children = {
            13, 7
        }
    },
    {
        .normal = { .x = 4096, .y = 0},
        .distance = 573440,
        .children = {
            10, 8
        }
    },
    {
        .normal = { .x = 0, .y = 4096},
        .distance = 163840,
        .children = {
            9, -1
        }
    },
    {
        .normal = { .x = 0, .y = 4096},
        .distance = 409600,
        .children = {
            -1, -2
        }
    },
    {
        .normal = { .x = 4096, .y = 0},
        .distance = 737280,
        .children = {
            11, -1
        }
    },
    {
        .normal = { .x = 0, .y = 4096},
        .distance = 245760,
        .children = {
            -1, 12
        }
    },
    {
        .normal = { .x = 4096, .y = 0},
        .distance = 901120,
        .children = {
            -1, -2
        }
    },
    {
        .normal = { .x = 4096, .y = 0},
        .distance = 901120,
        .children = {
            -2, -1
        }
    },
    {
        .normal = { .x = 0, .y = 4096},
        .distance = 327680,
        .children = {
            -1, -2
        }
    },
    {
        .normal = { .x = 4096, .y = 0},
        .distance = 1064960,
        .children = {
            -1, 16
        }
    },
    {
        .normal = { .x = 4096, .y = 0},
        .distance = 901120,
        .children = {
            -2, 17
        }
    },
    {
        .normal = { .x = 4096, .y = 0},
        .distance = 409600,
        .children = {
            -1, 18
        }
    },
    {
        .normal = { .x = 0, .y = 4096},
        .distance = 819200,
        .children = {
            -2, -1
        }
    },
};

BSPTree2 bspTree = {
    .nodes=bspNodes,
    .numNodes=19
};

#pragma endregion



//////////////////////////
// Controller Functions //
//////////////////////////
#pragma region Controller Funcs
void moveLeft(void){
    player.velocity.x-=(1<<12);
    if(player.velocity.x < -MAX_SPEED){
        player.velocity.x = -MAX_SPEED;
    }
}
void moveRight(void){
    player.velocity.x+=(1<<12);
    if(player.velocity.x > MAX_SPEED){
        player.velocity.x = MAX_SPEED;
    }
}
void moveUp(void){
    player.velocity.y-=(1<<12);
    if(player.velocity.y < -MAX_SPEED){
        player.velocity.y = -MAX_SPEED;
    }
}

void moveLeftNoVelocity(void){
    player.position.x-=(1<<12);
}
void moveRightNoVelocity(void){
    player.position.x+=(1<<12);
}
void moveUpNoVelocity(void){
    player.position.y-=(1<<12);
}
void moveDownNoVelocity(void){
    player.position.y+=(1<<12);
}

void jump(void){
    if(player.isGrounded || player.coyoteTimer > 0){
        player.velocity.y = -JUMP_FORCE;
        player.isGrounded = false;
        player.coyoteTimer = 0;
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
    //initCDROM();
    //initFilesystem();
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
    controller_subscribeOnKeyHold(moveLeft,  BUTTON_INDEX_LEFT );
    controller_subscribeOnKeyHold(moveRight, BUTTON_INDEX_RIGHT);
    controller_subscribeOnKeyHold(moveUp,    BUTTON_INDEX_UP   );
    controller_subscribeOnKeyDown(jump,      BUTTON_INDEX_X    );

    
    // Init player
    player.position.x = 10<<12;
    player.position.y = 10<<12;
    player.velocity.x = 0;
    player.velocity.y = 0;


    debug("Start of main loop");
    // Main loop. Runs every frame, forever
    for(;;){

        ///////////////////////////
        //       Game logic      //
        ///////////////////////////
        #pragma region Game logic
        // Poll the controllers and run their assoicated functions
        controller_update();

        // Horizontal Friction TODO: Change depending on grounded state, etc
        if(player.velocity.x > 0){
            if(player.velocity.x < FRICTION_CONSTANT){
                player.velocity.x = 0;
            } else {
                player.velocity.x -= FRICTION_CONSTANT;
            }
        } else if(player.velocity.x < 0){
            if(player.velocity.x > -FRICTION_CONSTANT){
                player.velocity.x = 0;
            } else {
                player.velocity.x += FRICTION_CONSTANT;
            }
        }

        // Gravity
        if(!player.isGrounded){
            player.velocity.y += GRAVITY_CONSTANT;
            
            if(player.velocity.y > TERMINAL_VELOCITY){
                player.velocity.y = TERMINAL_VELOCITY;
            }
        }


        // Move the player and handle collisions
        Player2_move(&bspTree, &player);
        #pragma endregion



        ///////////////////////////
        //       Rendering       //
        ///////////////////////////
        #pragma region Rendering

        // Text rendering
        printString(activeChain, &font, 100, 10, str_Buffer);

        // Draw Cross
        drawCross(player.position,        0x000000);

        // Draw rectangles
        for(int i = 0; i<numRects; i++){
            drawRect(mapRects[i], wallColor);
        }
        // Draw triangles
        for(int i = 0; i<numTris; i++){
            drawTri(mapTris[i], wallColor);
        }

        // Draw a plain background
        dmaPtr = allocatePacket(activeChain, ORDERING_TABLE_SIZE -1 , 3);
        dmaPtr[0] = screenColor | gp0_vramFill();
        dmaPtr[1] = gp0_xy(bufferX, bufferY);
        dmaPtr[2] = gp0_xy(SCREEN_WIDTH, SCREEN_HEIGHT);

        #pragma endregion



        ///////////////////////////
        //   Framebuffer Logic   //
        ///////////////////////////
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