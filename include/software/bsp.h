#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "types.h"

#define FIXED_EPSILON (1<<7) // 4096 * 0.03125 == 128

#define CONTENTS_EMPTY -1
#define CONTENTS_SOLID -2

////////////////////////////////
// 2D BSP Tree and Collisions //
////////////////////////////////

typedef struct BSPPlane2d {
	Vector2 normal;
	int32_t distance;
} BSPPlane2;

typedef struct BSPNode2d {
    Vector2 normal;
	int32_t distance;
    int16_t children[2];
} BSPNode2;

typedef struct BSPTree2d {
	BSPPlane2 *planes;
	BSPNode2 *nodes;
	uint32_t numPlanes;
	uint32_t numNodes;
} BSPTree2;

/// @brief Calculate what type of space the given point is within.
/// @param bspTree Pointer to the `BSPTree` to compare with
/// @param num Index of the node to start from
/// @param p Point to check
/// @return Negative number denoting the type of space.
int32_t BSPTree2_pointContents (BSPTree2 *bspTree, int num, Vector2 p);
/// @brief Trace a line through a node.
/// @param bspTree Pointer to the BSP tree.
/// @param node_num The node being traced. Negative for leaf nodes.
/// @param p1 Start of the line being traced. Must lie within the node.
/// @param p2 End of the line being traced. Must lie within the node.
/// @param intersection The first point on the line segment `p1` -> `p2` that is in a solid.
/// @param normal Normal vector of the wall intersected with.
/// Not set if the line lies entirely in empty space.
/// @return `true` if the line hits a solid object. `false` if the line lies entirely in empty space.
bool BSPTree2_recursiveCast(BSPTree2 *bspTree, int node_num, Vector2 p1, Vector2 p2, Vector2 *intersection, Vector2 *intersectionNormal);
/// @brief Use raycasts to handle a collision/slide with a wall.
/// @param bspTree Pointer to the BSP tree.
/// @param startPoint Start point of the movement.
/// @param endPoint End point of the movement.
/// @param result Final coordinate of the movement.
void BSPTree2_handleCollision(BSPTree2 *bspTree, Vector2 startPoint, Vector2 endPoint, Vector2 *result);
/// @brief Move the player and collide/slide against BSP tree sectors
/// @param bspTree Pointer to the BSP tree
/// @param player Pointer to the player to move
void Player2_move(BSPTree2 *bspTree, Player2 *player);


////////////////////////////////
// 3D BSP Tree and Collisions //
////////////////////////////////

typedef struct BSPPlane3 {
	Vector3 normal;
	int32_t distance;
} BSPPlane3;

typedef struct BSPNode3 {
    Vector3 normal;
	int32_t distance;
    int16_t children[2];
} BSPNode3;

typedef struct BSPTree3 {
	BSPPlane3 *planes;
	BSPNode3 *nodes;
	uint32_t numPlanes;
	uint32_t numNodes;
} BSPTree3;

int32_t BSPTree3_pointContents (BSPTree3 *bspTree, int num, Vector2 p);
bool BSPTree3_recursiveCast(BSPTree3 *bspTree, int node_num, Vector2 p1, Vector2 p2, Vector2 *intersection, Vector2 *intersectionNormal);
void Player3_move(BSPTree3 *bspTree, Player3 *player);

