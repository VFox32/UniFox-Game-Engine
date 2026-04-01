#include "ufpch.h"
#include "UniFox/Platform/OpenGL/OpenGLBuffer.h"

#include "glad/glad.h"

namespace UniFox {
    ////////////////////////
    ///// VertexBuffer /////
    ////////////////////////

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertecies, uint32_t size) {
        UF_PROFILE_FUNCTION();
        
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertecies, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        UF_PROFILE_FUNCTION();
        
        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLVertexBuffer::Bind() const {
        UF_PROFILE_FUNCTION();
        
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLVertexBuffer::Unbind() const {
        UF_PROFILE_FUNCTION();
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    
    void OpenGLVertexBuffer::SetData(float* vertecies, uint32_t size) {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertecies, GL_STATIC_DRAW);
    }

    ///////////////////////
    ///// IndexBuffer /////
    ///////////////////////
    
    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) 
        : m_Count(count) {
        UF_PROFILE_FUNCTION();
        
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        UF_PROFILE_FUNCTION();
        
        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLIndexBuffer::Bind() const {
        UF_PROFILE_FUNCTION();
        
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLIndexBuffer::Unbind() const {
        UF_PROFILE_FUNCTION();
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLIndexBuffer::SetData(uint32_t* indices, uint32_t count) {
        m_Count = count;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }
}