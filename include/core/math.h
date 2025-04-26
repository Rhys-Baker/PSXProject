#pragma once

#include <stdlib.h>
#include "fixedPoint.h"
#include "trig.h"
#include "types.h"


////////////////////////
// Integer operations //
////////////////////////

static inline int16_t  max16s(int16_t a,  int16_t b) {return ((a > b) ? a : b);}
static inline uint16_t max16u(uint16_t a, uint16_t b){return ((a > b) ? a : b);}
static inline int32_t  max32s(int32_t a,  int32_t b) {return ((a > b) ? a : b);}
static inline uint32_t max32u(uint32_t a, uint32_t b){return ((a > b) ? a : b);}

static inline int16_t  min16s(int16_t a,  int16_t b) {return ((a > b) ? b : a);}
static inline uint16_t min16u(uint16_t a, uint16_t b){return ((a > b) ? b : a);}
static inline int32_t  min32s(int32_t a,  int32_t b) {return ((a > b) ? b : a);}
static inline uint32_t min32u(uint32_t a, uint32_t b){return ((a > b) ? b : a);}


//////////////////////////
// 2D Vector operations //
//////////////////////////

/// @brief Rotate a vector by some number of radians
/// @param v Vector to rotate
/// @param theta 2.14 signed fixed-point radians to rotate by
/// @return Rotated Vector
static inline Vector2 rotateVector2(Vector2 v, int16_t theta) {
    Vector2 result;
    int16_t sin = isin(theta);
    int16_t cos = icos(theta);
    result.x = (v.x * cos - v.y * sin) >> 12; // Right-shift to adjust Fixed-Point scale
    result.y = (v.x * sin + v.y * cos) >> 12;
    return result;
}

static inline Vector2 Vector2_add(Vector2 a, Vector2 b){
    return (Vector2){a.x + b.x, a.y + b.y};
}
static inline Vector2 Vector2_sub(Vector2 a, Vector2 b){
    return (Vector2){a.x - b.x, a.y - b.y};
}
static inline Vector2 Vector2_scale(Vector2 v, int32_t s){ // 4.12
    return (Vector2){fixed32_mul(v.x, s), fixed32_mul(v.y, s)};
}
static inline int32_t Vector2_dot(Vector2 a, Vector2 b){
    return fixed32_mul(a.x, b.x) + fixed32_mul(a.y, b.y);
}
static inline int32_t Vector2_cross(Vector2 a, Vector2 b) {
    return ((a.x * b.y) >> 12) - ((a.y * b.x) >> 12);
}


//////////////////////////
// 3D Vector operations //
//////////////////////////

static inline Vector3 Vector3_add(Vector3 a, Vector3 b){
    return (Vector3){a.x + b.x, a.y + b.y, a.z + b.z};
}
static inline Vector3 Vector3_sub(Vector3 a, Vector3 b){
    return (Vector3){a.x - b.x, a.y - b.y, a.z - b.z};
}
static inline Vector3 Vector3_scale(Vector3 v, int32_t s){ // 4.12
    return (Vector3){fixed32_mul(v.x, s), fixed32_mul(v.y, s), fixed32_mul(v.z, s)};
}
static inline int32_t Vector3_dot(Vector3 a, Vector3 b){
    return fixed32_mul(a.x, b.x) + fixed32_mul(a.y, b.y) + fixed32_mul(a.z, b.z);
}
static inline Vector3 Vector3_cross(Vector3 a, Vector3 b) {
    return (Vector3) {
        ((a.y * b.z) >> 12) - ((a.z * b.y) >> 12), // c.x
        ((a.z * b.x) >> 12) - ((a.x * b.z) >> 12), // c.y
        ((a.x * b.y) >> 12) - ((a.y * b.x) >> 12)  // c.z
    };
}