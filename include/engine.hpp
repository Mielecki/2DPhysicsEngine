#pragma once

#include <vector>
#include "particle.hpp"

class Engine
{
public:
    Engine(int width, int height);

    void addParticle();

    void update(float dt);

    void resolveCollision();

    void resolveWallCollision();

    void applyGravity();

    void changeContainerSize(int width, int height);

    std::vector<Particle>& getParticles();

private:
    int mContainerWidth;
    int mContainerHeight;

    std::vector<Particle> mParticles;
};