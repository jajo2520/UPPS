#include <vector>
#include <cmath>
#include "Particle.h"

constexpr double PI {3.141592653};
using size_t = std::size_t;

void Particle::genGeometry()
{
    for (size_t i {}; i < verticesNum; ++i)
    {
        double xcoord {std::cos(i*2*PI/verticesNum)*mRadius};
        double ycoord {std::sin(i*2*PI/verticesNum)*mRadius};
        mVertices[2*(i+1)] = static_cast<float>(xcoord);
        mVertices[2*(i+1)+1] = static_cast<float>(ycoord);
        if (i == 0)
        {
            mVertices[2*(verticesNum+1)] = static_cast<float>(xcoord);
            mVertices[2*(verticesNum+1)+1] = static_cast<float>(ycoord);
        }
    }
}

Particle::Particle(float radius) : mRadius {radius}, mVertices{std::vector<float>(2*(verticesNum+2))}
{
    genGeometry();
}

float Particle::radius() { return mRadius; }
glm::vec2 Particle::pos() { return mPos; }
glm::vec2 Particle::vel() { return mVel; }
std::vector<float>& Particle::vertices() { return mVertices; }

void Particle::setPos(glm::vec2 vec) { mPos = vec; };
void Particle::setVel(glm::vec2 vec) { mVel = vec; };
