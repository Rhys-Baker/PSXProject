#include "util.h"

uint32_t hsv_to_rgb(int h) {
    uint8_t r, g, b;
    r = g = b = 0; // Initialise to 0 to prevent uninitialised values.
    // Ensure H is within 0-359
    h = h % 360;

    // Scale up for integer math
    int region = h / 60;       // Integer part of H / 60
    int remainder = h % 60;    // Remainder of H / 60
    int p = 0;                 // Min value (S = V = 100%)
    int q = (255 * (60 - remainder)) / 60;  // Falling edge
    int t = (255 * remainder) / 60;         // Rising edge

    // Assign RGB based on region
    switch (region) {
        case 0: r = 255; g = t;   b = p;   break; // Red to Yellow
        case 1: r = q;   g = 255; b = p;   break; // Yellow to Green
        case 2: r = p;   g = 255; b = t;   break; // Green to Cyan
        case 3: r = p;   g = q;   b = 255; break; // Cyan to Blue
        case 4: r = t;   g = p;   b = 255; break; // Blue to Magenta
        case 5: r = 255; g = p;   b = q;   break; // Magenta to Red
    }
    uint32_t rgb = 0;
    rgb += r;
    rgb += g << 8;
    rgb += b << 16;
    return rgb;
}