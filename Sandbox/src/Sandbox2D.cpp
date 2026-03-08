#include "Sandbox2D.h"

#include "UniFox/Platform/OpenGL/OpenGLShader.h" ///////////////////

#include "imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(16.0f/9.0f, true), m_Color(1.0f, 0.0f, 0.0f, 1.0f) {
}

void Sandbox2D::OnAttach() {
    m_VertexArray = UniFox::VertexArray::Create();

    float vertecies[4*3] = {
        -0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f
    };
    UniFox::Ref<UniFox::VertexBuffer> vertexBuffer;
    vertexBuffer = UniFox::VertexBuffer::Create(vertecies, sizeof(vertecies));
        
    UniFox::BufferLayout layout = {
        {UniFox::ShaderDataType::Float3, "a_Position"}
    };

    vertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(vertexBuffer);
        
    uint32_t indices[6] {
        0, 1, 2,
        2, 3, 0
    };
    UniFox::Ref<UniFox::IndexBuffer> indexBuffer;
    indexBuffer = UniFox::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
    m_VertexArray->SetIndexBuffer(indexBuffer);

    m_Shader = UniFox::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach() {

}

void Sandbox2D::OnUpdate(UniFox::Duration dt) {
    m_CameraController.OnUpdate(dt);

    UniFox::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    UniFox::RenderCommand::Clear();

    UniFox::Renderer::BeginScene(m_CameraController.GetCamera());

    std::dynamic_pointer_cast<UniFox::OpenGLShader>(m_Shader)->Bind();
    std::dynamic_pointer_cast<UniFox::OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", m_Color);

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
    UniFox::Renderer::Submit(m_Shader, m_VertexArray, transform);

    UniFox::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender() {
    ImGui::Begin("Colors");
        ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
    ImGui::End();
}

void Sandbox2D::OnEvent(UniFox::Event& e) {
    m_CameraController.OnEvent(e);
}