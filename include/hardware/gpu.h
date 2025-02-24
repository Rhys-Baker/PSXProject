#pragma once

#include <stdint.h>
#include "ps1/gpucmd.h"

#include "types.h"

#define DMA_MAX_CHUNK_SIZE 16
#define CHAIN_BUFFER_SIZE 65536
#define ORDERING_TABLE_SIZE 2048

#define SCREEN_WIDTH     320
#define SCREEN_HEIGHT    256

typedef struct{
    uint32_t data[CHAIN_BUFFER_SIZE];
    uint32_t orderingTable[ORDERING_TABLE_SIZE];
    uint32_t *nextPacket;
} DMAChain;

typedef struct {
    uint8_t u, v;
    uint16_t w, h;
    uint16_t page, clut;
} TextureInfo;

typedef struct Triangle{
    Point2 A, B, C;
} Triangle;
typedef struct Rectangle{
    Point2 A, B, C, D;
} Rectangle;



// the X and Y of the buffer we are currently using.
extern int bufferX;
extern int bufferY;
// The pointer to the DMA packet.
// We allocate space for each packet before we use it.
extern uint32_t *dmaPtr;
extern DMAChain dmaChains[2];
extern DMAChain *activeChain;
extern bool usingSecondFrame;

#ifdef __cplusplus
extern "C" {
#endif

void initGPU(void);
void setupGPU(GP1VideoMode mode, int width, int height);
void waitForGP0Ready(void);
void waitForDMADone(void);
void waitForVSync(void);

void sendLinkedList(const void *data);
void sendVRAMData(const void *data, int x, int y, int w, int h);
void clearOrderingTable(uint32_t *table, int numEntries);
uint32_t *allocatePacket(DMAChain *chain, int zIndex, int numCommands);

void uploadTexture(
    TextureInfo *info, const void *data, int x, int y, int w, int h
);
void uploadIndexedTexture(
    TextureInfo *info, const void *image, int x, int y, int w, int h,
    const void *palette, int paletteX, int paletteY, GP0ColorDepth colorDepth
);

#ifdef __cplusplus
}
#endif