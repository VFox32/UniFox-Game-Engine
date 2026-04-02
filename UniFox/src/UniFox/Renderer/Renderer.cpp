#include "ufpch.h"
#include "Renderer.h"

#include "UniFox/Renderer/Renderer2D.h"
#include "UniFox/Platform/OpenGL/OpenGLShader.h"

namespace UniFox {
    Ref<Renderer::SceneData> Renderer::m_SceneData = MakeRef<Renderer::SceneData>();

    void Renderer::Init() {
        UF_PROFILE_FUNCTION();
        
        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    void Renderer::BeginScene(PerspectiveCamera& camera) {
        UF_PROFILE_FUNCTION();
        
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene() {
        UF_PROFILE_FUNCTION();
    }

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4 transform) {
        UF_PROFILE_FUNCTION();
        
        shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
    
    void Renderer::SubmitInstanced(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4 transform, uint32_t count) {
        UF_PROFILE_FUNCTION();
        
        shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawInstanced(vertexArray, count);
    }

    void Renderer::Compute(const Ref<Shader>& shader, const Ref<StorageBuffer> storageBuffer, glm::vec3 groups) {
        UF_PROFILE_FUNCTION();

        shader->Bind();
        storageBuffer->Bind();
        RenderCommand::Compute(storageBuffer, groups);
    }
}