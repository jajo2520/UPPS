#pragma once

#include "Particle.h"
#include "ParticleQueue.h"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "Grid.h"

using size_t = std::size_t;

class Engine
{
private:
    Grid grid;
    void checkCollision(Particle& p1, Particle& p2);
    void resolveCollision(Particle& p1, Particle& p2);
    void applyGravity(Particle& particle);
    void resolveFloorCollision(Particle& particle);
    void gridLoop(size_t lowRow, size_t upRow, size_t lowCol, size_t upCol, Particle& particle);
public:
    Engine();
    void update(Particle& particle, int frameCount);
    void update(ParticleQueue& particles, int frameCount);
};
