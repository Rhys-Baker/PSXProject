#pragma once
#include <stdbool.h>

extern bool vblank;

void initIRQ(void *stream);

void interruptHandlerFunction(void *arg);

void handleCDROMIRQ(void);
