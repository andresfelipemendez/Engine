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

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
									   
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
	//float vertices[] = {
	//		0.5f, 1.5f, 1.0f,	// top right
	//		0.5f, 0.5f, 1.0f,	// bottom right
	//		-0.5f, 0.5f, 1.0f, // bottom left
	//		-0.5f, 1.5f, 1.0f }; // top left

	//unsigned int indices[] = {
	//		0, 1, 3,
	//		1, 2, 3 
	//};

	//const auto entity = registry.create();
	////rendererComponent rc;

	//unsigned int EBO;
	//unsigned int VBO;
	//unsigned int VAO;

	//glGenBuffers(1, &EBO);
	//glGenBuffers(1, &VBO);
	//glGenVertexArrays(1, &VAO);

	//glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//auto& entt = registry.emplace<rendererComponent>(entity);
	//entt.EBO = EBO;
	//entt.VBO = VBO;
	//entt.VAO = VAO;
	//entt.VAA = 0;
	//entt.triangleCount = 6;
	//entt.type = GL_UNSIGNED_INT;
	//entt.offset = 0;
	return false;
}

void setMatrix(Shader& shader, std::string name, glm::mat4& matrix) {
	unsigned int loc = glGetUniformLocation(shader.ID, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void RenderingSystem::Update(entt::registry& registry)
{
	auto view = registry.view<rendererComponent>();

	glm::vec3 eye = Globals::Renderer::cameraPos;
	glm::vec3 center = Globals::Renderer::cameraPos + Globals::Renderer::cameraFront;
	glm::vec3 up = Globals::Renderer::cameraUp;
	
	glm::mat4 cam = glm::mat4(1.0f);

	cam = glm::translate(cam, Globals::Renderer::cameraPos);
	
	cam = glm::rotate(cam, Globals::Renderer::cameraRot.x, glm::vec3(1.0, 0.0, 0.0));
	cam = glm::rotate(cam, Globals::Renderer::cameraRot.y, glm::vec3(0.0, 1.0, 0.0));
	cam = glm::rotate(cam, Globals::Renderer::cameraRot.z, glm::vec3(0.0, 0.0, 1.0));
	
	cam = glm::inverse(cam);

	view.each([&](const auto entity, auto& renderer) 
	{
		glBindVertexArray(renderer.VAO);
		glBindBuffer(GL_ARRAY_BUFFER, renderer.VBO);
		glEnableVertexAttribArray(renderer.VAA);

		s.use();

		setMatrix(s, "model", model);
		setMatrix(s, "view", cam);
		setMatrix(s, "projection", projection);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer.EBO);
		glDrawElements(renderer.mode, renderer.triangleCount, renderer.type, BUFFER_OFFSET(renderer.offset));
	});
}
