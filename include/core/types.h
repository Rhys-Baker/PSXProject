#pragma once
#include <stdint.h>


/// @brief Stores a 2D vector in 20.12 fixed-point format
typedef struct Vector2{
    int32_t x, y;
} Vector2;

/// @brief Stores a 3D vector in 20.12 fixed-point format
typedef struct Vector3{
    int32_t x, y, z;
} Vector3;


#define COYOTE_TIME 10
typedef struct Player2{
    Vector2 position;
    Vector2 velocity;
    bool isGrounded;
    int coyoteTimer;
} Player2;
typedef struct Player3{
    Vector2 position;
    Vector3 velocity;
    bool isGrounded;
    int coyoteTimer;
} Player3;