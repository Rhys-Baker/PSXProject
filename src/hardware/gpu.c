/*
 * (C) 2024 Rhys Baker, spicyjpeg
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include "gpu.h"
#include "gpucmd.h"
#include "registers.h"


// TODO: Now that these variables are here, we can make most if not all of it private.

// the X and Y of the buffer we are currently using.
int bufferX = 0;
int bufferY = 0;
// The pointer to the DMA packet.
// We allocate space for each packet before we use it.
uint32_t *dmaPtr;
DMAChain dmaChains[2];
DMAChain *activeChain;
bool usingSecondFrame = false;


void initGPU(void){
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
}

void setupGPU(GP1VideoMode mode, int width, int height){
    int x=0x760;
    int y= (mode == GP1_MODE_PAL) ? 0xa3 : 0x88;

    GP1HorizontalRes horizontalRes = GP1_HRES_320;
    GP1VerticalRes   verticalRes   = GP1_VRES_256;

    // Sets the number of displayed rows and columns.
    // As we are talking directly to hardware, the number of pixels is actually clock cycles.
    // The number of cycles is dependant on the number of pixels.
    // This is handled by a switch statement.
    int offsetX = (width  * gp1_clockMultiplierH(horizontalRes)) / 2;
    int offsetY = (height / gp1_clockDividerV(verticalRes))      / 2;

    // Hand the parameters to the GPU via "GP1 commands".
    // We will be using GP1 commands to talk to the GPU directly
    GPU_GP1 = gp1_resetGPU();
    GPU_GP1 = gp1_fbRangeH(x - offsetX, x + offsetX); // Set the Horizontal range of the framebuffer
    GPU_GP1 = gp1_fbRangeV(y - offsetY, y + offsetY); // Set the Vertical range of the framebuffer
    GPU_GP1 = gp1_fbMode( // Set up some other variables for this framebuffer.
        horizontalRes, verticalRes, mode, false, GP1_COLOR_16BPP
    );
}

void waitForGP0Ready(void){
    // GP1 is for "Display Control" instructions.
    // As you can see in setupGPU(), we tell it where to put things in VRAM such as a framebuffer, etc
    // GP0, on the other hand is for actually rendering things
    // This function will block until the GPU reports that GP0 is ready to receive an instruction
    // The status register that tells us this is mapped to the same location as GP1, except only when reading
    while(!(GPU_GP1 & GP1_STAT_CMD_READY)){
        __asm__ volatile(""); // Do absolutely nothing
    }
}

void waitForDMADone(){
    // Wait until the GPU's DMA unit has finished sending data and is ready.
    while (DMA_CHCR(DMA_GPU) & DMA_CHCR_ENABLE){
        __asm__ volatile("");
    }
}

void waitForVSync(void){
    // The GPU doesn't directly say when its done rendering a frame, but it does tell the "interrupt controller".
    // We can read the contents of the interrupt controller's flags and see if the vblank flag is set.
    // if it is, we can reset (acknowledge) it so it can be set again by the GPU after the next frame.
    while(!(IRQ_STAT & (1 << IRQ_VSYNC))){
        __asm__ volatile("");
    }
    IRQ_STAT = ~(1 << IRQ_VSYNC);
}

void sendLinkedList(const void *data){
    waitForDMADone();

    // Make sure the pointer is aligned to 32 bits (4 bytes).
    // The DMA engine cannot read unaligned data.
    assert(!((uint32_t) data % 4));

    // Give DMA a pointer to the beginning of the data and tell it to send it in linked list mode.
    // The DMA unit will start parsing a chain of "packets" from RAM.
    // Each packet is made up of a 32-bit header followed by zero or more 32-bit GP0 commands.
    DMA_MADR(DMA_GPU) = (uint32_t) data;
    DMA_CHCR(DMA_GPU) = DMA_CHCR_WRITE | DMA_CHCR_MODE_LIST | DMA_CHCR_ENABLE;
}

void sendVRAMData(const void *data, int x, int y, int w, int h){
    waitForDMADone();
    assert(!((uint32_t) data % 4));

    // How many 32-bit words need to be sent to send the whole texture?
    // If more than 16 words, split the transfer into sets of 16 words.

    size_t length = (w * h) / 2;
    size_t chunkSize, numChunks;

    if(length < DMA_MAX_CHUNK_SIZE) {
        chunkSize = length;
        numChunks = 1;
    } else {
        chunkSize = DMA_MAX_CHUNK_SIZE;
        numChunks = length / DMA_MAX_CHUNK_SIZE;
        // Make sure it is an exact multiple of 16 words.
        assert(!(length % DMA_MAX_CHUNK_SIZE));
    }
    
    // Put the GPU into VRAM upload mode.
    waitForGP0Ready();
    GPU_GP0 = gp0_vramWrite();
    GPU_GP0 = gp0_xy(x,y);
    GPU_GP0 = gp0_xy(w, h);

    // Give DMA a pointer to the data and tell it to send the data in slice (chunked) mode.
    DMA_MADR(DMA_GPU) = (uint32_t) data;
    DMA_BCR (DMA_GPU) = chunkSize | (numChunks << 16);
    DMA_CHCR(DMA_GPU) = DMA_CHCR_WRITE | DMA_CHCR_MODE_SLICE | DMA_CHCR_ENABLE;

}

void clearOrderingTable(uint32_t *table, int numEntries) {
	// Set up the OTC DMA channel to transfer a new empty ordering table to RAM.
	// The table is always reversed and generated "backwards" (the last item in
	// the table is the first one that will be written), so we must give DMA a
	// pointer to the end of the table rather than its beginning.
	DMA_MADR(DMA_OTC) = (uint32_t) &table[numEntries - 1];
	DMA_BCR (DMA_OTC) = numEntries;
	DMA_CHCR(DMA_OTC) = 0
		| DMA_CHCR_READ | DMA_CHCR_REVERSE | DMA_CHCR_MODE_BURST
		| DMA_CHCR_ENABLE | DMA_CHCR_TRIGGER;

	// Wait for DMA to finish generating the table.
	while (DMA_CHCR(DMA_OTC) & DMA_CHCR_ENABLE)
		__asm__ volatile("");
}

// As we're using an ordering table, allocatePacket() now takes the packet's Z
// index (i.e. the index of the "bucket" to link it to) as an argument. The
// table is reversed, so packets with higher Z values will be drawn first and
// between two packets with the same Z index the most recently added one will
// take precedence.
uint32_t *allocatePacket(DMAChain *chain, int zIndex, int numCommands) {
	uint32_t *ptr      = chain->nextPacket;
	chain->nextPacket += numCommands + 1;

	// Ensure the index is within valid range.
	assert(zIndex >= 0);
    assert((zIndex < ORDERING_TABLE_SIZE));

	// Splice the new packet into the ordering table by:
	// - taking the address the ordering table entry currently points to;
	// - replacing that address with a pointer to the packet;
	// - linking the packet to the old address.
	*ptr = gp0_tag(numCommands, (void *) chain->orderingTable[zIndex]);
	chain->orderingTable[zIndex] = gp0_tag(0, ptr);

	assert(chain->nextPacket < &(chain->data)[CHAIN_BUFFER_SIZE]);

	return &ptr[1];
}

void uploadTexture(
    TextureInfo *info, const void *data, int x, int y, int w, int h
){
    // Make sure the size is valid as the GPU doesn't support textures larger than 256x256
    assert((w <= 256) && (h <= 256));

    // Upload the texture into VRAM and wait.
    sendVRAMData(data, x, y, w, h);
    waitForDMADone();

    // Update the "texpage" attribute.
    // This tells the GPU which texture page the texture is within.
    // It also handles color depth and how semitransparent pixels are blended.
    info->page = gp0_page(
        x / 64,
        y / 256, 
        GP0_BLEND_SEMITRANS,
        GP0_COLOR_16BPP
    );


    // Calculate the UV coordinates relative to the top-left corner of the texture page they are in.
    info->u = (uint8_t) (x % 64);
    info->v = (uint8_t) (y % 256);
    info->w = (uint16_t) w;
    info->h = (uint16_t) h;
}

void uploadIndexedTexture(
    TextureInfo *info, const void *image, int x, int y, int w, int h,
    const void *palette, int paletteX, int paletteY, GP0ColorDepth colorDepth
    ){
    // Make sure the size is valid as the GPU doesn't support textures larger than 256x256
    assert((w <= 256) && (h <= 256));

    // Dertimine how large the palette is and how squished the image will be.
    int numColors    = (colorDepth == GP0_COLOR_8BPP) ? 256 : 16;
    int widthDivider = (colorDepth == GP0_COLOR_8BPP) ?   2 :  4;

    // Make sure the palette is aligned correctly within VRAM and does not exceed its bounds.
    assert(!(paletteX % 16) && ((paletteX + numColors) <= 1024));

    // Upload the texture into VRAM and wait.
    sendVRAMData(image, x, y, w / widthDivider, h);
    waitForDMADone();
    sendVRAMData(palette, paletteX, paletteY, numColors, 1);
    waitForDMADone();

    // Update the "texpage" and CLUT attributes.
    // This tells the GPU which texture page the texture is within.
    // It also handles color depth and how semitransparent pixels are blended.
    info->page = gp0_page(
        x / 64,
        y / 256, 
        GP0_BLEND_SEMITRANS,
        colorDepth
    );
    info->clut = gp0_clut(paletteX / 16, paletteY);


    // Calculate the UV coordinates relative to the top-left corner of the texture page they are in.
    info->u = (uint8_t) ((x % 64) * widthDivider);
    info->v = (uint8_t) (y % 256);
    info->w = (uint16_t) w;
    info->h = (uint16_t) h;
}
