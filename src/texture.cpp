#include "texture.hpp"

Texture::Texture(SDL_Renderer* renderer, TTF_Font* font) : mTexture(nullptr), mRenderer(renderer), mFont(font), mWidth(0), mHeight(0) {}

Texture::~Texture()
{
    free();
}

bool Texture::loadFromRenderedText(std::string text, SDL_Color color)
{
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, text.c_str(), color);
    if (textSurface == nullptr)
    {
        printf("SDL_ttf render text surface error: %s\n", TTF_GetError());
        return false;
    }

    mTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
    if (mTexture == nullptr)
    {
        printf("SDL create texture form rendered text error: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return false;
    }

    mWidth = textSurface->w;
    mHeight = textSurface->h;

    SDL_FreeSurface(textSurface);

    return true;
}

void Texture::free()
{
    if (mTexture != nullptr)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

void Texture::render(int x, int y)
{
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    SDL_RenderCopy(mRenderer, mTexture, nullptr, &renderQuad);
}