#include "Sandbox3D.h"

#include "imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

Sandbox3D::Sandbox3D()
    : Layer("Sandbox3D"), m_CameraController(120, 16.0f/9.0f, true) {
}

void Sandbox3D::OnAttach() {
    UF_PROFILE_FUNCTION();

    m_Emitter = new Emitter(
        {0, 0, 0}, 1, {0, 0, 0}, 1.0, 1.0,
        {0, 0, 0}, 1, {1, 1, 1}, 0.1, 0.1,
        {0.8, 0.3, 0.1, 1}, {0.2, 0.4, 0.9, 1},
        0.02f, 0.01f,
        3.0f, 0.5f,
        3.0,
        1000.0f
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

    ImGui::Begin("Emitter");
    ImGui::SliderFloat3("Position", glm::value_ptr(m_Emitter->m_Position), -1.0, 1.0);
    m_Emitter->m_ComputeShader->SetFloat3("u_Position", m_Emitter->m_Position);
    ImGui::End();
}

void Sandbox3D::OnEvent(UniFox::Event& e) {
    m_CameraController.OnEvent(e);
}