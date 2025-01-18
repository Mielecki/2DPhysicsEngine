#include "particle.hpp"
#include <SDL2/SDL.h>

Particle::Particle(SDL_Point center, int radius)
: Object(center), mRadius(radius) {}

void Particle::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, mColor.r, mColor.g, mColor.b, mColor.a);

    // For each y-coordiante, calculate the maximum x-range using the circle equation and then draw a line using it
    for (int y = -mRadius; y <= mRadius; y++)
    {
        int dx = std::sqrt(mRadius * mRadius - y * y);
        SDL_RenderDrawLine(renderer, mPosition.x - dx, mPosition.y + y, mPosition.x + dx, mPosition.y + y);
    }
}