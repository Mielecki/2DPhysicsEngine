#include "particle.hpp"
#include <SDL2/SDL.h>

Particle::Particle(SDL_Point center, int radius, SDL_Color color)
: mPosition(center.x, center.y), mPreviousPosition(center.x, center.y), mRadius(radius), mColor(color) {}

void Particle::draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, mColor.r, mColor.g, mColor.b, mColor.a);

    // Iterates through every pixel in the square of size 2*radius by 2*radius
    // If the pixel is inside the desired particle, it colors the pixel
    for (int x = -mRadius; x <= mRadius; x++)
    {
        for (int y = -mRadius; y <= mRadius; y++)
        {
            if ((x*x + y*y) <= (mRadius * mRadius))
            {
                SDL_RenderDrawPoint(renderer, mPosition.x + x, mPosition.y + y);
            }
        }
    }
}

void Particle::addVelocity(Vector2D velocity)
{
    mPreviousPosition -= velocity;
}

void Particle::changePosition(Vector2D position)
{
    mPreviousPosition = mPosition;
    mPosition = position;
}

void Particle::update(float dt)
{   
    // Verlet Integration (https://www.algorithm-archive.org/contents/verlet_integration/verlet_integration.html)
    Vector2D newPosition = mPosition * 2 - mPreviousPosition + (mAcceleration - (mPosition - mPreviousPosition) * 40) * dt * dt;

    changePosition(newPosition);
}