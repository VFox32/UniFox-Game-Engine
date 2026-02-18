#include "ufpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "UniFox/Platform/OpenGL/OpenGLBuffer.h"

namespace UniFox {
    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None : UF_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
            case RendererAPI::OpenGL : return new OpenGLVertexBuffer(vertices, size);
        }
        UF_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
    
    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None : UF_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
            case RendererAPI::OpenGL : return new OpenGLIndexBuffer(indices, size);
        }
        UF_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}