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

	GLFWgamepadstate state;
	if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state))
	{
		auto x = state.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
		if(glm::abs(x) > 0.2){
			Globals::Renderer::cameraPos += -x * cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
		}
		auto y = state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];
		if(glm::abs(y) > 0.2f ) {
			Globals::Renderer::cameraPos = y * cameraSpeed * cameraFront;
		}
		
		float sensitivity = 0.1f;

		float xpos = state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X];
		if (glm::abs(xpos) > 0.2) {
			Globals::Renderer::cameraFront.x += xpos * sensitivity;	
		}
		float ypos = state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y];
		if (glm::abs(ypos) > 0.2) {
			Globals::Renderer::cameraFront.y += -ypos * sensitivity;
		}
		

		
		
			
		
	}

	// ;

}
