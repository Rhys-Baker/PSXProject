#pragma once
#include <stdint.h>
#include "camera.h"
#include "gpu.h"
#include "gte.h"

#define MODEL_SCALE_MULTIPLIER (8)

extern int numPrims;
extern int maxNumVerts;


typedef struct Vert{
    int16_t x, y, z;
    int16_t _;
} Vert;
typedef struct Tri{
    uint16_t a;
    uint8_t  av, au;

    uint16_t b;
    uint8_t  bv, bu;

    uint16_t c;
    uint8_t  cv, cu;
} Tri;
typedef struct Model{
    uint16_t numVerts;
    uint16_t numTris;
    Vert    *verts;
    Tri     *tris;
} Model;

typedef struct TransformedVert{
    uint32_t XY;
    uint32_t  Z;
} TransformedVert;

extern TransformedVert *transformedVerts;


/// @brief Load a model from a file on disc. The .verts and .tris properties will be set. It is important to free these as they are allocated on the heap. Use model_destroy() to do this.
/// @param name Filename for the model.
/// @param model Pointer to a model struct to store the data.
/// @return 0 if successful, otherwise error code.
size_t model_load(const char *name, Model *model);

/// @brief Render the model with the given texture mapped to its UVs
/// @param model Pointer to the model to render
/// @param texture Pointer to the TextureInfo of the texture to map.
void model_renderTextured(Model *model, TextureInfo *texture, Camera *cam, uint16_t rotX, uint16_t rotY, uint16_t rotZ, int32_t tX, int32_t tY, int32_t tZ);

// TODO: Check that this is okay to do with invalid pointers. Will free() break if I pass some other pointer?

/// @brief Free the allocated pointers and set values to 0.
/// @param model Pointer to the model to destroy.
void model_destroy(Model *model);