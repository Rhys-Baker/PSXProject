#pragma once

#include <stdint.h>
#include "ps1/gpucmd.h"

#define DMA_MAX_CHUNK_SIZE 16
#define CHAIN_BUFFER_SIZE 32768
#define ORDERING_TABLE_SIZE 720

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