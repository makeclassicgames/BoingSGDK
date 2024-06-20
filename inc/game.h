#ifndef _H_GAME
#define _H_GAME

#include <genesis.h>
#include "globals.h"
#include "player.h"
#include "physics.h"


typedef enum state
{
    MENU,
    INIT_GAME,
    LOOP_GAME,
    GAME_OVER,
    PAUSE
} Status;

typedef struct
{
    Sprite * sprite;
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

//general Functions
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
Input checkGamepadInput(u16);
//Collisions Functions


#endif