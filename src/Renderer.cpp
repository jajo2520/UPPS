#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "particle.h"
#include "shader.h"
#include "Renderer.h"
#include <optional>


void framebuffer_size_callback(GLFWwindow* window, int width, int height); 

Renderer::Renderer()
{
    initialiseWindow();
    mShaderProgram.emplace("../shaders/vshader.vert", "../shaders/fshader.frag");
    mShaderProgram->use();
    // basically this shader construction needs to be delayed until window is initalised
    initialiseBuffers();
}

const unsigned int& Renderer::VBO() { return mVBO; }
const unsigned int& Renderer::VAO() { return mVAO; }
GLFWwindow* Renderer::window() { return mWindow; }

int Renderer::initialiseWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // apple thing
  
    GLFWwindow* window = glfwCreateWindow(800, 800, "UPPS", NULL, NULL);
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

    // tell OpenGL how big our GLFW window is 
    glViewport(0, 0, 800, 800); // first two is loc of bottom left of window
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

    glDrawArrays(GL_TRIANGLE_FAN, 0, verticesNum+2);
}
//void Renderer::draw(std::vector<Particle> particles);


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

