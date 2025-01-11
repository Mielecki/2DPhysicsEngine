#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Texture
{
public:
    Texture(SDL_Renderer* renderer, TTF_Font* font);

    ~Texture();

    bool loadFromRenderedText(std::string text, SDL_Color color);

    void free();

    void render(int x, int y);

private:
    SDL_Texture* mTexture;
    SDL_Renderer* mRenderer;
    TTF_Font* mFont;


    int mWidth;
    int mHeight;
};