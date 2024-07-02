#include "game.h"
#include "gfx.h"

void initLogo(void)
{
    frameCounter=0;
}
void drawInitLogo(void)
{
    SYS_disableInts();
    PAL_setPalette(PAL0,palette_black,DMA);
    VDP_drawImageEx(BG_A,&logo,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,TILE_USER_INDEX),0,0,TRUE,DMA);
    PAL_fadeIn(0,16,logo.palette->data,30,false);
    SYS_enableInts();
    game.state=LOGO;
}
void updateLogo(void)
{
    frameCounter++;
}
void drawLogo(void)
{
    if(frameCounter>240){
        game.state=INIT_MENU;
        PAL_fadeOut(0,16,30,FALSE);
    }
}