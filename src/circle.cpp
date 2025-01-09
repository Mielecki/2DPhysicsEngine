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

void Circle::update(float dt)
{   
    // gravity
    accelerationY = 200.0;

    // Solve the situation when ball has reached the wall
    if (mY >= 480 - radius) mY = 480 - radius;
    if (mX >= 640 - radius) mX = 640 - radius;
    if (mX <= radius) mX = radius;
    if (mY <= radius) mY = radius;

    // Verlet Integration (https://www.algorithm-archive.org/contents/verlet_integration/verlet_integration.html)
    float dx = mX - mPreviousX + (accelerationX - (mX - mPreviousX) * 40)*dt*dt;
    float dy = mY - mPreviousY + (accelerationY - (mY - mPreviousY) * 40) *dt*dt;

    changeCenter(dx, dy);
}

void Circle::resolveCollision(Circle& other)
{
    float distanceX = other.mX - mX;
    float distanceY = other.mY - mY;
    float minDistance = radius + other.radius;
    float distance = std::sqrt(distanceX * distanceX + distanceY * distanceY);

    if (distance < minDistance)
    {
        float delta = 0.5 * (distance - minDistance);
        float dx = distanceX / distance * delta;
        float dy = distanceY / distance * delta;
        
        mX += dx;
        mY += dy;
        other.mX -= dx;
        other.mY -= dy;
    }
}