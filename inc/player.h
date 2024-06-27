#ifndef _H_PLAYER
#define _H_PLAYER

#include <genesis.h>

typedef enum input{
    UP,
    DOWN,
    START,
    A,
    NONE
}Input;

typedef enum player_mode{
    IA,
    PLAYER
} PlayerMode;

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


void initPlayer(Player* ,u16,u16,PlayerMode);

void updatePlayer(Player*);

void drawPlayer(Player*);

s8 isTouchingPaddle(Player*,u16, u16, u16, u16);

#endif