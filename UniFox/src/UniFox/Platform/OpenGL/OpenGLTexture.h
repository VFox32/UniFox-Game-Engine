#pragma once

#include "UniFox/Renderer/Texture.h"

#include <glad/glad.h>

namespace UniFox {
    class OpenGLTexture2D : public Texture2D {
    public:
        OpenGLTexture2D(const std::string& path);
        OpenGLTexture2D(uint32_t width, uint32_t height, GLenum format);

        virtual ~OpenGLTexture2D();
        
        virtual uint32_t GetWidth() const override {return m_Width;}
        virtual uint32_t GetHeight() const override {return m_Height;}
        virtual uint32_t GetDepth() const override {return 1;}
        virtual unsigned int GetRendererID() const override {return m_RendererID;}

        virtual void SetData(void* data, uint32_t size) override;

        virtual void Bind(uint32_t slot = 0) const override;
        
        virtual void Resize(uint32_t width, uint32_t height) override;
    private:
        std::string m_Path;
        uint32_t m_Width, m_Height;
        uint32_t m_RendererID;
        GLenum m_InternalFormat, m_DataFormat;
    };
    
    class OpenGLTexture3D : public Texture3D {
    public:
        OpenGLTexture3D(const std::string& path);
        OpenGLTexture3D(uint32_t width, uint32_t height, uint32_t depth, GLenum format);

        virtual ~OpenGLTexture3D();
        
        virtual uint32_t GetWidth() const override {return m_Width;}
        virtual uint32_t GetHeight() const override {return m_Height;}
        virtual uint32_t GetDepth() const override {return m_Depth;}
        virtual unsigned int GetRendererID() const override {return m_RendererID;}

        virtual void SetData(void* data, uint32_t size) override;

        virtual void Bind(uint32_t slot = 0) const override;
        
        virtual void Resize(uint32_t width, uint32_t height, uint32_t depth) override;
    private:
        std::string m_Path;
        uint32_t m_Width, m_Height, m_Depth;
        uint32_t m_RendererID;
        GLenum m_InternalFormat, m_DataFormat;
    };
}