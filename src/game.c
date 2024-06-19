#include "game.h"

#include "gfx.h"
#include "sprt.h"

void initGame()
{

    // TODO: change with menu selection
    Game.singlePlayer = TRUE;

    //Init Player 1
    initPlayer(&Game.player1,
               PLAYER1_INITIAL_X,
               PLAYER_INITIAL_Y,
               PLAYER);
    //Init Player 2
    initPlayer(&Game.player2,
               PLAYER2_INITIAL_X,
               PLAYER_INITIAL_Y,
               (Game.singlePlayer) ? IA : PLAYER);
    // Init Ball
    Game.ball.x = BALL_INITIAL_X;
    Game.ball.y = BALL_INITIAL_Y;
    Game.ball.launched = FALSE;
    Game.ball.impact = FALSE;
}

void drawInitializedGame()
{

    u16 index = TILE_USER_INDEX;
    // Disable Ints for drawScreen and transfer palettes
    SYS_disableInts();
    VDP_drawImageEx(BG_A, &table, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, index), 0, 0, true, DMA);
    index += table.tileset->numTile;
    PAL_setPalette(PAL1, bat1.palette->data, CPU);
    PAL_setPalette(PAL2, pal2.data, CPU);
    PAL_setPalette(PAL3, ball.palette->data, CPU);
    SYS_enableInts();
    // draw Sprites
    Game.player1.sprite = SPR_addSprite(&bat1, Game.player1.x, Game.player1.y, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
    Game.player2.sprite = SPR_addSprite(&bat1, Game.player2.x, Game.player2.y, TILE_ATTR(PAL2, FALSE, FALSE, TRUE));
    Game.ball.sprite = SPR_addSprite(&ball, Game.ball.x, Game.ball.y, TILE_ATTR(PAL3, FALSE, FALSE, FALSE));
}
