#include "irq.h"

#include <stdio.h>
#include <stddef.h>

#include "cdrom.h"

#include "registers.h"
#include "system.h"

bool vblank = false;

// Sets the global vblank variable to true.
void handleVSyncIRQ(void){
    vblank = true;
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

// This is the first step to handling the IRQ.
// It will acknowledge the interrupt on the COP0 side, and call the relevant handler for the device.
void interruptHandlerFunction(void *arg) {
    if(acknowledgeInterrupt(IRQ_VSYNC)){
        handleVSyncIRQ();
    }
    if(acknowledgeInterrupt(IRQ_CDROM)){
        handleCDROMIRQ();
    }
}

void initIRQ(){
    installExceptionHandler();
    // This is the function that is called when an interrupt is raised.
    // You can also pass an argument to this handler.
    setInterruptHandler(interruptHandlerFunction, NULL);
    // The IRQ mask specifies which interrupt sources are actually allowed to raise an interrupt.
    IRQ_MASK = (1 << IRQ_VSYNC) | (1 << IRQ_CDROM);
    enableInterrupts();
}