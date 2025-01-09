#include "particle.hpp"
#include <SDL2/SDL.h>

Particle::Particle(SDL_Point center, int radius, SDL_Color color)
: mPosition(center.x, center.y), mPreviousPosition(center.x, center.y), mRadius(radius), mColor(color) {}

void Particle::draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, mColor.r, mColor.g, mColor.b, mColor.a);

    // For each y-coordiante, calculate the maximum x-range using the circle equation and then draw a line using it
    for (int y = -mRadius; y <= mRadius; y++)
    {
        int dx = std::sqrt(mRadius * mRadius - y * y);
        SDL_RenderDrawLine(renderer, mPosition.x - dx, mPosition.y + y, mPosition.x + dx, mPosition.y + y);
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
    Vector2D newPosition = mPosition * 2 - mPreviousPosition + (mAcceleration - (mPosition - mPreviousPosition) * 50) * dt * dt;

    changePosition(newPosition);
}