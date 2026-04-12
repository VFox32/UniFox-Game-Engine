#include "ufpch.h"
#include "UniFox/Renderer/Renderer2D.h"

#include "UniFox/Renderer/RenderCommand.h"
#include "UniFox/Renderer/VertexArray.h"
#include "UniFox/Renderer/Shader.h"

#include "glm/gtc/matrix_transform.hpp"

namespace UniFox {
    struct Renderer2DStorage {
        Ref<VertexArray> quadVertexArray;
        Ref<Shader> shader;
        Ref<Texture2D> whiteTexture;
    };

    static Ref<Renderer2DStorage> s_Data;

    void Renderer2D::Init() {
        UF_PROFILE_FUNCTION();
        
        s_Data = MakeRef<Renderer2DStorage>();

        s_Data->quadVertexArray = VertexArray::Create();

        float vertecies[4*5] = {
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f,  0.5f, 0.0f, 1.0f, 1.0f
        };
        Ref<VertexBuffer> vertexBuffer;
        vertexBuffer = VertexBuffer::Create(vertecies, sizeof(vertecies));
            
        BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float2, "a_TexCoord"}
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

        s_Data->whiteTexture = Texture2D::Create(1, 1, 0x1908); // 0x1908 = GL_RGBA
        static uint32_t whiteTextureData = 0xffffffff;
        s_Data->whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

        s_Data->shader = Shader::Create("assets/shaders/Shader2D.glsl");
        s_Data->shader->Bind();
        s_Data->shader->SetInt("u_Texture", 0);
    }

    void Renderer2D::Shutdown() {
        UF_PROFILE_FUNCTION();
        
        s_Data.reset();
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera) {
        UF_PROFILE_FUNCTION();
        
        s_Data->shader->Bind();
        s_Data->shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene() {
        UF_PROFILE_FUNCTION();
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& scale, const float angle, const glm::vec4& color) {
        DrawQuad({position.x, position.y, 0.0f}, scale, angle, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& scale, const float angle, const glm::vec4& color) {
        UF_PROFILE_FUNCTION();
        
        s_Data->shader->SetFloat4("u_Color", color);
        s_Data->whiteTexture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
        transform = glm::rotate(transform, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, {scale.x, scale.y, 0.0f});
        s_Data->shader->SetMat4("u_Transform", transform);

        s_Data->quadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->quadVertexArray);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& scale, const float angle, const Ref<Texture2D> texture, const glm::vec4& tint) {
        DrawQuad({position.x, position.y, 0.0f}, scale, angle, texture, tint);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& scale, const float angle, const Ref<Texture2D> texture, const glm::vec4& tint) {    
        UF_PROFILE_FUNCTION();
           
        s_Data->shader->SetFloat4("u_Color", tint);
        texture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
        transform = glm::rotate(transform, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, {scale.x, scale.y, 0.0f});
        s_Data->shader->SetMat4("u_Transform", transform);

        s_Data->quadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->quadVertexArray);
    }
}