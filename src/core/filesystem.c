#include "filesystem.h"
#include "cdrom.h"
#include <stdlib.h>

// Internal global variable for this lib. Hides away the rootDirData for internal use.
uint8_t rootDirData[2048];


void initFilesystem(void){
    getRootDirData(&rootDirData);
}

// Reads specifically the LBA that points to the root directory.
// You must pass it a pointer to the pvdSector data.
// It sets the LBA and returns the size of the directory.
uint32_t getRootDirLba(uint8_t *pvdSector, uint32_t *LBA){
    *LBA = int32_LM(pvdSector, 158);
    uint32_t size = int32_LM(pvdSector, 166);
    return size;
}

// Get the name, length, and LBA of a directory record.
// Returns 1 if it is the end of the directory list.
int parseDirRecord(uint8_t *dataSector, uint8_t *recordLength, DirectoryEntry *directoryEntry){
    *recordLength = dataSector[0];
    directoryEntry->lba = int32_LM(dataSector, 2);
    directoryEntry->length = int32_LM(dataSector, 10);
    if(*recordLength < 1){
        return 1; // End of list
    }
    if(dataSector[33] == 0x00){
        directoryEntry->name[0] = '.';
        directoryEntry->name[1] = '\0';
        return 0; // Working Dir
    }
    if(dataSector[33] == 0x01){
        directoryEntry->name[0] = '.';
        directoryEntry->name[1] = '.';
        directoryEntry->name[2] = '\0';
        return 0; // Parent Dir
    }
    __builtin_memcpy(directoryEntry->name, &dataSector[33], dataSector[32]);
    directoryEntry->name[dataSector[32]] = '\0';

    directoryEntry->fileSize[0] = (
        (uint32_t)(dataSector[10] << 24) |
        (uint32_t)(dataSector[11] << 16) |
        (uint32_t)(dataSector[12] <<  8) |
        (uint32_t)(dataSector[13])
    );
    directoryEntry->fileSize[1] = (
        (uint32_t)(dataSector[14] << 24) |
        (uint32_t)(dataSector[15] << 16) |
        (uint32_t)(dataSector[16] <<  8) |
        (uint32_t)(dataSector[17])
    );
    return 0;
}


// Gets the 2048 bytes that make up the root directory
void getRootDirData(void *rootDirData){
   uint8_t buffer[2048];
   uint32_t rootDirLBA;
   // Read the PVD sector into ram
   startCDROMRead(
      16,
      buffer,
      sizeof(buffer) / 2048,
      2048,
      true,
      true
   );

   // Get the LBA for the root directory.
   getRootDirLba(buffer, &rootDirLBA);

   // Read the contents of the root directory.
   startCDROMRead(
      rootDirLBA,
      rootDirData,
      1,
      2048,
      true,
      true
   );
}

#include <stdio.h>

/// @brief Get the LBA to the file with a given filename, assuming it is stored in the root directory.
/// @param rootDirData Pointer to the root directory data.
/// @param filename String containing the filename of the requested file.
/// @param fileSize Pointer to the first of two numbers in an array. Basically a 64-bit number
/// @return LBA to file or 0 if not found.
uint32_t getLbaToFile(const char *filename, uint32_t fileSize[2]){
    DirectoryEntry directoryEntry;
    uint8_t  recLen;
    int offset = 0;
    while(offset < 2048){
        if(parseDirRecord(
            &rootDirData[offset],
            &recLen,
            &directoryEntry
        )){
           break;
        }
        offset += recLen;

        if(!__builtin_strcmp(directoryEntry.name, filename)){
            if(fileSize != NULL){
                fileSize[0] = directoryEntry.fileSize[0];
                fileSize[1] = directoryEntry.fileSize[1];
            }
            return directoryEntry.lba;
        }
    }
    return 0;
}



// FileStream functions

FileStream *FileStream_open(const char *filename){
    if(!filename) return NULL;
    FileStream *s;
    uint32_t lba = getLbaToFile(filename, NULL);
    if(lba == 0){
        return NULL;
    }
    s = malloc(sizeof(FileStream));
    s->fileLBA = lba;
    s->sectorIndex = 0;
    startCDROMRead(
        s->fileLBA + s->sectorIndex,
        s->buffer,
        1, 2048,
        true, true
    );
    return s;
}
void FileStream_close(FileStream *s){
    if(!s) return;
    free(s);
}
void FileStream_seek(FileStream *s, uint32_t offset){
    if(!s) return;
    s->globalOffset = offset;
    uint32_t expectedSector = offset >> 11;

    // If the sector we want to read is not currently loaded, load the required sector
    if (expectedSector != s->sectorIndex){
        s->sectorIndex = expectedSector;
        startCDROMRead(
            s->fileLBA + s->sectorIndex,
            s->buffer,
            1, 2048,
            true, true
        );
    }
}
uint8_t FileStream_read8(FileStream *s){
    if(!s) return 0;
    uint32_t sectorOffset = s->globalOffset & 2047;  // % 2048
    uint32_t expectedSector = s->globalOffset >> 11; // / 2048 

    // If the sector we want to read is not currently loaded, load the required sector
    if (expectedSector != s->sectorIndex){
        s->sectorIndex = expectedSector;
        startCDROMRead(
            s->fileLBA + s->sectorIndex,
            s->buffer,
            1, 2048,
            true, true
        );
    }

    // Read the byte we want
    uint8_t v = s->buffer[sectorOffset];
    s->globalOffset++;
    return v;
}
uint16_t FileStream_read16(FileStream *s){
    if(!s) return 0;
    uint16_t v;
    v = (
        FileStream_read8(s) |
        FileStream_read8(s) << 8
    );
    return v;
}
uint32_t FileStream_read32(FileStream *s){
    if(!s) return 0;
    uint32_t v;
    v = (
        FileStream_read8(s)       |
        FileStream_read8(s) << 8  |
        FileStream_read8(s) << 16 |
        FileStream_read8(s) << 24
    );
    return v;
}
void FileStream_readBytes(FileStream *s, void *dest, uint32_t n){
    if(!s) return;
    if(!dest) return;
    for(int i=0; i<n; i++){
        ((uint8_t*)dest)[i] = FileStream_read8(s);
    }
}
