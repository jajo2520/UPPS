#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Particle.h"
#include "Renderer.h"
#include <vector>
#include <glm/glm.hpp>
// for random num
#include "RNG.h"
#include "ParticleQueue.h"
#include "Engine.h"
#include "Constants.h"

void processInput(GLFWwindow* window);
GLfloat deltaTime {}; 
GLfloat lastFrame {};
int frameCount {};
GLfloat accumulator {};
RNG rng {};

int main()
{

    ParticleQueue particles(geometry::P_NUMBER, geometry::P_RADIUS);
    for (auto& particle : particles)
    {
        particle.pos() = glm::vec2(rng.randInt(100, 700), rng.randInt(100, 700));
        particle.vel() = glm::vec2(rng.randInt(-2, 2), 0);
    }
    Renderer renderer;
    Engine engine;
    GLFWwindow* window {renderer.window()};
    // RENDER LOOP
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        frameCount += 1;

        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        accumulator += deltaTime;
        while (accumulator >= simulation::TIME_STEP)
        {     
            glClearColor(0.2f, 0.2f, 0.2f, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            engine.update(particles, frameCount);  
            renderer.draw(particles);

            accumulator -= simulation::TIME_STEP;

        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
