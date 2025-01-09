#pragma once

#include <SDL2/SDL.h>
#include "engine.hpp"

class Graphics
{
public:
    Graphics();

    void init();

    void run();

    void cleanup();

private:
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    const int SCREEN_FPS = 60;

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    Engine mEngine;
};