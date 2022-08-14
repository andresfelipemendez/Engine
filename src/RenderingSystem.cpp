//
// Created by fmend on 7/6/2022.
//

#include "RenderingSystem.h"
#include "Components/position.h"
#include "Components/renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static int width = 640;
static int height = 480;
static void* dc = nullptr;

static double l = -0.5500;
static double r = +0.5500;
static double b = -0.4125;
static double t = +0.4125;
static double n = +1.0;
static double f = +100.0;

static int xvp = 0;
static int yvp = 0;
static int wvp = width;
static int hvp = height;

glm::vec3 eye = { 0.0,0.0,0.0 };
glm::vec3 dir = { 0.0,0.0,-1.0 };
glm::vec3 up = { 0.0,1.0,0.0 };
glm::vec3 right = { 1.0,0.0,0.0 };


glm::vec3 vertex0 = { 1.0f,0.0f,0.0f };
glm::vec3 vertex1 = { -1.0f,1.0f,0.0f };
glm::vec3 vertex2 = { -1.0f,-1.0f,0.0f };
glm::vec3 color0 = { 1.0f,0.0f,0.0f };
glm::vec3 color1 = { 0.0f,1.0f,0.0f };
glm::vec3 color2 = { 0.0f,0.0f,1.0f };

glm::vec3 translate = { 0.0f, 0.0f, 0.0f };

glm::mat3 Model = glm::mat3(1.0);

static float poistion = 0.1f;

static float angle = 0.1f;
static float gcos = cosf(angle);
static float gsin = sinf(angle);


RenderingSystem::RenderingSystem() : s(Shader("shaders/vertex.vert", "shaders/fragment.frag")) {
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
            1, 2, 3 
    };

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

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

    view.each([&](const auto entity, auto& renderer) {

        s.use();
        unsigned int transformLoc = glGetUniformLocation(s.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer.EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    });
}
