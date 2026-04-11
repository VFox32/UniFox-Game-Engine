#include "Terrain.h"

#include "imgui.h"

Terrain::Terrain() : Layer("Terrain"), m_CameraController(120, 16.0f/9.0f, true) {

}

void Terrain::OnAttach() {
    m_Texture = UniFox::Texture2D::Create("assets/textures/dirt.png");

    m_Shader = UniFox::Shader::Create("assets/shaders/terrain.glsl");
    m_Shader->Bind();
    m_Shader->SetFloat3("u_Sun", glm::normalize(glm::vec3(1.0, 2.0, 3.0)));

    for(int z = -4; z <= 3; z++)
    for(int x = -4; x <= 3; x++) {
        Chunk chunk({x*16, 0, z*16});
        m_Chunks.push_back(chunk);
    }
}

void Terrain::OnDetach() {

}

void Terrain::OnUpdate(UniFox::Duration dt) {
    m_CameraController.OnUpdate(dt);

    UniFox::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    UniFox::RenderCommand::Clear();

    UniFox::Renderer::BeginScene(m_CameraController.GetCamera());
    m_Texture->Bind();
    for(auto& chunk : m_Chunks) {
        UniFox::Renderer::Submit(m_Shader, chunk.m_VAO, chunk.m_Transform);
    }
    UniFox::Renderer::EndScene();
}

void Terrain::OnImGuiRender() {
    ImGui::Begin("Camera");
    glm::vec3 position = m_CameraController.GetCamera().GetPosition();
    glm::vec3 rotation = m_CameraController.GetCamera().GetRotation();
    ImGui::Text("Position: %.3f, %.3f, %.3f", position.x, position.y, position.z);
    ImGui::Text("Rotation: %.3f, %.3f, %.3f", rotation.x, rotation.y, rotation.z);
    ImGui::End();
}

void Terrain::OnEvent(UniFox::Event& e) {
    m_CameraController.OnEvent(e);
}