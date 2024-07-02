#include "game.h"
#include "globals.h"
#include "physics.h"

#include "sprt.h"
#include "sound.h"

void paddleTouched(s8 paddleTouch);
void restartGame();

void deInitImpact(Sprite *);

void updateBall(){
     if(!game.ball.launched){
        if(game.player1.input==A){
            game.ball.dx=(game.lastScore==1)?-BALL_SPEED:BALL_SPEED;
            game.ball.dy=-BALL_SPEED;
            game.ball.launched=TRUE;

        }
    }else{

        
        if(isTouchingTop(game.ball.x+8,game.ball.y+8,13,13)){
            game.ball.dy=BALL_SPEED;
            game.ball.impact=TRUE;
            game.ball.bounced=TRUE;
        }
        if(isTouchingBottom(game.ball.x+8,game.ball.y+8,13,13)){
            game.ball.dy=-BALL_SPEED;
            game.ball.impact=TRUE;
            game.ball.bounced=TRUE;

        }

        if(isTouchingLeftEdge(game.ball.x+8,game.ball.y+8,13,13)){
            game.player2.score++;
            game.lastScore=2;
            game.ball.goalhit=TRUE;
            if(game.player2.score>9){
                deInitGame();
                game.state=GAME_OVER;
            }else{
                restartGame();
            }
            
        }

        if(isTouchingRightEdge(game.ball.x+8,game.ball.y+8,13,13)){
            game.player1.score++;
            game.lastScore=1;
            game.ball.goalhit=TRUE;
            if(game.player1.score>9){
                deInitGame();
                game.player1.score=0;
                game.player2.score=0;
                game.state=GAME_OVER;
            }else{
                restartGame();
            }

        }

        s8 tounchingpaddle1= isTouchingPaddle(&game.player1,game.ball.x+8, game.ball.y+8,13,13);
        paddleTouched(tounchingpaddle1);
        s8 tounchingpaddle2= isTouchingPaddle(&game.player2,game.ball.x+8, game.ball.y+8,13,13);
        paddleTouched(tounchingpaddle2);
        game.ball.x+=game.ball.dx;
        game.ball.y+=game.ball.dy;
    }
}

void restartGame(){
    game.player1.x=PLAYER1_INITIAL_X;
    game.player1.y=PLAYER_INITIAL_Y;
    game.player2.x=PLAYER2_INITIAL_X;
    game.player2.y=PLAYER_INITIAL_Y;

    game.ball.dx=0;
    game.ball.dy=0;
    game.ball.x=BALL_INITIAL_X;
    game.ball.y=BALL_INITIAL_Y;
    game.ball.launched=FALSE;
}

void paddleTouched(s8 paddleTouch){
    if(paddleTouch){
        game.ball.paddlehit=TRUE;
        game.ball.impact=TRUE;
        game.ball.dx= CHANGE_SING(game.ball.dx);
        if(paddleTouch<0){
            game.ball.dy=-BALL_SPEED;
        }else{
            game.ball.dy=BALL_SPEED;
        }
    }
}

void drawBall(){
   SPR_setPosition(game.ball.sprite,game.ball.x,game.ball.y);
   if(game.ball.impact){
     game.ball.impactSpr = SPR_addSprite(&hit,game.ball.x+4,game.ball.y+4,TILE_ATTR(PAL1,FALSE,FALSE,FALSE));
     SPR_setFrameChangeCallback(game.ball.impactSpr,deInitImpact);
     game.ball.impact=FALSE;
   }

   if(game.ball.bounced){
    XGM2_playPCM(bounce,5120,SOUND_PCM_CH_AUTO);
    game.ball.bounced=FALSE;
   }

   if(game.ball.goalhit){
    XGM2_playPCM(goal,6912,SOUND_PCM_CH_AUTO);
    game.ball.goalhit=FALSE;
   }

   if(game.ball.paddlehit){
    XGM2_playPCM(playerhit,6912,SOUND_PCM_CH_AUTO);
    game.ball.paddlehit=FALSE;
   }
}

void deInitImpact(Sprite* sprite){
    if(sprite->frameInd==3){
        SPR_releaseSprite(sprite);
    }
}