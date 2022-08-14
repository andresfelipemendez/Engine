//
// Created by fmend on 7/6/2022.
//

#include "RenderingSystem.h"
#include "Globals.h"
#include "Components/position.h"
#include "Components/renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using glm::vec3;
using glm::mat4;

glm::mat4 model = glm::mat4(1.0f);
glm::mat4 cameraView = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);

									   
RenderingSystem::RenderingSystem() : 
	s(Shader("shaders/vertex.vert", "shaders/fragment.frag")) 
{
	
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	projection = glm::perspective(glm::radians(45.0f),
		(float)Globals::Renderer::width / 
		(float)Globals::Renderer::height, 
		0.1f, 100.0f);
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

void RenderingSystem::Update(entt::registry& registry)
{
	auto view = registry.view<renderer>();

	glm::vec3 eye = Globals::Renderer::cameraPos;
	glm::vec3 center = Globals::Renderer::cameraPos + Globals::Renderer::cameraFront;
	glm::vec3 up = Globals::Renderer::cameraUp;
	
	cameraView = glm::lookAt(eye,center,up);

	view.each([&](const auto entity, auto& renderer) 
	{
		s.use();

		setMatrix(s, "model", model);
		setMatrix(s, "view", cameraView);
		setMatrix(s, "projection", projection);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer.EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	});
}
