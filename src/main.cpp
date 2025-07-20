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

void processInput(GLFWwindow* window);
GLfloat deltaTime {}; 
GLfloat lastFrame {};
int frameCount {};
GLfloat accumulator {};
float COFR {0.8};
float timeStep {0.0167}; // 60 fps
RNG rng {};

int main()
{

    ParticleQueue particles(1000, 2);
    for (auto& particle : particles)
    {
        particle.pos() = glm::vec2(rng.randInt(100, 700), rng.randInt(100, 700));
    }
    Renderer renderer;
    GLFWwindow* window {renderer.window()};
    // RENDER LOOP
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        frameCount += 1;

        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.2f, 0.2f, 0.2f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        accumulator += deltaTime;
        while (accumulator >= timeStep)
        {     
            for (auto& particle : particles)
            {
                if (std::abs(particle.vel().y) < 0.01 && frameCount > 100 && particle.pos().y <= 50) 
                {
                    particle.pos().y = 45;
                    particle.vel().y = 0;
                }
                else if (particle.pos().y < 45 && particle.vel().y < 0)
                {
                    particle.vel().y *= -COFR;
                    particle.pos().y = 45;
                }
                else 
                {
                    particle.pos() += particle.vel() * timeStep;
                    particle.vel() += glm::vec2(0.0f, -400.f) * timeStep;
                }
                
                renderer.draw(particle);
            }

            accumulator -= timeStep;

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
