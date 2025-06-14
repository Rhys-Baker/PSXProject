#pragma once
#include <stdint.h>

// Define RELEASE to disable debug features
#ifndef RELEASE

#define debug(...) printf("debug: "__VA_ARGS__)

#endif

uint32_t hsv_to_rgb(int h);