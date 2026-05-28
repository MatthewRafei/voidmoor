#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <SDL3/SDL.h>

#define WIDTH 320
#define HEIGHT 180

int main(void)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow("VoidMoor", 1280, 720, 0);
    if (window == NULL) {
        fprintf(stderr, "%s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL) {
        fprintf(stderr, "%s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    uint32_t *framebuffer = malloc((WIDTH * HEIGHT) * sizeof(uint32_t));
    if(framebuffer == NULL){
	    fprintf(stderr, "%s\n", "Failed to allocate framebuffer");
	    SDL_DestroyRenderer(renderer);
	    SDL_DestroyWindow(window);
	    SDL_Quit();
	    return EXIT_FAILURE;
    }
    memset(framebuffer, 0, ((WIDTH * HEIGHT) * sizeof(uint32_t)));

    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    free(framebuffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
