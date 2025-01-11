#pragma once

#include <SDL2/SDL.h>
#include "engine.hpp"
#include "texture.hpp"

class Graphics
{
public:
    Graphics();

    ~Graphics();

    bool init();

    bool loadMedia();

    void run();

    void cleanup();

private:
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    const int SCREEN_FPS = 60;

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    TTF_Font* mFont;
    Engine* mEngine;
};