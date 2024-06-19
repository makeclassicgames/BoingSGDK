/**
 * Hello World Example
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>

// includes
#include "game.h"
// Resources
#include "gfx.h"
#include "sprt.h"

void update();

void draw();

int main()
{
    // Initial State Menu
    Game.state = MENU;
    // init variables and Game
    VDP_setScreenWidth320();
    JOY_init();
    SPR_init();

    /* Sprite * selector = SPR_addSprite(&menuSel,75,132,TILE_ATTR(PAL1,FALSE,FALSE,FALSE));
     Sprite * selector2 = SPR_addSprite(&menuSel,230,132,TILE_ATTR(PAL1,FALSE,FALSE,TRUE));
     PAL_setPalette(PAL1,menuSel.palette->data,CPU);
     */
    while (1)
    {

        update();
        draw();
        // update Sprites and wait vblank
        SPR_update();
        SYS_doVBlankProcess();
    }
    return (0);
}

void update()
{

    switch (Game.state)
    {
    case MENU:
    case INIT_GAME:
        // init game
        initGame();
        break;

    default:
        break;
    }
}

void draw()
{

    switch (Game.state)
    {
    case MENU:
    case INIT_GAME:
        drawInitializedGame();
        Game.state = LOOP_GAME;
        break;

    default:
        break;
    }
}
