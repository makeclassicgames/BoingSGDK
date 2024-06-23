#ifndef _H_PLAYER
#define _H_PLAYER

#include <genesis.h>

typedef enum input
{
    NONE,
    UP,
    DOWN,
    START,
    A
}Input;

typedef enum player_mode{
    PLAYER,
    IA
}PlayerMode;

typedef struct
{
    Sprite *sprite;
    Sprite *points;
    u16 x;
    u16 y;
    s16 score;
    Input input;
    PlayerMode playerMode;
} Player;

void initPlayer(Player *, u16 , u16 , PlayerMode);

s8 isTouchingPaddle(Player *, u16,u16,u16,u16);

//Only For game Loop
void updatePlayer(Player *);

void updateMenuPlayer(Player* );

void drawPlayer(Player *);

void deInitPlayer(Player *);

#endif