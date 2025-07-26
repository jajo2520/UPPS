#pragma once
#include "Particle.h"
#include "ParticleQueue.h"
#include "Constants.h"
#include <vector>

using size_t = std::size_t;

class Grid
{
private:
    std::vector<std::vector<Particle*>> mData;
    size_t rows, cols;
public:
    Grid();
    size_t getIndex(size_t row, size_t col);
    void addParticle(Particle* particle, size_t row, size_t col);
    void removeParticle(Particle* particle, size_t row, size_t col);
    void eraseGrid();
    std::vector<Particle*>& getParticles(size_t row, size_t col);
};

