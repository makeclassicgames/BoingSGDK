#ifndef _H_PHYSICS
#define _H_PHYSICS
#define PLAYER_SPEED 3
#define BALL_SPEED 4

#define PADDLE_WIDTH 8
#define PADDLE_HEIGHT 57

#define TOP_EDGE 0
#define TOP_EDGE_Y 0
#define EDGE_WIDTH 320
#define EDGE_HEIGHT 8

#define BOTTOM_EDGE 216
#define LATERAL_EDE 312

#define LATERAL_EDGE_WITH 8
#define LATERAL_EDGE_HEIGHT 224

typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} BoxCollider;

#define CHANGE_SING(n) -n

bool isColliding(BoxCollider *, BoxCollider*);

bool isTouchingTop(u16, u16, u16, u16);
bool isTouchingBottom(u16, u16, u16, u16);

bool isTouchingLeftEdge(u16,u16,u16,u16);
bool isTouchingRightEdge(u16,u16,u16,u16);

#endif