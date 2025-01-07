#pragma once

#include <SDL2/SDL.h>

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

    SDL_Window* window;
    SDL_Renderer* renderer;
};