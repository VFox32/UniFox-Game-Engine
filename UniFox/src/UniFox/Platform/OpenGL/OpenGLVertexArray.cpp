#include "ufpch.h"
#include "UniFox/Platform/OpenGL/OpenGLVertexArray.h"

#include "UniFox/Core/Core.h"
#include "UniFox/Core/Log.h"

#include "glad/glad.h"

namespace UniFox {
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:  return GL_FLOAT;
            case ShaderDataType::Float2: return GL_FLOAT;
            case ShaderDataType::Float3: return GL_FLOAT;
            case ShaderDataType::Float4: return GL_FLOAT;
            
            case ShaderDataType::Mat3:   return GL_FLOAT;
            case ShaderDataType::Mat4:   return GL_FLOAT;
            
            case ShaderDataType::Int:    return GL_INT;
            case ShaderDataType::Int2:   return GL_INT;
            case ShaderDataType::Int3:   return GL_INT;
            case ShaderDataType::Int4:   return GL_INT;
            
            case ShaderDataType::Bool:   return GL_BOOL;
        }
        UF_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return GL_NONE;
    }
    
    OpenGLVertexArray::OpenGLVertexArray() {
        UF_PROFILE_FUNCTION();
        
        glCreateVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray() {
        UF_PROFILE_FUNCTION();
        
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const {
        UF_PROFILE_FUNCTION();
        
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const {
        UF_PROFILE_FUNCTION();
        
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
        UF_PROFILE_FUNCTION();
        
        UF_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size() != 0, "Vertex buffer has no layout!");
        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        for(const auto& element : vertexBuffer->GetLayout()) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index, element.GetComponentCount(),
                ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                vertexBuffer->GetLayout().GetStride(),
                (const void*)(uintptr_t)element.Offset
            );
            index++;
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
        UF_PROFILE_FUNCTION();
        
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }
}