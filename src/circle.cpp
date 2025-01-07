#include <circle.hpp>
#include <SDL2/SDL.h>

Circle::Circle(SDL_Renderer* renderer, SDL_Point center, int radius, SDL_Color color)
{
    this->renderer = renderer;
    this->center = center;
    this->radius = radius;
    this->color = color;
}

void Circle::draw()
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
                SDL_RenderDrawPoint(renderer, center.x + x, center.y + y);
            }
        }
    }
}

void Circle::changeCenter(int dx, int dy)
{
    setCenter({center.x + dx, center.y + dy});
}

SDL_Point Circle::getCenter()
{
    return center;
}

void Circle::setCenter(SDL_Point center)
{
    this->center = center;
}