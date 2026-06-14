#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>

typedef struct {
    int tx;
    int ty;
    uint32_t color;
} Player;

void check_player_input(int tx_offset, int ty_offset, Player *player);

#endif //PLAYER_H
