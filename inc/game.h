#ifndef _H_GAME
#define _H_GAME

#include <genesis.h>
#include "player.h"


typedef enum state
{
    MENU,
    INIT_GAME,
    LOOP_GAME,
    GAME_OVER
} Status;

typedef struct
{
    u16 x;
    u16 y;
    u16 dx;
    u16 dy;
} Ball;

struct
{
    Player player1;
    Player player2;
    Ball ball;
    Status state;
} Game;

//general Functions
void initGame();
void updateGame();
void drawGame();

//Init Game Functions
void updateMenu();
void drawMenu();

//Start Game Functions
void initGame();
void drawInitializedGame();

//Loop Game Functions
void updateLoop();
void drawLoop();

//Game Over Functions
void updateGameOver();
void drawGameOver();

//Input Functions
Input checkInput(u16 joyPad);

//Collisions Functions


#endif