#include "game.h"
#include "gfx.h"
#include "sprt.h"

    void initMenu(void){
        menuStruct.twoPlayers=FALSE;
    }
    void drawInitMenu(void){
        SYS_disableInts();
        u16 index=TILE_USER_INDEX;
        VDP_drawImageEx(BG_A,&menu,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,index),0,0,TRUE,DMA);
        index+=menu.tileset->numTile;
        PAL_setPalette(PAL1,menuSel.palette->data,DMA);
        SYS_enableInts();
        menuStruct.menuSel1= SPR_addSprite(&menuSel,75,132,TILE_ATTR(PAL1,FALSE,FALSE,FALSE));
        menuStruct.menuSel2= SPR_addSprite(&menuSel,230,132,TILE_ATTR(PAL1,FALSE,FALSE,TRUE));
        game.state=MENU;
    }

    void updateMenu(void){
        switch (game.player1.input)
        {
        case UP:
        case DOWN:
            menuStruct.twoPlayers++;
            break;
        case START:
            if(menuStruct.twoPlayers%2==0){
                game.singlePlayer=FALSE;
            }else{
                game.singlePlayer=TRUE;
            }
            break;
        default:
            break;
        }
    }
    void drawMenu(void){
        if(menuStruct.twoPlayers%2==0){
            SPR_setPosition(menuStruct.menuSel1,75,162);
            SPR_setPosition(menuStruct.menuSel2,230,162);
        }else{
            SPR_setPosition(menuStruct.menuSel1,75,132);
            SPR_setPosition(menuStruct.menuSel2,230,132); 
        }
        if(game.player1.input==START){
            game.state=INIT_GAME;
            SPR_releaseSprite(menuStruct.menuSel1);
            SPR_releaseSprite(menuStruct.menuSel2);
        }

    }