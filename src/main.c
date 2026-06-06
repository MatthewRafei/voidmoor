#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <SDL3/SDL.h>

#define RED	0xFFFF0000
#define GREEN	0xFF00FF00
#define BLUE	0xFF0000FF
#define BLACK	0xFF000000
#define WHITE	0xFFFFFFFF

#define WIDTH	320
#define HEIGHT	180

void tile_to_screen(int tx, int ty, int *sx, int *sy)
{
    *sx = (tx - ty) * 32 + (WIDTH / 2);
    *sy = (tx + ty) * 16 + (HEIGHT / 2);
}

void draw_to_screen(uint32_t *fb, int tx, int ty, uint32_t color)
{
    int sx = 0;
    int sy = 0;

    tile_to_screen(tx, ty, &sx, &sy);
    
    if(sx >= 0 && sx < WIDTH && sy >= 0 && sy < HEIGHT){
	fb[sy * WIDTH + sx] = color;
    }
}

int main(void)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
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
    
    draw_to_screen(framebuffer, 0, 0, RED);
    draw_to_screen(framebuffer, 1, 0, WHITE);
    draw_to_screen(framebuffer, 0, 1, BLUE);
    draw_to_screen(framebuffer, 1, 1, RED);
    
    int running = 1;
    SDL_Event event;
    while (running){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_EVENT_QUIT){
                running = 0;
            }
        }
	SDL_UpdateTexture(texture, NULL, framebuffer, WIDTH * sizeof(uint32_t));
	SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    free(framebuffer);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
