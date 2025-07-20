#pragma once

#include "Particle.h"
#include "RNG.h"
#include <vector>

using size_t = std::size_t;


class ParticleQueue
{
private:
    std::vector<Particle> mParticles;
public:
    ParticleQueue(size_t length, float radius);
    Particle& operator[] (size_t i);
    auto begin() -> typename std::vector<Particle>::iterator;
    auto end() -> typename std::vector<Particle>::iterator;
};
