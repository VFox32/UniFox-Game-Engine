#include "ufpch.h"
#include "UniFox/Platform/OpenGL/OpenGLRendererAPI.h"

#include "glad/glad.h"

namespace UniFox {
    void OpenGLRendererAPI::Init() {
        UF_PROFILE_FUNCTION();
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRendererAPI::SetViewport(uint32_t xMin, uint32_t yMin, uint32_t xMax, uint32_t yMax) {
        glViewport(xMin, yMin, xMax, yMax);
    }

    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray) {
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRendererAPI::DrawInstanced(const Ref<VertexArray>& vertexArray, uint32_t count) {
        glDrawElementsInstanced(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr, count);
    }

    void OpenGLRendererAPI::Compute(const Ref<StorageBuffer> storageBuffer, glm::vec3 groups) {
        glDispatchCompute(groups.x, groups.y, groups.z);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    }
}