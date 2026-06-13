#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>

#include "player.h"
#include "common.h"
#include "camera.h"

#define WIDTH	          640
#define HEIGHT 360

#define TILE_WIDTH        64
#define TILE_HEIGHT       32

#define TILE_WIDTH_HALF   (TILE_WIDTH / 2)
#define TILE_HEIGHT_HALF  (TILE_HEIGHT / 2)

#define TILE_DIAMOND_THRESHOLD (TILE_WIDTH_HALF * TILE_HEIGHT_HALF)

void tile_to_screen(int tx, int ty, int *sx, int *sy, Camera *camera);
void draw_tile(uint32_t *framebuffer, int sx, int sy, uint32_t color);
void render_tilemap(uint8_t tilemap[ROWS][COLUMNS], uint32_t *framebuffer, Camera *camera);
void render_player(uint32_t *framebuffer, Player player, Camera *camera);

#endif //RENDER_H
