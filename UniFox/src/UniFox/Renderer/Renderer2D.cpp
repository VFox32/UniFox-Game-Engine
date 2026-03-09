#include "ufpch.h"
#include "UniFox/Renderer/Renderer2D.h"

#include "UniFox/Renderer/RenderCommand.h"
#include "UniFox/Renderer/VertexArray.h"
#include "UniFox/Renderer/Shader.h"

#include "glm/gtc/matrix_transform.hpp"

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
        s_Data->flatColorShader->Bind();
        s_Data->flatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene() {

    }

    void Renderer2D::DrawQuad(const glm::vec4& color, const glm::vec2& position, const glm::vec2& scale, const float angle) {
        DrawQuad(color, {position.x, position.y, 0.0f}, scale, angle);
    }

    void Renderer2D::DrawQuad(const glm::vec4& color, const glm::vec3& position, const glm::vec2& scale, const float angle) {
        s_Data->flatColorShader->Bind();
        s_Data->flatColorShader->SetFloat4("u_Color", color);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
        transform = glm::rotate(transform, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, {scale.x, scale.y, 0.0f});
        s_Data->flatColorShader->SetMat4("u_Transform", transform);

        s_Data->quadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->quadVertexArray);
    }
}