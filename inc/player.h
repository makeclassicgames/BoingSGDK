/**
 * Player.h: Store all the player data structures and prototypes
 */
#ifndef _H_PLAYER
#define _H_PLAYER

#include <genesis.h>

//Input Mode
typedef enum input{
    //Up Button
    UP,
    //Down Button
    DOWN,
    //Start Button
    START,
    //A Button
    A,
    //No Button Pushed
    NONE
}Input;

//Player Mode Enum
typedef enum player_mode{
    //IA Mode (Single Player)
    IA,
    //Player Mode (2 Player Mode)
    PLAYER
} PlayerMode;

//Player Struct
typedef struct
{
    //Player's Sprite
    Sprite * sprite;
    //Player's marquer Sprite
    Sprite * marc;
    //X Coord
    u16 x;
    //Y Coord
    u16 y;
    //Player's Score
    s16 score;
    //Player Input
    Input input;
    //Player Mode
    PlayerMode playerMode;
} Player;


//Init Player
//Parameters:
//player-> player's pointer
//x-> x coord in pixels
//y-> y coord in pixels
void initPlayer(Player* ,u16,u16,PlayerMode);

//Update player Logic
//Parameters:
//player -> player's pointer
void updatePlayer(Player*);

//Draw player Logic
//Parameters:
//player -> player's pointer
void drawPlayer(Player*);

//Check Player Collision
//Parameters:
// Player-> player's Pointer
//x -> x position in pixels
//y -> y position in pixels
//w -> width in pixels
//h-> height in pixels
//Returns: -1 upper collision, 1 downer collision, 0 no collision
s8 isTouchingPaddle(Player*,u16, u16, u16, u16);

#endif