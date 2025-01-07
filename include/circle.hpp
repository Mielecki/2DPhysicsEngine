#pragma once

#include <SDL2/SDL.h>

class Circle
{
public:
    Circle(SDL_Renderer* renderer, SDL_Point center, int radius, SDL_Color color);

    void draw();

    void changeCenter(int dx, int dy);

    SDL_Point getCenter();

    void setCenter(SDL_Point center);
private:
    SDL_Renderer* renderer;
    SDL_Point center;
    int radius;
    SDL_Color color;
};