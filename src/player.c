#include "player.h"
#include "physics.h"

void updatePlayer(Player * player){

    switch (player->input)
    {
    case UP:
        player->y-=PLAYER_SPEED;
        break;
    case DOWN:
        player->y+=PLAYER_SPEED;
        break;
    default:
        break;
    }
}


void drawPlayer(Player* player){
    SPR_setPosition(player->sprite,player->x,player->y);
}