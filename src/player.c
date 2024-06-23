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
    }
}

s8 isTouchingPaddle(Player * player, u16 x,u16 y,u16 width,u16 height){
    //Generate Boxes
    //Box1 (Upper Paddle)
    u16 box1_x1 = player->x;
    u16 box1_y1 = player->y;
    u16 box1_x2 = player->x + PADDLE_WIDTH;
    u16 box1_y2 = player->y + PADDLE_HEIGHT/2;
    //Box 2 (Ball)
    u16 box2_x1 = x;
    u16 box2_y1 = y;
    u16 box2_x2 = x + width;
    u16 box2_y2 = y + height/2;

    //Box 3 (Dower Padle)
    u16 box3_x1 = player->x;
    u16 box3_y1 = player->y+ PADDLE_HEIGHT/2;
    u16 box3_x2 = player->x + PADDLE_WIDTH;
    u16 box3_y2 = player->y + PADDLE_HEIGHT;

     if ((box1_x1 <= box2_x2) &&
        (box1_x2 >= box2_x1) &&
        (box1_y1 <= box2_y2) &&
        (box1_y2 >= box2_y1))
        return -1;
    else
        if((box3_x1 <= box2_x2) &&
        (box3_x2 >= box2_x1) &&
        (box3_y1 <= box2_y2) &&
        (box3_y2 >= box2_y1)){
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