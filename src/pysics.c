#include "physics.h"

bool isTouchingTop(u16 x, u16 y, u16 width, u16 height)
{
    // check Box Collision with Top Edge
    // Box 1
    u16 box1_x1 = x;
    u16 box1_y1 = y;
    u16 box1_x2 = x + width;
    u16 box1_y2 = y + height;

    // Box 2

    u16 box2_x1 = TOP_EDGE;
    u16 box2_y1 = TOP_EDGE;
    u16 box2_x2 = TOP_EDGE + EDGE_WIDTH;
    u16 box2_y2 = TOP_EDGE + EDGE_HEIGHT;

    if ((box1_x1 <= box2_x2) &&
        (box1_x2 >= box2_x1) &&
        (box1_y1 <= box2_y2) &&
        (box1_y2 >= box2_y1))
        return TRUE;
    else
        return FALSE;
}

bool isTouchingBottom(u16 x, u16 y, u16 width, u16 height)
{
    // Check Box Collision with Bottom Edge
      // check Box Collision with Top Edge
    // Box 1
    u16 box1_x1 = x;
    u16 box1_y1 = y;
    u16 box1_x2 = x + width;
    u16 box1_y2 = y + height;

    // Box 2

    u16 box2_x1 = TOP_EDGE;
    u16 box2_y1 = BOTTOM_EDGE;
    u16 box2_x2 = TOP_EDGE + EDGE_WIDTH;
    u16 box2_y2 = BOTTOM_EDGE + EDGE_HEIGHT;
    
    if ((box1_x1 <= box2_x2) &&
        (box1_x2 >= box2_x1) &&
        (box1_y1 <= box2_y2) &&
        (box1_y2 >= box2_y1))
        return TRUE;
    else
        return FALSE;
}

bool isTouchingLeftEdge(u16 x, u16 y, u16 width, u16 height){
     // Box 1
    u16 box1_x1 = x;
    u16 box1_y1 = y;
    u16 box1_x2 = x + width;
    u16 box1_y2 = y + height;

    // Box 2

    u16 box2_x1 = LEFT_EDGE;
    u16 box2_y1 = LEFT_EDGE;
    u16 box2_x2 = LEFT_EDGE + LATERAL_EDGE_WIDTH;
    u16 box2_y2 = LEFT_EDGE + LATERAL_EDGE_HEIGHT;
    
    if ((box1_x1 <= box2_x2) &&
        (box1_x2 >= box2_x1) &&
        (box1_y1 <= box2_y2) &&
        (box1_y2 >= box2_y1))
        return TRUE;
    else
        return FALSE;
}

bool isTouchingRightEdge(u16 x,u16 y,u16 width,u16 height){
 // Box 1
    u16 box1_x1 = x;
    u16 box1_y1 = y;
    u16 box1_x2 = x + width;
    u16 box1_y2 = y + height;

    // Box 2

    u16 box2_x1 = RIGHT_EDGE;
    u16 box2_y1 = 0;
    u16 box2_x2 = RIGHT_EDGE + LATERAL_EDGE_WIDTH;
    u16 box2_y2 = RIGHT_EDGE + LATERAL_EDGE_HEIGHT;
    
    if ((box1_x1 <= box2_x2) &&
        (box1_x2 >= box2_x1) &&
        (box1_y1 <= box2_y2) &&
        (box1_y2 >= box2_y1))
        return TRUE;
    else
        return FALSE;
}

bool isTouchingPaddle(u16 x, u16 y, u16 width, u16 height)
{

    return FALSE;
}
