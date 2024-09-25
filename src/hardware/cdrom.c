#include <stdio.h>

#include "stdatomic.h"
#include "cdrom.h"

#include "string.h"

#include "registers.h"
#include "system.h"

bool waitingForInt1;
bool waitingForInt3;
bool waitingForInt5;

void  *cdromReadDataPtr;
size_t cdromReadDataSectorSize;
size_t cdromReadDataNumSectors;

uint8_t cdromResponse[16];
uint8_t cdromRespLength;
uint8_t cdromStatus;

#define toBCD(i) (((i) / 10 * 16) | ((i) % 10))

void initCDROM(void) {
    BIU_DEV5_CTRL = 0x00020943; // Configure bus
    DMA_DPCR |= DMA_DPCR_ENABLE << (DMA_CDROM * 4); // Enable DMA

    CDROM_ADDRESS = 1;
    CDROM_HCLRCTL = 0 // Acknowledge all IRQs
        | CDROM_HCLRCTL_CLRINT0
        | CDROM_HCLRCTL_CLRINT1
        | CDROM_HCLRCTL_CLRINT2;
    CDROM_HINTMSK_W = 0 // Enable all IRQs
        | CDROM_HCLRCTL_CLRINT0
        | CDROM_HCLRCTL_CLRINT1
        | CDROM_HCLRCTL_CLRINT2;

    CDROM_ADDRESS = 0;
    CDROM_HCHPCTL = 0; // Clear pending requests

    CDROM_ADDRESS = 2;
    CDROM_ATV0 = 128; // Send left audio channel to SPU left channel
    CDROM_ATV1 = 0;

    CDROM_ADDRESS = 3;
    CDROM_ATV2 = 128; // Send right audio channel to SPU right channel
    CDROM_ATV3 = 0;
    CDROM_ADPCTL = CDROM_ADPCTL_CHNGATV;
}

void issueCDROMCommand(uint8_t cmd, const uint8_t *arg, size_t argLength) {
    waitingForInt1 = true;
    waitingForInt3 = true;
    waitingForInt5 = true;

    while (CDROM_BUSY)
        __asm__ volatile("");
    
    CDROM_ADDRESS = 1;
    CDROM_HCLRCTL = CDROM_HCLRCTL_CLRPRM; // Clear parameter buffer
    delayMicroseconds(3);
    while (CDROM_BUSY)
        __asm__ volatile("");

    CDROM_ADDRESS = 0;
    for (; argLength > 0; argLength--)
        CDROM_PARAMETER = *(arg++);
    
    CDROM_COMMAND = cmd;
}

void waitForINT1(){
    while(waitingForInt1 && waitingForInt5){
        __asm__ volatile("");
    }
}

void waitForINT3(){
     while(waitingForInt3 && waitingForInt5){
        __asm__ volatile("");
    }
}

void convertLBAToMSF(MSF *msf, uint32_t lba) {
    lba += 150; // Add TOC pregap

    msf->minute = toBCD(lba / (75 * 60));
    msf->second = toBCD((lba / 75) % 60);
    msf->frame  = toBCD(lba % 75);
}

void startCDROMRead(uint32_t lba, void *ptr, size_t numSectors, size_t sectorSize, bool doubleSpeed) {
    cdromReadDataPtr        = ptr;
    cdromReadDataNumSectors = numSectors;
    cdromReadDataSectorSize = sectorSize;

    uint8_t mode = 0;
    MSF     msf;

    if (sectorSize == 2340)
        mode |= MODE_SECTOR_SIZE_2340;
    if (doubleSpeed)
        mode |= MODE_2X_SPEED;

    convertLBAToMSF(&msf, lba);

    issueCDROMCommand(CDROM_SETMODE, &mode, sizeof(mode));
    waitForINT3();
    issueCDROMCommand(CDROM_SETLOC, &msf, sizeof(msf));
    waitForINT3();
    issueCDROMCommand(CDROM_READN, NULL, 0);
    waitForINT3();
}

// Data is ready to be read from the CDROM via DMA.
// This will read the data into cdromReadDataPtr.
// It will also pause the CDROM drive.
void cdromINT1(void){
    DMA_MADR(DMA_CDROM) = (uint32_t) cdromReadDataPtr;
    DMA_BCR(DMA_CDROM)  = cdromReadDataSectorSize / 4;
    DMA_CHCR(DMA_CDROM) = DMA_CHCR_ENABLE | DMA_CHCR_TRIGGER;

    atomic_signal_fence(memory_order_acquire);
    cdromReadDataPtr = (void *) (
        (uintptr_t) cdromReadDataPtr + cdromReadDataSectorSize
    );
    if (!(--cdromReadDataNumSectors))
        issueCDROMCommand(CDROM_PAUSE, NULL, 0);
    atomic_signal_fence(memory_order_release);
    waitingForInt1 = false;
    return;
}

void cdromINT2(void){
    // Do something to handle this interrupt.
    return;
}

// This is usually just reading the status. It may be more than one parameter, however I don't handle that.
void cdromINT3(void){
    cdromStatus = cdromResponse[0];
    waitingForInt3 = false;
    return;
}

void cdromINT4(void){
    // Do something to handle this interrupt.
    return;
}

// This is the "Error" interrupt.
void cdromINT5(void){
    waitingForInt5 = false;
    return;
}

