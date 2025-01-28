#include "bsp.h"

#include <assert.h>
#include "math.h"

int32_t BSPPointContents (BSPTree *bspTree, int num, Point2 p, Vector2 *wallNormal){
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
    wallNormal->x = plane->normal.x;
    wallNormal->y = plane->normal.y;
    return num;
}
#include <stdio.h>
bool BSPRecursiveCast(BSPTree *bspTree, int node_num, Point2 p1, Point2 p2, Point2 *intersection, Vector2 *intersectionNormal){
    // Handle leaves
    if(node_num == CONTENTS_EMPTY) {
        intersection->x = p2.x;
        intersection->y = p2.y;
        intersectionNormal->x = 0;
        intersectionNormal->y = 0;
        return false; // Completely empty, so hit nothing.
    }

    if(node_num == CONTENTS_SOLID) {
        intersection->x = p1.x;
        intersection->y = p1.y;
        return true;
    }


    BSPNode *node = &bspTree->nodes[node_num];
    BSPPlane *plane = &bspTree->planes[node->planeNum];
    int32_t t1 = dot2VectorPoint(plane->normal, p1) - plane->distance;
    int32_t t2 = dot2VectorPoint(plane->normal, p2) - plane->distance;
    
    
    // Handle cases where the entire line is within a single child.
    if(t1 >= 0 && t2 >= 0){
        return BSPRecursiveCast(bspTree, node->children[0], p1, p2, intersection, intersectionNormal);
    }
    if(t1 < 0 && t2 < 0){
        return BSPRecursiveCast(bspTree, node->children[1], p1, p2, intersection, intersectionNormal);
    }

    int32_t frac = fixed32_div(t1, (t1-t2));
    Point2 mid;
    mid.x = p1.x + fixed32_mul(frac, (p2.x - p1.x));
    mid.y = p1.y + fixed32_mul(frac, (p2.y - p1.y));

    // `side` gives the child containing `p1`.
    int32_t side = (t1 >= 0) ? 0 : 1;

    intersectionNormal->x = plane->normal.x;
    intersectionNormal->y = plane->normal.y;
    // Trace through child nodes in order
    if (BSPRecursiveCast(bspTree, node->children[side], p1, mid, intersection, intersectionNormal)){
        return true;
    }
    
    intersectionNormal->x = plane->normal.x;
    intersectionNormal->y = plane->normal.y;
    return BSPRecursiveCast(bspTree, node->children[1 - side], mid, p2, intersection, intersectionNormal);
}

void BSPHandleCollision(BSPTree *bspTree, Point2 startPoint, Point2 endPoint, Point2 *result){
    Point2 newEndPoint;
    Point2 oldEndPoint;
    Point2 intersectionPoint;
    Point2 oldIntersectionPoint;
    Vector2 wallNormal;
    int32_t distancex;
    int32_t distancey;
    bool castResult;
    uint32_t maxIterations = 5;

    // Check that we aren't in a wall before doing the raycast
    if(BSPPointContents(bspTree, 0, startPoint, &wallNormal) != -2){
        castResult = BSPRecursiveCast(bspTree, 0, startPoint, endPoint, &intersectionPoint, &wallNormal);

        newEndPoint.x = endPoint.x;
        newEndPoint.y = endPoint.y;
        do{
        // Swap endpoint            
            oldEndPoint.x = newEndPoint.x;
            oldEndPoint.y = newEndPoint.y;

            // Get new endpoint location
            int32_t distancex = abs(oldEndPoint.x - intersectionPoint.x);
            int32_t distancey = abs(oldEndPoint.y - intersectionPoint.y);
            newEndPoint.x = oldEndPoint.x + fixed32_mul(distancex, (int32_t)wallNormal.x);
            newEndPoint.y = oldEndPoint.y + fixed32_mul(distancey, (int32_t)wallNormal.y);

            oldIntersectionPoint.x = intersectionPoint.x;
            oldIntersectionPoint.y = intersectionPoint.y;

        } while(
            maxIterations-- &&
            BSPRecursiveCast(bspTree, 0, oldIntersectionPoint, newEndPoint, &intersectionPoint, &wallNormal)
        );

        // Update player position

        result->x = newEndPoint.x;
        result->y = newEndPoint.y;

    } else {
        // We are inside a wall.
        // Simple solution is to shove in the direction of the wall's normal until we aren't
        // TODO: Make this better. Rather than shove some amount, maybe try shoving exactly the right amount?
        // Either way, we shouldn't find ourselves inside walls if all goes well.
        result->x -= fixed32_mul(1<<12, wallNormal.x);
        result->y -= fixed32_mul(1<<12, wallNormal.y);
    }
}