#include "Sandbox2D.h"

#include "imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

template<typename Fn>
class Timer {
public:
    Timer(const char* name, Fn&& func) 
        : m_Name(name), m_Func(func) {
    }

    ~Timer() {
        if(!m_Stopped)
            Stop();
    }

    void Stop() {
        float duration = (UniFox::Time::Now() - m_StartTime).ms();
        m_Func({m_Name, duration});
        m_Stopped = true;
    }
private:
    const char* m_Name;
    UniFox::TimePoint m_StartTime;
    bool m_Stopped = false;
    Fn m_Func;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult){m_ProfileResults.push_back(profileResult);})

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(16.0f/9.0f, true), m_Color(1.0f, 0.0f, 0.0f, 1.0f) {
}

void Sandbox2D::OnAttach() {
    m_Texture54 = UniFox::Texture2D::Create("assets/textures/54p_.png");
    m_TextureChecker = UniFox::Texture2D::Create("assets/textures/Checker.png");
}

void Sandbox2D::OnDetach() {
    
}

void Sandbox2D::OnUpdate(UniFox::Duration dt) {
    PROFILE_SCOPE("Sandbox2D::OnUpdate");
    {
        PROFILE_SCOPE("CameraController::OnUpdate");
        m_CameraController.OnUpdate(dt);
    }

    {
        PROFILE_SCOPE("Renderer Prep");
        UniFox::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        UniFox::RenderCommand::Clear();
    }

    {
        PROFILE_SCOPE("Renderer Draw");
        UniFox::Renderer2D::BeginScene(m_CameraController.GetCamera());
        UniFox::Renderer2D::DrawQuad({0.0f, 0.5f, -0.1f}, {1.0f, 1.0f}, 1.2, m_TextureChecker);
        UniFox::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f}, 0.0f, m_Texture54, m_Color);
        UniFox::Renderer2D::DrawQuad({1.0f, 1.0f}, {1.0f, 0.5f}, 0.0f, {0.0f, 1.0f, 0.0f, 1.0f});
        UniFox::Renderer2D::DrawQuad({1.0f, 0.0f}, {0.5f, 0.5f}, 0.4f, {0.0f, 0.0f, 1.0f, 1.0f});
        UniFox::Renderer2D::EndScene();
    }
}

void Sandbox2D::OnImGuiRender() {
    ImGui::Begin("Colors");
    ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
    ImGui::End();

    ImGui::Begin("Profile results");
    for(auto& result : m_ProfileResults) {
        ImGui::Text("%.3fms %s", result.time, result.name);
    }
    m_ProfileResults.clear();
    ImGui::End();
}

void Sandbox2D::OnEvent(UniFox::Event& e) {
    m_CameraController.OnEvent(e);
}