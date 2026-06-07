#pragma once
#include "UniFox.h"

class Team {
public:
    Team(std::string Name, glm::vec3 Color)
        : name(Name), color(Color) {}
public:
    std::string name;
    glm::vec3 color;
};