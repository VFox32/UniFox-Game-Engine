#include "Sandbox3D.h"

#include "imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

Sandbox3D::Sandbox3D()
    : Layer("Sandbox3D"), m_CameraController(120, 16.0f/9.0f, true) {
}

void Sandbox3D::OnAttach() {
    UF_PROFILE_FUNCTION();

    m_ParticleShader = UniFox::Shader::Create("assets/shaders/shader.glsl");
    m_ParticleVAO = UniFox::VertexArray::Create();
    UniFox::Ref<UniFox::VertexBuffer> particleVertexBuffer = UniFox::VertexBuffer::Create(nullptr, 0);
    UniFox::BufferLayout particelLayout = {
        {UniFox::ShaderDataType::Float3, "a_QuadPos"},
        {UniFox::ShaderDataType::Float2, "a_UV"}
    };
    particleVertexBuffer->SetLayout(particelLayout);
    m_ParticleVAO->AddVertexBuffer(particleVertexBuffer);
    UniFox::Ref<UniFox::VertexBuffer> instanceVertexBuffer = UniFox::VertexBuffer::Create(nullptr, 0);
    UniFox::BufferLayout instanceLayout = {
        {UniFox::ShaderDataType::Float3, "a_InstancePos", false, true},
        {UniFox::ShaderDataType::Float4, "a_Color", false, true},
        {UniFox::ShaderDataType::Float, "a_Size", false, true},
        {UniFox::ShaderDataType::Float, "a_TexIndex", false, true}
    };
    instanceVertexBuffer->SetLayout(instanceLayout);
    m_ParticleVAO->AddVertexBuffer(instanceVertexBuffer);
    UniFox::Ref<UniFox::IndexBuffer> particleIndexBuffer = UniFox::IndexBuffer::Create(nullptr, 0);
    m_ParticleVAO->SetIndexBuffer(particleIndexBuffer);

    m_Texture1 = UniFox::Texture2D::Create("assets/textures/54p_.png");
    m_Texture2 = UniFox::Texture2D::Create("assets/textures/Missing_Texture.png");
    m_Texture1->Bind(0);
    m_Texture2->Bind(1);

    m_Emitter = new Emitter(
        m_ParticleVAO,
        {0, 0, 0}, {0.1, 0.0, 0.1},
        {0, 2, 0}, {1.2, 0.2, 1.2},
        {1, 0, 0, 1}, {0, 0, 1, 1},
        0.02f, 0.01f,
        4.0f, 0.5f,
        0.5,
        10000.0f
    );
}

void Sandbox3D::OnDetach() {
    UF_PROFILE_FUNCTION();
}

void Sandbox3D::OnUpdate(UniFox::Duration dt) {
    UF_PROFILE_FUNCTION();
    
    m_CameraController.OnUpdate(dt);

    m_Emitter->OnUpdate(dt, m_CameraController.GetCamera());

    {
        UF_PROFILE_SCOPE("Renderer Prep");
        UniFox::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        UniFox::RenderCommand::Clear();
    }

    {
        UF_PROFILE_SCOPE("Renderer Draw");

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
        transform = glm::scale(transform, {1.0f, 1.0f, 1.0f});
        m_ParticleShader->SetMat4("u_Transform", transform);
        int samplers[2] = {0, 1};
        m_ParticleShader->SetIntV("u_Textures", samplers, 2);

        m_ParticleShader->SetMat4("u_View", m_CameraController.GetCamera().GetViewMatrix());

        UniFox::Renderer::BeginScene(m_CameraController.GetCamera());
        UniFox::Renderer::SubmitInstanced(m_ParticleShader, m_ParticleVAO, transform, m_Emitter->GetCount());
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