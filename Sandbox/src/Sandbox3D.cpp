#include "Sandbox3D.h"

#include "imgui.h"

Sandbox3D::Sandbox3D()
    : Layer("Sandbox3D"), m_CameraController(120, 16.0f/9.0f, true) {
}

void Sandbox3D::OnAttach() {
    UF_PROFILE_FUNCTION();

    m_Emitter = new Emitter(
        {0, 0, 0}, {0.1, 0.0, 0.1},
        {0, 2, 0}, {1.2, 0.2, 1.2},
        {1, 0, 0, 1}, {0, 0, 1, 1},
        0.01f, 0.0f,
        3.0f, 0.5f,
        0.5,
        1000000.0f
    );
}

void Sandbox3D::OnDetach() {
    UF_PROFILE_FUNCTION();
}

void Sandbox3D::OnUpdate(UniFox::Duration dt) {
    UF_PROFILE_FUNCTION();
    
    m_CameraController.OnUpdate(dt);

    {
        UF_PROFILE_SCOPE("Renderer Prep");
        UniFox::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        UniFox::RenderCommand::Clear();
    }

    {
        UF_PROFILE_SCOPE("Renderer Draw");

        UniFox::Renderer::BeginScene(m_CameraController.GetCamera());
        m_Emitter->OnUpdate(dt, m_CameraController.GetCamera());
        UniFox::Renderer::EndScene();
    }
}

void Sandbox3D::OnImGuiRender() {
    UF_PROFILE_FUNCTION();

    ImGui::Begin("Camera");
    glm::vec3 position = m_CameraController.GetCamera().GetPosition();
    glm::vec3 rotation = m_CameraController.GetCamera().GetRotation();
    ImGui::Text("Position: %.3f, %.3f, %.3f", position.x, position.y, position.z);
    ImGui::Text("Rotation: %.3f, %.3f, %.3f", rotation.x, rotation.y, rotation.z);
    ImGui::End();
}

void Sandbox3D::OnEvent(UniFox::Event& e) {
    m_CameraController.OnEvent(e);
}