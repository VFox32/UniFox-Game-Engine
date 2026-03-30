#include "Sandbox2D.h"

#include "imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(16.0f/9.0f, true), m_Color(1.0f, 0.0f, 0.0f, 1.0f) {

    UniFox::Buffer buffer(64);

    {
        UniFox::MemoryStreamWriter stream(buffer);
        UniFox::TimePoint tp = UniFox::TimePoint(2007, 12, 22);
        UniFox::Duration dt = UniFox::Hours(10);
        tp += dt;
        stream.WriteObject(tp);
        stream.WriteObject(dt);
        std::cout << tp.ToString() << "\n";
        std::cout << dt.Hours() << "\n";
    }

    {
        UniFox::MemoryStreamReader stream(buffer);
        UniFox::TimePoint tp;
        UniFox::Duration dt;
        stream.ReadObject(tp);
        stream.ReadObject(dt);
        std::cout << tp.ToString() << "\n";
        std::cout << dt.Hours() << "\n";
    }
}

void Sandbox2D::OnAttach() {
    UF_PROFILE_FUNCTION();
    
    m_Texture54 = UniFox::Texture2D::Create("assets/textures/54p_.png");
    m_TextureChecker = UniFox::Texture2D::Create("assets/textures/Checker.png");
}

void Sandbox2D::OnDetach() {
    UF_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(UniFox::Duration dt) {
    UF_PROFILE_FUNCTION();
    
    m_CameraController.OnUpdate(dt);

    {
        UF_PROFILE_SCOPE("Renderer Prep");
        UniFox::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        UniFox::RenderCommand::Clear();
    }

    {
        UF_PROFILE_SCOPE("Renderer Draw");
        UniFox::Renderer2D::BeginScene(m_CameraController.GetCamera());
        UniFox::Renderer2D::DrawQuad({0.0f, 0.5f, -0.1f}, {1.0f, 1.0f}, 1.2, m_TextureChecker);
        UniFox::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f}, 0.0f, m_Texture54, m_Color);
        UniFox::Renderer2D::DrawQuad({1.0f, 1.0f}, {1.0f, 0.5f}, 0.0f, {0.0f, 1.0f, 0.0f, 1.0f});
        UniFox::Renderer2D::DrawQuad({1.0f, 0.0f}, {0.5f, 0.5f}, 0.4f, {0.0f, 0.0f, 1.0f, 1.0f});
        UniFox::Renderer2D::EndScene();
    }
}

void Sandbox2D::OnImGuiRender() {
    UF_PROFILE_FUNCTION();

    ImGui::Begin("Colors");
    ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
    ImGui::End();

    ImGui::Begin("Time Test");
    UniFox::TimePoint tp = UniFox::TimePoint(2007, 12, 22);
    UniFox::Duration d = UniFox::Clock::Now() - tp;
    ImGui::Text("%s", tp.ToString().c_str());
    ImGui::Text("%.2f", d.d());
    ImGui::End();
}

void Sandbox2D::OnEvent(UniFox::Event& e) {
    m_CameraController.OnEvent(e);
}