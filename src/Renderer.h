#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "particle.h"
#include "shader.h"
#include <optional>

class Renderer
{
public:
    Renderer();
    void draw(Particle particle);
    void draw(std::vector<Particle> particles);
    const unsigned int& VBO();
    const unsigned int& VAO();
    GLFWwindow* window();

private:
    int initialiseBuffers();
    int initialiseWindow();
    GLFWwindow* mWindow;
    unsigned int mVBO;
    unsigned int mVAO;
    std::optional<Shader> mShaderProgram;
};
