#include <genesis.h>
#include "globals.h"
#include "game.h"
#include "gfx.h"
#include "sprt.h"

Input checkInput(u16 joy)
{
    u16 value = JOY_readJoypad(joy);
    if (value & BUTTON_UP)
    {
        return UP;
    }
    else
    {
        if (value & BUTTON_DOWN)
        {
            return DOWN;
        }
    }

    if (value & BUTTON_A)
    {
        return A;
    }

    if (value & BUTTON_START)
    {
        return START;
    }

    return NONE;
}

void initGame()
{
    game.player1.x = PLAYER1_INITIAL_X;
    game.player1.y = PLAYER_INITIAL_Y;
    game.player2.x = PLAYER2_INITIAL_X;
    game.player2.y = PLAYER_INITIAL_Y;
    game.ball.x = BALL_INITIAL_X;
    game.ball.y = BALL_INITIAL_Y;
}
void updateGame(){
    updatePlayer(&game.player1);
    updatePlayer(&game.player2);
}

void drawInitGame(){
    u16 index = TILE_USER_INDEX;
    SYS_disableInts();
    VDP_drawImageEx(BG_A,&table,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,index),
    0,0,TRUE,DMA);
    PAL_setPalette(PAL1,bat1.palette->data,CPU);
    PAL_setPalette(PAL2, pal2.data,CPU);
    PAL_setPalette(PAL3, ball.palette->data,CPU);
    SYS_enableInts();
    game.player1.sprite = SPR_addSprite(&bat1,game.player1.x, game.player1.y, TILE_ATTR(PAL1,FALSE,FALSE,FALSE));
    game.player2.sprite = SPR_addSprite(&bat1, game.player2.x, game.player2.y, TILE_ATTR(PAL2,FALSE,FALSE,TRUE));
    game.ball.sprite = SPR_addSprite(&ball, game.ball.x, game.ball.y,TILE_ATTR(PAL3,FALSE,FALSE,FALSE));
}

//loop Game

void drawGame(){
    drawPlayer(&game.player1);
    drawPlayer(&game.player2);
}