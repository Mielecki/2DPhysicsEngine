#include "circle.hpp"
#include <SDL2/SDL.h>

Circle::Circle(SDL_Point center, int radius, SDL_Color color)
{
    this->mX = center.x;
    this->mY = center.y;
    this->mPreviousX = center.x;
    this->mPreviousY = center.y;
    this->radius = radius;
    this->color = color;
}

void Circle::draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Iterates through every pixel in the square of size 2*radius by 2*radius
    // If the pixel is inside the desired circle, it colors the pixel
    for (int x = -radius; x <= radius; x++)
    {
        for (int y = -radius; y <= radius; y++)
        {
            if ((x*x + y*y) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, mX + x, mY + y);
            }
        }
    }
}

void Circle::changeCenter(float dx, float dy)
{
    mPreviousX = mX;
    mPreviousY = mY;
    mX += dx;
    mY += dy;
}

int Circle::getRadius()
{
    return radius;
}

void Circle::update(float dt)
{
    float dy = mY - mPreviousY + 500*dt*dt;

    // Check if the circle has reached the floor
    // If so, reverse vertical velocity to simulate a bounce
    if (mY + dy >= 480 - radius) 
    {   
        dy = -dy * 0.8;
        mY = 480 - radius;
    }
    changeCenter(0, dy);
}