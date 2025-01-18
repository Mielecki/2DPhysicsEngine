#include "object.hpp"

Object::Object(SDL_Point center)
: mPosition(center.x, center.y), mPreviousPosition(center.x, center.y) {}

void Object::update(float dt)
{
    // Verlet Integration (https://www.algorithm-archive.org/contents/verlet_integration/verlet_integration.html)
    Vector2D newPosition = mPosition * 2 - mPreviousPosition + (mAcceleration - (mPosition - mPreviousPosition) * 50) * dt * dt;

    mPreviousPosition = mPosition;
    mPosition = newPosition;
}


void Object::setColor(SDL_Color color)
{
    mColor = color;
}

void Object::addVelocity(Vector2D velocity)
{
    mPreviousPosition -= velocity;
}


Vector2D Object::getVelocity(float dt)
{
    return (mPosition - mPreviousPosition) / dt;
}