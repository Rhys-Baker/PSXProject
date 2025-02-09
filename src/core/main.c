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

#define SCREEN_WIDTH     320
#define SCREEN_HEIGHT    256

#define ACCELERATION_CONSTANT (1<<12)
#define MAX_SPEED (1<<12)
#define FRICTION_CONSTANT (1<<8)


// Include texture data files
extern const uint8_t fontData[];
extern const uint8_t fontPalette[];
TextureInfo font;

int screenHue = 0;
int screenColor = 0xfa823c;

// Lookup table of 6 colours, used for debugging purposes
int colours[6] = {
    0xFF0000,
    0x00FF00,
    0x0000FF,
    0xFF00FF,
    0xFFFF00,
    0x00FFFF
};

// Gets called once at the start of main.
void initHardware(void){
    // Enable display blanking if not already.
    // Prevents logo from appearing while loading.
    GPU_GP1 = gp1_dispBlank(true);

    // Initialise the serial port for printing
    initSerialIO(115200);
    initSPU();
    initCDROM();
    initIRQ();
    initControllerBus();
    initFilesystem();
    // TODO: Fill the screen with black / Add a loading screen here?
    initGPU(); // Disables screen blanking after setting up screen.
    
    setupGTE(SCREEN_WIDTH, SCREEN_HEIGHT);
    // Upload textures
    uploadIndexedTexture(&font, fontData, SCREEN_WIDTH, 0, FONT_WIDTH, FONT_HEIGHT, 
        fontPalette, SCREEN_WIDTH, FONT_HEIGHT, GP0_COLOR_4BPP);

    // Initalise the transformed verts list
    // TODO: Look into whether this is actually useful or not
    transformedVerts = malloc(sizeof(TransformedVert) * maxNumVerts);
}

