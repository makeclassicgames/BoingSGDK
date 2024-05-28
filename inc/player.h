#ifndef _H_PLAYER
#define _H_PLAYER

#include <genesis.h>

typedef enum input
{
    NONE,
    UP,
    DOWN,
    START
}Input;

typedef enum player_mode{
    PLAYER,
    IA
}PlayerMode;

typedef struct
{
    Sprite *sprite;
    u16 x;
    u16 y;
    u8 score;
    Input input;
    PlayerMode playerMode;
} Player;

void updatePlayer(Player *, u8);

void drawPlayer(Player *, u8);

#endif