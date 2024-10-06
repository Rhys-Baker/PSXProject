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

/// @brief Get the LBA to the file with a given filename, assuming it is stored in the root directory.
/// @param rootDirData Pointer to the root directory data.
/// @param filename String containing the filename of the requested file.
/// @return LBA to file or 0 if not found.
uint32_t getLBAToFile(uint8_t *rootDirData, const char *filename){
    DirectoryEntry directoryEntry;
    uint8_t  recLen;
    int offset = 0;
    for(int i=0; i<10; i++){
        if(parseDirRecord(
            &rootDirData[offset],
            &recLen,
            &directoryEntry
        )){
           break;
        }
        offset += recLen;
        
        if(!__builtin_strcmp(directoryEntry.name, filename)){
            return directoryEntry.lba;
        }
    }
    return 0;
}

// Gets called once at the start of main.
void init(void *stream){
    // Initialise the serial port for printing
    initSerialIO(115200);
    initSPU();
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
    
}

ControllerInfo controllerInfo;
// TODO: Consider changing these into a single variable and just using bits instead
bool squarePressed   = false;
bool circlePressed   = false;
bool trianglePressed = false;
bool r1Pressed       = false;
bool l1Pressed       = false;
bool upPressed       = false;
bool downPressed     = false;


Stream myStream;
size_t freeChunks;

void hexdump(const uint8_t *ptr, size_t length) {
    while (length) {
        size_t lineLength = (length < 16) ? length : 16;
        length -= lineLength;

        for (; lineLength; lineLength--)
            printf(" %02x", *(ptr++));

        putchar('\n');
    }
}


typedef enum{
	CDROM_SM_IDLE            = 0,
	CDROM_SM_WAIT_FOR_STREAM = 1
} CDROMStateMachineState;

CDROMStateMachineState cdromSMState = CDROM_SM_IDLE;

VAGHeader mySongVAGHeader;

void updateCDROMStateMachine(void){
    switch(cdromSMState){
        case CDROM_SM_IDLE:
            // Get the number of free chunks that must be read
            freeChunks = stream_getFreeChunkCount(&myStream);
            if(freeChunks >= 16){
                
            }
            break;

        case CDROM_SM_WAIT_FOR_STREAM:
            if(waitingForInt3)
                break;
            // Update Stream

            cdromSMState = CDROM_SM_IDLE;
            break;
    }
}


// Start of main
__attribute__((noreturn))
int main(void){   
    // Tell the compiler that variables might be updated randomly (ie, IRQ handlers)
    __atomic_signal_fence(__ATOMIC_ACQUIRE);
    // Initialise stream


    // Initialise important things for later
    init(&myStream);
    
    printf("\n\n=====Program start=====\n");

    uint8_t rootDirData[2048];
    getRootDirData(&rootDirData);
    uint32_t songLBA = getLBAToFile(&rootDirData, "SONG.VAG;1");

    char songVagHeaderSector[2048];
    uint8_t streamBuffer[32 * 2048]; // 32 chunk buffer
    if(songLBA){
        startCDROMRead(songLBA, songVagHeaderSector, 1, 2048, true, true);
        startCDROMRead(songLBA+1, streamBuffer, 32, 2048, true, true);
    }


    // TODO: Make this not bad
    // While this doesn't NOT work, it's terrible and nigh impossible to read
    // I have to scroll up and down to understand it. Please fix.
    stream_create(&myStream);
    uint32_t spuAllocPtr = 0x1010;
    VAGHeader *songVagHeader;
    __builtin_memcpy(songVagHeader, songVagHeaderSector, sizeof(VAGHeader));
    
    size_t streamLength = vagHeader_getSPULength(songVagHeader);
    size_t streamOffset = 0;
    stream_initFromVAGHeader(&myStream, songVagHeader, spuAllocPtr, 32);
    spuAllocPtr += stream_getChunkLength(&myStream) * myStream.numChunks;
    streamOffset = stream_feed(&myStream, streamBuffer, 16*2048);

    stream_startWithChannelMask(&myStream, MAX_VOLUME, MAX_VOLUME, 1 << 1);


    
    // Load a click sound.
    // TODO: Move these out of here and make it all a bit neater.
    //stopChannels(ALL_CHANNELS);
    //setMasterVolume(MAX_VOLUME, 0);
    //Sound mySound;
    //sound_create(&mySound);
    //const VAGHeader *vagHeader = (const VAGHeader*) computer_keyboard_spacebarAudio;
    //sound_initFromVAGHeader(&mySound, vagHeader, spuAllocPtr);
    //spuAllocPtr += upload(mySound.offset, vagHeader_getData(vagHeader), mySound.length, true);
    

    // Create pointer to header
    //vagHeader = (const VAGHeader *) groovy_gravyAudio;
    //size_t streamLength = vagHeader_getSPULength(vagHeader) * vagHeader_getNumChannels(vagHeader);
    //size_t streamOffset = 0;
    //const uint8_t *streamData = ((const uint8_t *) vagHeader) + 0x800;
//
    //// Init from header
    //stream_initFromVAGHeader(&myStream, vagHeader, spuAllocPtr, 32);
    //spuAllocPtr += stream_getChunkLength(&myStream) * myStream.numChunks;
//
    //// Fill up the buffer with data from the file
    //streamOffset += stream_feed(&myStream, streamData + streamOffset, streamLength - streamOffset);
//
    //// Kick off playback of the stream
    //stream_startWithChannelMask(&myStream, MAX_VOLUME, MAX_VOLUME, 1 << 1);



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
      
    
        // TODO: Rewrite this block to work with the new CDROM State Machine I'm working on.
        // The purpose of that is to prevent the CDROM read command from blocking the rest of program execution.

        // Check audio playback and top-up buffer
        //int streamFreeChunks = stream_getFreeChunkCount(&myStream);
        //printf("Stream free chunks: %d\n", streamFreeChunks);
        //if(streamFreeChunks >= 8){
        //    printf(" Stream free chunks > half. Reading more data.\n");
        //    startCDROMRead(songLBA+1+(streamOffset / 2048), streamBuffer, streamFreeChunks, 2048, true, true);
        //    printf(" Read completed. Feeding stream from buffer.\n");
        //    streamOffset += stream_feed(&myStream, streamBuffer, streamLength - streamOffset);
        //    printf(" Stream feed complete.\n");
        //    // If we reached the end of the stream, loop back to the start
        //    if(streamOffset >= streamLength){
        //        printf("  Stream has reached end. Resetting!\n");
        //        streamOffset -= streamLength;
        //    }
        //}



        getControllerInfo(0, &controllerInfo);
        // Square
        if(controllerInfo.buttons & BUTTON_MASK_SQUARE){
            if(!squarePressed){
                squarePressed = true;
                //uint8_t rootDirData[2048];
                //getRootDirData(rootDirData);
                DirectoryEntry *directoryListing[10];
                uint8_t  recLen;
                int offset = 0;
                printf("\n\n==== Directory Contents ====\n\n");
                for(int i=0; i<10; i++){
                    if(parseDirRecord(
                        &rootDirData[offset],
                        &recLen,
                        directoryListing[i]
                    )){
                       break;
                    }
                    offset += recLen;
                    printf("%d: \"%s\" | %d\n", i, &directoryListing[i]->name, directoryListing[i]->lba);
                }
            }
        } else {
            squarePressed = false;
        }

        // Circle
        if(controllerInfo.buttons & BUTTON_MASK_CIRCLE){
            if(!circlePressed){
                circlePressed = true;
            //    sound_playOnChannel(&mySound, MAX_VOLUME, MAX_VOLUME, 0);
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

    __builtin_unreachable();
}