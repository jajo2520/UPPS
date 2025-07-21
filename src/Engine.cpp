#include "Engine.h"
#include "Particle.h"
#include "ParticleQueue.h"
#include "Constants.h"
#include <cmath>


using size_t = std::size_t;

void Engine::update(Particle& particle, int frameCount)
{

    if (std::abs(particle.vel().y) < 0.1 && frameCount > 100 && particle.pos().y <= 50) 
    {
        particle.pos().y = 45;
        particle.vel().y = 0;
    }
    else if (particle.pos().y < 45 && particle.vel().y < 0)
    {
        resolveFloorCollision(particle);
    }
    else if ((particle.pos().x < 50 && particle.vel().x < 0) || (particle.pos().x > 750 && particle.vel().x > 0)) 
    {
        particle.vel().x *= -constants::COFR;
    }
    else 
    {
        applyGravity(particle);
    }
}

void Engine::update(ParticleQueue& particles, int frameCount)
{
    for (size_t i {}; i < particles.size(); ++i)
    {
        update(particles[i], frameCount);
        // check collisions
        for (size_t j {}; j < particles.size(); ++j)
        {
            if (i == j) continue;
            checkCollision(particles[i], particles[j]);
        }
    }
}

void Engine::applyGravity(Particle& particle)
{
    particle.pos() += particle.vel() * constants::TIME_STEP;
    particle.vel() += glm::vec2(0.0f, -400.f) * constants::TIME_STEP;
}

void Engine::resolveFloorCollision(Particle& particle)
{
    particle.vel().y *= -(constants::COFR);
    particle.pos().y = 45;
}

void Engine::resolveCollision(Particle& p1, Particle& p2)
{
    glm::vec2 vDiff {p1.vel() - p2.vel()};
    glm::vec2 xDiff {p1.pos() - p2.pos()};
    float dotP {glm::dot(vDiff, xDiff)};
    float dSqr {glm::dot(xDiff, xDiff)};
    glm::vec2 newV1 {p1.vel() - dotP/dSqr * xDiff};
    vDiff *= -1.0f;
    xDiff *= -1.0f;
    dotP = glm::dot(vDiff, xDiff);
    dSqr = glm::dot(xDiff, xDiff);
    glm::vec2 newV2 {p2.vel() - dotP/dSqr * xDiff};
    p1.vel() = newV1;
    p2.vel() = newV2;
}


void Engine::checkCollision(Particle& p1, Particle& p2)
{
    glm::vec2 dVec {p1.pos() - p2.pos()};
    float dSquared {dVec.x*dVec.x + dVec.y*dVec.y};
    if (dSquared < std::pow(constants::P_RADIUS*2, 2))
    {
        resolveCollision(p1, p2);
    }
}

