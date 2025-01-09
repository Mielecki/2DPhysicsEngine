#include "engine.hpp"

bool Engine::addCircle()
{
    Circle circle({125, 50}, 5, {0xFF, 0xFF, 0xFF, 0xFF});
    circle.mPreviousX = 124;
    circle.mPreviousY = 49;
    


    circles.push_back(circle);
    return true;
}

void Engine::update(float dt)
{
    for (Circle& circle : circles)
    {
        for (Circle& other : circles)
        {
            if (&circle != &other) circle.resolveCollision(other);
        }
    }

    for (size_t i = 0; i < circles.size(); i++)
    {
        circles.at(i).update(dt);
    }
}

void Engine::drawAll(SDL_Renderer* renderer)
{
    for (size_t i = 0; i < circles.size(); i++)
    {
        circles.at(i).draw(renderer);
    }  
}