#include <genesis.h>
#include "game.h"
#include "gfx.h"
#include "sprt.h"


void updateMenu(){
    switch (Game.player1.input)
    {
    case DOWN:
    case UP:
        Menu.twoPlayers++;
        break;
    case START:
        if(Menu.twoPlayers%2 ==0){
            Game.singlePlayer=FALSE;
        }else{
            Game.singlePlayer=TRUE;
        }
        break;
    default:
        break;
    }
}

void drawInitMenu(){
    SYS_disableInts();
    VDP_drawImageEx(BG_A,&menu,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,TILE_USER_INDEX),0,0,TRUE,CPU);
    PAL_setPalette(PAL1,menuSel.palette->data,CPU);
    Menu.selector1 = SPR_addSprite(&menuSel,75,132,TILE_ATTR(PAL1,FALSE,FALSE,FALSE));
    Menu.selector2 = SPR_addSprite(&menuSel,230,132,TILE_ATTR(PAL1,FALSE,FALSE,TRUE));
   
}

void drawMenu(){
 if(Menu.twoPlayers%2 ==0){
    SPR_setPosition(Menu.selector1,75,162);
    SPR_setPosition(Menu.selector2,230,162);
 }else{
    SPR_setPosition(Menu.selector1,75,132);
    SPR_setPosition(Menu.selector2,230,132);
 }
 if(Game.player1.input==START){
        Game.state=INIT_GAME;
        SPR_releaseSprite(Menu.selector1);
        SPR_releaseSprite(Menu.selector2);

 }
}