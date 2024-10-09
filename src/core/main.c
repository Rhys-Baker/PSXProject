#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "cdrom.h"
#include "controller.h"
#include "filesystem.h"
#include "font.h"
#include "gpu.h"
#include "irq.h"
#include "spu.h"
#include "stream.h"

#include "registers.h"
#include "system.h"

#define SCREEN_WIDTH     320
#define SCREEN_HEIGHT    256


// Include texture data files
extern const uint8_t fontData[];
extern const uint8_t fontPalette[];
TextureInfo font;

// the X and Y of the buffer we are currently using.
int bufferX = 0;
int bufferY = 0;
// The pointer to the DMA packet.
// We allocate space for each packet before we use it.
uint32_t *ptr;

DMAChain dmaChains[2];
bool usingSecondFrame = false;

int screenColor = 0xfa823c;

void waitForVblank(){
    while(!vblank){
        // Do nothing
    }
    vblank = false;
}

// Gets called once at the start of main.
void init(void){
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

    // Upload textures
    uploadIndexedTexture(&font, fontData, SCREEN_WIDTH+16, 0, FONT_WIDTH, FONT_HEIGHT, 
        fontPalette, SCREEN_WIDTH+16, FONT_HEIGHT, GP0_COLOR_4BPP);
    
}

// Debugging hexdump function.
// Considering adding a "utilies" or "debug" library for these kinds of things
void hexdump(const uint8_t *ptr, size_t length) {
    while (length) {
        size_t lineLength = (length < 16) ? length : 16;
        length -= lineLength;

        for (; lineLength; lineLength--)
            printf(" %02x", *(ptr++));

        putchar('\n');
    }
}

// CDROM State machine states.
// Don't want these in main either if possible. Perhaps we can put all this into a Stream lib?
typedef enum{
	CDROM_SM_IDLE            = 0,
	CDROM_SM_WAIT_FOR_DATA = 1,
    CDROM_SM_DATA_READY      = 2
} CDROMStateMachineState;
CDROMStateMachineState cdromSMState = CDROM_SM_IDLE;

// Used to keep track of which channel is playing.
// 0 is clean, 1 is combat.
int selectedMusicChannel = 1;


void swapMusic(void){
    setChannelVolume(selectedMusicChannel+1, MAX_VOLUME);
    selectedMusicChannel = !selectedMusicChannel;
    setChannelVolume(selectedMusicChannel+1, 0);
    // Update screen colour to reflect which music we are playing.
    screenColor = selectedMusicChannel ? 0x0c34e8 : 0xfa823c;
}


// Start of main
__attribute__((noreturn))
int main(void){   
    // Tell the compiler that variables might be updated randomly (ie, IRQ handlers)
    __atomic_signal_fence(__ATOMIC_ACQUIRE);

    // Initialise important things for later
    init();
    
    stream_init();
    stream_loadSong("SONG.VAG;1");

    stream_startWithChannelMask(MAX_VOLUME, MAX_VOLUME, 0b000000000000000000000110);

    // This isn't necessarily a part of the stream function.
    // By default, the stream will play all channels. It is up to the user to handle the volume of which channels they want.
    setChannelVolume(( selectedMusicChannel)+1, MAX_VOLUME);
    setChannelVolume((!selectedMusicChannel)+1, 0); // Mute the other channel
    

    // It may also be worth it to create a function for initialising and playing sounds.

    // Load a click sound.
    // TODO: Move these out of here and make it all a bit neater.
#if 0
    stopChannels(ALL_CHANNELS);
    setMasterVolume(MAX_VOLUME, 0);
    Sound mySound;
    sound_create(&mySound);
    const VAGHeader *vagHeader = (const VAGHeader*) computer_keyboard_spacebarAudio;
    sound_initFromVAGHeader(&mySound, vagHeader, spuAllocPtr);
    spuAllocPtr += upload(mySound.offset, vagHeader_getData(vagHeader), mySound.length, true);
#endif

    // Attach functions to button presses
    controller_attachFunctionToButton(&swapMusic, BUTTON_INDEX_CIRCLE);

    // Main loop. Runs every frame, forever
    for(;;){
        // Point to the relevant DMA chain for this frame, then swap the active frame.
        DMAChain *chain = &dmaChains[usingSecondFrame];
        usingSecondFrame = !usingSecondFrame;

        // Reset the ordering table to a blank state.
        clearOrderingTable((chain->orderingTable), ORDERING_TABLE_SIZE);
        chain->nextPacket = chain->data;
      
        // Place the framebuffer offset and screen clearing commands last.
        // This means they will be executed first and be at the back of the screen.
        ptr = allocatePacket(chain, ORDERING_TABLE_SIZE -1 , 3);
        ptr[0] = screenColor | gp0_vramFill();
        ptr[1] = gp0_xy(bufferX, bufferY);
        ptr[2] = gp0_xy(SCREEN_WIDTH, SCREEN_HEIGHT);

        ptr = allocatePacket(chain, ORDERING_TABLE_SIZE - 1, 4);
        ptr[0] = gp0_texpage(0, true, false);
        ptr[1] = gp0_fbOffset1(bufferX, bufferY);
        ptr[2] = gp0_fbOffset2(bufferX + SCREEN_WIDTH - 1, bufferY + SCREEN_HEIGHT - 2);
        ptr[3] = gp0_fbOrigin(bufferX, bufferY);


        // Update the stream state machine.
        // Feed more data if needed.
        // Do this every frame, or almost every frame.
        // It is non-blocking but must be checked constantly.
        stream_update();

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
        sendLinkedList(&(chain->orderingTable)[ORDERING_TABLE_SIZE - 1]);
   }

    __builtin_unreachable();
}