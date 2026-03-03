
#include <UniFox.h>

#include "UniFox/Platform/OpenGL/OpenGLShader.h"

#include "imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class ExampleLayer : public UniFox::Layer {
public:
    ExampleLayer() 
        : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {

        // TRIANGLE
        m_VertexArray.reset(UniFox::VertexArray::Create());

        float vertecies[3 * 7] = {
            -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
             0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
             0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f
        };
        UniFox::Ref<UniFox::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(UniFox::VertexBuffer::Create(vertecies, sizeof(vertecies)));

        UniFox::BufferLayout layout = {
            {UniFox::ShaderDataType::Float3, "a_Position"},
            {UniFox::ShaderDataType::Float4, "a_Color"}
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] {
            0, 1, 2
        };
        UniFox::Ref<UniFox::IndexBuffer> indexBuffer;
        indexBuffer.reset(UniFox::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);
        
        // SQUARE
        m_SquareVertexArray.reset(UniFox::VertexArray::Create());

        float SquareVertecies[4*7] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
        };
        UniFox::Ref<UniFox::VertexBuffer> squareVertexBuffer;
        squareVertexBuffer.reset(UniFox::VertexBuffer::Create(SquareVertecies, sizeof(SquareVertecies)));

        squareVertexBuffer->SetLayout(layout);
        m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);
        
        uint32_t squareIndices[6] {
            0, 1, 2,
            2, 1, 3
        };
        UniFox::Ref<UniFox::IndexBuffer> squareIndexBuffer;
        squareIndexBuffer.reset(UniFox::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

        // SHADER
        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;
            out vec4 v_Color;

            void main() {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";
        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            uniform vec4 u_Color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main() {
                color = u_Color;
                //color = v_Color;
                //color = vec4(v_Position*0.5+0.5, 1);
            }
        )";

        m_Shader.reset(UniFox::Shader::Create(vertexSrc, fragmentSrc));
    }

    void OnUpdate(UniFox::Duration dt) override {
        UF_INFO("UPS: {0}", 1.0f/dt.s());

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

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));

        std::dynamic_pointer_cast<UniFox::OpenGLShader>(m_Shader)->Bind();
        std::dynamic_pointer_cast<UniFox::OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", m_Color);

        for(int x = 0; x < 5; x++)
        for(int y = 0; y < 5; y++) {
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3((float)x * 0.2f, (float)y * 0.2f, 0.0f)) * scale;
            UniFox::Renderer::Submit(m_Shader, m_SquareVertexArray, transform);
        }
        UniFox::Renderer::Submit(m_Shader, m_VertexArray);

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
    UniFox::Ref<UniFox::Shader> m_Shader;
    UniFox::Ref<UniFox::VertexArray> m_VertexArray;
    UniFox::Ref<UniFox::VertexArray> m_SquareVertexArray;

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