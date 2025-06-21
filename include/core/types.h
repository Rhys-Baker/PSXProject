#pragma once
#include <stdint.h>


/// @brief Stores a 2D vector in 20.12 fixed-point format
typedef struct Vector2{
    int32_t x, y;
} Vector2;

typedef struct Vector2_16{
    int16_t x, y;
} Vector2_16;
static inline Vector2 Vector2_16toVector2(Vector2_16 v){
    return (Vector2){v.x, v.y};
}
static inline Vector2_16 Vector2toVector2_16(Vector2 v){
    return (Vector2_16){v.x, v.y};
}

/// @brief Stores a 3D vector in 20.12 fixed-point format
typedef struct Vector3{
    int32_t x, y, z;
} Vector3;

// Shape definitions

typedef struct Tri2{
    Vector2_16 a, b, c;
    uint32_t z;
} Tri2;
typedef struct Tri2_flat{
    Vector2_16 a, b, c;
    uint32_t z;
    uint32_t colour;
} Tri2_flat;
typedef struct Tri2_shaded{
    Vector2_16 a, b, c;
    uint32_t z;
    uint32_t acol, bcol, ccol;
} Tri2_shaded;
typedef struct Tri2_texturedFlat {
    Vector2_16 a, b, c;
    uint32_t z;
    Vector2 auv, buv, cuv;
    int32_t textureIndex;
} Tri2_texturedFlat;
typedef struct Tri2_texturedShaded {
    Vector2_16 a, b, c;
    uint32_t z;
    Vector2 auv, buv, cuv;
    uint32_t acol, bcol, ccol;
    int32_t textureIndex;
} Tri2_texturedShaded;

typedef struct Tri3{
    Vector3 a, b, c;
} Tri3;
typedef struct Tri3_flat{
    Vector3 a, b, c;
    uint32_t colour;
} Tri3_flat;
typedef struct Tri3_shaded{
    Vector3 a, b, c;
    uint32_t acol, bcol, ccol;
} Tri3_shaded;
typedef struct Tri3_texturedFlat {
    Vector3 a, b, c;
    Vector2 auv, buv, cuv;
    int32_t textureIndex;
} Tri3_texturedFlat;
typedef struct Tri3_texturedShaded {
    Vector3 a, b, c;
    Vector2 uva, uvb, uvc;
    uint32_t acol, bcol, ccol;
    int32_t textureIndex;
} Tri3_texturedShaded;


typedef struct Quad2{
    Vector2_16 a, b, c, d;
    uint32_t z;
} Quad2;
typedef struct Quad2_texturedFlat{
    Vector2_16 a, b, c, d;
    Vector2 auv, buv, cuv, duv;
    int32_t textureIndex;
    uint32_t z;
} Quad2_texturedFlat;

typedef struct Quad3{
    Vector3 a, b, c, d;
} Quad3;
typedef struct Quad3_texturedFlat{
    Vector3 a, b, c, d;
    Vector2 auv, buv, cuv, duv;
    int32_t textureIndex;
} Quad3_texturedFlat;



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