//
// Created by fmend on 7/6/2022.
//

#include "RenderingSystem.h"
#include "Components/position.h"
#include "Components/renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using glm::vec3;

static int width = 800;
static int height = 600;
static void* dc = nullptr;


static int xvp = 0;
static int yvp = 0;
static int wvp = width;
static int hvp = height;

float fieldOfView = glm::radians(45.0f);
float aspectRatio = (float)width / (float)height;
glm::mat4 proj = glm::perspective(fieldOfView, aspectRatio, 0.1f, 100.0f);


glm::mat4 model = glm::mat4(1.0f);

vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
vec3 cameraTarget = vec3(0.0f, 0.0f, 0.0f);
vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

glm::vec3 eye = { 0.0,0.0,0.0 };
glm::vec3 dir = { 0.0,0.0,-1.0 };
glm::vec3 up { 0.0,1.0,0.0 };
glm::vec3 cameraRight = glm::normalize(glm::cross(up,cameraDirection));
vec3 cameraUp = glm::cross(cameraDirection, cameraRight);


glm::mat4 cameraView;
									   
RenderingSystem::RenderingSystem() : 
	s(Shader("shaders/vertex.vert", "shaders/fragment.frag")) 
{
	cameraView = glm::translate(cameraView, glm::vec3(0.0f, 0.0f, -3.0f));
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

void setMatrix(Shader& shader, std::string name, glm::mat4& matrix) {
	unsigned int loc = glGetUniformLocation(shader.ID, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void RenderingSystem::update(entt::registry& registry)
{
	auto view = registry.view<renderer>();

	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

	view.each([&](const auto entity, auto& renderer) 
	{
		s.use();

		setMatrix(s, "model", model);
		setMatrix(s, "view", cameraView);
		setMatrix(s, "projection", proj);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer.EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	});
}
