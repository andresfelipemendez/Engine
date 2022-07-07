//
// Created by fmend on 7/6/2022.
//

#ifndef ENGINE_RENDERINGSYSTEM_H
#define ENGINE_RENDERINGSYSTEM_H

#include "Shader.h"
#include <entt/entt.hpp>

class RenderingSystem {
public:
	Shader s;

	RenderingSystem();
	bool Initialize(entt::registry& registry);
	void update(entt::registry& registry);
};


#endif //ENGINE_RENDERINGSYSTEM_H
