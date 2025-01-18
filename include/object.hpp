#pragma once

#include <SDL2/SDL.h>
#include "vector2D.hpp"

// An abstract class that defines all objects in the simulation
class Object
{
public:
    Object(SDL_Point position);

    // Renders Object on screen using renderer
    virtual void render(SDL_Renderer* renderer) = 0;

    // Updates Object's position
    void update(float dt);

    // Adds the given velocity value to current object's velocity
    void addVelocity(Vector2D velocity);

    void setColor(SDL_Color color);

    Vector2D getVelocity(float dt);


    Vector2D mPosition;
    Vector2D mPreviousPosition;
    Vector2D mAcceleration;
protected:
    SDL_Color mColor = {0xFF, 0xFF, 0xFF, 0xFF};
};