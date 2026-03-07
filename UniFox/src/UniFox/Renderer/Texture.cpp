#include "ufpch.h"
#include "Texture.h"

#include "UniFox/Renderer/Renderer.h"

#include "UniFox/Platform/OpenGL/OpenGLTexture.h"

namespace UniFox {
    Ref<Texture2D> Texture2D::Create(const std::string& path) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None : UF_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
            case RendererAPI::API::OpenGL : return MakeRef<OpenGLTexture2D>(path);
        }
        UF_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}