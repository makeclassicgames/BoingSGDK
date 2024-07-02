#include "game.h"

#include "gfx.h"
#include "sprt.h"
#include "sound.h"

void updateBall();
void paddleTouched(s8 touched);
void drawBall();
void checkPauseGame();

void disableImpact(Sprite * sprite);

bool isBallNear(Ball*,Player*);

void initGame()
{

    // Init Player 1
    initPlayer(&Game.player1,
               PLAYER1_INITIAL_X,
               PLAYER_INITIAL_Y,
               PLAYER);
    // Init Player 2
    initPlayer(&Game.player2,
               PLAYER2_INITIAL_X,
               PLAYER_INITIAL_Y,
               (Game.singlePlayer) ? IA : PLAYER);
    // Init Ball
    Game.ball.dx = 0;
    Game.ball.dy = 0;
    Game.ball.x = BALL_INITIAL_X;
    Game.ball.y = BALL_INITIAL_Y;
    Game.ball.launched = FALSE;
    Game.ball.bounced = FALSE;
    Game.ball.impact = FALSE;
}

void restartGame()
{
    Game.player1.x = PLAYER1_INITIAL_X;
    Game.player1.y = PLAYER_INITIAL_Y;
    Game.player2.x = PLAYER2_INITIAL_X;
    Game.player2.y = PLAYER_INITIAL_Y;
    Game.ball.x = BALL_INITIAL_X;
    Game.ball.y = BALL_INITIAL_Y;
    Game.ball.dx = 0;
    Game.ball.dy = 0;
    Game.ball.launched = FALSE;
}

