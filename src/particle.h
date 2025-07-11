#pragma once
#include <vector>

constexpr std::size_t verticesNum {15};

class Particle
{
private:
    float mRadius {};
    float mXTrans {};
    float mYTrans {};
    std::vector<float> mVertices;
    void genGeometry();
public:
    Particle(float radius); 
    float radius();
    std::vector<float>& vertices();
    float xTrans();
    float yTrans();
    void setXTrans(float x);
    void setYTrans(float y);
};
