#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cdrom.h"
#include "controller.h"
#include "filesystem.h"
#include "font.h"
#include "gpu.h"
#include "gte.h"
#include "irq.h"
#include "model.h"
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

extern const uint8_t reference_64Data[];
extern const uint8_t reference_64Palette[];
TextureInfo reference_64;

extern const uint8_t myHead_256Data[];
TextureInfo myHead_256;

extern const uint8_t obama_256Data[];
TextureInfo obama_256;

Model myModel;
Model obamaPrism;

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


bool showingText = true;

// Used to keep track of which channel is playing.
// 0 is combat, 1 is clean.
int selectedMusicChannel = 1;
Sound laser;


void waitForVblank(){
    while(!vblank){
        // Do nothing
    }
    vblank = false;
}

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
    uploadIndexedTexture(&reference_64, reference_64Data, SCREEN_WIDTH, FONT_HEIGHT+1,
        64, 64, reference_64Palette, SCREEN_WIDTH, FONT_HEIGHT+65, GP0_COLOR_4BPP);

    uploadTexture(&myHead_256, myHead_256Data, SCREEN_WIDTH + 256, 0, 256, 256);
    uploadTexture(&obama_256, obama_256Data, SCREEN_WIDTH + 256, 256, 256, 256);
    
}

// Used for movement calculations.
int yawSin;
int yawCos;

// Camera variables stored as separate variables.
int camX     = 0;
int camY     = 0;
int camZ     = 20000;
int camYaw   = -2048;
int camRoll  = 0;
int camPitch = 0;


// Functions for look controls
void lookLeft(void){
    camYaw += 20;
}
void lookRight(void){
    camYaw -= 20;
}
void lookUp(void){
    camPitch -= 20;
}
void lookDown(void){
    camPitch += 20;
}

// Functions for move controls
void moveForward(void){
    camX -= (yawSin)>>6;
    camZ += (yawCos)>>6;
}
void moveBackward(void){
    camX += (yawSin)>>6;
    camZ -= (yawCos)>>6;
}
void moveLeft(void){
    camX -=  ((yawCos)>>6);
    camZ += -((yawSin)>>6);
}
void moveRight(void){
    camX +=  ((yawCos)>>6);
    camZ -= -((yawSin)>>6);
}

// Misc button functions
void swapMusic(void){
    setChannelVolume(selectedMusicChannel, 0);
    selectedMusicChannel = !selectedMusicChannel;
    setChannelVolume(selectedMusicChannel, MAX_VOLUME);
    // Update screen colour to reflect which music we are playing.
    screenColor = selectedMusicChannel ? 0xfa823c : 0x0c34e8;
}

void playSfx(void){
    sound_play(&laser, MAX_VOLUME, MAX_VOLUME);
}

void toggleText(void){
    showingText = !showingText;
}

