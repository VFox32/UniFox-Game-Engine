#include "ufpch.h"
#include "UniFox/Core/Application.h"

#include "UniFox/Renderer/Renderer.h"
#include "UniFox/Core/Core.h"

#include "imgui.h"

namespace UniFox {
    #define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application() {
        UF_PROFILE_FUNCTION();

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
        UF_PROFILE_FUNCTION();
    }

    void Application::PushLayer(Ref<Layer> layer) {
        UF_PROFILE_FUNCTION();
        
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Ref<Layer> overlay) {
        UF_PROFILE_FUNCTION();
        
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }
    
    void Application::OnEvent(Event& e) {
        UF_PROFILE_FUNCTION();
        
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
        UF_PROFILE_FUNCTION();
        
        m_LastTime = Clock::Now();

        while(m_Running) {
            UF_PROFILE_SCOPE("RunLoop");
        
            TimePoint now = Clock::Now();
            Duration dt = now - m_LastTime;
            while(dt.s() < 1.0f/165.0f) {
                now = Clock::Now();
                dt = now - m_LastTime;
            };
            m_LastTime = now;

            if(!m_Minimized) {
                UF_PROFILE_SCOPE("LayerStack OnUpdate");
        
                for(Ref<Layer> layer : m_LayerStack)
                    layer->OnUpdate(dt);
            }

            m_ImGuiLayer->Begin();
            {
                UF_PROFILE_SCOPE("ImGui Render");

                {
                    UF_PROFILE_SCOPE("LayerStack OnImGuiRender");
            
                    for(Ref<Layer> layer : m_LayerStack)
                        layer->OnImGuiRender();
                }

                {
                    UF_PROFILE_SCOPE("ImGui Stats");
            
                    ImGui::Begin("Stats");
                        ImGui::Text("Time: %s", Clock::Now().ToString().c_str());
                        ImGui::Text("Start time: %s", Clock::StartTime().ToString().c_str());
                        ImGui::Text("Run time: %.2f", Clock::RunTime().s());
                        ImGui::Text("FPS: %.2f", 1.0f/dt);
                        ImGui::Text("Delta Time: %.2fms", dt.ms());
                        ImGui::Text("Resolution: %d:%d", m_Window->GetWidth(), m_Window->GetHeight());
                        ImGui::Text("VSync: %d", m_Window->IsVSync());
                    ImGui::End();
                }
            }
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    };

    bool Application::OnWindowClose(WindowCloseEvent& e) {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e) {
        UF_PROFILE_FUNCTION();
        
        if(e.GetWidth() == 0 || e.GetHeight() == 0) {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

        return false;
    }
}