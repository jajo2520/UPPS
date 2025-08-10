#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Particle.h"
#include "Renderer.h"
#include <glm/glm.hpp>
#include "RNG.h"
#include "ParticleQueue.h"
#include "Engine.h"
#include "Constants.h"
#include <IOKit/pwr_mgt/IOPMLib.h>
#include "Generator.h"

void processInput(GLFWwindow* window, IOPMAssertionID assertionID);
GLfloat deltaTime {}; 
GLfloat lastFrame {};
GLfloat accumulator {};
RNG rng {};

int main()
{
    IOPMAssertionID assertionID;
    IOReturn success = IOPMAssertionCreateWithName(kIOPMAssertionTypeNoIdleSleep,
                                                    kIOPMAssertionLevelOn,
                                                    CFSTR("UPPS high perf"),
                                                    &assertionID);

    

    Generator generator {};
    generator.genRandom(100, 100, 1000, 1000, 5000);
    ParticleQueue particles {generator.particles()};
    for (auto& particle : particles)
    {
        particle.vel() = glm::vec2(rng.randInt(-2, 2), 0);
    }

    Renderer renderer;
    Engine engine;
    GLFWwindow* window {renderer.window()};
    // RENDER LOOP
    while (!glfwWindowShouldClose(window))
    {


        processInput(window, assertionID);

        renderer.draw(particles);
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        accumulator += deltaTime;
        while (accumulator >= simulation::TIME_STEP)
        {     
            engine.update(particles, simulation::FRAME_COUNT);  
            std::cout << simulation::COLLISIONS << std::endl;
            simulation::TOTAL_COLLISIONS += simulation::COLLISIONS;
            simulation::COLLISIONS = 0;
            simulation::FRAME_COUNT += 1;

            accumulator -= simulation::TIME_STEP;
            
        }

        glfwSwapBuffers(window);        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(0.1f, 0.1f, 0.1f, 1);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow* window, IOPMAssertionID assertionID)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        std::cout << "AVG: " << simulation::TOTAL_COLLISIONS / simulation::FRAME_COUNT;
        IOPMAssertionRelease(assertionID);
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        physics::GRAVITY = glm::vec2(0.f, 250.f);
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        physics::GRAVITY = glm::vec2(0.f, -250.f);
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
        physics::GRAVITY = glm::vec2(-250.f, 0.f);
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        physics::GRAVITY = glm::vec2(250.f, 0.f);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        physics::GRAVITY = glm::vec2(0.f, 0.f);
}
