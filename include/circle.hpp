#pragma once

#include <SDL2/SDL.h>

class Circle
{
public:
    Circle(SDL_Point center, int radius, SDL_Color color);

    void draw(SDL_Renderer* renderer);

    void changeCenter(float dx, float dy);

    void resolveCollision(Circle& other);

    void update(float dt);
    
    float mX, mY;
    float mPreviousX, mPreviousY;
    int radius;
    float accelerationX = 0;
    float accelerationY = 0;
private:
    SDL_Color color;
};