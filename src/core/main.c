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

// the X and Y of the buffer we are currently using.
int bufferX = 0;
int bufferY = 0;
// The pointer to the DMA packet.
// We allocate space for each packet before we use it.
uint32_t *ptr;

DMAChain dmaChains[2];
bool usingSecondFrame = false;

void waitForVblank(){
   while(!vblank){
      // Do nothing
   }
   vblank = false;
}

// Gets called once at the start of main.
void init(void){
   // Initialise the serial port for printing
   initSerialIO(115200);
   initSPU();
   initCDROM();
   initIRQ();
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

   GPU_GP1 = gp1_dmaRequestMode(GP1_DREQ_GP0_WRITE); // Fetch GP0 commands from DMA when possible
   GPU_GP1 = gp1_dispBlank(false); // Disable display blanking

   // Upload textures
   uploadIndexedTexture(&font, fontData, SCREEN_WIDTH+16, 0, FONT_WIDTH, FONT_HEIGHT, 
      fontPalette, SCREEN_WIDTH+16, FONT_HEIGHT, GP0_COLOR_4BPP);
}

uint8_t isoHeader[2048];
uint8_t pvdData[2048];

void hexdump(const uint8_t *ptr, size_t length) {
    while (length) {
        size_t lineLength = (length < 16) ? length : 16;
        length -= lineLength;

        for (; lineLength; lineLength--)
            printf(" %02x", *(ptr++));

        putchar('\n');
    }
}

ControllerInfo controllerInfo;
bool squarePressed = false;
bool circlePressed = false;
bool r1Pressed     = false;
bool l1Pressed     = false;
bool upPressed     = false;
bool downPressed   = false;

int ReadSector = 16;
int DisplayingPage = 0;
char* UIBuffer[32];
char* DataBuffer[2048];
char* LoadingString = "Loading...";

void formatDataOutput(char* string){
   for(int i = 0; i<1024; i++){
      if(!(i%40)){
         sprintf(DataBuffer, "%s\n", DataBuffer);
      }
      sprintf(DataBuffer, "%s%c", DataBuffer, string[i + (1024 * DisplayingPage)]);
   }
}

uint8_t rootDirEntry[34];
uint32_t rootDirLBA;
uint8_t rootDirData[2048];

int main(void){   
   // Tell the compiler that variables might be updated randomly (ie, IRQ handlers)
   __atomic_signal_fence(__ATOMIC_ACQUIRE);

   // Initialise important things for later
   init();

   printf("\n\n==== PROGRAM START ====\n\n");

   // Main loop. Runs every frame, forever
   for(;;){
      // Point to the relevant DMA chain for this frame, then swap the active frame.
      DMAChain *chain = &dmaChains[usingSecondFrame];
      usingSecondFrame = !usingSecondFrame;

      // Reset the ordering table to a blank state.
      clearOrderingTable((chain->orderingTable), ORDERING_TABLE_SIZE);
      chain->nextPacket = chain->data;


      sprintf(UIBuffer, "Read Sector: \t%d \tPage: %d/4", ReadSector, DisplayingPage+1);

      printString(chain, &font, 10, 10, UIBuffer);
      printDataString(chain, &font, 10, 20, DataBuffer);
      
      // Place the framebuffer offset and screen clearing commands last.
      // This means they will be executed first and be at the back of the screen.
      ptr = allocatePacket(chain, ORDERING_TABLE_SIZE -1 , 3);
      ptr[0] = gp0_rgb(60, 130, 250) | gp0_vramFill();
      ptr[1] = gp0_xy(bufferX, bufferY);
      ptr[2] = gp0_xy(SCREEN_WIDTH, SCREEN_HEIGHT);

      ptr = allocatePacket(chain, ORDERING_TABLE_SIZE - 1, 4);
      ptr[0] = gp0_texpage(0, true, false);
      ptr[1] = gp0_fbOffset1(bufferX, bufferY);
      ptr[2] = gp0_fbOffset2(bufferX + SCREEN_WIDTH - 1, bufferY + SCREEN_HEIGHT - 2);
      ptr[3] = gp0_fbOrigin(bufferX, bufferY);
      
      
      getControllerInfo(0, &controllerInfo);
      // Square
      if(controllerInfo.buttons & BUTTON_MASK_SQUARE){
         if(!squarePressed){
            squarePressed = true;
            printf("\n\n==== READ CDROM DATA ====\n\n");
            printString(chain, &font, 200, 10, LoadingString);
            startCDROMRead(
               ReadSector,
               isoHeader,
               sizeof(isoHeader) / 2048,
               2048,
               true
            );
            waitForINT1();
            hexdump(isoHeader, 2048);
            sprintf(DataBuffer, "");
            formatDataOutput(isoHeader);
         }
      } else {
         squarePressed = false;
      }
      
      // Circle
      if(controllerInfo.buttons & BUTTON_MASK_CIRCLE){
         if(!circlePressed){
            circlePressed = true;
            startCDROMRead(
               16,
               pvdData,
               sizeof(pvdData) / 2048,
               2048,
               true
            );
            waitForINT1();
            uint32_t pathTableSize;
            uint16_t pathTableLBA;
            int result;           
            int rootDirSize = getRootDirLBA(pvdData, &rootDirLBA);
            startCDROMRead(
               rootDirLBA,
               rootDirData,
               sizeof(rootDirData) / 2048,
               2048,
               true
            );
            waitForINT1();
            uint8_t  recLen;
            uint32_t len;
            uint32_t lba;
            char *name[255];
            int offset = 0;
            
            printf("\n\n==== Directory Contents ====\n\n");
            for(int i=0; i<10; i++){
               result = parseDirRecord(&rootDirData[offset], &name, &recLen, &len, &lba);
               if(result){
                  break;
               }
               offset += recLen;
               printf("%d: \"%s\"\n", i, name);
            }
         }
      } else {
         circlePressed = false;
      }

      // R1
      if(controllerInfo.buttons & BUTTON_MASK_R1){
         if(!r1Pressed){
            r1Pressed = true;
            if(DisplayingPage++ >= 3) DisplayingPage = 0;
            sprintf(DataBuffer, "");
            formatDataOutput(isoHeader);
         }
      } else {
         r1Pressed = false;
      }

      // L1
      if(controllerInfo.buttons & BUTTON_MASK_L1){
         if(!l1Pressed){
            l1Pressed = true;
            if(DisplayingPage-- <= 0) DisplayingPage = 3;
            sprintf(DataBuffer, "");
            formatDataOutput(isoHeader);
         }
      } else {
         l1Pressed = false;
      }

      // Up
      if(controllerInfo.buttons & BUTTON_MASK_UP){
         if(!upPressed){
            // Max number of sectors
            if(ReadSector++ >= 214349) ReadSector = 0;
            upPressed = true;
         }
      } else {
         upPressed = false;
      }

      // Down
      if(controllerInfo.buttons & BUTTON_MASK_DOWN){
         if(!downPressed){
            if(ReadSector-- <= 0) ReadSector = 214349;
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