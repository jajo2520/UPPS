#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Particle.h"
#include "Renderer.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include "ParticleQueue.h"
#include "Constants.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height); 


Renderer::Renderer()
{
    initialiseWindow();
    mShaderProgram = Shader("../shaders/vshader.vert", "../shaders/fshader.frag");
    mShaderProgram.use();
    initialiseBuffers();
}

const unsigned int& Renderer::VBO() { return mVBO; }
const unsigned int& Renderer::VAO() { return mVAO; }
Shader& Renderer::shaderProgram() { return mShaderProgram; }
GLFWwindow* Renderer::window() { return mWindow; }

int Renderer::initialiseWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // apple thing
  
    GLFWwindow* window = glfwCreateWindow(screen::SCREEN_WIDTH, screen::SCREEN_HEIGHT, "UPPS", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to initialise window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // make main context of current thread

    // deal with glad (load function pointers)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // thank u stack overflow 
    {
        std::cout << "Failed to initialise GLAD" << std::endl;
        return -1;
    }
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    int frameBufferWidth, frameBufferHeight;
    glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);

    // tell OpenGL how big our GLFW window is 
    glViewport(0, 0, frameBufferWidth, frameBufferHeight); // first two is loc of bottom left of window
    std::cout << "all good;";
    mWindow = window;
    return 0;
}

int Renderer::initialiseBuffers()
{
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO); // remember VBO stores vertices

    return 0;
};



void Renderer::draw(Particle particle)
{
    glBindVertexArray(VAO());

    glBindBuffer(GL_ARRAY_BUFFER, VBO());
    glBufferData(GL_ARRAY_BUFFER, particle.vertices().size()*sizeof(float), particle.vertices().data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    shaderProgram().setVec2("pos", particle.pos());
    shaderProgram().setVec2("vel", particle.vel());
    shaderProgram().setVec2("screenSize", glm::vec2(screen::SCREEN_WIDTH, screen::SCREEN_HEIGHT));

    glDrawArrays(GL_TRIANGLE_FAN, 0, verticesNum+2);
}

void Renderer::draw(ParticleQueue particles)
{
    for (Particle& particle : particles)
    {
        Renderer::draw(particle);
    }
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

