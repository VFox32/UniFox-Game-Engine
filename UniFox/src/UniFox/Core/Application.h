#pragma once
#include "ufpch.h"

#include "UniFox/Core/Core.h"
#include "UniFox/Core/Log.h"

#include "Window.h"
#include "LayerStack.h"
#include "UniFox/Events/Event.h"
#include "UniFox/Events/WindowEvent.h"

#include "UniFox/Core/Time.h"

#include "UniFox/ImGui/ImGuiLayer.h"

namespace UniFox {

    class UF_API Application {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        inline static Application& Get() {return *s_Instance;}
        inline Window& GetWindow() {return *m_Window;}
    private:
        bool OnWindowClose(WindowCloseEvent& e);
    private:
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;
        TimePoint m_LastTime = Clock::Now();
    private:
        static Application* s_Instance;
    };

    Application* CreateApplication();

}