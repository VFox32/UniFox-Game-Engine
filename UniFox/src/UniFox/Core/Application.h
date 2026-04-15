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
    class Application {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);

        void PushLayer(Ref<Layer> layer);
        void PushOverlay(Ref<Layer> overlay);

        inline static Application& Get() {return *s_Instance;}
        inline Window& GetWindow() {return *m_Window;}
    private:
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);
    private:
        Ref<Window> m_Window;
        Ref<ImGuiLayer> m_ImGuiLayer;
        bool m_Running = true;
        bool m_Minimized = false;
        LayerStack m_LayerStack;
        TimePoint m_LastTime;
    private:
        static Application* s_Instance;
    };

    Application* CreateApplication();
}