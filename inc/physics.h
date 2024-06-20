#ifndef _H_PHYSICS
#define _H_PHYSICS
#include <genesis.h>


#define PLAYER_SPEED 3

#define BALL_SPEED 5

#define PADDLE_WIDTH 8
#define PADDLE_HEIGHT 57

#define TOP_EDGE 0
#define BOTTOM_EDGE 216
#define LEFT_EDGE 0
#define RIGHT_EDGE 312

#define EDGE_WIDTH 320
#define EDGE_HEIGHT 8
#define LATERAL_EDGE_WIDTH 8
#define LATERAL_EDGE_HEIGHT 224

#define CHANGE_SING(n) return -n

//Check Collisions
bool isTouchingTop(u16, u16,u16,u16);
bool isTouchingBottom(u16,u16,u16,u16);

bool isTouchingLeftEdge(u16,u16,u16,u16);
bool isTouchingRightEdge(u16,u16,u16,u16);

#endif