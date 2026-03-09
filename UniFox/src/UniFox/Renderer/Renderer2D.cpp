#include "ufpch.h"
#include "UniFox/Renderer/Renderer2D.h"

#include "UniFox/Renderer/RenderCommand.h"
#include "UniFox/Renderer/VertexArray.h"
#include "UniFox/Renderer/Shader.h"

#include "UniFox/Platform/OpenGL/OpenGLShader.h" ///////////////////

namespace UniFox {
    struct Renderer2DStorage {
        Ref<VertexArray> quadVertexArray;
        Ref<Shader> flatColorShader;
    };

    static Ref<Renderer2DStorage> s_Data;

    void Renderer2D::Init() {
        s_Data = MakeRef<Renderer2DStorage>();

        s_Data->quadVertexArray = VertexArray::Create();

        float vertecies[4*3] = {
            -0.5f,  0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f,  0.5f, 0.0f
        };
        Ref<VertexBuffer> vertexBuffer;
        vertexBuffer = VertexBuffer::Create(vertecies, sizeof(vertecies));
            
        BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"}
        };

        vertexBuffer->SetLayout(layout);
        s_Data->quadVertexArray->AddVertexBuffer(vertexBuffer);
            
        uint32_t indices[6] {
            0, 1, 2,
            2, 3, 0
        };
        Ref<IndexBuffer> indexBuffer;
        indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        s_Data->quadVertexArray->SetIndexBuffer(indexBuffer);

        s_Data->flatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
    }

    void Renderer2D::Shutdown() {
        s_Data.reset();
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera) {
        std::dynamic_pointer_cast<UniFox::OpenGLShader>(s_Data->flatColorShader)->Bind();
        std::dynamic_pointer_cast<UniFox::OpenGLShader>(s_Data->flatColorShader)->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
        std::dynamic_pointer_cast<UniFox::OpenGLShader>(s_Data->flatColorShader)->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
    }

    void Renderer2D::EndScene() {

    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
        DrawQuad({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
        //std::dynamic_pointer_cast<UniFox::OpenGLShader>(s_Data->flatColorShader)->Bind();
        std::dynamic_pointer_cast<UniFox::OpenGLShader>(s_Data->flatColorShader)->UploadUniformFloat4("u_Color", color);

        s_Data->quadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->quadVertexArray);
    }
}