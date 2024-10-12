#pragma once
#include <stdint.h>
#include "gte.h"
#include "gpu.h"

typedef struct Vert{
    int16_t x, y, z;
    int16_t _;
} Vert;
typedef struct Tri{
    uint16_t a ,auv,
             b, buv,
             c ,cuv;
} Tri;
typedef struct Model{
    uint16_t numVerts;
    uint16_t numTris;
    Vert    *verts;
    Tri     *tris;
} Model;


/// @brief Load a model from a file on disc. The .verts and .tris properties will be set. It is important to free these as they are allocated on the heap. Use model_destroy() to do this.
/// @param name Filename for the model.
/// @param model Pointer to a model struct to store the data.
/// @return 0 if successful, otherwise error code.
size_t model_load(const char *name, Model *model);

/// @brief Render the model with the given texture mapped to its UVs
/// @param model Pointer to the model to render
/// @param texture Pointer to the TextureInfo of the texture to map.
void model_renderTextured(Model *model, TextureInfo *texture);

// TODO: Check that this is okay to do with invalid pointers. Will free() break if I pass some other pointer?

/// @brief Free the allocated pointers and set values to 0.
/// @param model Pointer to the model to destroy.
void model_destroy(Model *model);