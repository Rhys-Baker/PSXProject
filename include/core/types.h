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


typedef struct Tri2{
    Vector2 a, b, c;
    uint32_t z;
} Tri2;
typedef struct Tri3{
    Vector3 a, b, c;
} Tri3;

typedef struct Quad2{
    Vector2 a, b, c, d;
    uint32_t z;
} Quad2;
typedef struct Quad3{
    Vector3 a, b, c, d;
} Quad3;

#define COYOTE_TIME 10
typedef struct Player2{
    Vector2 position;
    Vector2 velocity;
    bool isGrounded;
    int coyoteTimer;
} Player2;
typedef struct Player3{
    Vector3 position;
    Vector3 velocity;
    bool isGrounded;
    int coyoteTimer;
} Player3;