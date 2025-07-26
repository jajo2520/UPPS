#include "Engine.h"
#include "Particle.h"
#include "ParticleQueue.h"
#include "Constants.h"
#include <cmath>


using size_t = std::size_t;

Engine::Engine() : grid{}
{}

void Engine::update(Particle& particle, int frameCount)
{
    size_t row = static_cast<size_t>(particle.pos().y / screen::CELL_SIZE);
    size_t col = static_cast<size_t>(particle.pos().x / screen::CELL_SIZE);
    grid.removeParticle(&particle, row, col);    
    

    if (std::abs(particle.vel().y) < 0.1 && frameCount > 100 && particle.pos().y <= geometry::FLOOR) 
    {
        particle.pos().y = geometry::FLOOR;
        particle.vel().y = 0;
    }
    else if (particle.pos().y < geometry::FLOOR && particle.vel().y < 0)
    {
        resolveFloorCollision(particle);
    }
    else if (particle.pos().y > geometry::CEILING && particle.vel().y > 0)
    {
        particle.vel().y *= -physics::COFR;
        particle.pos().y = geometry::CEILING;
    }
    else if ((particle.pos().x < geometry::WALL_LEFT && particle.vel().x < 0) || (particle.pos().x > geometry::WALL_RIGHT && particle.vel().x > 0)) 
    {
        particle.vel().x *= -physics::COFR;
    }
    else 
    {
        applyGravity(particle);
    }
    
    row = static_cast<size_t>(particle.pos().y / screen::CELL_SIZE);
    col = static_cast<size_t>(particle.pos().x / screen::CELL_SIZE);

    grid.addParticle(&particle, row, col);


}

void Engine::gridLoop(size_t lowRow, size_t upRow, size_t lowCol, size_t upCol, Particle& particle)
{
    for (size_t i {lowRow}; i < upRow; ++i)
    {
        for (size_t j {lowCol}; j < upCol; ++j)
        {
            std::vector<Particle*> particlePointers {grid.getParticles(i, j)};
            for (Particle* partPoint : particlePointers)
            {
                if (&particle != partPoint)
                {
                    checkCollision(particle, *partPoint);
                    // this is the shittiest code i have ever written
                }
            }
        }
    }
}
    
void Engine::update(ParticleQueue& particles, int frameCount)
{
    // new collision checker
    for (auto& particle : particles)
    {
        
        update(particle, frameCount);

        size_t row = static_cast<size_t>(particle.pos().y / screen::CELL_SIZE);
        size_t col = static_cast<size_t>(particle.pos().x / screen::CELL_SIZE);
        if (row > 0 && row < (screen::SCREEN_HEIGHT / screen::CELL_SIZE))
        {
            if (col > 0 && col < (screen::SCREEN_WIDTH / screen::CELL_SIZE))
            {
                gridLoop(row-1, row+1, col-1, col+1, particle);
            }
            else 
            {
                if (col <= 0)
                    gridLoop(row-1, row+1, col, col+1, particle);
                else 
                    gridLoop(row-1, row+1, col-1, col, particle);
            }
        }
        else 
        {
            if (row <= 0)
                gridLoop(row, row+1, col-1, col+1, particle);
            else 
                gridLoop(row-1, row, col-1, col+1, particle);
        }
        
    }
}



void Engine::applyGravity(Particle& particle)
{
    particle.pos() += particle.vel() * simulation::TIME_STEP;
    particle.vel() += physics::GRAVITY * simulation::TIME_STEP;
}

void Engine::resolveFloorCollision(Particle& particle)
{
    particle.vel().y *= -(physics::COFR);
    particle.pos().y = geometry::FLOOR;
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
    if (dSquared < std::pow(geometry::P_RADIUS*2, 2))
    {
        resolveCollision(p1, p2);
    }
}

