#pragma once
#include "UniFox.h"

class Transition {
public:
    virtual float Sample(const float t) const = 0;
};

class LinearTransition : public Transition {
    virtual float Sample(const float t) const override {
        return t;
    }
};

class EaseInTransition : public Transition {
    virtual float Sample(const float t) const override {
        return t;
    }
};