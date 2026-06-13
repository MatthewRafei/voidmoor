#include <stdlib.h>

#include "render.h"
#include "common.h"


void tile_to_screen(int tx, int ty, int *sx, int *sy)
{
    *sx = (tx - ty) * TILE_WIDTH_HALF + (WIDTH / 2);
    *sy = (tx + ty) * TILE_HEIGHT_HALF + (HEIGHT / 2);
}

void draw_tile(uint32_t *framebuffer, int sx, int sy, uint32_t color)
{
    for(int dy = -TILE_HEIGHT_HALF; dy < TILE_HEIGHT_HALF; dy++){
	for(int dx = -TILE_WIDTH_HALF; dx < TILE_WIDTH_HALF; dx++){
	    if(abs(dx) * TILE_HEIGHT_HALF + abs(dy) * TILE_WIDTH_HALF <= TILE_DIAMOND_THRESHOLD){
		int px = sx + dx;
		int py = sy + dy;
		if(px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT){
		    framebuffer[py * WIDTH + px] = color;
		}
	    }
	}
    }
}

void render_tilemap(uint8_t tilemap[ROWS][COLUMNS], uint32_t *framebuffer)
{
    for(int i = 0; i < ROWS; i++){
	for(int j = 0; j < COLUMNS; j++){
	    if(tilemap[i][j] == 1){
		int sx = 0;
		int sy = 0;
		tile_to_screen(j, i, &sx, &sy);
		draw_tile(framebuffer, sx, sy, (i + j) % 2 ? RED : GREEN);
	    }
	}
    }
}

void render_player(uint32_t *framebuffer, Player player)
{
    int tx = player.tx;
    int ty = player.ty;

    int sx = 0;
    int sy = 0;

    tile_to_screen(tx, ty, &sx, &sy);

    if(sx >= 0 && sx < WIDTH && sy >= 0 && sy < HEIGHT){
	draw_tile(framebuffer, sx, sy, player.color);
    }
}
