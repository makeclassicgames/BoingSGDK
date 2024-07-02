#include "game.h"
#include "globals.h"
#include "physics.h"

#include "sprt.h"
#include "sound.h"

//When Paddle Touched add the current animation
void paddleTouched(s8 paddleTouch);
//Restart game after Goal
void restartGame();

//De Init Impact Sprite
void deInitImpact(Sprite *);

void updateBall(){
    //IF the game is not launched
     if(!game.ball.launched){
        //When player1 press A
        if(game.player1.input==A){
            //Check last player scored and launch to the other side
            game.ball.dx=(game.lastScore==1)?-BALL_SPEED:BALL_SPEED;
            game.ball.dy=-BALL_SPEED;//dy Speed UP
            game.ball.launched=TRUE;//Set Ball to Launched

        }
    }else{

        //if ball touch top made it bounced
        if(isTouchingTop(game.ball.x+8,game.ball.y+8,13,13)){
            game.ball.dy=BALL_SPEED;//Change dy direction
            game.ball.impact=TRUE;//impact to True
            game.ball.bounced=TRUE; //Bounced to True
        }
        //If ball Touch Bottom made it bounced
        if(isTouchingBottom(game.ball.x+8,game.ball.y+8,13,13)){
            game.ball.dy=-BALL_SPEED;//Change Dy to go up
            game.ball.impact=TRUE;//Impact To True
            game.ball.bounced=TRUE; //Bounced to True

        }

        //If Ball go to Left Edge (player 2 Score)
        if(isTouchingLeftEdge(game.ball.x+8,game.ball.y+8,13,13)){
            game.player2.score++;//Player 2 Score
            game.lastScore=2;//Last player Score 2
            game.ball.goalhit=TRUE; //Goal Hit to True
            //If the Player 2 Score >9 player 2 Wins
            if(game.player2.score>9){
                //DeInit Game and go to Game Over
                deInitGame();
                game.player1.score=0;
                game.player2.score=0;
                game.state=GAME_OVER;
            }else{
                //Restart The Game
                restartGame();
            }
            
        }
        //If the ball is touching right edge player 1 Score
        if(isTouchingRightEdge(game.ball.x+8,game.ball.y+8,13,13)){
            game.player1.score++; //Player 1 Score
            game.lastScore=1; //Last Player score
            game.ball.goalhit=TRUE; //Goal Hit True
            //If player 1 score >9 Player 1 Wins
            if(game.player1.score>9){
                //De Init Game and set status to Game_Over
                deInitGame();
                game.player1.score=0;
                game.player2.score=0;
                game.state=GAME_OVER;
            }else{
                //Restar the Game
                restartGame();
            }

        }
        //if the Ball is Touchng Paddle1 bounce
        s8 tounchingpaddle1= isTouchingPaddle(&game.player1,game.ball.x+8, game.ball.y+8,13,13);
        paddleTouched(tounchingpaddle1);
        //if the Ball is Touchng Paddle2 bounce
        s8 tounchingpaddle2= isTouchingPaddle(&game.player2,game.ball.x+8, game.ball.y+8,13,13);
        paddleTouched(tounchingpaddle2);
        //Change Ball coords with the current directions
        game.ball.x+=game.ball.dx;
        game.ball.y+=game.ball.dy;
    }
}

void restartGame(){
    //Restart Player Coords
    game.player1.x=PLAYER1_INITIAL_X;
    game.player1.y=PLAYER_INITIAL_Y;
    game.player2.x=PLAYER2_INITIAL_X;
    game.player2.y=PLAYER_INITIAL_Y;

    //Restart Ball Coords
    game.ball.dx=0;
    game.ball.dy=0;
    game.ball.x=BALL_INITIAL_X;
    game.ball.y=BALL_INITIAL_Y;
    game.ball.launched=FALSE;
}

void paddleTouched(s8 paddleTouch){
    //If paddle touched !=0
    if(paddleTouch){
        //Set paddle Hit and impact to True
        game.ball.paddlehit=TRUE;
        game.ball.impact=TRUE;
        //Change dx Sign (go to the other side)
        game.ball.dx= CHANGE_SING(game.ball.dx);
        //IF paddle touch <0 dy go up (dy<0) otherwise the Ball Goes Down (dy>0)
        if(paddleTouch<0){
            game.ball.dy=-BALL_SPEED;
        }else{
            game.ball.dy=BALL_SPEED;
        }
    }
}

void drawBall(){
   //Set current Ball SPrite Position
   SPR_setPosition(game.ball.sprite,game.ball.x,game.ball.y);
   //If Ball Impact, add a new Sprite and set frameChange Callback
   if(game.ball.impact){
     game.ball.impactSpr = SPR_addSprite(&hit,game.ball.x+4,game.ball.y+4,TILE_ATTR(PAL1,FALSE,FALSE,FALSE));
     SPR_setFrameChangeCallback(game.ball.impactSpr,deInitImpact);
     game.ball.impact=FALSE;
   }

    //If ball bounced player Bounce Sound
   if(game.ball.bounced){
    XGM2_playPCM(bounce,5120,SOUND_PCM_CH_AUTO);
    game.ball.bounced=FALSE;
   }

    //If Player goals play goal Sound
   if(game.ball.goalhit){
    XGM2_playPCM(goal,6912,SOUND_PCM_CH_AUTO);
    game.ball.goalhit=FALSE;
   }

    //If paddle hit play paddle hit Sound
   if(game.ball.paddlehit){
    XGM2_playPCM(playerhit,6912,SOUND_PCM_CH_AUTO);
    game.ball.paddlehit=FALSE;
   }
}

void deInitImpact(Sprite* sprite){
    //This function is called whe Sprite change frame.
    //In this case if the frame index is 3 Release the Sprite
    if(sprite->frameInd==3){
        SPR_releaseSprite(sprite);
    }
}