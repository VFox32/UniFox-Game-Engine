#pragma once

#include "UniFox/Renderer/RendererAPI.h"

namespace UniFox {
    class RenderCommand {
    public:
        inline static void Init() {
            s_RendererAPI->Init();
        }

        inline static void SetViewport(uint32_t xMin, uint32_t yMin, uint32_t xMax, uint32_t yMax) {
            s_RendererAPI->SetViewport(xMin, yMin, xMax, yMax);
        }

        inline static void SetClearColor(const glm::vec4& color) {
            s_RendererAPI->SetClearColor(color);
        }
        
        inline static void Clear() {
            s_RendererAPI->Clear();
        }

        inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) {
            s_RendererAPI->DrawIndexed(vertexArray);
        }
        
        inline static void DrawInstanced(const Ref<VertexArray>& vertexArray, uint32_t count) {
            s_RendererAPI->DrawInstanced(vertexArray, count);
        }

        inline static void Compute(const Ref<StorageBuffer> storageBuffer, glm::vec3 groups) {
            s_RendererAPI->Compute(storageBuffer, groups);
        }
    private:
        static Ref<RendererAPI> s_RendererAPI;
    };
}