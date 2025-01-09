#pragma once

#include <vector>
#include "circle.hpp"

class Engine
{
public:
    bool addCircle();

    void update(float dt);

    void drawAll(SDL_Renderer* renderer);

private:
    std::vector<Circle> circles;
};