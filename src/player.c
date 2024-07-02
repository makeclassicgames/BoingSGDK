#include "player.h"
#include "physics.h"

void initPlayer(Player* player,u16 x,u16 y,PlayerMode mode){
    player->x=x;
    player->y=y;
    player->playerMode=mode;
    player->score=0;
}

void updatePlayer(Player *player)
{

    
    switch (player->input)
    {
    case UP://When player push Up Button
        //IF the player is not Touching Top
        if (!isTouchingTop(player->x + 10, player->y + 2, PADDLE_WIDTH, PADDLE_HEIGHT))
        {  
            player->y -= PLAYER_SPEED; //Move Player Up
        }
        break;
    case DOWN://When the player Push Down Button
        //If the player os not touching Bottom
        if (!isTouchingBottom(player->x + 10, player->y + 2, PADDLE_WIDTH, PADDLE_HEIGHT))
        {
            player->y += PLAYER_SPEED; //Move Player Down
        }
        break;
    default:
        break;
    }
}

s8 isTouchingPaddle(Player *player, u16 x, u16 y, u16 w, u16 h)
{
    //Upper Box Collider (0-1/2 player)
    BoxCollider box1 = {player->x + 10, player->y + 4, PADDLE_WIDTH, PADDLE_HEIGHT / 2};
    //Object Collider (Ball)
    BoxCollider box2 = {x, y, w, h};
    //Downer Box Collider (1/2 - end player)
    BoxCollider box3 = {player->x + 10, player->y + PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT / 2};

    //If the object is colliding with the upper player top return -1.
    if (isColliding(&box1, &box2))
    {
        return -1;
    }
    else
    {
        //if the object is colliding with the downer player return 1
        if (isColliding(&box3, &box2))
        {
            return 1;
        }
        else
        {
            return 0;//Return 0 otherwise
        }
    }
}

void drawPlayer(Player *player)
{
    //Draw Player Sprite Position
    SPR_setPosition(player->sprite, player->x, player->y);
    //Draw Score Frame Position
    SPR_setFrame(player->marc, player->score);
}