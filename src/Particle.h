#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Constants.h"

constexpr std::size_t verticesNum {geometry::VERT_NUMBER};

class Particle
{
private:
    float mRadius {};
    glm::vec2 mPos {};
    glm::vec2 mVel {};
    std::vector<float> mVertices;

    void genGeometry();
public:
    Particle(float radius, bool first);
    Particle(float radius, std::vector<float>& verticles);
    Particle(float radius, float xpos, float ypos);
    Particle();

    float radius();
    std::vector<float>& vertices();
    glm::vec2& pos();
    glm::vec2& vel();

};