void drawCross(Point2 p, uint32_t colour){
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

void drawLine(Point2 a, Point2 b, uint32_t colour){
    dmaPtr = allocatePacket(activeChain, ORDERING_TABLE_SIZE - 1, 3);
    dmaPtr[0] = colour | gp0_line(false, false);
    dmaPtr[1] = gp0_xy(a.x>>12, a.y>>12);
    dmaPtr[2] = gp0_xy(b.x>>12, b.y>>12);
}


Camera mainCamera = {
    .x=2000,
    .y=-(3*128),
    .z=0,
    .pitch=0,
    .yaw=1024,
    .roll=0,
};


typedef struct Line {
    Point2 a, b;
} Line;

Line lines[] = {
    {
        .a = {
            .x = 10<<12,
            .y = 10<<12
        },
        .b = {
            .x = 10<<12,
            .y = 230<<12
        }
    },
    {
        .a = {
            .x = 310<<12,
            .y = 10<<12
        },
        .b = {
            .x = 310<<12,
            .y = 230<<12
        }
    },
    {
        .a = {
            .x = 10<<12,
            .y = 10<<12
        },
        .b = {
            .x = 310<<12,
            .y = 10<<12
        }
    },
    {
        .a = {
            .x = 10<<12,
            .y = 230<<12
        },
        .b = {
            .x = 310<<12,
            .y = 230<<12
        }
    },
    {
        .a = {
            .x = 92<<12,
            .y = 120<<12
        },
        .b = {
            .x = 159<<12,
            .y = 187<<12
        }
    },
    {
        .a = {
            .x = 226<<12,
            .y = 120<<12
        },
        .b = {
            .x = 159<<12,
            .y = 187<<12
        }
    },
    {
        .a = {
            .x = 159<<12,
            .y = 53<<12
        },
        .b = {
            .x = 92<<12,
            .y = 120<<12
        }
    },
    {
        .a = {
            .x = 159<<12,
            .y = 53<<12
        },
        .b = {
            .x = 226<<12,
            .y = 120<<12
        }
    },
};



Point2 endPoint;
Vector2 facingVector = {1<<12, 0};

// Define the BSP tree and all the nodes within it.
BSPNode bspNodes[9] = {
    {
        .normal = { .x = 4096, .y = 0},
        .distance = 40960,
        .children = {
            1, -2
        }
    },
    {
        .normal = { .x = -4096, .y = 0},
        .distance = -1269760,
        .children = {
            2, -2
        }
    },
    {
        .normal = { .x = 0, .y = 4096},
        .distance = 491520,
        .children = {
            6, 3
        }
    },
    {
        .normal = { .x = 0, .y = 4096},
        .distance = 40960,
        .children = {
            4, -2
        }
    },
    {
        .normal = { .x = -2896, .y = -2896},
        .distance = -614400,
        .children = {
            -1, 5
        }
    },
    {
        .normal = { .x = 2896, .y = -2896},
        .distance = 307200,
        .children = {
            -1, -2
        }
    },
    {
        .normal = { .x = 0, .y = -4096},
        .distance = -942080,
        .children = {
            7, -2
        }
    },
    {
        .normal = { .x = -2896, .y = 2896},
        .distance = 81920,
        .children = {
            -1, 8
        }
    },
    {
        .normal = { .x = 2896, .y = 2896},
        .distance = 1003520,
        .children = {
            -1, -2
        }
    },
};

BSPTree bspTree = {
    .nodes = bspNodes,
    .numNodes = 9
};

int32_t bspContents;
uint32_t crossColour;

char str_Buffer[256];


struct player{
    Point2 pos;
    Point2 delta;
} player;

void moveLeft(void){
    player.delta.x-=(1<<12);
    if(player.delta.x < -MAX_SPEED){
        player.delta.x = -MAX_SPEED;
    }
}
void moveRight(void){
    player.delta.x+=(1<<12);
    if(player.delta.x > MAX_SPEED){
        player.delta.x = MAX_SPEED;
    }
}
void moveUp(void){
    player.delta.y-=(1<<12);
    if(player.delta.y < -MAX_SPEED){
        player.delta.y = -MAX_SPEED;
    }
}
void moveDown(void){
    player.delta.y+=(1<<12);
    if(player.delta.y > MAX_SPEED){
        player.delta.y = MAX_SPEED;
    }
}

void moveLeftNoVelocity(void){
    player.pos.x-=(1<<12);
}
void moveRightNoVelocity(void){
    player.pos.x+=(1<<12);
}
void moveUpNoVelocity(void){
    player.pos.y-=(1<<12);
}
void moveDownNoVelocity(void){
    player.pos.y+=(1<<12);
}

void rotateClockwise(void){
    facingVector = rotateVector2(facingVector, 10);
}
void rotateCounterClockwise(void){
    facingVector = rotateVector2(facingVector, -10);
}

// Start of main
__attribute__((noreturn))
int main(void){

    // Tell the compiler that variables might be updated randomly (ie, IRQ handlers)
    __atomic_signal_fence(__ATOMIC_ACQUIRE);

    // Initialise important things for later
    initHardware();

    // Run this stuff once before the main loop.
    controller_subscribeOnKeyHold(moveLeft,               BUTTON_INDEX_LEFT );
    controller_subscribeOnKeyHold(moveRight,              BUTTON_INDEX_RIGHT);
    controller_subscribeOnKeyHold(moveUp,                 BUTTON_INDEX_UP   );
    controller_subscribeOnKeyHold(moveDown,               BUTTON_INDEX_DOWN );

    if(false){
        controller_subscribeOnKeyHold(moveLeftNoVelocity,               BUTTON_INDEX_LEFT );
        controller_subscribeOnKeyHold(moveRightNoVelocity,              BUTTON_INDEX_RIGHT);
        controller_subscribeOnKeyHold(moveUpNoVelocity,                 BUTTON_INDEX_UP   );
        controller_subscribeOnKeyHold(moveDownNoVelocity,               BUTTON_INDEX_DOWN );
    }

    controller_subscribeOnKeyHold(rotateClockwise,        BUTTON_INDEX_R1);
    controller_subscribeOnKeyHold(rotateCounterClockwise, BUTTON_INDEX_L1);

    // Point to the relevant DMA chain for this frame, then swap the active frame.
    activeChain = &dmaChains[usingSecondFrame];
    usingSecondFrame = !usingSecondFrame;

    // Reset the ordering table to a blank state.
    clearOrderingTable((activeChain->orderingTable), ORDERING_TABLE_SIZE);
    activeChain->nextPacket = activeChain->data;

    // Init player
    player.pos.x = 20<<12;
    player.pos.y = 20<<12;
    player.delta.x = 0;
    player.delta.y = 0;


    printf("\n\n\nStart of main loop!\n\n\n");
    // Main loop. Runs every frame, forever
    for(;;){
        ///////////////////////////
        //       Game logic      //
        ///////////////////////////
        
        // Poll the controllers and run their assoicated functions
        controller_update();

        // Horizontal Friction
        if(player.delta.x > 0){
            if(player.delta.x < FRICTION_CONSTANT){
                player.delta.x = 0;
            } else {
                player.delta.x -= FRICTION_CONSTANT;
            }
        } else if(player.delta.x < 0){
            if(player.delta.x > -FRICTION_CONSTANT){
                player.delta.x = 0;
            } else {
                player.delta.x += FRICTION_CONSTANT;
            }
        }
        // Vertical Friction
        if(player.delta.y > 0){
            if(player.delta.y < FRICTION_CONSTANT){
                player.delta.y = 0;
            } else {
                player.delta.y -= FRICTION_CONSTANT;
            }
        } else if(player.delta.y < 0){
            if(player.delta.y > -FRICTION_CONSTANT){
                player.delta.y = 0;
            } else {
                player.delta.y += FRICTION_CONSTANT;
            }
        }


        Point2 intersectionPoint;
        if(true){
            endPoint.x = player.pos.x + player.delta.x;
            endPoint.y = player.pos.y + player.delta.y;
            BSPHandleCollision(&bspTree, player.pos, endPoint, &player.pos);
        } else {
            player.pos.x += player.delta.x;
            player.pos.y += player.delta.y;
            endPoint.x = player.pos.x + (facingVector.x * 50);
            endPoint.y = player.pos.y + (facingVector.y * 50);
            Vector2 wallNormal;
            testHue = 50;
            BSPHandleCollision(&bspTree, player.pos, endPoint, &intersectionPoint);
            //BSPRecursiveCast2(&bspTree, 0, player.pos, endPoint, &intersectionPoint, &wallNormal);
        }
        


        ///////////////////////////
        //       Rendering       //
        ///////////////////////////

        // Text rendering
        printString(activeChain, &font, 100, 10, str_Buffer);

        // Draw Cross
        drawCross(player.pos,        0x000000);
        //drawCross(endPoint, 0x000000);
        //drawCross(intersectionPoint, 0x0000FF);
        //drawLine(player.pos, intersectionPoint, 0x0000FF);
        //drawLine(player.pos, endPoint, 0x00FF00);

        // Draw walls
        for(int i = 0; i < 8; i++){
            drawLine(lines[i].a, lines[i].b, 0x000000);
        }

        // Update the screen colour
        //screenHue++;
        //screenColor = hsv_to_rgb(screenHue);

        // Draw a plain background
        dmaPtr = allocatePacket(activeChain, ORDERING_TABLE_SIZE -1 , 3);
        dmaPtr[0] = screenColor | gp0_vramFill();
        dmaPtr[1] = gp0_xy(bufferX, bufferY);
        dmaPtr[2] = gp0_xy(SCREEN_WIDTH, SCREEN_HEIGHT);




        ///////////////////////////
        //   Framebuffer Logic   //
        ///////////////////////////
        
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
   }
    __builtin_unreachable();
}