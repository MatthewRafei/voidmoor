#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <SDL3/SDL.h>

// TODO: Test painters algoithm
// TODO: Create consistent frame timing

#define RED	0xFFFF0000
#define GREEN	0xFF00FF00
#define BLUE	0xFF0000FF
#define BLACK	0xFF000000
#define WHITE	0xFFFFFFFF

#define WIDTH	640
#define HEIGHT	360

#define COLUMNS 8
#define ROWS    8

typedef struct {
    int ptx;
    int pty;
    uint32_t color;
} Player;

void tile_to_screen(int tx, int ty, int *sx, int *sy)
{
    *sx = (tx - ty) * 32 + (WIDTH / 2);
    *sy = (tx + ty) * 16 + (HEIGHT / 2);
}

void draw_to_screen(uint32_t *framebuffer, int tx, int ty, uint32_t color)
{
    int sx = 0;
    int sy = 0;

    tile_to_screen(tx, ty, &sx, &sy);
    
    if(sx >= 0 && sx < WIDTH && sy >= 0 && sy < HEIGHT){
	framebuffer[sy * WIDTH + sx] = color;
    }
}

void draw_tile(uint32_t *framebuffer, int sx, int sy, uint32_t color)
{
    for(int dy = -16; dy < 16; dy++){
	for(int dx = -32; dx < 32; dx++){
	    if(abs(dx) * 16 + abs(dy) * 32 <= 512){
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
    int ptx = player.ptx;
    int pty = player.pty;
    
    int psx = 0;
    int psy = 0;
    
    tile_to_screen(ptx, pty, &psx, &psy);
    
    if(psx >= 0 && psx < WIDTH && psy >= 0 && psy < HEIGHT){
	framebuffer[psy * WIDTH + psx] = player.color;
    }
}

int main(void)
{
    Player player = {4, 4, BLACK};
    
    uint8_t tilemap[ROWS][COLUMNS];
    memset(tilemap, 1, sizeof(tilemap));    
    
    if (!SDL_Init(SDL_INIT_VIDEO)){
        fprintf(stderr, "%s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow("VoidMoor", 1280, 720, 0);
    if (window == NULL){
        fprintf(stderr, "%s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL){
        fprintf(stderr, "%s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
    if(texture == NULL){
	fprintf(stderr, "%s\n", SDL_GetError());
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_FAILURE;
    }

    uint32_t *framebuffer = calloc((WIDTH * HEIGHT), sizeof(uint32_t));
    if(framebuffer == NULL){
	fprintf(stderr, "%s\n", "Failed to allocate framebuffer");
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_FAILURE;
    }
    
    bool running = true;
    SDL_Event event;
    while (running){
	memset(framebuffer, 0, WIDTH * HEIGHT * sizeof(*framebuffer));
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_EVENT_QUIT){
                running = false;
            }
	    if (event.type == SDL_EVENT_KEY_DOWN){
		if(event.key.key == SDLK_W){
		    player.ptx = player.ptx - 1;
		    player.pty = player.pty - 1;
		}
		if(event.key.key == SDLK_A){
		    player.ptx = player.ptx - 1;
		    player.pty = player.pty + 1;
		}
		if(event.key.key == SDLK_D){
		    player.ptx = player.ptx + 1;
		    player.pty = player.pty - 1;
		}
		if(event.key.key == SDLK_S){
		    player.ptx = player.ptx + 1;
		    player.pty = player.pty + 1;
		}
	    }
        }
	render_tilemap(tilemap, framebuffer);
	render_player(framebuffer, player);
	SDL_UpdateTexture(texture, NULL, framebuffer, WIDTH * sizeof(uint32_t));
	SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        //SDL_Delay(16);
    }

    free(framebuffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
