#include "graphics.hpp"
#include <SDL2/SDL.h>
#include "circle.hpp"

Graphics::Graphics() : window(nullptr), renderer(nullptr) {}

// Initalizes SDL, window and renderer
void Graphics::init()
{
    // Initializes SDL video
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL initaliaztion error: %s\n", SDL_GetError());
        return;
    }

    // Creates window
    window = SDL_CreateWindow("2DPhysicsEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        printf("SDL creating window error: %s\n", SDL_GetError());
        return;
    }

    // Creates renderer for window that uses hardware acceleration and vsync
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        printf("SDL creating renderer error: %s\n", SDL_GetError());
        return;
    }
}

// Closes SDL2
void Graphics::cleanup()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = nullptr;
    window = nullptr;

    SDL_Quit();
}

void Graphics::run()
{
    // Flag that indicates wheter the engine is running
    bool running = true;

    // Event handler (necessary to prevent the window from closing immediately)
    SDL_Event e;

    Circle circle(renderer, {100, 100}, 100, {0xFF, 0xFF, 0xFF, 0xFF});

    while (running)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            // Prevents from closing immediately
            if (e.type == SDL_QUIT)
            {
                running = false;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0x40, 0x40, 0x40, 0xFF);
        SDL_RenderClear(renderer);

        circle.draw();
        circle.changeCenter(1, 1);

        SDL_RenderPresent(renderer);
    }
}