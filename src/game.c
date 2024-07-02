#include <genesis.h>
#include "globals.h"
#include "game.h"
#include "physics.h"
#include "gfx.h"
#include "sprt.h"

//Check if the Ball is Near the Player
//Parameters
//Ball-> Ball struct pointer
//Player-> current player pointer
bool isBallNear(Ball*, Player* );

Input checkInput(u16 joy)
{
    //Read Current Joypad Value
    u16 value = JOY_readJoypad(joy);
    //If button UP pressed
    if (value & BUTTON_UP)
    {
        return UP;
    }
    else
    {
        //If button DOWN pressed
        if (value & BUTTON_DOWN)
        {
            return DOWN;
        }
    }

    //IF BUTTON A Pressed
    if (value & BUTTON_A)
    {
        return A;
    }

    //If Button START Pressed
    if (value & BUTTON_START)
    {
        return START;
    }

    return NONE; //Return None Otherwise
}

Input iaInput(){
    //IF the ball is not launched do nothing
    if(!game.ball.launched) return NONE;

    //If the ball is not near
    if(!isBallNear(&game.ball,&game.player2)){
        //IF the Ball is going Up (Dy<0) Go UP
        if(game.ball.dy<0){
            return UP;
        }else{
            //Go Dow OTherWise
            return DOWN;
        }
    }

    return NONE;//Do Nothing OtherWise

}

bool isBallNear(Ball* ball, Player* player){
    //Box1 (Ball)
    BoxCollider box1= {ball->x+8,ball->y+8,13,13};
    //Box2 (player-20x to check a near area collision)
    BoxCollider box2 = {player->x-20,player->y,PADDLE_WIDTH,PADDLE_HEIGHT};

    return isColliding(&box1,&box2);
}

void initGame()
{
    //Init the game with all the information
    initPlayer(&game.player1,PLAYER1_INITIAL_X,PLAYER_INITIAL_Y,PLAYER);
    initPlayer(&game.player2,PLAYER2_INITIAL_X,PLAYER_INITIAL_Y,(game.singlePlayer)?IA:PLAYER);
    game.ball.x = BALL_INITIAL_X;
    game.ball.y = BALL_INITIAL_Y;
    game.ball.launched=FALSE;
    game.ball.dx=0;
    game.ball.dx=0;
    game.lastScore=2;
}
void updateGame(){
    //Update the Player logic and Ball
    updatePlayer(&game.player1);
    updatePlayer(&game.player2);
    updateBall();
}

void updateGameOver(){
    //IF the Player1 Push Start go to InitMenu
    if(game.player1.input==START){
        game.state=INIT_MENU;
    }
}

void deInitGame(){
    //Clear Plane
    VDP_clearPlane(BG_A,true);
    //Release all the game Sprites
    SPR_releaseSprite(game.ball.sprite);
    SPR_releaseSprite(game.player1.sprite);
    SPR_releaseSprite(game.player2.sprite);
    SPR_releaseSprite(game.player1.marc);
    SPR_releaseSprite(game.player2.marc);
}

void drawInitGame(){
    //Init index variable
    u16 index = TILE_USER_INDEX;
    //Disable Interruptions
    SYS_disableInts();
    //Draw Table Image on BGA
    VDP_drawImageEx(BG_A,&table,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,index),
    0,0,TRUE,DMA);
    //Set the Sprites paletes
    PAL_setPalette(PAL1,bat1.palette->data,CPU);
    PAL_setPalette(PAL2, pal2.data,CPU);
    PAL_setPalette(PAL3, ball.palette->data,CPU);
    //Enable Interruptions
    SYS_enableInts();
    //Add Player 1 Sprite
    game.player1.sprite = SPR_addSprite(&bat1,game.player1.x, game.player1.y, TILE_ATTR(PAL1,FALSE,FALSE,FALSE));
    //Add Player 1 Score Sprite
    game.player1.marc = SPR_addSprite(&marc1,24,32,TILE_ATTR(PAL1,TRUE,FALSE,FALSE));
    //Add Player 2 Sprite using the same Sprite of player 1 using PAL2 and FLIPV to TRUE
    game.player2.sprite = SPR_addSprite(&bat1, game.player2.x, game.player2.y, TILE_ATTR(PAL2,FALSE,FALSE,TRUE));
    //ADd Player 2 Score Sprite
    game.player2.marc = SPR_addSprite(&marc1,296,32,TILE_ATTR(PAL1,TRUE,FALSE,FALSE));
    //Add Ball Sprite
    game.ball.sprite = SPR_addSprite(&ball, game.ball.x, game.ball.y,TILE_ATTR(PAL3,FALSE,FALSE,FALSE));
    //Set Score Animation to 0
    SPR_setAnim(game.player1.marc,0);
    SPR_setAnim(game.player2.marc,0);

}

//loop Game

void drawGame(){
    //Draw Players Status
    drawPlayer(&game.player1);
    drawPlayer(&game.player2);
    //Draw Ball
    drawBall();
}

void drawGameOver(){
    //Draw Game Over Status
    u16 index = TILE_USER_INDEX;
    VDP_drawImageEx(BG_A,&over,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,index),0,0,TRUE,DMA);
}