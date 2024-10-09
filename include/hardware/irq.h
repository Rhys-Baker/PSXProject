#pragma once
#include <stdbool.h>

extern bool vblank;

void initIRQ(void);

void interruptHandlerFunction(void *arg);

void handleCDROMIRQ(void);
