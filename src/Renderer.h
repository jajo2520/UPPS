#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Particle.h"
#include "Shader.h"

class Renderer
{
public:
    Renderer();
    void draw(Particle particle);
    void draw(std::vector<Particle> particles);
    const unsigned int& VBO();
    const unsigned int& VAO();
    Shader& shaderProgram();
    GLFWwindow* window();

private:
    int initialiseBuffers();
    int initialiseWindow();
    GLFWwindow* mWindow;
    unsigned int mVBO;
    unsigned int mVAO;
    Shader mShaderProgram;
};
