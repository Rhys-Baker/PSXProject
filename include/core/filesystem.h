#pragma once

#include <stdint.h>

// Macros

// Read a 32-bit number in the format int32_LSB-MSB from the array, starting at startIndex
// Returns the uint32_t that is parsed.
#define int32_LM(array, startIndex) (((uint32_t)array[startIndex]) | ((uint32_t)array[startIndex+1] << 8) | ((uint32_t)array[startIndex+2] << 16) | ((uint32_t)array[startIndex+3] << 24))

// Global variables
extern uint8_t gRootDirData[2048];

// Structs

typedef struct{
   uint32_t lba;
   uint8_t length;
   uint32_t fileSize[2];
   char name[255];
} DirectoryEntry;

typedef struct FileStream {
   uint8_t buffer[2048];  // Buffer to store the current sector
   uint32_t globalOffset; // absolute file offset
   uint32_t fileLBA;      // Starting LBA on disc
   uint32_t sectorIndex;  // Currently loaded sector
} FileStream;


// Functions

void initFilesystem(void);
uint32_t getRootDirLba(uint8_t *pvdSector, uint32_t *LBA);
int parseDirRecord(uint8_t *dataSector, uint8_t *recordLength, DirectoryEntry *directoryEntry);
void getRootDirData(void *rootDirData);
uint32_t getLbaToFile(const char *filename, uint32_t fileSize[2]);


/// @brief Create a FileStream to a given filename
/// @param filename Name of the file to open
/// @return FileStream or NULL if not found
FileStream *FileStream_open(const char *filename);
/// @brief Close/Free a FileStream
/// @param s Pointer to FileStream to close
void        FileStream_close(FileStream *s);
/// @brief Seek to a given offset
/// @param s Pointer to FileStream
/// @param offset Offset from start of file
void        FileStream_seek(FileStream *s, uint32_t offset);
/// @brief Read a 1-byte uint8_t from the file and increment the global offset
/// @param s Pointer to FileStream
/// @return The value that was read
uint8_t     FileStream_read8(FileStream *s);
/// @brief Read a 2-byte uint16_t from the file and increment the global offset
/// @param s Pointer to FileStream
/// @return The value that was read
uint16_t    FileStream_read16(FileStream *s);
/// @brief Read a 4-byte uint32_t from the file and increment the global offset
/// @param s Pointer to FileStream
/// @return The value that was read
uint32_t    FileStream_read32(FileStream *s);
/// @brief Read n bytes into dest from FileStream
/// @param s Pointer to Filestream
/// @param dest Destination buffer to write data to
/// @param n number of bytes to read
void FileStream_readBytes(FileStream *s, void *dest, uint32_t n);
