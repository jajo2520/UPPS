#include "ParticleQueue.h"
#include "RNG.h"
#include <vector>

using size_t = std::size_t;

ParticleQueue::ParticleQueue(size_t length, float radius)
{
    mParticles.reserve(length);
    for (size_t i {}; i < length; i++)
    {
        mParticles.emplace_back(radius);
    }
}

Particle& ParticleQueue::operator[] (size_t i) { return mParticles[i]; };
auto ParticleQueue::begin() -> typename std::vector<Particle>::iterator 
{
    return mParticles.begin();
}
auto ParticleQueue::end() -> typename std::vector<Particle>::iterator 
{
    return mParticles.end();
}

size_t ParticleQueue::size()
{
    return mParticles.size();
}
