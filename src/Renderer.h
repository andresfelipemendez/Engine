#pragma once


#include <entt/entt.hpp>

class Renderer
{
public:
    Renderer();
    ~Renderer();

    bool Initialize(entt::registry& registry);
    void Render();
};