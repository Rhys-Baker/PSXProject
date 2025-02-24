#include "bsp.h"

#include <stdio.h>
#include <assert.h>
#include "types.h"
#include "math.h"
#include "util.h"
#include "gpu.h"


////////////////////////////////
// 2D BSP Tree and Collisions //
////////////////////////////////

static inline Vector2 slideAlongWall2(Vector2 velocity, Vector2 normal){
    int32_t dot = Vector2_dot(velocity, normal);
    Vector2 proj = Vector2_scale(normal, dot);
    return Vector2_sub(velocity, proj);
}

int32_t BSPTree2_pointContents(BSPTree2 *bspTree, int num, Vector2 p){
	int32_t fdot;
	BSPNode2 *node;
	while (num >= 0){
		assert(num < bspTree->numNodes && num >= 0);
        
		node = &bspTree->nodes[num];
       
		fdot = Vector2_dot(node->normal, p);

        fdot -= node->distance;
        if(fdot < 0){
            num = node->children[1];
        } else {
            num = node->children[0];
        }
	}
    return num;
}

bool BSPTree2_recursiveCast(BSPTree2 *bspTree, int node_num, Vector2 p1, Vector2 p2, Vector2 *intersection, Vector2 *intersectionNormal){
    // TODO: Move all declarations to the top
    int32_t frac;
    Vector2 mid;
    
    // Handle leaves
    if(node_num < 0){
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
    }
    
    // TODO: Add bounds checking here.
    // If < min or > max, etc
    
    BSPNode2 *node = &bspTree->nodes[node_num];
    // Both points, which side of the wall are they on?
    int32_t t1 = Vector2_dot(node->normal, p1) - node->distance;
    int32_t t2 = Vector2_dot(node->normal, p2) - node->distance;

    // Handle cases where the entire line is within a single child.
    if(t1 >= 0 && t2 >= 0){
        return BSPTree2_recursiveCast(bspTree, node->children[0], p1, p2, intersection, intersectionNormal);
    }
    if(t1 < 0 && t2 < 0){
        return BSPTree2_recursiveCast(bspTree, node->children[1], p1, p2, intersection, intersectionNormal);
    }

    // Compute the intersection distance.
    // Offset by FIXED_EPSILON to avoid stuck-in-wall issues.
    if(t1<0){
        frac = fixed32_div(t1 + FIXED_EPSILON, (t1-t2));
    } else {
        frac = fixed32_div(t1 - FIXED_EPSILON, (t1-t2));
    }
    
    // Clamp frac to 0-1
    if(frac < 0){
        frac = 0;
    }
    if(frac > (1<<12)){
        frac = (1<<12);
    }
    
    // Calculate the midpoint.
    mid.x = p1.x + fixed32_mul(frac, (p2.x - p1.x));
    mid.y = p1.y + fixed32_mul(frac, (p2.y - p1.y));


    // `side` gives the child containing `p1` 
    int32_t side = (t1 < 0); // -x = 1 | +x = 0;

    
    // Recurse into the child node of p1->mid
    if (BSPTree2_recursiveCast(bspTree, node->children[side], p1, mid, intersection, intersectionNormal)){
        return true;
    }
    
    // If no collision is detected in p1 -> mid,
    // Try the other side of the wall.

    // If the contents of the midpoint is not solid...
    if(BSPTree2_pointContents(bspTree, node->children[1 - side], mid) != CONTENTS_SOLID){
        return BSPTree2_recursiveCast(bspTree, node->children[1 - side], mid, p2, intersection, intersectionNormal);
    }

    // The other side of this node is solid!
    // Therefore, this midpoint, is the impact point.
    
    // If the side p1 is on is the near side?
    if(!side){
        // Output the node's normal.
        intersectionNormal->x = node->normal.x;
        intersectionNormal->y = node->normal.y;
    } else {
        // Output the inverse of the node's normal.
        intersectionNormal->x = 0-node->normal.x;
        intersectionNormal->y = 0-node->normal.y;
    }
    
    // Step back while inside wall
    while(BSPTree2_pointContents(bspTree, 0, mid) == CONTENTS_SOLID){
        frac -= 410;
        if(frac < 0){
            intersection->x = mid.x;
            intersection->y = mid.y;
            return true;
        }
            
        mid.x = p1.x + fixed32_mul(frac, p2.x - p1.x);
        mid.x = p1.y + fixed32_mul(frac, p2.y - p1.y);
    }

    intersection->x = mid.x;
    intersection->y = mid.y;

    return true;
}

