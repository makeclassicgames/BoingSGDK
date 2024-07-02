#include "game.h"
#include "gfx.h"

void initLogo(void)
{
    //Frame Counter is 0
    frameCounter=0;
}
void drawInitLogo(void)
{
    //Disable Ints
    SYS_disableInts();
    //Set palette to back
    PAL_setPalette(PAL0,palette_black,DMA);
    //Draw Image 
    VDP_drawImageEx(BG_A,&logo,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,TILE_USER_INDEX),0,0,FALSE,DMA);
    //Made a Fade In
    PAL_fadeIn(0,16,logo.palette->data,30,false);
    //Enable Ints
    SYS_enableInts();
    //Go to NExt State Logo
    game.state=LOGO;
}
void updateLogo(void)
{
    //add One Frame to Frame Counter
    frameCounter++;
}
void drawLogo(void)
{
    //If the frameCounter > 240 (4 seconds) Go to Next State and made a FadeOut
    if(frameCounter>240){
        game.state=INIT_MENU;
        PAL_fadeOut(0,16,30,FALSE);
    }
}