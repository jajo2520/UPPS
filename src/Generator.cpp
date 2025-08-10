#include "Generator.h"
#include "Particle.h"
#include <vector>
#include "ParticleQueue.h"
#include "Constants.h"
#include "RNG.h"


Generator::Generator() : mParticles{}
{}
 
void Generator::genRandom(float x, float y, float width, float height, size_t num)
{
    RNG rng {};
    ParticleQueue newParticles(num, geometry::P_RADIUS);
    for (auto& particle : newParticles)
    {
        particle.pos() = glm::vec2(rng.randInt(x, x+width), rng.randInt(y, y+height));
    }
    mParticles.push(newParticles);
}

ParticleQueue& Generator::particles() { return mParticles; }
