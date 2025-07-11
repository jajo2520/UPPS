#pragma once
#include <vector>
#include <glm/glm.hpp>

constexpr std::size_t verticesNum {15};

class Particle
{
private:
    float mRadius {};
    glm::vec2 mPos {};
    glm::vec2 mVel {};
    std::vector<float> mVertices;

    void genGeometry();
public:
    Particle(float radius); 

    float radius();
    std::vector<float>& vertices();
    glm::vec2 pos();
    glm::vec2 vel();

    void setPos(glm::vec2 vec);
    void setVel(glm::vec2 vec);
};
