#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "camera.h"
#include "cdrom.h"
#include "controller.h"
#include "filesystem.h"
#include "font.h"
#include "gpu.h"
#include "gte.h"
#include "irq.h"
#include "model.h"
#include "menu.h"
#include "spu.h"
#include "stream.h"
#include "trig.h"

#include "registers.h"
#include "system.h"

#define SCREEN_WIDTH     320
#define SCREEN_HEIGHT    256


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


Camera mainCamera = {
    .x=2000,
    .y=-(3*128),
    .z=0,
    .pitch=0,
    .yaw=1024,
    .roll=0,
    };



char *str_HelloWorld = "Hello World!";


// Start of main
__attribute__((noreturn))
int main(void){

    // Tell the compiler that variables might be updated randomly (ie, IRQ handlers)
    __atomic_signal_fence(__ATOMIC_ACQUIRE);

    // Initialise important things for later
    initHardware();

        // Point to the relevant DMA chain for this frame, then swap the active frame.
        activeChain = &dmaChains[usingSecondFrame];
        usingSecondFrame = !usingSecondFrame;
        
        // Reset the ordering table to a blank state.
        clearOrderingTable((activeChain->orderingTable), ORDERING_TABLE_SIZE);
        activeChain->nextPacket = activeChain->data;

    printf("\n\n\nStart of main loop!\n\n\n");
    // Main loop. Runs every frame, forever
    for(;;){
        ///////////////////////////
        //       Game logic      //
        ///////////////////////////
        
        // Poll the controllers and run their assoicated functions
        controller_update();
        



        ///////////////////////////
        //       Rendering       //
        ///////////////////////////

        // Text rendering
        printString(activeChain, &font, 125, 100, str_HelloWorld);

        // Update the screen colour
        screenHue++;
        screenColor = hsv_to_rgb(screenHue);

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