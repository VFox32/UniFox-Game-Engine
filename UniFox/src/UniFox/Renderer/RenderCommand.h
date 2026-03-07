#pragma once

#include "RendererAPI.h"

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
    private:
        static Ref<RendererAPI> s_RendererAPI;
    };
}