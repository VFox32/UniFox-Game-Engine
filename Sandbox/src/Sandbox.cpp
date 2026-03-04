
#include <UniFox.h>

#include "UniFox/Platform/OpenGL/OpenGLShader.h"

#include "imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class ExampleLayer : public UniFox::Layer {
public:
    ExampleLayer() 
        : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {
        
        m_VertexArray.reset(UniFox::VertexArray::Create());

        float vertecies[4*5] = {
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        };
        UniFox::Ref<UniFox::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(UniFox::VertexBuffer::Create(vertecies, sizeof(vertecies)));
        
        UniFox::BufferLayout layout = {
            {UniFox::ShaderDataType::Float3, "a_Position"},
            {UniFox::ShaderDataType::Float2, "a_TexCoord"}
        };

        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);
        
        uint32_t indices[6] {
            0, 1, 2,
            2, 3, 0
        };
        UniFox::Ref<UniFox::IndexBuffer> indexBuffer;
        indexBuffer.reset(UniFox::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_FlatColorShader = UniFox::Shader::Create("assets/shaders/FlatColor.glsl");
        
        m_Texture = UniFox::Texture2D::Create("assets/textures/54p_.png");
        m_CheckerTexture = UniFox::Texture2D::Create("assets/textures/Checker.png");

        auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
        std::dynamic_pointer_cast<UniFox::OpenGLShader>(textureShader)->Bind();
        std::dynamic_pointer_cast<UniFox::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
    }

    void OnUpdate(UniFox::Duration dt) override {
        //UF_INFO("UPS: {0}", 1.0f/dt.s());

        float movementSpeed = 1.0f * dt;
        float rotationSpeed = 40.0f * dt;

        if(UniFox::Input::IsKeyPressed(UF_KEY_W)) m_CameraPosition.y += movementSpeed;
        if(UniFox::Input::IsKeyPressed(UF_KEY_S)) m_CameraPosition.y -= movementSpeed;
        if(UniFox::Input::IsKeyPressed(UF_KEY_A)) m_CameraPosition.x -= movementSpeed;
        if(UniFox::Input::IsKeyPressed(UF_KEY_D)) m_CameraPosition.x += movementSpeed;

        if(UniFox::Input::IsKeyPressed(UF_KEY_Q)) m_CameraRotation += rotationSpeed;
        if(UniFox::Input::IsKeyPressed(UF_KEY_E)) m_CameraRotation -= rotationSpeed;

        UniFox::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        UniFox::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        UniFox::Renderer::BeginScene(m_Camera);

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.19f));

        std::dynamic_pointer_cast<UniFox::OpenGLShader>(m_FlatColorShader)->Bind();
        std::dynamic_pointer_cast<UniFox::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_Color);

        for(int x = 0; x < 5; x++)
        for(int y = 0; y < 5; y++) {
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3((float)x * 0.2f, (float)y * 0.2f, 0.0f)) * scale;
            UniFox::Renderer::Submit(m_FlatColorShader, m_VertexArray, transform);
        }
        
        auto textureShader = m_ShaderLibrary.Get("Texture");
        m_Texture->Bind();
        UniFox::Renderer::Submit(textureShader, m_VertexArray);
        m_CheckerTexture->Bind();
        UniFox::Renderer::Submit(textureShader, m_VertexArray);

        UniFox::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override {
        ImGui::Begin("Colors");
            ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
        ImGui::End();
    }

    void OnEvent(UniFox::Event& event) override {
        UniFox::EventDispatcher dispatcher(event);

        //dispatcher.Dispatch<UniFox::WindowResizeEvent>(UF_BIND_EVENT_FN(OnWindowResize));
    }
private:
    UniFox::ShaderLibrary m_ShaderLibrary;
    UniFox::Ref<UniFox::Shader> m_FlatColorShader;
    UniFox::Ref<UniFox::VertexArray> m_VertexArray;

    UniFox::Ref<UniFox::Texture2D> m_Texture, m_CheckerTexture;

    UniFox::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraRotation;
    
    glm::vec4 m_Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
};

class Sandbox : public UniFox::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
    }
    ~Sandbox() {

    }
};

UniFox::Application* UniFox::CreateApplication() {
    return new Sandbox();
}