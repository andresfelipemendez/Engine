#include "SpaceManager.h"

SpaceManager::SpaceManager()
{
}

SpaceManager::~SpaceManager()
{
}

bool SpaceManager::CreateSpace(std::string name)
{
    return false;
}

bool SpaceManager::RegisterSystem(std::string name, std::string systemName)
{
    return false;
}

template<typename T>
bool SpaceManager::RegisterComponent(std::string name, std::string systemName,T component) {
    
}
