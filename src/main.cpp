#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Particle.h"
#include "Renderer.h"
#include <glm/glm.hpp>


void processInput(GLFWwindow* window);
GLfloat deltaTime = 0.0f; 
GLfloat lastFrame = 0.0f;

int main()
{

    Particle particle(50);
    glm::vec2 pos(400, 700);
    glm::vec2 vel {};

    Renderer renderer;
    GLFWwindow* window {renderer.window()};
    // RENDER LOOP
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.2f, 0.2f, 0.2f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        vel += glm::vec2(0.0f, -9.8f) * deltaTime;
        pos += particle.vel();

        if (particle.pos().y < 45 && particle.vel().y < 0)
        {
            vel.y *= -1;
        }
        
        particle.setVel(vel);
        particle.setPos(pos);

        renderer.draw(particle);

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
