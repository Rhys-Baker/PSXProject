#pragma once
#include <stdbool.h>

extern bool vblank;

void initIRQ();

void interruptHandlerFunction(void *arg);

void handleCDROMIRQ(void);
