#pragma once
#include "ufpch.h"

#include "Events/Event.h"
#include "Window.h"

#include "Events/WindowEvent.h"

namespace UniFox {

    class UF_API Application {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);
    private:
        bool OnWindowClose(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    Application* CreateApplication();

}