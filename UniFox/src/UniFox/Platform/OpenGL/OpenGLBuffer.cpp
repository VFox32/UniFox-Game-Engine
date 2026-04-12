#include "ufpch.h"
#include "UniFox/Platform/OpenGL/OpenGLBuffer.h"

#include "glad/glad.h"

#include "UniFox/Platform/OpenGL/OpenGLTexture.h"

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

    /////////////////////////
    ///// StorageBuffer /////
    /////////////////////////

    OpenGLStorageBuffer::OpenGLStorageBuffer(float* data, uint32_t size) {
        UF_PROFILE_FUNCTION();
        
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_RendererID);
        glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_DRAW);

        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_RendererID);
    }

    OpenGLStorageBuffer::~OpenGLStorageBuffer() {
        UF_PROFILE_FUNCTION();
        
        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLStorageBuffer::Bind(unsigned int index) const {
        UF_PROFILE_FUNCTION();
        
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_RendererID);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, m_RendererID);
    }

    void OpenGLStorageBuffer::Unbind() const {
        UF_PROFILE_FUNCTION();
        
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0);
    }
    
    void OpenGLStorageBuffer::SetData(float* data, uint32_t size) {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_RendererID);
        glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_STATIC_DRAW);
    }

    /////////////////////////
    ///// FrameBuffer /////
    /////////////////////////

    OpenGLFrameBuffer::OpenGLFrameBuffer(uint32_t width, uint32_t height) {
        UF_PROFILE_FUNCTION();
        
        glGenFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

        
        glGenRenderbuffers(1, &m_RenderBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RenderBuffer);
    }

    OpenGLFrameBuffer::~OpenGLFrameBuffer() {
        UF_PROFILE_FUNCTION();
        
        glDeleteFramebuffers(1, &m_RendererID);
    }

    void OpenGLFrameBuffer::Bind() const {
        UF_PROFILE_FUNCTION();
        
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
    }

    void OpenGLFrameBuffer::Unbind() const {
        UF_PROFILE_FUNCTION();
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFrameBuffer::Attach(const Ref<Texture2D> texture) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_ColorAttachments.size(), GL_TEXTURE_2D, texture->GetRendererID(), 0);
        //glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,gPosition,0);

        m_ColorAttachments.push_back(texture);
    }

    void OpenGLFrameBuffer::Draw() {
        std::vector<GLuint> attachments;
        for(int i = 0; i < m_ColorAttachments.size(); i++) {
            attachments.push_back(GL_COLOR_ATTACHMENT0 + i);
        }

        glDrawBuffers(attachments.size(), attachments.data());
        //GLuint attachments[3]={GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1,GL_COLOR_ATTACHMENT2};
        //glDrawBuffers(3,attachments);
    }

    void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height) {
        Bind();

        //glDeleteTextures(1, &m_RenderBuffer);
        //glDeleteRenderbuffers(1, &m_RenderBuffer);

        //glGenRenderbuffers(1, &m_RenderBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RenderBuffer);

        for(Ref<Texture2D> texture : m_ColorAttachments) {
            texture->Resize(width, height);
        }

        for(uint32_t i = 0; i < m_ColorAttachments.size(); i++) {
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_ColorAttachments[i]->GetRendererID(), 0);
        }
        Draw();
        
        if (!IsComplete()) {
            std::cout << "Framebuffer incomplete!" << std::endl;
        }

        Unbind();
    }

    bool OpenGLFrameBuffer::IsComplete() const {
        return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    }
}