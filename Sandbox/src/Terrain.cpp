#include "Terrain.h"

#include "imgui.h"

Terrain::Terrain() : Layer("Terrain"), m_CameraController(120, 16.0f/9.0f, true) {

}

void Terrain::OnAttach() {
    m_Texture = UniFox::Texture2D::Create("assets/textures/dirt.png");

    for(int z = -4; z <= 3; z++)
    for(int x = -4; x <= 3; x++) {
        Chunk chunk({x*32, 0, z*32});
        m_Chunks.push_back(chunk);
    }

    m_QuadVAO = UniFox::VertexArray::Create();
    float q[] = {
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,
         1.0f,  1.0f, 1.0f, 1.0f
    };
    UniFox::Ref<UniFox::VertexBuffer> vertexBuffer = UniFox::VertexBuffer::Create(q, sizeof(q));
    static UniFox::BufferLayout layout = {
        {UniFox::ShaderDataType::Float2, "a_Position"},
        {UniFox::ShaderDataType::Float2, "a_TexCoord"}
    };
    vertexBuffer->SetLayout(layout);
    uint32_t i[] = {
        0, 1, 2,
        2, 1, 3
    };
    m_QuadVAO->AddVertexBuffer(vertexBuffer);
    UniFox::Ref<UniFox::IndexBuffer> indexBuffer = UniFox::IndexBuffer::Create(i, sizeof(i) / sizeof(uint32_t));
    m_QuadVAO->SetIndexBuffer(indexBuffer);

    m_WorldShader = UniFox::Shader::Create("assets/shaders/terrain.glsl");
    m_DisplayShader = UniFox::Shader::Create("assets/shaders/quad.glsl");

    m_Position = UniFox::Texture2D::Create(1280, 720, 0x881A); // 0x881A = GL_RGBA16F
    m_Normal = UniFox::Texture2D::Create(1280, 720, 0x881A); // 0x881A = GL_RGBA16F
    m_Albedo = UniFox::Texture2D::Create(1280, 720, 0x1908); // 0x1908 = GL_RGBA

    m_FBO = UniFox::FrameBuffer::Create(1280, 720);
    m_FBO->Bind();
    m_FBO->Attach(m_Position);
    m_FBO->Attach(m_Normal);
    m_FBO->Attach(m_Albedo);
    m_FBO->Draw();
    if (!m_FBO->IsComplete()) {
        std::cout << "Framebuffer incomplete!" << std::endl;
    }
    m_FBO->Unbind();
}

void Terrain::OnDetach() {

}

void Terrain::OnUpdate(UniFox::Duration dt) {
    m_CameraController.OnUpdate(dt);

    UniFox::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});

    // 1. Geometry pass
    m_FBO->Bind();
    UniFox::Renderer::BeginScene(m_CameraController.GetCamera());
    UniFox::RenderCommand::Clear();
    m_Texture->Bind(0);
    m_WorldShader->Bind();
    m_WorldShader->SetInt("u_Texture", 0);
    for(auto& chunk : m_Chunks) {
        UniFox::Renderer::Submit(m_WorldShader, chunk.m_VAO, chunk.m_Transform);
    }
    UniFox::Renderer::EndScene();
    m_FBO->Unbind();

    // 2. Lighting pass
    UniFox::Renderer::BeginScene(m_CameraController.GetCamera());
    UniFox::RenderCommand::Clear();
    m_DisplayShader->Bind();
    m_Position->Bind(0);
    m_Normal->Bind(1);
    m_Albedo->Bind(2);
    m_DisplayShader->SetInt("g_Position", 0);
    m_DisplayShader->SetInt("g_Normal", 1);
    m_DisplayShader->SetInt("g_Albedo", 2);
    UniFox::Renderer::Submit(m_DisplayShader, m_QuadVAO);
    UniFox::Renderer::EndScene();
}

void Terrain::OnImGuiRender() {
    ImGui::Begin("Camera");
    glm::vec3 position = m_CameraController.GetCamera().GetPosition();
    glm::vec3 rotation = m_CameraController.GetCamera().GetRotation();
    ImGui::Text("Position: %.3f, %.3f, %.3f", position.x, position.y, position.z);
    ImGui::Text("Rotation: %.3f, %.3f, %.3f", rotation.x, rotation.y, rotation.z);
    ImGui::End();

    //ImGui::Begin("Texture Test");
    //ImGui::Image((void*)(uintptr_t)m_FBO->GetColorAttachment(0).get(), ImVec2(1280, 720));
    //ImGui::End();
}

void Terrain::OnEvent(UniFox::Event& e) {
    m_CameraController.OnEvent(e);

    UniFox::EventDispatcher dispatcher(e);
    
    dispatcher.Dispatch<UniFox::WindowResizeEvent>(UF_BIND_EVENT_FN(OnWindowResize));
}


bool Terrain::OnWindowResize(UniFox::WindowResizeEvent& e) {
    UF_PROFILE_FUNCTION();
    
    unsigned int w = e.GetWidth(), h = e.GetHeight();

    m_FBO->Resize(w, h);

    return false;
}