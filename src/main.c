/**
 * BoingMD
 * Pong Game based on "BOING" from the book "Code The Classics Vol. 1"
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>
#include "game.h"

// Init program
void init(void);

//Check the input
void checkInputs();

//Update game logic (based on game state)
void update();

//Draw Game (Based on Game State)
void draw();

//Main Function
int main()
{
    //Init game
    init();
    //Game Loop
    while (1)
    {
        //Check the current Input
        checkInputs();
        //Update Game Logic
        update();

        draw();
        //Update SGDK Sprite Engine
        SPR_update();

        //Wait until VBLank Process (Screen Printed)
        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}

//Init the game set default properties and init hardware or the Sprite Engine
void init(void)
{
    //Set the default width screen to 320px
    VDP_setScreenWidth320();
    //Init Joy System (input)
    JOY_init();
    //Set the YM6212 Volume for FM sound (require SGDK 2.00 or later)
    XGM2_setFMVolume(80);
    //Set the PSG Volume (Require SGDK 2.00 or later)
    XGM2_setPSGVolume(80);
    //Init Sprite Engine
    SPR_init();
    //Set game State to INIT_LOGO
    game.state = INIT_LOGO;
}

//Check the Input for player 1 or player2
void checkInputs(void){
    //Check input for Player 1 using JOYPAD
    game.player1.input=checkInput(JOY_1);
    //If the game is 2 player (single player = False) get the input for player 2 using JOYPAD
    if(!game.singlePlayer){
        game.player2.input=checkInput(JOY_2);
    }else{
        //IF the game is 1 player (SInglePlayer =true) get the input using IA.
        game.player2.input=iaInput();
    }
}

//Update the game logic based on Game State
void update(void)
{
    //on Each Game State...
    switch (game.state)
    {
    case INIT_LOGO: //Init logo
        initLogo();
        break;
    case LOGO: //Show Logo (wait 4 secs)
        updateLogo();
        break;
    case INIT_MENU: //Init MEnu
        initMenu();
        break;
    case MENU: //Show Menu
        updateMenu();
        break;
    case INIT_GAME: //Init Game
        initGame();
        break;
    case LOOP_GAME: //Game Loop
        updateGame();
        break;
    case GAME_OVER: //Game Over
        updateGameOver();
        break;
    default:
        break;
    }
}

//Draw the game in each state
void draw(void)
{
    switch (game.state)
    {
    case INIT_LOGO: //Draw Initial Logo 
        drawInitLogo();
        break;
    case LOGO: //Draw the Logo and waits 4 secs
        drawLogo();
        break;
    case INIT_MENU: //Draw Initial Menu
        drawInitMenu();
        break;
    case MENU://Draw Menu changes and waits for start button
        drawMenu();
        break;
    case INIT_GAME: //Draw Init Game
        drawInitGame();
        game.state=LOOP_GAME;
        break;
    case LOOP_GAME: //Loop Game
        drawGame();
        break;
    case GAME_OVER: //Game Over
        drawGameOver();
        break;
    default:
        break;
    }
}
