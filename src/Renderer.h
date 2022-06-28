#pragma once
#include "Shader.h"

class Renderer
{
public:
    Shader s;
    unsigned int EBO;
    unsigned int VBO;
    unsigned int VAO;

    Renderer();
    ~Renderer();

    void Render();
};