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


void drawPlayer(Player * player){
    SPR_setPosition( player->sprite,player->x,player->y);
}