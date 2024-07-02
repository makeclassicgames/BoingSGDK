#include "game.h"
#include "gfx.h"
#include "sprt.h"

    void initMenu(void){
        //Two Players mode= False
        menuStruct.twoPlayers=FALSE;
    }
    void drawInitMenu(void){
        //Disable Interruptions
        SYS_disableInts();
        //set index for user index in VRAM
        u16 index=TILE_USER_INDEX;
        //Draw menu Image on Background A
        VDP_drawImageEx(BG_A,&menu,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,index),0,0,TRUE,DMA);
        //Update Index
        index+=menu.tileset->numTile;
        //Set the PAL1 with the menu selector sprite palete data.
        PAL_setPalette(PAL1,menuSel.palette->data,DMA);
        //Enable Interruptions
        SYS_enableInts();
        //add Menu Selector 1 
        menuStruct.menuSel1= SPR_addSprite(&menuSel,75,132,TILE_ATTR(PAL1,FALSE,FALSE,FALSE));
        //Add a secound menu selector Sprite using the same sprite definition and flipV on TRUE.
        menuStruct.menuSel2= SPR_addSprite(&menuSel,230,132,TILE_ATTR(PAL1,FALSE,FALSE,TRUE));
        //Set Game State to MENU
        game.state=MENU;
    }

    void updateMenu(void){
        //Check the current player 1 Input
        switch (game.player1.input)
        {
        //If the current input is UP or DOWN
        case UP:
        case DOWN:
            //add two Players to next value
            menuStruct.twoPlayers++;
            break;
        case START:
            //If the menu Option is One Player set the SinglePlayer to TRUE
            if(menuStruct.twoPlayers%2!=0){
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
        //if the menu option is single player draw Menu Selector Sprites to first Option
        if(menuStruct.twoPlayers%2!=0){
            SPR_setPosition(menuStruct.menuSel1,75,162);
            SPR_setPosition(menuStruct.menuSel2,230,162);
        }else{
            //if the menu option is 2 player2 draw Menu Selector Sprites to Second Option
            SPR_setPosition(menuStruct.menuSel1,75,132);
            SPR_setPosition(menuStruct.menuSel2,230,132); 
        }
        //If we press Start DeInitSprite and change to INIT_GAME Status
        if(game.player1.input==START){
            game.state=INIT_GAME;
            SPR_releaseSprite(menuStruct.menuSel1);
            SPR_releaseSprite(menuStruct.menuSel2);
        }

    }