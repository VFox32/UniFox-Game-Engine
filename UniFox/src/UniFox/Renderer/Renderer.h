#pragma once

#include "UniFox/Renderer/RenderCommand.h"

#include "UniFox/Renderer/Camera.h"
#include "UniFox/Renderer/Shader.h"

namespace UniFox {
    class Renderer {
    public:
        static void Init();
        static void OnWindowResize(uint32_t width, uint32_t height);

        static void BeginScene(Camera& camera);
        static void EndScene();

        static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4 transform = glm::mat4(1.0f));
        static void SubmitInstanced(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4 transform = glm::mat4(1.0f), uint32_t count = 0);

        static void Compute(const Ref<Shader>& shader, const Ref<StorageBuffer> storageBuffer, glm::vec3 groups);

        inline static RendererAPI::API GetAPI() {return RendererAPI::GetAPI();}
    private:
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
        };

        static Ref<SceneData> m_SceneData;
    };
}