Input checkGamepadInput(u16 joyPad)
{
    u16 value = JOY_readJoypad(joyPad);
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

Input iaInput() {
    //Check if the ball is near the Player

    if(!isBallNear(&Game.ball,&Game.player2) && Game.ball.launched){
        if(Game.ball.dy<0){
            return UP;
        }else{
            return DOWN;
        }
    }
    return NONE;
}

void checkPauseGame()
{
    if (Game.player1.input == START || Game.player2.input == START)
    {
        switch (Game.state)
        {
        case LOOP_GAME:
            Game.state = PAUSE;
            break;
        case PAUSE:
            Game.state = LOOP_GAME;
            break;
        default:
            break;
        }
    }
}

void updateGame()
{
    switch (Game.state)
    {
    case INIT_LOGO:
        InitLogo();
        break;
    case LOGO:
        updateLogo();
        break;
    case INIT_MENU:
        Game.singlePlayer=FALSE;
        Menu.twoPlayers=FALSE;
        break;
    case MENU:
        updateMenu();
        break;
    case INIT_GAME:
        // init game
        initGame();
        break;
    case LOOP_GAME:
        updateLoop();
        break;
    case GAME_OVER:
        updateGameOver();
    case PAUSE:
        checkPauseGame();
        break;
    default:
        break;
    }
}



void updateLoop()
{
    checkPauseGame();
    updatePlayer(&Game.player1);
    updatePlayer(&Game.player2);
    updateBall();
}

void updateBall()
{
    if (!Game.ball.launched)
    {

        if (Game.player1.input == A)
        {

            if(Game.lastScore%2==0){
                Game.ball.dx = CHANGE_SING(BALL_SPEED);
            }else{
                Game.ball.dx = BALL_SPEED;
            }
            Game.ball.dy = CHANGE_SING(BALL_SPEED);
            Game.ball.launched = TRUE;
        }
    }
    else
    {
        if (isTouchingTop(Game.ball.x + 8, Game.ball.y + 8, 13, 13))
        {
            Game.ball.dy = CHANGE_SING(Game.ball.dy);
            Game.ball.impact=TRUE;
            Game.ball.bounced=TRUE;
        }
        if (isTouchingBottom(Game.ball.x + 8, Game.ball.y + 8, 13, 13))
        {
            Game.ball.dy = CHANGE_SING(Game.ball.dy);
            Game.ball.impact=TRUE;
            Game.ball.bounced=TRUE;
        }
        // touching paddle
        s8 touchingPaddle1 = isTouchingPaddle(&Game.player1, Game.ball.x + 8, Game.ball.y + 8, 13, 13);
        paddleTouched(touchingPaddle1);
        s8 touchingPaddle2 = isTouchingPaddle(&Game.player2, Game.ball.x + 8, Game.ball.y + 8, 13, 13);
        paddleTouched(touchingPaddle2);
        if (isTouchingLeftEdge(Game.ball.x + 8, Game.ball.y + 8, 13, 13))
        {
            Game.ball.hit=TRUE;
            // Player 1 Goal
            Game.lastScore = 1;
            Game.player2.score++;
            if(Game.player2.score>=MAX_SCORE){
                deInitGame();
                Game.state=GAME_OVER;
            }else{
                  restartGame();
            }
        }
        if (isTouchingRightEdge(Game.ball.x + 8, Game.ball.y + 8, 13, 13))
        {
            // Player 2 Goal
            Game.lastScore = 2;
            Game.player1.score++;
            if(Game.player1.score>=MAX_SCORE){
                deInitGame();
                Game.state=GAME_OVER;
            }else{
                  restartGame();
            }
          
        }
        Game.ball.x += Game.ball.dx;
        Game.ball.y += Game.ball.dy;
    }
}

void updateGameOver(){
    if(Game.player1.input==START){
        Game.state=INIT_MENU;
        VDP_clearPlane(BG_A,TRUE);
    }
}

void paddleTouched(s8 touchingPaddle)
{
    if (touchingPaddle)
    {
        Game.ball.playerHit=TRUE;
        Game.ball.dx = CHANGE_SING(Game.ball.dx);
        if (touchingPaddle > 0)
        {
            Game.ball.dy = CHANGE_SING(Game.ball.dy);
        }
        Game.ball.impact=TRUE;
    }
}

bool isBallNear(Ball* ball, Player* player){
    //box 1(Ball)

    BoxCollider box1={ball->x+8, ball->y+8,13,13};

    
    //box2(near Paddle (x-20,y),(width, height))
    BoxCollider box2={player->x-20,player->y,PADDLE_WIDTH,PADDLE_HEIGHT};
   

    if (isColliding(&box1,&box2))
        return TRUE;
    else
        return FALSE;

}

void deInitGame(){
    deInitPlayer(&Game.player1);
    deInitPlayer(&Game.player2);
    SPR_releaseSprite(Game.ball.sprite);
    VDP_clearPlane(BG_A,TRUE);

}


//------------------------------------ DRAW------------------------------------------------
void drawGame()
{
    switch (Game.state)
    {
    case INIT_LOGO:
        drawInitLogo();
        break;
    case LOGO:
        drawLogo();
        break;
    case INIT_MENU:
        drawInitMenu();
        Game.state=MENU;
        Menu.twoPlayers=1;
        break;
    case MENU:
        drawMenu();
        break;
    case INIT_GAME:
        drawInitializedGame();
        Game.state = LOOP_GAME;
        break;
    case LOOP_GAME:
        drawLoop();
        break;
    case GAME_OVER:
        drawGameOver();
        break;
    case PAUSE:
    // TODO Show Pause
    default:
        break;
    }
}

void drawInitializedGame()
{

    u16 index = TILE_USER_INDEX;
    // Disable Ints for drawScreen and transfer palettes
    SYS_disableInts();
    VDP_drawImageEx(BG_A, &table, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, index), 0, 0, true, DMA);
    index += table.tileset->numTile;
    PAL_setPalette(PAL1, bat1.palette->data, CPU);
    PAL_setPalette(PAL2, pal2.data, CPU);
    PAL_setPalette(PAL3, ball.palette->data, CPU);
    SYS_enableInts();
    // draw Sprites
    Game.player1.sprite = SPR_addSprite(&bat1, Game.player1.x, Game.player1.y, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
    Game.player2.sprite = SPR_addSprite(&bat1, Game.player2.x, Game.player2.y, TILE_ATTR(PAL2, FALSE, FALSE, TRUE));
    Game.ball.sprite = SPR_addSprite(&ball, Game.ball.x, Game.ball.y, TILE_ATTR(PAL3, FALSE, FALSE, FALSE));
    Game.player1.points = SPR_addSprite(&marc1,24,32,TILE_ATTR(PAL1,TRUE,FALSE,FALSE));
    SPR_setAnim(Game.player1.points,0);
    Game.player2.points = SPR_addSprite(&marc1,296,32,TILE_ATTR(PAL2,TRUE,FALSE,FALSE));
    SPR_setAnim(Game.player2.points,0);
}

void drawLoop()
{
    drawPlayer(&Game.player1);
    drawPlayer(&Game.player2);
    drawBall();
}

void drawBall()
{
    SPR_setPosition(Game.ball.sprite, Game.ball.x, Game.ball.y);
    // TODO: Create Impact Sprite
    if(Game.ball.impact){
       Game.ball.impactSprt= SPR_addSprite(&impact,Game.ball.x,Game.ball.y+4,TILE_ATTR(PAL1,FALSE,FALSE,FALSE));
       SPR_setFrameChangeCallback(Game.ball.impactSprt,disableImpact);
       Game.ball.impact=FALSE; 
    }

    if(Game.ball.bounced){
        XGM2_playPCM(bounce,5120,SOUND_PCM_CH_AUTO);
        Game.ball.bounced=FALSE;
    }
    if(Game.ball.hit){
        XGM2_playPCM(hit,6912, SOUND_PCM_CH_AUTO);
        Game.ball.hit=FALSE;
    }
    if(Game.ball.playerHit){
        XGM2_playPCM(playerhit,6912, SOUND_PCM_CH_AUTO);
        Game.ball.playerHit=FALSE;
    }
    
}

void disableImpact(Sprite * sprite){
    if(sprite->frameInd==3){
        SPR_releaseSprite(sprite);
    }
}
void drawGameOver(){
    SYS_disableInts();
    u16 index=TILE_USER_INDEX;
    VDP_drawImageEx(BG_A, &over, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, index), 0, 0, true, DMA);
    index += table.tileset->numTile;
    SYS_enableInts();
}