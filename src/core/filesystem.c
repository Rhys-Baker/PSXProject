#include "filesystem.h"
#include "cdrom.h"

// Reads specifically the LBA that points to the root directory.
// You must pass it a pointer to the pvdSector data.
// It sets the LBA and returns the size of the directory.
uint32_t getRootDirLBA(uint8_t *pvdSector, uint32_t *LBA){
    *LBA = int32_LM(pvdSector, 158);
    uint32_t size = int32_LM(pvdSector, 166);
    return size;
}

// Get the name, length, and LBA of a directory record.
// Returns 1 if it is the end of the directory list.
int parseDirRecord(uint8_t *dataSector, char *name, uint8_t *recordLength, uint32_t *dataLength, uint32_t *LBA){

    *recordLength = dataSector[0];
    *LBA = int32_LM(dataSector, 2);
    *dataLength = int32_LM(dataSector, 10);
    if(*recordLength < 1){
        return 1; // End of list
    }
    if(dataSector[33] == 0x00){
        name[0] = '.';
        name[1] = '\0';
        return 0; // Working Dir
    }
    if(dataSector[33] == 0x01){
        name[0] = '.';
        name[1] = '.';
        name[2] = '\0';
        return 0; // Parent Dir
    }
    memcpy(name, &dataSector[33], dataSector[32]);
    name[dataSector[32]] = '\0';
    return 0;
}