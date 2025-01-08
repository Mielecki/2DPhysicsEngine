#include "engine.hpp"

void Engine::addCircle()
{
    Circle circle({20, 50}, 20, {0xFF, 0xFF, 0xFF, 0xFF});
    circles.push_back(circle);

    Circle circle2({200, 220}, 10, {0xFF, 0xFF, 0xFF, 0xFF});
    circles.push_back(circle2);
}

void Engine::update(float dt)
{
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