#pragma once

#include <stdint.h>

#include "assert.h"

#define FIXED_OFFSET 12
#define FIXED_ONE (1<<FIXED_OFFSET)


static inline int16_t fixed16_mul(int16_t a, int16_t b){
    return (int16_t)(((int64_t)a * b) >> FIXED_OFFSET);
}

static inline int32_t fixed32_mul(int32_t a, int32_t b){
    int64_t product = ((int64_t)a * b) >> FIXED_OFFSET;
    //if (product > INT32_MAX) return INT32_MAX;
    //if (product < INT32_MIN) return INT32_MIN;
    return (int32_t)product;
}

// Are you sure you need to use this function? Its very slow.
static inline int16_t fixed16_div(int16_t a, int16_t b) {
    assert(b != 0);

    int32_t numerator = (int32_t)a << FIXED_OFFSET;
    return (int16_t)(numerator / (int32_t)b);
}

// Are you sure you need to use this function? Its very VERY slow.
static inline int32_t fixed32_div(int32_t a, int32_t b) {
    assert(b != 0);

    int64_t numerator = (int64_t)a << FIXED_OFFSET;
    return (int32_t)(numerator / (int64_t)b);
}