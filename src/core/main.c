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

#include "registers.h"
#include "system.h"

#define SCREEN_WIDTH     320
#define SCREEN_HEIGHT    256

#define ACCELERATION_CONSTANT (1<<10)
#define MAX_SPEED (1<<13)
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

uint32_t hsv_to_rgb(int h) {
    uint8_t r, g, b;
    // Ensure H is within 0-359
    h = h % 360;

    // Scale up for integer math
    int region = h / 60;       // Integer part of H / 60
    int remainder = h % 60;    // Remainder of H / 60
    int p = 0;                 // Min value (S = V = 100%)
    int q = (255 * (60 - remainder)) / 60;  // Falling edge
    int t = (255 * remainder) / 60;         // Rising edge

    // Assign RGB based on region
    switch (region) {
        case 0: r = 255; g = t;   b = p;   break; // Red to Yellow
        case 1: r = q;   g = 255; b = p;   break; // Yellow to Green
        case 2: r = p;   g = 255; b = t;   break; // Green to Cyan
        case 3: r = p;   g = q;   b = 255; break; // Cyan to Blue
        case 4: r = t;   g = p;   b = 255; break; // Blue to Magenta
        case 5: r = 255; g = p;   b = q;   break; // Magenta to Red
    }
    uint32_t rgb = 0;
    rgb += r;
    rgb += g << 8;
    rgb += b << 16;
    return rgb;
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
    }
};

Point2 startPoint = {20<<12, 20<<12};
Point2 intersectionPoint;
Point2 endPoint;
Vector2 facingVector = {1<<12, 0};

// All the planes in the BSP tree
BSPPlane bspPlanes[4] = {
    // Left wall
    {
        .normal = {.x=(1<<12), .y=0},
        .distance = (10<<12)
    },
    // Right wall
    {
        .normal = {.x=-(1<<12), .y=0},
        .distance = -(310<<12)
    },
    // Top wall
    {
        .normal = {.x=0, .y=(1<<12)},
        .distance = (10<<12)
    },
    // Bottom wall
    {
        .normal = {.x=0, .y=-(1<<12)},
        .distance = -(230<<12)
    }
};

// Define the BSP tree and all the nodes within it.
BSPNode bspNodes[4] = {
    // Left wall
    {
        .planeNum = 0,
        .children = {
            1, -2
        }
    },
    // Right wall
    {
        .planeNum = 1,
        .children = {
            2, -2
        }
    },
    // Top wall
    {
        .planeNum = 2,
        .children = {
            3, -2
        }
    },
    // Bottom wall
    {
        .planeNum = 3,
        .children = {
            -1, -2
        }
    }
};

BSPTree bspTree = {
    .planes = bspPlanes,
    .nodes = bspNodes,
    .numPlanes = 4,
    .numNodes = 4
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

#define ROTATION_SPEED (1<<4)
void rotateClockwise(void){
    facingVector = rotateVector2(facingVector, ROTATION_SPEED);
}
void rotateCounterClockwise(void){
    facingVector = rotateVector2(facingVector, -ROTATION_SPEED);
}
Point2 oldEndPoint;
Point2 newEndPoint;
Point2 oldIntersectionPoint;

void teleport(void){
    player.pos.x = newEndPoint.x;
    player.pos.y = newEndPoint.y;
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
    controller_subscribeOnKeyHold(rotateClockwise,        BUTTON_INDEX_R1   );
    controller_subscribeOnKeyHold(rotateCounterClockwise, BUTTON_INDEX_L1   );
    controller_subscribeOnKeyDown(teleport,               BUTTON_INDEX_X    );

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


    int32_t intA = 10<<12; // 10.0
    int32_t intB = -(1<<11); // -0.5

    int32_t intC = 10<<12; // 10.0
    int16_t intD = -(1<<11); // -0.5
    


    printf("A: %d * %d = %d\n", intA>>12, intB>>12, fixed32_mul(intA, intB)>>12);
    printf("B: %d * %d = %d\n", intC>>12, intD>>12, fixed32_mul(intC, intD)>>12);
    printf("\n");

    //while(true){
        // Do nothing
    //}

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

        Point2 startPoint = {player.pos.x, player.pos.y};
        Point2 endPoint = {player.pos.x + player.delta.x, player.pos.y + player.delta.y};
        BSPHandleCollision(&bspTree, startPoint, endPoint, &player.pos);
    




        ///////////////////////////
        //       Rendering       //
        ///////////////////////////

        // Text rendering
        printString(activeChain, &font, 100, 10, str_Buffer);

        // Draw Cross
        drawCross(startPoint,        0x000000);

        // Draw walls
        for(int i = 0; i < 4; i++){
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