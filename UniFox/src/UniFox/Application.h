#pragma once
#include "ufpch.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"

namespace UniFox {

    class UF_API Application {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void Pushoverlay(Layer* overlay);
    private:
        bool OnWindowClose(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;
    };

    Application* CreateApplication();

}