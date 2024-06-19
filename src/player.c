#include "player.h"


void initPlayer(Player * output, u16 x, u16 y ,PlayerMode playerMode){
    output->x=x;
    output->y=y;
    output->playerMode=playerMode;
    output->score=0;
}

void updatePlayer(Player* player, Input input){

}