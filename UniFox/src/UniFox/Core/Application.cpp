#include "ufpch.h"
#include "UniFox/Core/Application.h"

#include "UniFox/Renderer/Renderer.h"
#include "UniFox/Core/Core.h"

#include "imgui.h"

namespace UniFox {
    #define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application() {
        UF_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = Ref<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
        m_Window->SetVSync(true);

        Renderer::Init();

        m_ImGuiLayer = MakeRef<ImGuiLayer>();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application() {

    }

    void Application::PushLayer(Ref<Layer> layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Ref<Layer> overlay) {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }
    
    void Application::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

        for(auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
            (*--it)->OnEvent(e);
            if(e.Handled)
                break;
        }
    }

    void Application::Run() {
        while(m_Running) {
            TimePoint now = Time::Now();
            Duration dt = now - m_LastTime;
            if(dt.s() < 1.0f/165.0f) continue;
            m_LastTime = now;

            if(!m_Minimized) {
                for(Ref<Layer> layer : m_LayerStack)
                    layer->OnUpdate(dt);
            }

            m_ImGuiLayer->Begin();
            for(Ref<Layer> layer : m_LayerStack)
                layer->OnImGuiRender();

            ImGui::Begin("Stats");
                ImGui::Text("Resolution: %d:%d", m_Window->GetWidth(), m_Window->GetHeight());
                ImGui::Text("VSync: %d", m_Window->IsVSync());
                ImGui::Text("FPS: %.2f", 1.0f/dt);
                ImGui::Text("Delta Time: %.2fms", dt.ms());
            ImGui::End();

            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    };

    bool Application::OnWindowClose(WindowCloseEvent& e) {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e) {
        if(e.GetWidth() == 0 || e.GetHeight() == 0) {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

        return false;
    }
}