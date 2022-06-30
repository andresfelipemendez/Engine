#pragma once

#include <string>

class SpaceManager
{
public:
    SpaceManager();
    ~SpaceManager();

    bool CreateSpace(std::string name);
    bool RegisterSystem(std::string name, std::string systemName);

    template <typename  T>
    bool RegisterComponent(std::string name, std::string systemName, T component);
};