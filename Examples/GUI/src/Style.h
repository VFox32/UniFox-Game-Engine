#pragma once
#include "UniFox.h"

class Style {
public:
    Style(glm::vec4 FGColor = glm::vec4(0.1, 0.1, 0.1, 1.0), glm::vec4 BGColor = glm::vec4(0.9, 0.9, 0.9, 1.0))
        : fgColor(FGColor), bgColor(BGColor) {}

    glm::vec4 fgColor;
    glm::vec4 bgColor; 
};