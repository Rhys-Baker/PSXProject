#pragma once

#include <stdint.h>
#include "gpu.h"

#define FONT_FIRST_TABLE_CHAR '!'
#define FONT_SPACE_WIDTH      4
#define FONT_TAB_WIDTH        32
#define FONT_LINE_HEIGHT      10

#define FONT_WIDTH       96
#define FONT_HEIGHT      56

typedef struct {
	uint8_t x, y, width, height;
} SpriteInfo;

#ifdef __cplusplus
extern "C" {
#endif

void printString(
	DMAChain *chain, const TextureInfo *font, int x, int y, const char *str
);

#ifdef __cplusplus
}
#endif

