#include "graphics.hpp"
#include <SDL2/SDL.h>
#include "engine.hpp"
#include "timer.hpp"
#include <string>
#include <sstream>

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

    Engine engine;

    std::stringstream title;
    title.precision(4);

    Timer capTimer;

    float dt = 1.0 / FPS;

    int maxCircles = 1500;
    int currentCircles = 0;

    while (running)
    {   
        capTimer.start();
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

        if (currentCircles < maxCircles && engine.addCircle()) currentCircles++;
        engine.update(dt);
        engine.drawAll(renderer);

        SDL_RenderPresent(renderer);

        title.str("");
        title << "FPS: " << 1000.0 / capTimer.getTicks() << "; Circles: " << currentCircles;
        SDL_SetWindowTitle(window, title.str().c_str());

        int frameTicks = capTimer.getTicks();
        if (frameTicks < 1000 / FPS)
        {
            SDL_Delay(1000/FPS - frameTicks);
        }
    }
}