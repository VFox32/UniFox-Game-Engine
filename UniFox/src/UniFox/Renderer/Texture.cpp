#include "ufpch.h"
#include "Texture.h"

#include "UniFox/Renderer/Renderer.h"

#include "UniFox/Platform/OpenGL/OpenGLTexture.h"

namespace UniFox {
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height, unsigned int format) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None : UF_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
            case RendererAPI::API::OpenGL : return MakeRef<OpenGLTexture2D>(width, height, format);
        }
        UF_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
    
    Ref<Texture2D> Texture2D::Create(const std::string& path) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None : UF_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
            case RendererAPI::API::OpenGL : return MakeRef<OpenGLTexture2D>(path);
        }
        UF_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
    
	Ref<Texture3D> Texture3D::Create(uint32_t width, uint32_t height, uint32_t depth, unsigned int format) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None : UF_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
            case RendererAPI::API::OpenGL : return MakeRef<OpenGLTexture3D>(width, height, depth, format);
        }
        UF_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
    
    Ref<Texture3D> Texture3D::Create(const std::string& path) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None : UF_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
            case RendererAPI::API::OpenGL : return MakeRef<OpenGLTexture3D>(path);
        }
        UF_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}