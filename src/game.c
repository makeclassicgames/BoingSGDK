#include <genesis.h>
#include "globals.h"
#include "game.h"
#include "physics.h"
#include "gfx.h"
#include "sprt.h"

bool isBallNear(Ball*, Player* );

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

Input iaInput(){
    if(!game.ball.launched) return NONE;

    if(!isBallNear(&game.ball,&game.player2)){
        if(game.ball.dy<0){
            return UP;
        }else{
            return DOWN;
        }
    }

    return NONE;

}

bool isBallNear(Ball* ball, Player* player){
    BoxCollider box1= {ball->x+8,ball->y+8,13,13};
    BoxCollider box2 = {player->x-20,player->y,PADDLE_WIDTH,PADDLE_HEIGHT};

    return isColliding(&box1,&box2);
}

void initGame()
{
    game.player1.x = PLAYER1_INITIAL_X;
    game.player1.y = PLAYER_INITIAL_Y;
    game.player2.x = PLAYER2_INITIAL_X;
    game.player2.y = PLAYER_INITIAL_Y;
    game.ball.x = BALL_INITIAL_X;
    game.ball.y = BALL_INITIAL_Y;
    game.ball.launched=FALSE;
    game.ball.dx=0;
    game.ball.dx=0;
    game.player1.score=0;
    game.player2.score=0;
}
void updateGame(){
    updatePlayer(&game.player1);
    updatePlayer(&game.player2);
    updateBall();
}

void updateGameOver(){
    if(game.player1.input==START){
        game.state=INIT_MENU;
    }
}

void deInitGame(){
    VDP_clearPlane(BG_A,true);
    SPR_releaseSprite(game.ball.sprite);
    SPR_releaseSprite(game.player1.sprite);
    SPR_releaseSprite(game.player2.sprite);
    SPR_releaseSprite(game.player1.marc);
    SPR_releaseSprite(game.player2.marc);
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
    game.player1.marc = SPR_addSprite(&marc1,24,32,TILE_ATTR(PAL1,TRUE,FALSE,FALSE));
    game.player2.sprite = SPR_addSprite(&bat1, game.player2.x, game.player2.y, TILE_ATTR(PAL2,FALSE,FALSE,TRUE));
    game.player2.marc = SPR_addSprite(&marc1,296,32,TILE_ATTR(PAL1,TRUE,FALSE,FALSE));
    game.ball.sprite = SPR_addSprite(&ball, game.ball.x, game.ball.y,TILE_ATTR(PAL3,FALSE,FALSE,FALSE));
    SPR_setAnim(game.player1.marc,0);
    SPR_setAnim(game.player2.marc,0);

}

//loop Game

void drawGame(){
    drawPlayer(&game.player1);
    drawPlayer(&game.player2);
    drawBall();
}

void drawGameOver(){
    u16 index = TILE_USER_INDEX;
    VDP_drawImageEx(BG_A,&over,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,index),0,0,TRUE,DMA);
}