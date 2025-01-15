#pragma once

#include <stdint.h>

#define FIXED_OFFSET 12
#define FIXED_ONE (1<<FIXED_OFFSET)


static inline int16_t fixed16_mul(int16_t a, int16_t b){
    return (int16_t) ((int32_t) a * b)>>FIXED_OFFSET;
}
static inline int32_t fixed32_mul(int32_t a, int32_t b){
    return (int32_t) ((int64_t) a * b)>>FIXED_OFFSET;
}

// Are you sure you need to use this function? Its very slow.
static inline int16_t fixed16_div(int16_t a, int16_t b){
    return (int16_t) ((int32_t) (a<<FIXED_OFFSET) / (int32_t) (b<<FIXED_OFFSET));
}

// Are you sure you need to use this function? Its very VERY slow.
static inline int32_t fixed32_div(int32_t a, int32_t b){
    return (int32_t) ((int64_t) (a<<FIXED_OFFSET) / (int64_t) (b<<FIXED_OFFSET));
}