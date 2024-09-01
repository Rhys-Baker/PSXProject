#pragma once

#include <stdint.h>

// Macros

// Read a 32-bit number in the format int32_LSB-MSB from the array, starting at startIndex
// Returns the uint32_t that is parsed.
#define int32_LM(array, startIndex) (((uint32_t)array[startIndex]) | ((uint32_t)array[startIndex+1] << 8) | ((uint32_t)array[startIndex+2] << 16) | ((uint32_t)array[startIndex+3] << 32))


uint32_t getRootDirLBA(uint8_t *pvdSector, uint32_t *LBA);
int parseDirRecord(uint8_t *dataSector, char *name, uint8_t *recordLength, uint32_t *dataLength, uint32_t *LBA);

