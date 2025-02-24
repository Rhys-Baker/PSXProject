#pragma once

#include <stdlib.h>
#include "fixedPoint.h"
#include "trig.h"
#include "types.h"

// Arctan function
// Approximate atan2 using a lookup table
static inline int16_t atan2_fixed(int16_t y, int16_t x) {
    if (x == 0) return (y > 0) ? (90 << 12) : -90 << 12; // Vertical case

    int16_t absY = y < 0 ? -y : y;
    int16_t absX = x < 0 ? -x : x;
    int16_t angle = fixed16_div(absY, absX); // Compute y/x in fixed-point

    if (x < 0) {
        if (y < 0)
            return (-180 << 12) + angle; // Quadrant III
        else
            return (180 << 12) - angle;  // Quadrant II
    } else {
        if (y < 0)
            return -angle; // Quadrant IV
        else
            return angle;  // Quadrant I
    }
}



/// @brief Calculate the 2D cross-product of a `Vector2` and a `Point2`
/// @param v The `Vector2` in 4.12 fixed-point format
/// @param p The `Point2` in 20.12 fixed-point format
/// @return The 2D cross-product calculated
static inline int32_t cross2VectorPoint(Vector2 v, Point2 p){
    return ((v.x*(p.y>>16))<<12)-((v.y*(p.x>>16))<<12);
}

/// @brief Calculate the 2D dot-product of a `Vector2` and a `Point2`
/// @param v The `Vector2` in 4.12 fixed-point format
/// @param p The `Point2` in 20.12 fixed-point format
/// @return The 2D dot-product calculated
static inline int32_t dot2VectorPoint(Vector2 v, Point2 p){
    int32_t result = (fixed32_mul(v.x, p.x) + fixed32_mul(v.y, p.y));
    return result;
}

/// @brief Calculate the 2D dot-product of two `Vector2`
/// @param a The first `Vector2` in 4.12 fixed-point format
/// @param b The second `Vector2` in 4.12 fixed-point format
/// @return The 2D dot-product calculated
static inline int32_t dot2VectorVector(Vector2 a, Vector2 b){
    int32_t result = (fixed32_mul(a.x, a.x) + fixed32_mul(b.y, b.y));
    return result;
}

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

// Vector operations

static inline Vector2 addVector2(Vector2 a, Vector2 b){
    return (Vector2){a.x + b.x, a.y + b.y};
}
static inline Vector2 subVector2(Vector2 a, Vector2 b){
    return (Vector2){a.x - b.x, a.y - b.y};
}
static inline Vector2 scaleVector2(Vector2 v, int32_t s){ // 4.12
    return (Vector2){fixed32_mul(v.x, s), fixed32_mul(v.y, s)};
}
static inline int32_t dotVector2(Vector2 a, Vector2 b){
    return fixed32_mul(a.x, b.x) + fixed32_mul(a.y, b.y);
}