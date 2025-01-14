#pragma once

#include <SDL2/SDL.h>
#include "engine.hpp"
#include "texture.hpp"
#include "timer.hpp"

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
    const Uint32 FPS_UPDATE_INTERVAL = 400;
    const float MAX_DRAW_VELOCITY = 200;
    const SDL_Color TEXT_COLOR = {0xFF, 0xFF, 0xFF};

    float dt;    
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    TTF_Font* mFont;
    Engine* mEngine;

    void updateFPS(int &frameCounter, Timer& fpsTimer, Texture& fpsText);

    void drawParticles();

    void handleEvents(SDL_Event& e, bool& running, SDL_Point &mousePosition, int &particlesCount);
};