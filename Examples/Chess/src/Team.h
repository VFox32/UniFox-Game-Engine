#pragma once
#include "UniFox.h"

class Team {
public:
    Team(std::string Name, glm::vec3 Color)
        : name(Name), color(Color) {}

    
    static void Serialize(UniFox::StreamWriter* serializer, const Team& instance) {
        serializer->WriteString(instance.name);
        serializer->WriteRaw(instance.color);
    }
    static void Deserialize(UniFox::StreamReader* deserializer, Team& instance) {
        deserializer->ReadString(instance.name);
        deserializer->ReadRaw(instance.color);
    }
public:
    std::string name;
    glm::vec3 color;
};