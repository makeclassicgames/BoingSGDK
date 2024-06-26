#include "player.h"
#include "physics.h"

void initPlayer(Player *output, u16 x, u16 y, PlayerMode playerMode)
{
    output->x = x;
    output->y = y;
    output->playerMode = playerMode;
    output->score = 0;
}

void updatePlayer(Player *player)
{
    switch (player->input)
    {
    case UP:
        if (!isTouchingTop(player->x+10, player->y+2,PADDLE_WIDTH,PADDLE_HEIGHT))
            player->y -= PLAYER_SPEED;
        break;
    case DOWN:
        if (!isTouchingBottom(player->x+10, player->y+2,PADDLE_WIDTH,PADDLE_HEIGHT))
            player->y += PLAYER_SPEED;
        break;
    default:
        break;
    }
}

s8 isTouchingPaddle(Player * player, u16 x,u16 y,u16 width,u16 height){
    //Generate Boxes
    //Box1 (Upper Paddle)

    BoxCollider box1={player->x,player->y,PADDLE_WIDTH,PADDLE_HEIGHT/2};

    //Box 2 (Ball)
    BoxCollider box2={x,y,width,height/2};

    //Box 3 (Dower Paddle)
    BoxCollider box3={player->x,player->y+PADDLE_HEIGHT/2,PADDLE_WIDTH,PADDLE_HEIGHT};

     if (isColliding(&box1,&box2))
        return -1;
    else
        if(isColliding(&box3,&box2)){
            return 1;
        }else{
            return 0;
        }
}


void drawPlayer(Player * player){
    SPR_setPosition( player->sprite,player->x,player->y);
    SPR_setFrame(player->points,player->score);
}

void deInitPlayer(Player* player){
    SPR_releaseSprite(player->sprite);
    SPR_releaseSprite(player->points);
}