#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "cdrom.h"
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

char textBuffer[1024];


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

char secondTextBuffer[2048];

void hexdump(const uint8_t *ptr, size_t length) {
    while (length) {
        size_t lineLength = (length < 16) ? length : 16;
        length -= lineLength;

        for (; lineLength; lineLength--)
            printf(" %02x", *(ptr++));

        putchar('\n');
    }
}

int main(void){   
   // Tell the compiler that variables might be updated randomly (ie, IRQ handlers)
   __atomic_signal_fence(__ATOMIC_ACQUIRE);

   // Initialise important things for later
   init();

   printf("\n\n==== PROGRAM START ====\n\n");

   startCDROMRead(
      16,
      isoHeader,
      sizeof(isoHeader) / 2048,
      2048,
      true
   );

   hexdump(isoHeader, 2048);

   //for(int i=0; i<2048; i++){
   //   // Newline every 80 characters
   //   if(!(i % 80)){
   //      printf("\n");
   //   }
   //   if(isoHeader[i] <= 32 || isoHeader[i] > 0x80){
   //      printf(".");
   //   } else {
   //      printf("%c", isoHeader[i]);
   //   }
   //}
   //printf("\n");

   sprintf(textBuffer, secondTextBuffer);

   // Main loop. Runs every frame, forever
   for(;;){
      // Point to the relevant DMA chain for this frame, then swap the active frame.
      DMAChain *chain = &dmaChains[usingSecondFrame];
      usingSecondFrame = !usingSecondFrame;

      // Reset the ordering table to a blank state.
      clearOrderingTable((chain->orderingTable), ORDERING_TABLE_SIZE);
      chain->nextPacket = chain->data;

      printString(chain, &font, 50, 10, textBuffer);
      
      // Place the framebuffer offset and screen clearing commands last.
      // This means they will be executed first and be at the back of the screen.
      ptr = allocatePacket(chain, ORDERING_TABLE_SIZE -1 , 3);
      ptr[0] = gp0_rgb(255, 0, 255) | gp0_vramFill();
      ptr[1] = gp0_xy(bufferX, bufferY);
      ptr[2] = gp0_xy(SCREEN_WIDTH, SCREEN_HEIGHT);

      ptr = allocatePacket(chain, ORDERING_TABLE_SIZE - 1, 4);
      ptr[0] = gp0_texpage(0, true, false);
      ptr[1] = gp0_fbOffset1(bufferX, bufferY);
      ptr[2] = gp0_fbOffset2(bufferX + SCREEN_WIDTH - 1, bufferY + SCREEN_HEIGHT - 2);
      ptr[3] = gp0_fbOrigin(bufferX, bufferY);
      
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