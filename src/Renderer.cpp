#include "Renderer.h"

#include "Shader.h"
#include "Globals.h"

color Globals::Renderer::clearColor;
GLFWwindow *Globals::Renderer::window;


void Renderer::Render() {



    glViewport(0, 0, Globals::Renderer::width, Globals::Renderer::height);
    auto clear_color = Globals::Renderer::clearColor;
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    //glUseProgram(shaderProgram);
    s.use();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


}

Renderer::Renderer() : s(Shader("shaders/vertex.glsl", "shaders/fragment.glsl")) {
    float vertices[] = {
            0.5f, 0.5f, 0.0f,	// top right
            0.5f, -0.5f, 0.0f,	// bottom right
            -0.5f, -0.5f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f}; // top left

    unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3};


    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

}

Renderer::~Renderer() {

}