// Start of main
__attribute__((noreturn))
int main(void){

    // Tell the compiler that variables might be updated randomly (ie, IRQ handlers)
    __atomic_signal_fence(__ATOMIC_ACQUIRE);

    // Initialise important things for later
    initHardware();
    stream_init();
    
    // Load model from the disk
    model_load("MODEL.MDL;1", &myModel);
    model_load("OBAMA.MDL;1", &obamaPrism);

    // Load sound and song from disk.
    sound_loadSound("LASER.VAG;1", &laser);
    stream_loadSong("SONG.VAG;1");
    
    // Begin playback of music on channels 0 and 1.
    //stream_startWithChannelMask(MAX_VOLUME, MAX_VOLUME, 0b000000000000000000000011);


    // The song uses Left and Right channels to hold the Combat and Calm songs.
    // I set the selected channel to Max on both left and right. This allows me
    // to swap the song instantly without needing to load anything.
    setChannelVolume(( selectedMusicChannel), MAX_VOLUME);
    setChannelVolume((!selectedMusicChannel), 0); // Mute the other channel


    // Associate functions with keypresses (button presses)
    // Look controls
    controller_subscribeOnKeyHold(&lookLeft,     BUTTON_INDEX_SQUARE  );
    controller_subscribeOnKeyHold(&lookRight,    BUTTON_INDEX_CIRCLE  );
    controller_subscribeOnKeyHold(&lookUp,       BUTTON_INDEX_TRIANGLE);
    controller_subscribeOnKeyHold(&lookDown,     BUTTON_INDEX_X       );
    // Move controls
    controller_subscribeOnKeyHold(&moveForward,  BUTTON_INDEX_UP      );
    controller_subscribeOnKeyHold(&moveBackward, BUTTON_INDEX_DOWN    );
    controller_subscribeOnKeyHold(&moveLeft,     BUTTON_INDEX_LEFT    );
    controller_subscribeOnKeyHold(&moveRight,    BUTTON_INDEX_RIGHT   );
    // Visual toggles
    controller_subscribeOnKeyDown(&toggleText,   BUTTON_INDEX_L1);
    // Sound
    controller_subscribeOnKeyDown(&swapMusic,   BUTTON_INDEX_L2);
    controller_subscribeOnKeyDown(&playSfx,     BUTTON_INDEX_R2);



    int32_t transXoffset = 0;
    int32_t transYoffset = 0;
    int32_t transZoffset = 0;
    int32_t rotXoffset = 0;
    int32_t rotYoffset = 0;
    int32_t rotZoffset = 0;

    int dY = 20;


    // Main loop. Runs every frame, forever
    for(;;){
        // Point to the relevant DMA chain for this frame, then swap the active frame.
        activeChain = &dmaChains[usingSecondFrame];
        usingSecondFrame = !usingSecondFrame;

        // Reset the ordering table to a blank state.
        clearOrderingTable((activeChain->orderingTable), ORDERING_TABLE_SIZE);
        activeChain->nextPacket = activeChain->data;

        if(transYoffset > 500){
            dY = -20;
        }
        if(transYoffset < -500){
            dY = 20;
        }
        

        // Refresh the GTE for transformations
        gte_setRotationMatrix(
            ONE, 0, 0,
            0, ONE, 0,
            0, 0, ONE
        );
        rotateCurrentMatrix(camPitch, camRoll, camYaw);
        updateTranslationMatrix((camX), (camY), (camZ));

        model_renderTextured(&obamaPrism, &obama_256, 0, 0, 1024, 0, 0, 0);


        // Place the framebuffer offset and screen clearing commands last.
        // This means they will be executed first and be at the back of the screen.
        dmaPtr = allocatePacket(activeChain, ORDERING_TABLE_SIZE -1 , 3);
        dmaPtr[0] = screenColor | gp0_vramFill();
        dmaPtr[1] = gp0_xy(bufferX, bufferY);
        dmaPtr[2] = gp0_xy(SCREEN_WIDTH, SCREEN_HEIGHT);

        dmaPtr = allocatePacket(activeChain, ORDERING_TABLE_SIZE - 1, 4);
        dmaPtr[0] = gp0_texpage(0, true, false);
        dmaPtr[1] = gp0_fbOffset1(bufferX, bufferY);
        dmaPtr[2] = gp0_fbOffset2(bufferX + SCREEN_WIDTH - 1, bufferY + SCREEN_HEIGHT - 2);
        dmaPtr[3] = gp0_fbOrigin(bufferX, bufferY);
    

        // Display the help/debug text.
        if(showingText){
            char textBuffer[1024];
            sprintf(textBuffer, "D-Pad: Move\nFace buttons: Look Around\nL1: Toggle menu\nL2: Toggle music\nR2: Play SFX\n\nPitch(x): %d\nRoll (y): %d\nYaw  (Z): %d\n\nx: %d\ny: %d\nz: %d", camPitch, camRoll, camYaw, camX, camY, camZ);        
            printString(activeChain, &font, 10, 10, textBuffer);
        }

        // Update the stream state machine.
        // Feed more data if needed.
        // Do this every frame, or almost every frame.
        // It is non-blocking but must be checked constantly.
        stream_update();

        // Used for movement calculations.
        // Update these before polling the controller
        yawSin = isin(camYaw);
        yawCos = icos(camYaw);
        // Update the controller every frame.
        // Will run the function associated with each button if the button is pressed.
        controller_update();



        // This will wait for the GPU to be ready,
        // It also waits for Vblank.
        waitForGP0Ready();
        waitForVblank();

        // Swap the frame buffers.
        bufferY = usingSecondFrame ? SCREEN_HEIGHT : 0;
        GPU_GP1 = gp1_fbOffset(bufferX, bufferY);

        // Give DMA a pointer to the last item in the ordering table.
        // We don't need to add a terminator, as it is already done for us by the OTC.
        sendLinkedList(&(activeChain->orderingTable)[ORDERING_TABLE_SIZE - 1]);
   }

    __builtin_unreachable();
}