#include "Renderer.h"

#include "Globals.h"
#include "Shader.h"
#include "Components/renderer.h"

color Globals::Renderer::clearColor;
GLFWwindow *Globals::Renderer::window;


void Renderer::Render() {
    glViewport(0, 0, Globals::Renderer::width, Globals::Renderer::height);
    auto clear_color = Globals::Renderer::clearColor;
    glClearColor(clear_color.v.x , clear_color.v.y , clear_color.v.z , clear_color.v.w);
    glClear(GL_COLOR_BUFFER_BIT);

    //s.use();
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Renderer::Renderer() 
{

}

Renderer::~Renderer() {

}
