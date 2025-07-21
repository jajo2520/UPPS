#pragma once

#include "Particle.h"
#include "ParticleQueue.h"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Engine
{
private:
    void checkCollision(Particle& p1, Particle& p2);
    void resolveCollision(Particle& p1, Particle& p2);
    void applyGravity(Particle& particle);
    void resolveFloorCollision(Particle& particle);
public:
    Engine() = default;
    void update(Particle& particle, int frameCount);
    void update(ParticleQueue& particles, int frameCount);
};
