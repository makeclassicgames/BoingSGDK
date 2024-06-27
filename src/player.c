#include "player.h"
#include "physics.h"

void updatePlayer(Player * player){

    switch (player->input)
    {
    case UP:
        if(!isTouchingTop(player->x+10,player->y+2,PADDLE_WIDTH,PADDLE_HEIGHT)){
        player->y-=PLAYER_SPEED;
        }
        break;
    case DOWN:
        if(!isTouchingBottom(player->x+10,player->y+2,PADDLE_WIDTH,PADDLE_HEIGHT)){
        player->y+=PLAYER_SPEED;
        }
        break;
    default:
        break;
    }
}

s8 isTouchingPaddle(Player* player,u16 x, u16 y, u16 w, u16 h){
    BoxCollider box1 = {player->x,player->y,PADDLE_WIDTH,PADDLE_HEIGHT/2};
    BoxCollider box2= {x,y,w,h};
    BoxCollider box3={player->x+10,player->y+PADDLE_HEIGHT/2,PADDLE_WIDTH,PADDLE_HEIGHT/2};

    if(isColliding(&box1,&box2)){
        return -1;
    }else{
        if(isColliding(&box3,&box2)){
            return 1;
        }else{
            return 0;
        }
    }    
}

void drawPlayer(Player* player){
    SPR_setPosition(player->sprite,player->x,player->y);
    SPR_setFrame(player->marc,player->score);
}