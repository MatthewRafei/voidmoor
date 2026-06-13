#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <SDL3/SDL.h>

#include "player.h"
#include "render.h"
#include "common.h"

// TODO: Test painters algoithm
// TODO: Create consistent frame

int main(void)
{
    Player player = {4, 4, BLUE};

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
            if (event.type == SDL_EVENT_KEY_DOWN) {
		int tx_offset = 0;
		int ty_offset = 0;
		switch (event.key.key) {
                case SDLK_W:
                    tx_offset = -1;
                    ty_offset = -1;
                    break;
                case SDLK_A:
                    tx_offset = -1;
                    ty_offset = 1;
                    break;
                case SDLK_D:
                    tx_offset = 1;
                    ty_offset = -1;
                    break;
                case SDLK_S:
                    tx_offset = 1;
                    ty_offset = 1;
                    break;
                default:
                    break;
                }
                check_player_input(tx_offset, ty_offset, &player);
            }
        }
    	render_tilemap(tilemap, framebuffer);
	render_player(framebuffer, player);
	SDL_UpdateTexture(texture, NULL, framebuffer, WIDTH * sizeof(uint32_t));
	SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    free(framebuffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
