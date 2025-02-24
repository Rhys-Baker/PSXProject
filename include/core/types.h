#pragma once
#include <stdint.h>


/// @brief Stores a 2D vector in 20.12 fixed-point format
typedef struct Vector2{
    int32_t x, y;
} Vector2;

/// @brief Stores a 3D vector in 4.12 fixed-point format
typedef struct Vector3{
    int16_t x, y, z, _;
} Vector3;


/// @brief Stores a 2D point in 20.12 fixed-point format
typedef struct Point2 {
    int32_t x, y;
} Point2;


#define COYOTE_TIME 10
typedef struct Player{
    Point2 position;
    Vector2 velocity;
    bool isGrounded;
    int coyoteTimer;
} Player;