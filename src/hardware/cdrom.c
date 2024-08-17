#include "cdrom.h"

#include "registers.h"
#include "system.h"

bool cdromInterruptReady = false;

void  *cdromReadDataPtr;
size_t cdromReadDataSectorSize;
size_t cdromReadDataNumSectors;

uint8_t cdromResponse[16];
uint8_t cdromRespLength;
uint8_t cdromStatus;

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

    cdromInterruptReady = true;
}

void issueCDROMCommand(uint8_t cmd, const uint8_t *arg, size_t argLength) {
    cdromInterruptReady = false;
    while (CDROM_HSTS & CDROM_HSTS_BUSYSTS)
        __asm__ volatile("");

    CDROM_ADDRESS = 1;
    CDROM_HCLRCTL = CDROM_HCLRCTL_CLRPRM; // Clear parameter buffer
    delayMicroseconds(3);

    while (CDROM_HSTS & CDROM_HSTS_BUSYSTS)
        __asm__ volatile("");

    CDROM_ADDRESS = 0;
    for (; argLength > 0; argLength--)
        CDROM_PARAMETER = *(arg++);

    CDROM_COMMAND = cmd;
}

void convertLBAToMSF(MSF *msf, uint32_t lba) {
    lba += 150; // Add TOC pregap

    msf->minute = toBCD(lba / (75 * 60));
    msf->second = toBCD((lba / 75) % 60);
    msf->frame  = toBCD(lba % 75);
}

void cdromINT1(void){
    // Do something to handle this interrupt.
    DMA_MADR(DMA_CDROM) = (uint32_t) cdromReadDataPtr;
    DMA_BCR(DMA_CDROM)  = cdromReadDataSectorSize / 4;
    DMA_CHCR(DMA_CDROM) = DMA_CHCR_ENABLE | DMA_CHCR_TRIGGER;

    cdromReadDataPtr = (void *) (
        (uintptr_t) cdromReadDataPtr + cdromReadDataSectorSize
    );
    if (!(--cdromReadDataNumSectors))
        issueCDROMCommand(CDROM_PAUSE, NULL, 0);
    return;
}
void cdromINT2(void){
    // Do something to handle this interrupt.
    return;
}
void cdromINT3(void){
    // Do something to handle this interrupt.
    cdromStatus = cdromResponse[0];
    cdromInterruptReady=true;
    return;
}
void cdromINT4(void){
    // Do something to handle this interrupt.
    uint8_t args[] = {2};
    issueCDROMCommand(0x03, args, 1); // Go back to the start
    return;
}
void cdromINT5(void){
    // Do something to handle this interrupt.
    return;
}