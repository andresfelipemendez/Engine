//
// Created by fmend on 7/6/2022.
//

#include "RenderingSystem.h"
#include "Components/position.h"
#include "Components/renderer.h"


RenderingSystem::RenderingSystem() : s(Shader("shaders/vertex.glsl", "shaders/fragment.glsl")) {
}

bool RenderingSystem::Initialize(entt::registry& registry)
{
    float vertices[] = {
            0.5f, 0.5f, 0.0f,	// top right
            0.5f, -0.5f, 0.0f,	// bottom right
            -0.5f, -0.5f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f }; // top left

    unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3 };

    const auto entity = registry.create();

    unsigned int EBO;
    unsigned int VBO;
    unsigned int VAO;

    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    registry.emplace<renderer>(entity, EBO);

    return false;
}

void RenderingSystem::update(entt::registry& registry)
{
	auto view = registry.view<renderer>();
    view.each([&](const auto entity, auto& renderer) {

        s.use();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer.EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    });
}
