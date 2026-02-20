#include "ufpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "UniFox/Platform/OpenGL/OpenGLVertexArray.h"

namespace UniFox {
    VertexArray* VertexArray::Create() {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None : UF_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
            case RendererAPI::API::OpenGL : return new OpenGLVertexArray();
        }
        UF_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}