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

unsigned int openShader(std::string path, ShaderType type)
{
    unsigned int shader = 0;

    shader = glCreateShader(
        type == VERTEX_SHADER ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

    std::ifstream shaderFile;
    std::stringstream shaderStream;
    std::string shaderSource;
    shaderFile.open(path);
    shaderStream << shaderFile.rdbuf();
    shaderSource = shaderStream.str();

    const char *pshaderSource = shaderSource.c_str();

    glShaderSource(shader, 1, &pshaderSource, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        switch (type)
        {
        case VERTEX_SHADER:
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
            break;
        case FRAGMENT_SHADER:
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";
            break;
        }
        std::cout << infoLog << std::endl;
        return -1;
    }
    return shader;
}

unsigned int createShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    unsigned int vertexShader = openShader(vertexShaderPath, VERTEX_SHADER);
    unsigned int fragmentShader = openShader(fragmentShaderPath, FRAGMENT_SHADER);
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n";
        return -1;
    }
    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}
