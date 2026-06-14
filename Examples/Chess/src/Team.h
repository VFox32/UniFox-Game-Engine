#pragma once
#include "UniFox.h"

class Team {
public:
    Team(const std::string Name, const glm::vec4 Color, const glm::ivec2 Dir)
        : name(Name), color(Color), dir(Dir) {}

    
    static void Serialize(UniFox::StreamWriter* serializer, const Team& instance) {
        serializer->WriteString(instance.name);
        serializer->WriteRaw(instance.color);
        serializer->WriteRaw(instance.dir);
    }
    static void Deserialize(UniFox::StreamReader* deserializer, Team& instance) {
        deserializer->ReadString(instance.name);
        deserializer->ReadRaw(instance.color);
        deserializer->ReadRaw(instance.dir);
    }
public:
    std::string name;
    glm::vec4 color;
    glm::ivec2 dir;
};