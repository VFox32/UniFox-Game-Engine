#include "Sandbox2D.h"

#include "UniFox/Platform/OpenGL/OpenGLShader.h" ///////////////////

#include "imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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
    m_CameraController.OnUpdate(dt);

    UniFox::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    UniFox::RenderCommand::Clear();

    UniFox::Renderer2D::BeginScene(m_CameraController.GetCamera());
    UniFox::Renderer2D::DrawQuad(m_Texture54, {0.0f, 0.0f});
    UniFox::Renderer2D::DrawQuad(m_TextureChecker, {0.0f, 0.5f, -0.1f}, {1.0f, 1.0f}, 1.2);
    UniFox::Renderer2D::DrawQuad({0.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.5f});
    UniFox::Renderer2D::DrawQuad({0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.5f, 0.5f}, 0.4);
    UniFox::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender() {
    ImGui::Begin("Colors");
        ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
    ImGui::End();
}

void Sandbox2D::OnEvent(UniFox::Event& e) {
    m_CameraController.OnEvent(e);
}