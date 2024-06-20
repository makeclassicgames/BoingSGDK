#include "game.h"

#include "gfx.h"
#include "sprt.h"

void updateBall();
void drawBall();
void restartGame();
void checkPauseGame();

void initGame()
{

    // TODO: change with menu selection
    Game.singlePlayer = FALSE;

    //Init Player 1
    initPlayer(&Game.player1,
               PLAYER1_INITIAL_X,
               PLAYER_INITIAL_Y,
               PLAYER);
    //Init Player 2
    initPlayer(&Game.player2,
               PLAYER2_INITIAL_X,
               PLAYER_INITIAL_Y,
               (Game.singlePlayer) ? IA : PLAYER);
    // Init Ball
    Game.ball.dx=0;
    Game.ball.dy=0;
    Game.ball.x = BALL_INITIAL_X;
    Game.ball.y = BALL_INITIAL_Y;
    Game.ball.launched = FALSE;
    Game.ball.impact = FALSE;
}

void updateGame(){
     switch (Game.state)
    {
    case MENU:
    case INIT_GAME:
        // init game
        initGame();
        break;
    case LOOP_GAME:
        updateLoop();
        break;
    case PAUSE:
        checkPauseGame();
    default:
        break;
    }
}

void restartGame(){
    Game.player1.x=PLAYER1_INITIAL_X;
    Game.player1.y=PLAYER_INITIAL_Y;
    Game.player2.x=PLAYER2_INITIAL_X;
    Game.player2.y=PLAYER_INITIAL_Y;
    Game.ball.x=BALL_INITIAL_X;
    Game.ball.y=BALL_INITIAL_Y;
    Game.ball.dx=0;
    Game.ball.dy=0;
    Game.ball.launched=FALSE;
}
void drawGame(){
     switch (Game.state)
    {
    case MENU:
    case INIT_GAME:
        drawInitializedGame();
        Game.state = LOOP_GAME;
        break;
    case LOOP_GAME:
        drawLoop();
        break;
    case PAUSE:
    //TODO Show Pause
    default:
        break;
    }
}






Input checkGamepadInput(u16 joyPad){
    u16 value = JOY_readJoypad(joyPad);
    if(value & BUTTON_UP){
        return UP;
    }else{
        if(value & BUTTON_DOWN){
            return DOWN;
        }
    }

    if(value & BUTTON_A){
       return  A;
    }
    if(value & BUTTON_START){
        return START;
    }

    return NONE;
}


void updateLoop(){
    checkPauseGame();
    updatePlayer(&Game.player1);
    updatePlayer(&Game.player2);
    updateBall();
}

void updateBall(){
    if(!Game.ball.launched) {
       
        if(Game.player1.input==A){

            Game.ball.dx=BALL_SPEED;
            Game.ball.dy=BALL_SPEED;
            Game.ball.launched=TRUE;
        }
    }else{
        if(isTouchingTop(Game.ball.x+8,Game.ball.y+8,13,13)){
            Game.ball.dy=-Game.ball.dy;
        }
        if(isTouchingBottom(Game.ball.x+8,Game.ball.y+8,13,13)){
            Game.ball.dy=-Game.ball.dy;
        }
        if(isTouchingLeftEdge(Game.ball.x+8,Game.ball.y+8,13,13)){
            //Player 1 Goal
            Game.lastScore=2;
            Game.player2.score++;
            restartGame();
        }
        if(isTouchingRightEdge(Game.ball.x+8,Game.ball.y+8,13,13)){
           //Player 2 Goal
           Game.lastScore=1;
           Game.player1.score++;
           restartGame();
        }
        Game.ball.x+=Game.ball.dx;
        Game.ball.y+=Game.ball.dy;
    }

   
}

void checkPauseGame(){
    if(Game.player1.input==START || Game.player2.input==START){
        switch (Game.state)
        {
        case LOOP_GAME:
            Game.state=PAUSE;
            break;
        case PAUSE:
            Game.state=LOOP_GAME;
        default:
            break;
        }

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
}

void drawLoop(){
    drawPlayer(&Game.player1);
    drawPlayer(&Game.player2);
    drawBall();
}

void drawBall(){
    SPR_setPosition(Game.ball.sprite,Game.ball.x,Game.ball.y);
    //TODO: Create Impact Sprite
}