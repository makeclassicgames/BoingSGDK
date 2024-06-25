/**
 * Hello World Example
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>
#include "game.h"

void init();

void checkInputs();

void update();

void draw();

int main()
{
    init();
    while (1)
    {
        checkInputs();
        update();

        draw();
        SPR_update();
        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}

void init()
{
    VDP_setScreenWidth320();
    JOY_init();
    SPR_init();
    game.state = INIT_MENU;
    //TODO: Change using menu
    game.singlePlayer=TRUE;
}

void checkInputs(){
    game.player1.input=checkInput(JOY_1);
    if(!game.singlePlayer){
        game.player2.input=checkInput(JOY_2);
    }else{
        //TODO: IA MODE
    }
}

void update()
{
    switch (game.state)
    {
    case INIT_MENU:
    case MENU:
    case INIT_GAME:
        initGame();
        break;
    case LOOP_GAME:
        updateGame();
    default:
        break;
    }
}

void draw()
{
    switch (game.state)
    {
    case INIT_MENU:
    case MENU:
    case INIT_GAME:
        drawInitGame();
        game.state=LOOP_GAME;
        break;
    case LOOP_GAME:
        drawGame();
    default:
        break;
    }
}
