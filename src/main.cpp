#include <iostream>

#include "PhysicsSystem.h"
#include "RenderingSystem.h"
#include "InputSystem.h"

#include "Platform.h"
#include "Renderer.h"
#include "GUI.h"
#include "Scene.h"
#include "Model.h"
#include "Globals.h"
#include "Components/position.h"
#include "Components/velocity.h"

int main()
{
	Platform platform;
	Renderer renderer;
	GUI gui;
	Scene scene;
	Model model;
	PhysicsSystem physicsSystem;
	RenderingSystem renderingSystem;
	InputSystem inputSystem;

	entt::registry registry;

	gui.Initialize();
	renderingSystem.Initialize(registry);
	inputSystem.Initialize(registry);

	for (auto i = 0u;i<10u;++i) {
		const auto entity = registry.create();
		registry.emplace<position>(entity,i*1.f,i*1.f);
		if(i %2==0){
			registry.emplace<velocity>(entity,i*1.f,i*1.f);
		}

	}

	while (platform.isRunning()) {
		float currentFrame = glfwGetTime();
		Globals::Renderer::deltaTime = currentFrame - Globals::Renderer::lastFrame;
		platform.Update();
		physicsSystem.update(registry);
		
		renderer.Render();
		inputSystem.Update(registry);
		renderingSystem.Update(registry);
		gui.Update();
		Globals::Renderer::lastFrame = currentFrame;
	}
	return 0;
}