void BSPTree2_handleCollision(BSPTree2 *bspTree, Vector2 startPoint, Vector2 endPoint, Vector2 *result){
    Vector2 wallNormal;
    
    Vector2 prevEndPoint;
    Vector2 intersectionPoint;
    Vector2 newEndPoint;
    
    // Check to see if our starting point is in a wall.
    // If it is, we don't want to do anything at all.
    if(BSPTree2_pointContents(bspTree, 0, startPoint) == CONTENTS_SOLID){
        result->x = startPoint.x;
        result->y = startPoint.y;
        return;
    }
    
    prevEndPoint.x = startPoint.x;
    prevEndPoint.y = startPoint.y;

    newEndPoint.x = endPoint.x;
    newEndPoint.y = endPoint.y;

    // Raycast once to see where we intersect with a wall
    // If we don't intersect with any wall, great! Return the endPoint and move on.
    while(BSPTree2_recursiveCast(bspTree, 0, prevEndPoint, newEndPoint, &intersectionPoint, &wallNormal)){
        // If we did intersect with a wall, we need to move our endpoint in the direction of the wall's
        // normal until it is in line with the intersection point

        // Distance between endPoint and intersection Point
        Vector2 dist;
        dist.x = newEndPoint.x - intersectionPoint.x;
        dist.y = newEndPoint.y - intersectionPoint.y;

        int32_t dot = Vector2_dot(wallNormal, dist);

        int32_t normalMagnitudeSquared = fixed32_mul(wallNormal.x, wallNormal.x) +
                                         fixed32_mul(wallNormal.y, wallNormal.y);

        int32_t projectionFactor = fixed32_div(dot, normalMagnitudeSquared);

        Vector2 projectedVector;
        projectedVector.x = fixed32_mul(projectionFactor, wallNormal.x);
        projectedVector.y = fixed32_mul(projectionFactor, wallNormal.y);


        //Scaled by the normal vector
        newEndPoint.x = newEndPoint.x - projectedVector.x;
        newEndPoint.y = newEndPoint.y - projectedVector.y;

        // Swap the end points around
        prevEndPoint.x = intersectionPoint.x;
        prevEndPoint.y = intersectionPoint.y;
    }

    result->x = intersectionPoint.x;
    result->y = intersectionPoint.y;
}

void Player2_move(BSPTree2 *bspTree, Player2 *player){
    Vector2 prevPos = player->position;
    Vector2 nextPos = {player->position.x + player->velocity.x, player->position.y + player->velocity.y};

    Vector2 hitPoint;
    Vector2 hitNormal;

    const int maxIterations = 5;
    int iterations = 0;

    player->isGrounded = false;

    while (BSPTree2_recursiveCast(bspTree, 0, prevPos, nextPos, &hitPoint, &hitNormal)){
        if (iterations++ >= maxIterations) {
            break; // Prevent infinite loops
        }

        // Determine collision type
        if (abs(hitNormal.y) <= abs(hitNormal.x)) {  
            // Wall collision -> Slide along the wall
            player->velocity = slideAlongWall2(player->velocity, hitNormal);
        } 
        else if (hitNormal.y < abs(hitNormal.x)) {  
            // Walkable slope -> Snap to ground
            player->position = hitPoint;
            player->velocity.y = 0;  
            player->isGrounded = true;
            player->coyoteTimer = COYOTE_TIME;

            // Align movement with slope tangent
            Vector2 tangent = {-hitNormal.y, hitNormal.x}; 
            player->velocity = Vector2_scale(tangent, player->velocity.x);
        } 
        else {  
            // Ceiling or steep slope -> Slide along it
            player->velocity = slideAlongWall2(player->velocity, hitNormal);
        }

        // Update positions for next iteration
        prevPos = hitPoint;
        nextPos = (Vector2){player->position.x + player->velocity.x, player->position.y + player->velocity.y};
    }

    // Final position update
    player->position = nextPos;

    if(!player->isGrounded && player->coyoteTimer > 0){
        player->coyoteTimer--;
    }
}


////////////////////////////////
// 3D BSP Tree and Collisions //
////////////////////////////////
