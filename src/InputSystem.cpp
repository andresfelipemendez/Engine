#include "InputSystem.h"
#include "Globals.h"
#include <GLFW/glfw3.h>
#include "Components/components.h"

InputSystem::InputSystem(/* args */)
{
}

InputSystem::~InputSystem()
{
}

bool InputSystem::Initialize(entt::registry& registry) {
	const auto entity = registry.create();

	inputComponent ic = { 0,0 };
	translationComponent tc = { 0,0,0 };
	registry.emplace<inputComponent>(entity, ic);
	registry.emplace<translationComponent>(entity, tc);
	return true;
}

void InputSystem::Update(entt::registry& registry) {

	GLFWwindow* window = Globals::Renderer::window;
	auto cameraFront = Globals::Renderer::cameraFront;
	auto cameraUp = Globals::Renderer::cameraUp;

	const float cameraSpeed = 0.05f; // adjust accordingly


	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		Globals::Renderer::cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Globals::Renderer::cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		Globals::Renderer::cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		Globals::Renderer::cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;


	auto view = registry.view<inputComponent, translationComponent>();

	view.each([&](const auto entity, auto& ic, translationComponent& tc) {
		
	});

	/**/
}
