#pragma once

#include "UniFox/Events/Event.h"

namespace UniFox {
    class  WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : m_Width(width), m_Height(height) {}

        inline unsigned int GetWidth() {return m_Width;}
        inline unsigned int GetHeight() {return m_Height;}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryWindow)
    private:
        unsigned int m_Width, m_Height;
    };

    class  WindowMovedEvent : public Event {
    public:
        WindowMovedEvent(unsigned int x, unsigned int y)
            : m_WindowX(x), m_WindowY(y) {}

        inline unsigned int GetX() {return m_WindowX;}
        inline unsigned int GetY() {return m_WindowY;}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowMovedEvent: " << m_WindowX << ", " << m_WindowY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowMoved)
        EVENT_CLASS_CATEGORY(EventCategoryWindow)
    private:
        unsigned int m_WindowX, m_WindowY;
    };

    class  WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowCloseEvent";
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryWindow)
    };

    class  WindowFocusEvent : public Event {
    public:
        WindowFocusEvent() {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowFocusEvent";
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowFocus)
        EVENT_CLASS_CATEGORY(EventCategoryWindow)
    };

    class  WindowUnfocusEvent : public Event {
    public:
        WindowUnfocusEvent() {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowUnfocusEvent";
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowUnfocus)
        EVENT_CLASS_CATEGORY(EventCategoryWindow)
    };

    class  WindowEnteredEvent : public Event {
    public:
        WindowEnteredEvent() {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowEnteredEvent";
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowEntered)
        EVENT_CLASS_CATEGORY(EventCategoryWindow)
    };

    class  WindowLeftEvent : public Event {
    public:
        WindowLeftEvent() {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowLeftEvent";
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowLeft)
        EVENT_CLASS_CATEGORY(EventCategoryWindow)
    };

    class  WindowMaximizeEvent : public Event {
    public:
        WindowMaximizeEvent() {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowMaximizeEvent";
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowMaximize)
        EVENT_CLASS_CATEGORY(EventCategoryWindow)
    };

    class  WindowIconifyEvent : public Event {
    public:
        WindowIconifyEvent() {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowIconifyEvent";
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowIconify)
        EVENT_CLASS_CATEGORY(EventCategoryWindow)
    };

    class  WindowRestoreEvent : public Event {
    public:
        WindowRestoreEvent() {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowRestoreEvent";
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowRestore)
        EVENT_CLASS_CATEGORY(EventCategoryWindow)
    };

    class  WindowRefreshEvent : public Event {
    public:
        WindowRefreshEvent() {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowRefreshEvent";
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowRefresh)
        EVENT_CLASS_CATEGORY(EventCategoryWindow)
    };
}