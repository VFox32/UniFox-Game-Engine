#pragma once
#include "UniFox.h"

enum class LengthMode {
    Auto,
    Pixels,
    Fill,
    Percent,
    Ratio
};
struct Length {
    LengthMode mode = LengthMode::Auto;
    float size = 0;
};

struct Rect {
    //Rect(const glm::vec2 Position = glm::vec2(0, 0), const glm::vec2 Size = glm::vec2(0, 0))
    //    : position(Position), size(Size) {}
        
    glm::vec2 position = glm::vec2(0, 0);
    glm::vec2 size = glm::vec2(0, 0);

    bool operator == (const Rect& other) {return position == other.position && size == other.size;}
};

struct Constraint {
    //Constraint(const glm::vec2 MinSize = glm::vec2(0, 0), const glm::vec2 MaxSize = glm::vec2(1, 1))
    //    : minSize(MinSize), maxSize(MaxSize) {}

    glm::vec2 minSize = {0, 0};
    glm::vec2 maxSize = {INFINITY, INFINITY};

    bool operator == (const Constraint& other) {return minSize == other.minSize && maxSize == other.maxSize;}
};

struct MeasureCache {
    Constraint constraint;
    glm::vec2 size;
};
struct ArrangeCache {
    Rect rect;
};