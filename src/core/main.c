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

#include "registers.h"
#include "system.h"

#define SCREEN_WIDTH     320
#define SCREEN_HEIGHT    256

// Include texture data files
extern const uint8_t fontData[];
extern const uint8_t fontPalette[];
TextureInfo font;

extern const uint8_t computer_keyboard_spacebarAudio[];
extern const uint8_t groovy_gravyAudio[];

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


#define DMA_CHUNK_SIZE 4
#define DMA_TIMEOUT 100000
#define STATUS_TIMEOUT 10000


static bool waitForStatus(uint16_t mask, uint16_t value) {
	for (int timeout = STATUS_TIMEOUT; timeout > 0; timeout -= 10) {
		if ((SPU_STAT & mask) == value)
			return true;

		delayMicroseconds(10);
	}

	return false;
}

size_t uploadAudioSample(uint32_t ramOffset, const void *data, size_t length, bool wait) {
    length /= 4;
    length = (length + DMA_CHUNK_SIZE - 1) / DMA_CHUNK_SIZE;

    if (!waitForDMATransfer(DMA_SPU, DMA_TIMEOUT))
        return 0;
    
    uint16_t ctrlReg = SPU_CTRL & ~SPU_CTRL_XFER_BITMASK;

    SPU_CTRL = ctrlReg;
    waitForStatus(SPU_CTRL_XFER_BITMASK, 0);

    SPU_DMA_CTRL = 4;
    SPU_ADDR = ramOffset / 8;
    SPU_CTRL = ctrlReg | SPU_CTRL_XFER_DMA_WRITE;
    waitForStatus(SPU_CTRL_XFER_BITMASK, SPU_CTRL_XFER_DMA_WRITE);

    DMA_MADR(DMA_SPU) = (uint32_t)data;
    DMA_BCR (DMA_SPU) = DMA_CHUNK_SIZE | (length << 16);
    DMA_CHCR(DMA_SPU) = DMA_CHCR_WRITE | DMA_CHCR_MODE_SLICE | DMA_CHCR_ENABLE;

    if (wait)
        waitForDMATransfer(DMA_SPU, DMA_TIMEOUT);
    
    return length * DMA_CHUNK_SIZE * 4;
}


