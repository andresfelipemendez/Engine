//
// Created by Andres on 27/06/22.
//

#ifndef ENGINE_MODEL_H
#define ENGINE_MODEL_H

#include <vector>

#include <entt/entt.hpp>

struct meshComponent
{
    int vao;
    int vbo;
    int ebo;
    int vaa;
    int mode;
    size_t count;
    int type;
    size_t offset;
};

class ModelSystem 
{
public:
    std::vector<meshComponent> meshes;
    ModelSystem();
    ~ModelSystem();
    void Initialize(entt::registry& registry);
private:
    
};


#endif //ENGINE_MODEL_H
