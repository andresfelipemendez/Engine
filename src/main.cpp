#include <iostream>

#include "PhysicsSystem.h"
#include "RenderingSystem.h"

#include "Platform.h"
#include "Renderer.h"
#include "GUI.h"
#include "Scene.h"
#include "Model.h"
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

    entt::registry registry;

    gui.Initialize();
    renderingSystem.Initialize(registry);

    for (auto i = 0u;i<10u;++i) {
        const auto entity = registry.create();
        registry.emplace<position>(entity,i*1.f,i*1.f);
        if(i %2==0){
            registry.emplace<velocity>(entity,i*1.f,i*1.f);
        }

    }

	while (platform.isRunning()) {
        platform.Update();
        physicsSystem.update(registry);
        
        renderer.Render();
        renderingSystem.update(registry);
        gui.Update();
    }
	return 0;
}
