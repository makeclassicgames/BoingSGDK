#ifndef _H_GAME
#define _H_GAME

#include <genesis.h>
#include "globals.h"
#include "player.h"
#include "physics.h"

#define MAX_SCORE 10

typedef enum state
{
    INIT_MENU,
    MENU,
    INIT_GAME,
    LOOP_GAME,
    GAME_OVER,
    PAUSE
} Status;

typedef struct
{
    Sprite * sprite;
    Sprite * impactSprt;
    s16 x;
    s16 y;
    s16 dx;
    s16 dy;
    bool launched;
    bool impact;
} Ball;

struct
{
    Player player1;
    Player player2;
    Ball ball;
    Status state;
    u8 lastScore;
    bool singlePlayer;
} Game;

struct{
    Sprite * selector1;
    Sprite * selector2;
    bool twoPlayers;
}Menu;

//general Functions
void updateGame();
void drawGame();

//InitMenu
void drawInitMenu();

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

//Restart Game Options
void restartGame();
void deInitGame();

//Input Functions
Input checkGamepadInput(u16);
Input iaInput();
//Collisions Functions



#endif