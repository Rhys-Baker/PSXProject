/*
 * (C) 2024 Rhys Baker
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#pragma once
#include <stdint.h>

// Constants for the speed and sensitivity of our camera
#define CAMERA_SENSITIVITY 10
#define MOVEMENT_SPEED 4

// Somewhere to store the Sine and Cosine of the camera's yaw value.
// This saves us from recalculating it multiple times per frame.
//int16_t yawSin;
//int16_t yawCos;

typedef struct {
   int32_t x, y, z;
   int16_t pitch, roll, yaw;
   uint32_t forward[3], up[3], right[3];
} Camera;
