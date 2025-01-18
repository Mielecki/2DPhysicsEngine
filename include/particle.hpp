#pragma once

#include "object.hpp"

class Particle : public Object
{
public:
    Particle(SDL_Point position, int radius);

    void render(SDL_Renderer* renderer) override;
    
    int mRadius;
};