/**
 * Hello World Example
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>

#include "gfx.h"

int main()
{
    SPR_init();
    u16 index=TILE_USER_INDEX;
    VDP_drawImageEx(BG_A,&table,TILE_ATTR_FULL(
        PAL0,FALSE,FALSE,FALSE,index
    ),0,0, true,DMA);
    index+=table.tileset->numTile;
    Sprite* sprbat1 = SPR_addSprite(&bat1,40,110,TILE_ATTR(PAL1,TRUE,FALSE,FALSE));
    PAL_setPalette(PAL1,bat1.palette->data,CPU);
    Sprite * sprbat2 = SPR_addSprite(&bat2, 280,110,TILE_ATTR(PAL2,TRUE,FALSE,FALSE));
    PAL_setPalette(PAL2,bat2.palette->data,CPU);
    Sprite * sprball = SPR_addSprite(&ball, 160,105,TILE_ATTR(PAL3,TRUE,FALSE,FALSE));
    PAL_setPalette(PAL3, ball.palette->data,CPU);

    while(1)
    {
        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SPR_update();
        SYS_doVBlankProcess();
    }
    return (0);
}
