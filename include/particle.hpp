#pragma once

#include <SDL2/SDL.h>
#include "vector2D.hpp"

class Particle
{
public:
    Particle(SDL_Point position, int radius, SDL_Color color);

    void draw(SDL_Renderer* renderer);

    // Sets current position to the given position and sets mPreviousPosition to the previous position 
    void changePosition(Vector2D position);

    void update(float dt);

    void addVelocity(Vector2D velocity);

    void setColor(SDL_Color color);

    Vector2D getVelocity(float dt);
    
    Vector2D mPosition;
    Vector2D mPreviousPosition;
    Vector2D mAcceleration;
    int mRadius;
private:
    SDL_Color mColor;
};