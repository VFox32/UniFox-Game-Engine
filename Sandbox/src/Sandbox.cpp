
#include <UniFox.h>

#include "imgui.h"

class ExampleLayer : public UniFox::Layer {
public:
    ExampleLayer() 
        : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {

        m_VertexArray.reset(UniFox::VertexArray::Create());

        float vertecies[3 * 7] = {
            -0.5f, -0.5f,  0.0f, 0.8f, 0.2f, 0.1f, 1.0f,
             0.5f, -0.5f,  0.0f, 0.1f, 0.8f, 0.2f, 1.0f,
             0.0f,  0.5f,  0.0f, 0.2f, 0.1f, 0.8f, 1.0f
        };
        std::shared_ptr<UniFox::VertexBuffer> vertexBuffer;
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
        std::shared_ptr<UniFox::IndexBuffer> indexBuffer;
        indexBuffer.reset(UniFox::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;

            out vec3 v_Position;
            out vec4 v_Color;

            void main() {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
            }
        )";
        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main() {
                color = v_Color;
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

        UniFox::Renderer::Submit(m_Shader, m_VertexArray);

        UniFox::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override {
    }

    void OnEvent(UniFox::Event& event) override {
        UniFox::EventDispatcher dispatcher(event);

        dispatcher.Dispatch<UniFox::MouseScrolledEvent>(UF_BIND_EVENT_FN(OnMouseScroll));
    }

    bool OnMouseScroll(UniFox::MouseScrolledEvent& e) {
        return false;
    }
private:
    std::shared_ptr<UniFox::Shader> m_Shader;
    std::shared_ptr<UniFox::VertexArray> m_VertexArray;

    UniFox::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraRotation;
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