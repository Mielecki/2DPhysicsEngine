#include "graphics.hpp"
#include <SDL2/SDL.h>
#include "particle.hpp"
#include "timer.hpp"
#include "engine.hpp"
#include <string>
#include <sstream>

Graphics::Graphics() : mWindow(nullptr), mRenderer(nullptr), mEngine(nullptr) {}

Graphics::~Graphics()
{
    cleanup();
}

// Initalizes SDL, window, renderer and physics engine
void Graphics::init()
{
    // Initializes SDL video
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL initaliaztion error: %s\n", SDL_GetError());
        return;
    }

    // Creates window
    mWindow = SDL_CreateWindow("2DPhysicsEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (mWindow == nullptr)
    {
        printf("SDL creating window error: %s\n", SDL_GetError());
        return;
    }

    // Creates renderer for window that uses hardware acceleration and vsync
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (mRenderer == nullptr)
    {
        printf("SDL creating renderer error: %s\n", SDL_GetError());
        return;
    }

    mEngine = new Engine(SCREEN_WIDTH, SCREEN_HEIGHT);
}

// Closes SDL2
void Graphics::cleanup()
{
    if (mEngine != nullptr)
    {
        delete mEngine;
        mEngine = nullptr;
    }

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    mRenderer = nullptr;
    mWindow = nullptr;

    SDL_Quit();
}

void Graphics::run()
{
    // Flag that indicates wheter the engine is running
    bool running = true;

    // Event handler (necessary to prevent the window from closing immediately)
    SDL_Event e;

    std::stringstream title;
    title.precision(4);

    Timer capTimer;

    float dt = 1.0 / SCREEN_FPS;

    int maxParticles = 50;
    int currentParticles = 0;

    int currentFrame = 0;

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

        if (currentFrame % 5 == 0 && currentParticles < maxParticles)
        {
            currentParticles++;
            mEngine->addParticle();
        }

        int h, w;
        SDL_GetWindowSize(mWindow, &w, &h);
        mEngine->changeContainerSize(w, h);

        SDL_SetRenderDrawColor(mRenderer, 0x40, 0x40, 0x40, 0xFF);
        SDL_RenderClear(mRenderer);

        mEngine->update(dt);

        for (Particle& particle : mEngine->getParticles())
        {
            particle.draw(mRenderer);
        }

        SDL_RenderPresent(mRenderer);

        // Shows FPS and current amount of particles in the window title
        title.str("");
        title << "FPS: " << 1000.0 / capTimer.getTicks() << "; Particles: " << currentParticles;
        SDL_SetWindowTitle(mWindow, title.str().c_str());

        int frameTicks = capTimer.getTicks();
        if (frameTicks < 1000 / SCREEN_FPS)
        {
            SDL_Delay(1000/SCREEN_FPS - frameTicks);
        }

        currentFrame++;
    }
}