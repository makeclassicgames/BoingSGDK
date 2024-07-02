/**
 * Physics.h: Store all the Physics and collision detection logic
 */
#ifndef _H_PHYSICS
#define _H_PHYSICS

//Player Speed (pixels/frame)
#define PLAYER_SPEED 3
//Ball Speed (Pixels/frame)
#define BALL_SPEED 4

//Paddle collision width
#define PADDLE_WIDTH 8
//Paddle collision height
#define PADDLE_HEIGHT 57

//Top/Bottom edge Box variables

//Top Edge X in Pixels
#define TOP_EDGE 0

//Top Edge X in Pixels
#define TOP_EDGE_Y 0
//Edge Width
#define EDGE_WIDTH 320
//Edge height
#define EDGE_HEIGHT 8

//Botom Edge x
#define BOTTOM_EDGE 216

//Lateral Collision Box Variables

//Lateral EDGE 
#define LATERAL_EDE 312

//Lateral Edge Width
#define LATERAL_EDGE_WITH 8
//Lateral Edge Height
#define LATERAL_EDGE_HEIGHT 224

//BoxCollider Struct
typedef struct {
    //X Position in pixels
    u16 x;
    //Y Position in pixels
    u16 y;
    //Width Position in pixels
    u16 w;
    //Height Position in pixels
    u16 h;
} BoxCollider;

//Change Sign Macro
//Paramter: n
//return -1
#define CHANGE_SING(n) -n

//Check if a BoxCollider is colliding to another
//Parameters:
//Box1: Box Collider 1
//Box2: Box Collider 2
bool isColliding(BoxCollider *, BoxCollider*);

//Check if a boxCollider is touching top Edge
//parameters:
//X-> X parameter in pixels
//Y-> Y parameter in pixels
//w-> Width in pixels
//h-> height in pixels
bool isTouchingTop(u16, u16, u16, u16);

//Check if a boxCollider is touching Bottom Edge
//parameters:
//X-> X parameter in pixels
//Y-> Y parameter in pixels
//w-> Width in pixels
//h-> height in pixels
bool isTouchingBottom(u16, u16, u16, u16);

//Check if a boxCollider is touching Left Edge
//parameters:
//X-> X parameter in pixels
//Y-> Y parameter in pixels
//w-> Width in pixels
//h-> height in pixels
bool isTouchingLeftEdge(u16,u16,u16,u16);

//Check if a boxCollider is touching Right Edge
//parameters:
//X-> X parameter in pixels
//Y-> Y parameter in pixels
//w-> Width in pixels
//h-> height in pixels
bool isTouchingRightEdge(u16,u16,u16,u16);

#endif