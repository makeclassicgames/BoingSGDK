#include "game.h"

#include "gfx.h"

void InitLogo(void){
    frameLogoCounter=0;
}
void drawInitLogo(void){
    SYS_disableInts();
    PAL_setPalette(PAL0,logo.palette->data,DMA);
    PAL_fadeIn(0,63,logo.palette->data,30,FALSE);
    VDP_drawImageEx(BG_A,&logo,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,TILE_USER_INDEX),0,0,FALSE,DMA);
    SYS_enableInts();
    Game.state=LOGO;
}

void updateLogo(void){
    frameLogoCounter++;
}
void drawLogo(void){
    if(frameLogoCounter>240){
        Game.state=INIT_MENU;
        PAL_fadeOut(0,63,40,FALSE);
    }
}