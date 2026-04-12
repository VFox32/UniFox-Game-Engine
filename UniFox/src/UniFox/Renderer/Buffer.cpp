#include "ufpch.h"
#include "Buffer.h"

#include "UniFox/Renderer/Renderer.h"

#include "UniFox/Platform/OpenGL/OpenGLBuffer.h"

namespace UniFox {
    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None : UF_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
            case RendererAPI::API::OpenGL : return MakeRef<OpenGLVertexBuffer>(vertices, size);
        }
        UF_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
    
    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None : UF_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
            case RendererAPI::API::OpenGL : return MakeRef<OpenGLIndexBuffer>(indices, size);
        }
        UF_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
    
    Ref<StorageBuffer> StorageBuffer::Create(float* data, uint32_t size) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None : UF_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
            case RendererAPI::API::OpenGL : return MakeRef<OpenGLStorageBuffer>(data, size);
        }
        UF_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<FrameBuffer> FrameBuffer::Create(uint32_t width, uint32_t height) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None : UF_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
            case RendererAPI::API::OpenGL : return MakeRef<OpenGLFrameBuffer>(width, height);
        }
        UF_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}