// Gets called once at the start of main.
void init(Stream *stream){
    // Initialise the serial port for printing
    initSerialIO(115200);
    //initSPU();
    initCDROM();
    initIRQ(stream);
    initControllerBus();

    // Read the GPU's status register to check if it was left in PAL or NTSC mode by the BIOS
    if ((GPU_GP1 & GP1_STAT_MODE_BITMASK) == GP1_STAT_MODE_PAL){
       setupGPU(GP1_MODE_PAL, SCREEN_WIDTH, SCREEN_HEIGHT);
    } else {
       setupGPU(GP1_MODE_NTSC, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    // Enable the GPU's DMA channel
    DMA_DPCR |= DMA_DPCR_ENABLE << (DMA_GPU * 4);
    DMA_DPCR |= DMA_DPCR_ENABLE << (DMA_OTC * 4);

    // Enable the SPU's DMA channel
    DMA_DPCR |= DMA_DPCR_ENABLE << (DMA_SPU * 4);

    GPU_GP1 = gp1_dmaRequestMode(GP1_DREQ_GP0_WRITE); // Fetch GP0 commands from DMA when possible
    GPU_GP1 = gp1_dispBlank(false); // Disable display blanking


    // Upload textures
    uploadIndexedTexture(&font, fontData, SCREEN_WIDTH+16, 0, FONT_WIDTH, FONT_HEIGHT, 
        fontPalette, SCREEN_WIDTH+16, FONT_HEIGHT, GP0_COLOR_4BPP);

    //if(!uploadAudioSample(0x01000, computer_keyboard_spacebarAudio+0x30, 0xB70, true)){
    //    screenColor = 0x0000FF;
    //}
    
}


ControllerInfo controllerInfo;
bool squarePressed   = false;
bool circlePressed   = false;
bool trianglePressed = false;
bool r1Pressed       = false;
bool l1Pressed       = false;
bool upPressed       = false;
bool downPressed     = false;


void hexdump(const uint8_t *ptr, size_t length) {
    while (length) {
        size_t lineLength = (length < 16) ? length : 16;
        length -= lineLength;

        for (; lineLength; lineLength--)
            printf(" %02x", *(ptr++));

        putchar('\n');
    }
}


// Start of main

int main(void){   
    // Tell the compiler that variables might be updated randomly (ie, IRQ handlers)
    __atomic_signal_fence(__ATOMIC_ACQUIRE);
    // Initialise stream
    Stream myStream;


    // Initialise important things for later
    init(&myStream);
    
    uint32_t spuAllocPtr = 0x1010;
    
    // Load and play a click sound.
    // TODO: Move these out of here and make it all a bit neater.
    initSPU();
    stopChannels(ALL_CHANNELS);
    setMasterVolume(MAX_VOLUME, 0);
    Sound mySound;
    sound_create(&mySound);
    const VAGHeader *vagHeader = (const VAGHeader*) computer_keyboard_spacebarAudio;
    sound_initFromVAGHeader(&mySound, vagHeader, spuAllocPtr);
    spuAllocPtr += upload(mySound.offset, vagHeader_getData(vagHeader), mySound.length, true);
    sound_playOnChannel(&mySound, MAX_VOLUME, MAX_VOLUME, 0);
    

    
    stream_create(&myStream);
    
    // Create pointer to header
    vagHeader = (const VAGHeader *) groovy_gravyAudio;
    size_t streamLength = vagHeader_getSPULength(vagHeader) * vagHeader_getNumChannels(vagHeader);
    size_t streamOffset = 0;
    const uint8_t *streamData = ((const uint8_t *) vagHeader) + 0x800;

    // Init from header
    stream_initFromVAGHeader(&myStream, vagHeader, spuAllocPtr, 8);
    spuAllocPtr += stream_getChunkLength(&myStream) * myStream.numChunks;

    // Fill up the buffer with data from the file
    streamOffset += stream_feed(&myStream, streamData + streamOffset, streamLength - streamOffset);

    // Kick off playback of the stream
    stream_startWithChannelMask(&myStream, MAX_VOLUME, MAX_VOLUME, 1 << 1);



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
      
      
        // Check audio playback and top-up buffer
        if(stream_getFreeChunkCount(&myStream) > 0){
            streamOffset += stream_feed(&myStream, streamData + streamOffset, streamLength - streamOffset);
            if(streamOffset >= streamLength){
                streamOffset -= streamLength;
            }
        }


        getControllerInfo(0, &controllerInfo);
        // Square
        if(controllerInfo.buttons & BUTTON_MASK_SQUARE){
            if(!squarePressed){
                squarePressed = true;
            }
        } else {
            squarePressed = false;
        }

        // Circle
        if(controllerInfo.buttons & BUTTON_MASK_CIRCLE){
            if(!circlePressed){
                circlePressed = true;
                sound_playOnChannel(&mySound, MAX_VOLUME, MAX_VOLUME, 0);
            }
        } else {
            circlePressed = false;
        }

        // Triangle
        if(controllerInfo.buttons & BUTTON_MASK_TRIANGLE){
            if(!trianglePressed){
                trianglePressed = true;
                stopChannels(ALL_CHANNELS);
            }
        } else {
            trianglePressed = false;
        }

        // R1
        if(controllerInfo.buttons & BUTTON_MASK_R1){
            if(!r1Pressed){
                r1Pressed = true;

            }
        } else {
            r1Pressed = false;
        }

        // L1
        if(controllerInfo.buttons & BUTTON_MASK_L1){
            if(!l1Pressed){
                l1Pressed = true;
              
            }
        } else {
            l1Pressed = false;
        }

        // Up
        if(controllerInfo.buttons & BUTTON_MASK_UP){
            if(!upPressed){
                upPressed = true;
            }
        } else {
            upPressed = false;
        }

        // Down
        if(controllerInfo.buttons & BUTTON_MASK_DOWN){
            if(!downPressed){
                downPressed = true;
            }
        } else {
            downPressed = false;
        }

        waitForGP0Ready();
        waitForVblank();

        // Swap the frame buffers.
        bufferY = usingSecondFrame ? SCREEN_HEIGHT : 0;
        GPU_GP1 = gp1_fbOffset(bufferX, bufferY); 

        // Give DMA a pointer to the last item in the ordering table.
        // We don't need to add a terminator, as it is already done for us by the OTC.
        sendLinkedList(&(chain->orderingTable)[ORDERING_TABLE_SIZE - 1]);
   }


   // Stops intellisense from yelling at me.
   return 0; // 100% totally necessary.
}