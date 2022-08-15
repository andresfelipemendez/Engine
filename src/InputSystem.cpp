#include "InputSystem.h"
#include "Globals.h"
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

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

void InputSystem::Update(entt::registry& registry) 
{

	GLFWwindow* window = Globals::Renderer::window;
	auto cameraFront = Globals::Renderer::cameraFront;
	auto cameraUp = Globals::Renderer::cameraUp;


	glm::mat4 cam = glm::mat4(1.0f);

	cam = glm::rotate(cam, Globals::Renderer::cameraRot.x, glm::vec3(1.0, 0.0, 0.0));
	cam = glm::rotate(cam, Globals::Renderer::cameraRot.y, glm::vec3(0.0, 1.0, 0.0));
	cam = glm::rotate(cam, Globals::Renderer::cameraRot.z, glm::vec3(0.0, 0.0, 1.0));

	glm::vec3 right = glm::vec3(cam[0][0], cam[0][1], cam[0][2]);
	glm::vec3 up = glm::vec3(cam[1][0], cam[1][1], cam[1][2]);
	glm::vec3 forward = glm::vec3(cam[2][0], cam[2][1], cam[2][2]);

	const float cameraSpeed = 0.8f; // adjust accordingly

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
		if(glm::abs(x) > 0.1){
			Globals::Renderer::cameraPos += x * cameraSpeed * Globals::Renderer::deltaTime * right;
		}
		auto y = state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];
		if(glm::abs(y) > 0.1f ) {
			Globals::Renderer::cameraPos += y * cameraSpeed * Globals::Renderer::deltaTime * forward;
		}
		
		float sensitivity = 0.8f;

		float xpos = state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X];
		if (glm::abs(xpos) > 0.2) {
			Globals::Renderer::cameraRot.y += xpos * Globals::Renderer::deltaTime * sensitivity;
		}
		else {

		}
		float ypos = state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y];
		if (glm::abs(ypos) > 0.2) {
			Globals::Renderer::cameraRot.x += -ypos * Globals::Renderer::deltaTime  * sensitivity;
		}
		

		
		
			
		
	}

	

}
