#pragma once
#include "ufpch.h"

#include "Window.h"
#include "LayerStack.h"
#include "UniFox/Events/Event.h"
#include "UniFox/Events/WindowEvent.h"

#include "UniFox/ImGui/ImGuiLayer.h"

#include "UniFox/Renderer/Shader.h"
#include "UniFox/Renderer/Buffer.h"
#include "UniFox/Renderer/VertexArray.h"
#include "UniFox/Renderer/OrthographicCamera.h"

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
        bool OnKeyPressed(KeyPressedEvent& e);
        bool OnMouseScroll(MouseScrolledEvent& e);

        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;

        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<VertexArray> m_VertexArray;

        OrthographicCamera m_Camera;
    private:
        static Application* s_Instance;
    };

    Application* CreateApplication();

}