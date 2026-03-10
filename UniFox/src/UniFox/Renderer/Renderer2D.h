#pragma once

#include "UniFox/Renderer/OrthographicCamera.h"
#include "UniFox/Renderer/Texture.h"

namespace UniFox {
    class Renderer2D {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();

        static void DrawQuad(const glm::vec2& position, const glm::vec2& scale, const float angle, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& scale, const float angle, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& position, const glm::vec2& scale, const float angle, const Ref<Texture2D> texture, const glm::vec4& tint = glm::vec4(1.0f));
        static void DrawQuad(const glm::vec3& position, const glm::vec2& scale, const float angle, const Ref<Texture2D> texture, const glm::vec4& tint = glm::vec4(1.0f));
    };
}