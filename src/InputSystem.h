#pragma once

#include <entt/entt.hpp>

class InputSystem
{
private:
	/* data */
public:
	InputSystem(/* args */);
	~InputSystem();

	bool Initialize(entt::registry& registry);
	void Update(entt::registry& registry);
};
