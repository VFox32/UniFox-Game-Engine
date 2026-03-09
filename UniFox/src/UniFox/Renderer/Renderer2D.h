#pragma once

#include "UniFox/Renderer/OrthographicCamera.h"

namespace UniFox {
    class Renderer2D {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();

        static void DrawQuad(const glm::vec4& color, const glm::vec2& position, const glm::vec2& scale = glm::vec2(1.0f), const float angle = 0.0f);
        static void DrawQuad(const glm::vec4& color, const glm::vec3& position, const glm::vec2& scale = glm::vec2(1.0f), const float angle = 0.0f);
    };
}