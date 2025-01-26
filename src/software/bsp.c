#include "bsp.h"

#include <assert.h>
#include "math.h"

int32_t BSPPointContents (BSPTree *bspTree, int num, Point2 p){
	int32_t fdot;
	BSPNode *node;
	BSPPlane *plane;
	while (num >= 0){
		assert(num < bspTree->numNodes && num >= 0);
        
		node = &bspTree->nodes[num];
		plane = &bspTree->planes[node->planeNum];
       
		fdot = dot2VectorPoint(plane->normal, p);

        fdot -= plane->distance;
        if(fdot < 0){
            num = node->children[1];
        } else {
            num = node->children[0];
        }
	}
    return num;
}
#include <stdio.h>
bool BSPRecursiveCast(BSPTree *bspTree, int node_num, Point2 p1, Point2 p2, Point2 *intersection){
    // Handle leaves
    if(node_num == CONTENTS_SOLID) {
        intersection->x = p1.x;
        intersection->y = p1.y;
        return true;
    } else if(node_num == CONTENTS_EMPTY) {
        intersection->x = p2.x;
        intersection->y = p2.y;
        return false; // Completely empty, so hit nothing.
    }

    BSPNode *node = &bspTree->nodes[node_num];
    BSPPlane *plane = &bspTree->planes[node->planeNum];
    int32_t t1 = dot2VectorPoint(plane->normal, p1) - plane->distance;
    int32_t t2 = dot2VectorPoint(plane->normal, p2) - plane->distance;
    
    // Handle cases where the entire line is within a single child.
    if(t1 >= 0 && t2 >= 0){
        return BSPRecursiveCast(bspTree, node->children[0], p1, p2, intersection);
    }
    if(t1 < 0 && t2 < 0){
        return BSPRecursiveCast(bspTree, node->children[1], p1, p2, intersection);
    }

    int32_t frac = fixed32_div(t1, (t1-t2)); // TODO: Fix divide-by-zero when parallel!
    Point2 mid;
    mid.x = p1.x + fixed32_mul(frac, (p2.x - p1.x));
    mid.y = p1.y + fixed32_mul(frac, (p2.y - p1.y));

    // `side` gives the child containing `p1`.
    int32_t side = (t1 >= 0) ? 0 : 1;

    // Trace through child nodes in order
    if (BSPRecursiveCast(bspTree, node->children[side], p1, mid, intersection)){
        return true;
    }
    
    return BSPRecursiveCast(bspTree, node->children[1 - side], mid, p2, intersection);
}