/**
 * Game.h: This file contains all the data structures and function prototypes for the game logic and draw
 */
#ifndef _H_GAME
#define _H_GAME

#include <genesis.h>

#include "player.h"
    /**
     * Game State
     */
    typedef enum state{
        //Init Logo Screen
        INIT_LOGO,
        //Logo Screen
        LOGO,
        //Init Menu Screen
        INIT_MENU,
        //Menu Screen
        MENU,
        //Init Game Screen
        INIT_GAME,
        //Game Loop
        LOOP_GAME,
        //Game Over Screen
        GAME_OVER,
        PAUSE
    }Status;
    //Ball Struct: Contains all the information needed for the ball
    typedef struct{
        //Ball Sprite
        Sprite * sprite;
        //Impact Sprite (bounced)
        Sprite * impactSpr;
        //X position in pixels
        s16 x;
        //Y position in pixels
        s16 y;
        //X displacement in pixels
        s16 dx;
        //Y displacement in pixels
        s16 dy;
        //True when the ball is launched
        bool launched;
        //True when the ball is bounced
        bool impact;
        //True when the ball bounced through the wall
        bool bounced;
        //True when the ball hit one of the lateral.
        bool goalhit;
        //True when the ball hit one player paddle
        bool paddlehit;
    }Ball;

    //Game Logic Struct: Store all the Game Logic
    struct 
    {
       //Player 1
       Player player1;
       //Player 2
       Player player2;
       //Game Ball
       Ball ball;
       //Game State
       Status state;
       //Last Player Score
       u8 lastScore;
       //True when the game is One Player
       bool singlePlayer;
    }game;

    //Menu Struct: Store all the Menu Logic variables
    struct{
        //Menu Selector 1
        Sprite* menuSel1;
        //Menu Selector 2
        Sprite* menuSel2;
        //True when two player is selected
        bool twoPlayers;
    }menuStruct;

    //Frame Counter for Logo Screen
    u16 frameCounter;

    //Init the Logo Screen variables
    void initLogo(void);
   
    //Update for the Logo Status wait for the 240 seconds.
    void updateLogo(void);


    //Init the Menu variables
    void initMenu(void);


    //Update the menu Screen: check the input and move the selector
    void updateMenu(void);


    //Init the Game with all the componentes to the initial status.
    void initGame();

    //Update the game (Game Loop Status)
    void updateGame();

    //Update the Ball Logic
    void updateBall();
    //Update the GameOver Status
    void updateGameOver();

     //Draw the Initial Logo Screen using a FadeIn
    void drawInitLogo(void);
    //Check that the 240 seconds has passed and show a Fade Out
    void drawLogo(void);
    //Draw the Initial Menu Screen
    void drawInitMenu(void);

    //Draw the Menu screen: move the Selector Sprites and if the
    // Start Button is pressed change the status to INIT_GAME
    void drawMenu(void);
    
    //Draw the Loop Game Status
    void drawGame();

    //Draw Init Game Status
    void drawInitGame();

    //Draw the current Ball Status
    void drawBall();

    //De Initialize the Game Values
    void deInitGame();

    //Draw the Game Over
    void drawGameOver();

    //Check Current Input From Joy Pad
    //parameters:
    //JoyPad: Joypad Number (JOY_1...JOY_8)
    Input checkInput(u16);
    //Check current Input From IA
    Input iaInput();

#endif