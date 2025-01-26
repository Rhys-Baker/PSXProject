#pragma once

#include <stdint.h>
#include "types.h"

#define CONTENTS_EMPTY -1
#define CONTENTS_SOLID -2


typedef struct BSPPlane {
	Vector2 normal;
	uint32_t distance;
} BSPPlane;

typedef struct BSPNode {
    uint16_t planeNum;
    int16_t children[2];
} BSPNode;

typedef struct BSPTree {
	BSPPlane *planes;
	BSPNode *nodes;
	uint32_t numPlanes;
	uint32_t numNodes;
} BSPTree;


/// @brief Calculate what type of space the given point is within.
/// @param bspTree Pointer to the `BSPTree` to compare with
/// @param num Index of the node to start from
/// @param p Point to check
/// @return Negative number denoting the type of space.
int BSPPointContents(BSPTree *bspTree, int num, Point2 p);
