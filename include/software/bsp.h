#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "types.h"

#define FIXED_EPSILON (1<<7) // 4096 * 0.03125 == 128

#define CONTENTS_EMPTY -1
#define CONTENTS_SOLID -2


extern uint32_t testHue;

typedef struct BSPPlane {
	Vector2 normal;
	int32_t distance;
} BSPPlane;

typedef struct BSPNode {
    Vector2 normal;
	int32_t distance;
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
int32_t BSPPointContents (BSPTree *bspTree, int num, Point2 p);


/// @brief Trace a line through a node.
/// @param bspTree Pointer to the BSP tree.
/// @param node_num The node being traced. Negative for leaf nodes.
/// @param p1 Start of the line being traced. Must lie within the node.
/// @param p2 End of the line being traced. Must lie within the node.
/// @param intersection The first point on the line segment `p1` -> `p2` that is in a solid.
/// @param normal Normal vector of the wall intersected with.
/// Not set if the line lies entirely in empty space.
/// @return `true` if the line hits a solid object. `false` if the line lies entirely in empty space.
bool BSPRecursiveCast(BSPTree *bspTree, int node_num, Point2 p1, Point2 p2, Point2 *intersection, Vector2 *intersectionNormal);

/// @brief Use raycasts to handle a collision/slide with a wall.
/// @param bspTree Pointer to the BSP tree.
/// @param startPoint Start point of the movement.
/// @param endPoint End point of the movement.
/// @param result Final coordinate of the movement.
void BSPHandleCollision(BSPTree *bspTree, Point2 startPoint, Point2 endPoint, Point2 *result);