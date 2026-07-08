#pragma once
#include "UniFox.h"

enum class LengthMode {
    Auto,
    Pixels,
    Fill,
    Percent,
    Ratio
};
class Length {
public:
    LengthMode mode = LengthMode::Auto;
    float size = 0;
};

class Rect {
public:
    Rect(const glm::vec2 Position = glm::vec2(0, 0), const glm::vec2 Size = glm::vec2(0, 0))
        : position(Position), size(Size) {}
public:
    glm::vec2 position = glm::vec2(0, 0);
    glm::vec2 size = glm::vec2(0, 0);

    bool operator == (const Rect& other) {return position == other.position && size == other.size;}
};

class Constraint {
public:
    Constraint(const glm::vec2 MinSize = glm::vec2(0, 0), const glm::vec2 MaxSize = glm::vec2(1, 1))
        : minSize(MinSize), maxSize(MaxSize) {}

    glm::vec2 minSize;
    glm::vec2 maxSize;

    bool operator == (const Constraint& other) {return minSize == other.minSize && maxSize == other.maxSize;}
};

class MeasureCache {
public:
    Constraint constraint;
    glm::vec2 size;
};
class ArrangeCache {
public:
    Rect rect;
};