#include "player.h"
#include "common.h"

void check_player_input(int tx_offset, int ty_offset, Player *player)
{

    player->tx = player->tx + tx_offset;
    player->ty = player->ty + ty_offset;
    
    if (player->tx < 0) player->tx = 0;
    if (player->ty < 0) player->ty = 0;
    if (player->tx > COLUMNS - 1) player->tx = COLUMNS - 1;
    if (player->ty > ROWS - 1) player->ty = ROWS - 1;
}
    
