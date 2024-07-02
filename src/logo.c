#include "game.h"

#include "gfx.h"

void InitLogo(void){
    frameLogoCounter=0;
}
void drawInitLogo(void){
    SYS_disableInts();
    VDP_drawImageEx(BG_A,&logo,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,TILE_USER_INDEX),0,0,TRUE,DMA);
    SYS_enableInts();
    Game.state=LOGO;
}

void updateLogo(void){
    frameLogoCounter++;
}
void drawLogo(void){
    if(frameLogoCounter>240){
        Game.state=INIT_MENU;
    }
}