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

    m_ComputeShader = UniFox::Shader::Create("assets/shaders/particle.glsl");
    m_ComputeShader->Bind();
    m_ComputeShader->SetFloat("u_Lifetime", 5);
    m_ComputeShader->SetFloat("u_LifetimeVariance", 0.5);
    m_ComputeShader->SetFloat3("u_Position", {0, 0, 0});
    m_ComputeShader->SetFloat3("u_PositionVariance", {0.1, 0.1, 0.1});
    m_ComputeShader->SetFloat3("u_Velocity", {0, 2, 0});
    m_ComputeShader->SetFloat3("u_VelocityVariance", {1.2, 0.2, 1.2});
    m_ComputeShader->SetFloat4("u_StartColor", {1, 0, 0, 1});
    m_ComputeShader->SetFloat4("u_EndColor", {0, 0, 1, 1});
    m_ComputeShader->SetFloat("u_Size", 0.02);
    m_ComputeShader->SetFloat("u_SizeVariance", 0.01);
    m_ComputeShader->SetFloat("u_FadeOut", 0.5);

    m_StorageBuffer = UniFox::StorageBuffer::Create(nullptr, 1000000 * 16 * sizeof(float));

    static float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
        -0.5f,  0.5f,
         0.5f,  0.5f
    };
    static uint32_t indices[] = {
        0, 1, 2,
        2, 1, 3
    };
    m_ParticleVAO = UniFox::VertexArray::Create();
    UniFox::Ref<UniFox::VertexBuffer> particleVertexBuffer = UniFox::VertexBuffer::Create(vertices, sizeof(vertices));
    UniFox::BufferLayout particelLayout = {
        {UniFox::ShaderDataType::Float2, "a_QuadPos"},
    };
    particleVertexBuffer->SetLayout(particelLayout);
    m_ParticleVAO->AddVertexBuffer(particleVertexBuffer);
    UniFox::Ref<UniFox::IndexBuffer> particleIndexBuffer = UniFox::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
    m_ParticleVAO->SetIndexBuffer(particleIndexBuffer);

    /*m_Texture1 = UniFox::Texture2D::Create("assets/textures/54p_.png");
    m_Texture2 = UniFox::Texture2D::Create("assets/textures/Missing_Texture.png");
    m_Texture1->Bind(0);
    m_Texture2->Bind(1);*/

    /*m_Emitter = new Emitter(
        m_ParticleVAO,
        {0, 0, 0}, {0.1, 0.0, 0.1},
        {0, 2, 0}, {1.2, 0.2, 1.2},
        {1, 0, 0, 1}, {0, 0, 1, 1},
        0.02f, 0.01f,
        4.0f, 0.5f,
        0.5,
        10000.0f
    );*/
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

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
        transform = glm::scale(transform, {1.0f, 1.0f, 1.0f});
        m_ParticleShader->SetMat4("u_Transform", transform);
        int samplers[2] = {0, 1};
        m_ParticleShader->SetIntV("u_Textures", samplers, 2);

        m_ParticleShader->SetMat4("u_View", m_CameraController.GetCamera().GetViewMatrix());

        m_ComputeShader->Bind();
        m_ComputeShader->SetFloat("u_DeltaTime", dt);
        UniFox::Renderer::BeginScene(m_CameraController.GetCamera());
        UniFox::Renderer::Compute(m_ComputeShader, m_StorageBuffer, {(1000000+255) / 256, 1, 1});
        UniFox::Renderer::SubmitInstanced(m_ParticleShader, m_ParticleVAO, transform, 1000000);
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