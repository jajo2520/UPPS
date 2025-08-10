#pragma once

#include "ParticleQueue.h"

using size_t = std::size_t;

class Generator
{
private:
    ParticleQueue mParticles;

public:
    Generator();
    void genCircle(float x, float y, float radius, size_t num);
    void genRectangle(float x, float y, float width, float height, size_t num);
    void genRandom(float x, float y, float width, float height, size_t num);
    ParticleQueue& particles();
};
