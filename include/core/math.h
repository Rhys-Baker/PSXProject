#pragma once

#include <stdlib.h>
#include "fixedPoint.h"
#include "trig.h"
#include "types.h"

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