#pragma once
#include "UniFox.h"

class Team {
public:
    Team(glm::vec4 color) 
        : m_Color(color) {
    };

    glm::vec4 GetColor() const {return m_Color;}
    void SetColor(const glm::vec4 color) {m_Color = color;}
    uint8_t GetPlayer() const {return m_Player;}
    void GetColor(const uint8_t player) {m_Player = player;}
private:
    glm::vec4 m_Color;
    uint8_t m_Player;
};