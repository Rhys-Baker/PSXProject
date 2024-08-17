#include "irq.h"

#include <stddef.h>

#include "cdrom.h"

#include "registers.h"
#include "system.h"

bool vblank = false;

void initIRQ(){
    installExceptionHandler();
   setInterruptHandler(interruptHandlerFunction, NULL);
   IRQ_MASK = (1 << IRQ_VSYNC) | (1 << IRQ_CDROM);
   enableInterrupts();
}

void handleVSyncIRQ(void){
   vblank = true;
}

void interruptHandlerFunction(void *arg) {
   if(acknowledgeInterrupt(IRQ_VSYNC)){
      handleVSyncIRQ();
   }
   if(acknowledgeInterrupt(IRQ_CDROM)){
      handleCDROMIRQ();
   }
}


void handleCDROMIRQ(void) {
    CDROM_ADDRESS = 1;
    uint8_t irqType = CDROM_HINTSTS & (0
        | CDROM_HINT_INT0
        | CDROM_HINT_INT1
        | CDROM_HINT_INT2);

    // If a new sector is available, request a sector buffer read.
    if (irqType == IRQ_DATA_READY) {
        CDROM_ADDRESS = 0;
        CDROM_HCHPCTL = 0;
        CDROM_HCHPCTL = CDROM_HCHPCTL_BFRD;
    }

    CDROM_ADDRESS = 1;
    CDROM_HCLRCTL = 0 // Acknowledge all IRQs
        | CDROM_HCLRCTL_CLRINT0
        | CDROM_HCLRCTL_CLRINT1
        | CDROM_HCLRCTL_CLRINT2;
    CDROM_HCLRCTL = CDROM_HCLRCTL_CLRPRM; // Clear parameter buffer
    delayMicroseconds(3);

    cdromRespLength = 0;

    while (CDROM_HSTS & CDROM_HSTS_RSLRRDY)
        cdromResponse[cdromRespLength++] = CDROM_RESULT;

    switch (irqType) {
        case IRQ_DATA_READY:
            cdromINT1();
            break;
        case IRQ_BLOCKING_CMD_DONE:
            cdromINT2();
            break;
        case IRQ_CMD_ACKNOWLEDGE:
            cdromINT3();
            break;
        case IRQ_TRACK_END:
            cdromINT4();
            break;
        case IRQ_ERROR:
            cdromINT5();
            break;
    }
}
