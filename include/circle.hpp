#pragma once

#include <SDL2/SDL.h>

class Circle
{
public:
    Circle(SDL_Point center, int radius, SDL_Color color);

    void draw(SDL_Renderer* renderer);

    void changeCenter(float dx, float dy);

    int getRadius();

    void update(float dt);
    
private:
    float mX, mY;
    int radius;
    SDL_Color color;

    float mPreviousX, mPreviousY;
};