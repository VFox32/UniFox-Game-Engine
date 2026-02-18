#include "ufpch.h"
#include "Shader.h"

#include "Renderer.h"

#include "UniFox/Platform/OpenGL/OpenGLShader.h"

namespace UniFox {
    Shader* Shader::Create(const std::string& vertexSrc, const std::string fragmentSrc) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None : UF_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
            case RendererAPI::OpenGL : return new OpenGLShader(vertexSrc, fragmentSrc);
        }
        UF_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}