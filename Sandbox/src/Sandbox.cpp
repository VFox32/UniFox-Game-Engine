
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

        // SHADER
        std::string flatColorVertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;

            void main() {
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";
        std::string flatColorFragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            uniform vec4 u_Color;

            void main() {
                color = u_Color;
            }
        )";
        m_FlatColorShader.reset(UniFox::Shader::Create(flatColorVertexSrc, flatColorFragmentSrc));

        std::string textureVertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec2 a_TexCoord;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec2 v_TexCoord;

            void main() {
                v_TexCoord = a_TexCoord;

                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";
        std::string textureFragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            uniform sampler2D u_Texture;

            in vec2 v_TexCoord;

            void main() {
                color = texture(u_Texture , v_TexCoord);
            }
        )";
        m_TextureShader.reset(UniFox::Shader::Create(textureVertexSrc, textureFragmentSrc));
        
        m_Texture = UniFox::Texture2D::Create("assets/textures/54p_.png");
        std::dynamic_pointer_cast<UniFox::OpenGLShader>(m_TextureShader)->Bind();
        std::dynamic_pointer_cast<UniFox::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
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

        m_Texture->Bind();
        UniFox::Renderer::Submit(m_TextureShader, m_VertexArray);

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
    UniFox::Ref<UniFox::Shader> m_FlatColorShader, m_TextureShader;
    UniFox::Ref<UniFox::VertexArray> m_VertexArray;

    UniFox::Ref<UniFox::Texture2D> m_Texture;

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