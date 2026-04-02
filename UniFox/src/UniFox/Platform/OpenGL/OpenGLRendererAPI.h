#pragma once

#include "UniFox/Renderer/RendererAPI.h"

namespace UniFox {
    class OpenGLRendererAPI : public RendererAPI {
    public:
        virtual void Init() override;
        virtual void SetViewport(uint32_t xMin, uint32_t yMin, uint32_t xMax, uint32_t yMax) override;

        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void Clear() override;

        virtual void DrawIndexed(const Ref<VertexArray>& vbertexArray) override;
        virtual void DrawInstanced(const Ref<VertexArray>& vbertexArray, uint32_t count) override;

        virtual void Compute(const Ref<StorageBuffer> storageBuffer, glm::vec3 groups) override;
    };
}