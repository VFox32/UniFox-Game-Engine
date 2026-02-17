#pragma once

#include "UniFox/Layer.h"

#include "UniFox/Events/KeyEvent.h"
#include "UniFox/Events/MouseEvent.h"
#include "UniFox/Events/WindowEvent.h"

namespace UniFox {
    class UF_API ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer() = default;
        
        virtual void OnAttach();
        virtual void OnDetach();
        virtual void OnUpdate();
        virtual void OnEvent(Event& event);
    private:
        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);
        bool OnKeyTypedEvent(KeyTypedEvent& e);

        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrolledEvent(MouseScrolledEvent& e);

        bool OnWindowResizeEvent(WindowResizeEvent& e);
        bool OnWindowMovedEvent(WindowMovedEvent& e);
    private:
        float m_Time = 0.0;
    };
}