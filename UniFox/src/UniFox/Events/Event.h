#pragma once

#include <sstream>

#include "UniFox/Core/Core.h"

namespace UniFox {
    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowUnfocus, WindowMoved, WindowEntered, WindowLeft, WindowMaximize, WindowIconify, WindowRestore, WindowRefresh,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4),
        EventCategoryWindow = BIT(5)
    };

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}

    class UF_API Event {
        friend class EventDispatcher;
    public:
        bool Handled = false;

        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const {return GetName();}

        inline bool IsInCategory(EventCategory category) {
            return GetCategoryFlags() & category;
        }

        friend std::ostream& operator<<(std::ostream& os, const Event& e) {
            return os << e.ToString();
        }
    };

    class EventDispatcher {
        template<typename T>
        using EventFn = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& event)
            : m_Event(event) {}

        template<typename T>
        bool Dispatch(EventFn<T> func) {
            if(m_Event.GetEventType() == T::GetStaticType()) {
                m_Event.Handled = func(*(T*)&m_Event);
                return true;
            }
            return false;
        }

    private:
        Event& m_Event;
    };

    inline std::string format_as(const Event& e) {
	    return e.ToString();
    }
}