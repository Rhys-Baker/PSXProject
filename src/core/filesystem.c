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
    memcpy(&directoryEntry->name, &dataSector[33], dataSector[32]);
    directoryEntry->name[dataSector[32]] = '\0';
    return 0;
}

// Gets the 2048 bytes that make up the root directory
void getRootDirData(uint8_t *rootDirData){
   uint8_t *buffer[2048];
   uint32_t rootDirLBA;
   
   // Read the PVD sector into ram
   startCDROMRead(
      16,
      buffer,
      sizeof(buffer) / 2048,
      2048,
      true
   );
   waitForINT1();

   // Get the LBA for the root directory.
   int rootDirSize = getRootDirLBA(buffer, &rootDirLBA);

   // Read the contents of the root directory.
   startCDROMRead(
      rootDirLBA,
      rootDirData,
      sizeof(rootDirData) / 2048,
      2048,
      true
   );
   waitForINT1();
   // Pause the CDROM.
   issueCDROMCommand(CDROM_PAUSE, NULL, 0);
   waitForINT3();
}