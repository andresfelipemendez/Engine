//
// Created by fmend on 7/4/2022.
//

#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


struct rendererComponent {
    unsigned int triangleCount;
    unsigned int EBO;
    unsigned int VBO;
    unsigned int VAO;
    unsigned int VAA;
    int type;
    int mode;
    size_t offset;
};
#endif //ENGINE_RENDERER_H

