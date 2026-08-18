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
    glm::vec2 position = glm::vec2(0, 0);
    glm::vec2 size = glm::vec2(0, 0);

    bool operator == (const Rect& other) {return position == other.position && size == other.size;}
};

struct Constraint {
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

class EventDispatcher {
    template<typename T>
    using EventFn = std::function<bool(T&)>;
public:
    EventDispatcher() {}

    template<typename T>
    void Connect(EventFn<T> func) {
        EventFn<UniFox::Event> wrapper = [func](UniFox::Event& e) {
            return func(static_cast<T&>(e));
        };
        m_Callbacks[T::GetStaticType()] = wrapper;
    }
    template<typename T>
    void Disconnect() {
        m_Callbacks.erase(T::GetStaticType());
    }
    bool Emit(UniFox::Event& event) {
        auto it = m_Callbacks.find(event.GetEventType());
        if(it != m_Callbacks.end()) {
            event.Handled |= it->second(event);
            return true;
        }
        return false;
    }
private:
    std::unordered_map<UniFox::EventType, EventFn<UniFox::Event>> m_Callbacks;
};