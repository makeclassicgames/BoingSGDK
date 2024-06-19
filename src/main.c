/**
 * Hello World Example
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>

#include "gfx.h"
#include "sprt.h"

int main()
{
    //init variables and Game
    VDP_setScreenWidth320();
    JOY_init();
    SPR_init();
    //init game
    
    u16 index=TILE_USER_INDEX;
    VDP_drawImageEx(BG_A,&over,TILE_ATTR_FULL(
        PAL0,FALSE,FALSE,FALSE,index
    ),0,0, true,DMA);
    index+=table.tileset->numTile;
   /* Sprite * selector = SPR_addSprite(&menuSel,75,132,TILE_ATTR(PAL1,FALSE,FALSE,FALSE));
    Sprite * selector2 = SPR_addSprite(&menuSel,230,132,TILE_ATTR(PAL1,FALSE,FALSE,TRUE));
    PAL_setPalette(PAL1,menuSel.palette->data,CPU);
    */
    while(1)
    {
        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SPR_update();
        SYS_doVBlankProcess();
    }
    return (0);
}
