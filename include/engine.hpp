#pragma once

#include <vector>
#include "particle.hpp"

class Engine
{
public:
    void addParticle();

    void update(float dt);

    void resolveCollision();

    void resolveWallCollision();

    void applyGravity();

    std::vector<Particle>& getParticles();

private:
    std::vector<Particle> mParticles;
};