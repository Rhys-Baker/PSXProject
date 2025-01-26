#include "bsp.h"

#include <assert.h>
#include "math.h"

int BSPPointContents (BSPTree *bspTree, int num, Point2 p){
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