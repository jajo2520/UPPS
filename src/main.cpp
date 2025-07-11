#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "particle.h"
#include "Renderer.h"


void processInput(GLFWwindow* window);

int main()
{

    Particle particle(0.05);

    Renderer renderer;
    GLFWwindow* window {renderer.window()};
    // RENDER LOOP
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.2f, 0.2f, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        
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
