#pragma once

#include <entt/entt.hpp>

class InputSystem
{
private:

public:
	InputSystem();
	~InputSystem();

	bool Initialize(entt::registry& registry);
	void Update(entt::registry& registry);
};
