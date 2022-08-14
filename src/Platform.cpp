//
// Created by Andres on 27/06/22.
//

#include "Platform.h"
#include "Globals.h"
#include "glad/glad.h"
#include <iostream>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}


Platform::Platform() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    Globals::Renderer::window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (Globals::Renderer::window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return;
    }

    glfwMakeContextCurrent(Globals::Renderer::window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }


    glfwSetFramebufferSizeCallback(Globals::Renderer::window, framebuffer_size_callback);
}

Platform::~Platform() {

}

void Platform::Update() {
    glfwPollEvents();
    ProcessInput(Globals::Renderer::window);
    glfwGetFramebufferSize(Globals::Renderer::window, &Globals::Renderer::width, &Globals::Renderer::height);
    glfwSwapBuffers(Globals::Renderer::window);
}

bool Platform::isRunning() {
    return !glfwWindowShouldClose(Globals::Renderer::window);
}
