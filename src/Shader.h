#pragma once
#include <glad/glad.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

enum ShaderType
{
    VERTEX_SHADER,
    FRAGMENT_SHADER
};

class Shader
{
public:
    unsigned int ID;

    Shader(const std::string vertexPath, const std::string fragmentPath);
    void use();
    void setBool(const std::string &name, bool value) const;
};