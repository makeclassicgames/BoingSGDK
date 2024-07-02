#ifndef _H_GAME
#define _H_GAME

#include <genesis.h>

#include "player.h"

    typedef enum state{
        INIT_LOGO,
        LOGO,
        INIT_MENU,
        MENU,
        INIT_GAME,
        LOOP_GAME,
        GAME_OVER,
        PAUSE
    }Status;

    typedef struct{
        Sprite * sprite;
        Sprite * impactSpr;
        s16 x;
        s16 y;
        s16 dx;
        s16 dy;
        bool launched;
        bool impact;
        bool bounced;
        bool goalhit;
        bool paddlehit;
    }Ball;

    struct 
    {
       Player player1;
       Player player2;
       Ball ball;
       Status state;
       u8 lastScore;
       bool singlePlayer;
    }game;

    struct{
        Sprite* menuSel1;
        Sprite* menuSel2;
        bool twoPlayers;
    }menuStruct;

    u16 frameCounter;

    void initLogo(void);
    void drawInitLogo(void);
    void updateLogo(void);
    void drawLogo(void);
    void initMenu(void);
    void drawInitMenu(void);

    void updateMenu(void);
    void drawMenu(void);

    void initGame();

    void updateGame();

    void drawGame();

    void drawInitGame();

    void updateBall();

    void drawBall();

    void deInitGame();

    void updateGameOver();
    void drawGameOver();

    Input checkInput(u16);
    Input iaInput();

#endif