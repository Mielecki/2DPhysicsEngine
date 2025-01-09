#include "engine.hpp"

Engine::Engine(int width, int height) : mContainerWidth(width), mContainerHeight(height) {}

void Engine::addParticle()
{
    Particle particle({125, 50}, 5, {0xFF, 0xFF, 0xFF, 0xFF});
    particle.addVelocity({1, 1});
    
    mParticles.push_back(particle);
}

void Engine::resolveWallCollision()
{
    for (Particle& p : mParticles)
    {
        if (p.mPosition.y >= mContainerHeight - p.mRadius) p.mPosition.y = mContainerHeight - p.mRadius;
        if (p.mPosition.x >= mContainerWidth - p.mRadius) p.mPosition.x = mContainerWidth - p.mRadius;
        if (p.mPosition.x <= p.mRadius) p.mPosition.x = p.mRadius;
        if (p.mPosition.y <= p.mRadius) p.mPosition.y = p.mRadius;
    }
}

void Engine::resolveCollision()
{
    for (Particle& p1 : mParticles)
    {
        for (Particle& p2 : mParticles)
        {
            if (&p1 == &p2) continue;

            Vector2D offset = p1.mPosition - p2.mPosition;
            float minDistance = p1.mRadius + p2.mRadius;

            float distance = std::sqrt(offset.x * offset.x + offset.y * offset.y);

            if (distance < minDistance)
            {
                float delta = 0.5 * (distance - minDistance);
                Vector2D positionChange = offset / distance * delta;
                
                p1.mPosition -= positionChange;
                p2.mPosition += positionChange;
            }
        }
    }
}

void Engine::applyGravity()
{
    for (Particle& particle : mParticles)
    {
        particle.mAcceleration = {0, 200.0};
    }
}

void Engine::update(float dt)
{
    applyGravity();
    resolveCollision();
    resolveWallCollision();

    for (Particle& particle : mParticles)
    {
        particle.update(dt);
    }
}

std::vector<Particle>& Engine::getParticles()
{
    return mParticles;
}


void Engine::changeContainerSize(int width, int height)
{
    mContainerWidth = width;
    mContainerHeight = height;
}