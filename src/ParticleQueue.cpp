#include "ParticleQueue.h"
#include <vector>

using size_t = std::size_t;

ParticleQueue::ParticleQueue(size_t length, float radius)
{
    mParticles.reserve(length);
    mParticles.emplace_back(radius, true);
    for (size_t i {1}; i < length; i++) // start at second particle with other constructor
    {
        mParticles.emplace_back(radius, false);
    }
}


// todo: find a less shitty way of default initialising

ParticleQueue::ParticleQueue()
{
    mParticles.reserve(1);
    mParticles.emplace_back(0, true); // default value
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

void ParticleQueue::push(ParticleQueue& newParticles)
{
    if (mParticles.size() == 1 && mParticles[0].radius() == 0)
    {
        mParticles.erase(mParticles.begin());
    }
    // wow this is the shittiest solution ever
    
    mParticles.insert(mParticles.end(), newParticles.begin(), newParticles.end());
}

size_t ParticleQueue::size()
{
    return mParticles.size();
}


