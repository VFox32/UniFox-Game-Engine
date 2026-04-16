#include "ufpch.h"
#include "UniFox/Platform/OpenGL/OpenGLTexture.h"

#include "stb_image.h"

namespace UniFox {
    ////////////////////
    //// Texture 2D ////
    ////////////////////
    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, GLenum format) 
        : m_Width(width), m_Height(height) {
        UF_PROFILE_FUNCTION();
        
        m_InternalFormat = format;
        unsigned int type = 0;
        switch (m_InternalFormat) {
        case GL_RGBA:
            m_DataFormat = GL_RGBA;
            type = GL_UNSIGNED_BYTE;
            break;
        case GL_RGB:
            m_DataFormat = GL_RGB;
            type = GL_UNSIGNED_BYTE;
            break;
        case GL_RGBA16F:
            m_DataFormat = GL_RGBA;
            type = GL_FLOAT;
            break;
        case GL_RGB16F:
            m_DataFormat = GL_RGB;
            type = GL_FLOAT;
            break;
        }

        //glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        //glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
        glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, width, height, 0, m_DataFormat, type, nullptr);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture2D::OpenGLTexture2D(const std::string& path) 
        : m_Path(path) {
        UF_PROFILE_FUNCTION();
        
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = nullptr;
        {
            UF_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string&)");
            data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        }
        UF_CORE_ASSERT(data, "Failed to load Image!");
        m_Width = width;
        m_Height = height;

        GLenum internalFormat = 0, dataFormat = 0;
        if(channels == 4) {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        } else if(channels == 3) {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        m_InternalFormat = internalFormat;
        m_DataFormat = dataFormat;

        UF_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D() {
        UF_PROFILE_FUNCTION();
        
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const {
        UF_PROFILE_FUNCTION();
        
        //glBindTextureUnit(slot, m_RendererID);
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }

    void OpenGLTexture2D::Resize(uint32_t width, uint32_t height) {
        UF_PROFILE_FUNCTION();
        
        unsigned int type = 0;
        switch (m_InternalFormat) {
        case GL_RGBA:
            type = GL_UNSIGNED_BYTE;
            break;
        case GL_RGB:
            type = GL_UNSIGNED_BYTE;
            break;
        case GL_RGBA16F:
            type = GL_FLOAT;
            break;
        case GL_RGB16F:
            type = GL_FLOAT;
            break;
        }

        glDeleteTextures(1, &m_RendererID);
        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
        glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, width, height, 0, m_DataFormat, type, nullptr);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    void OpenGLTexture2D::SetData(void* data, uint32_t size) {
        UF_PROFILE_FUNCTION();
        
        uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
        UF_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }

    ////////////////////
    //// Texture 3D ////
    ////////////////////
    OpenGLTexture3D::OpenGLTexture3D(uint32_t width, uint32_t height, uint32_t depth, GLenum format) 
        : m_Width(width), m_Height(height), m_Depth(depth) {
        UF_PROFILE_FUNCTION();
        
        m_InternalFormat = format;
        unsigned int type = 0;
        switch (m_InternalFormat) {
        case GL_RGBA:
            m_DataFormat = GL_RGBA;
            type = GL_UNSIGNED_BYTE;
            break;
        case GL_RGB:
            m_DataFormat = GL_RGB;
            type = GL_UNSIGNED_BYTE;
            break;
        case GL_RGBA16F:
            m_DataFormat = GL_RGBA;
            type = GL_FLOAT;
            break;
        case GL_RGB16F:
            m_DataFormat = GL_RGB;
            type = GL_FLOAT;
            break;
        }

        //glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        //glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_3D, m_RendererID);
        glTexImage3D(GL_TEXTURE_3D, 0, m_InternalFormat, width, height, depth, 0, m_DataFormat, type, nullptr);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture3D::OpenGLTexture3D(const std::string& path) 
        : m_Path(path) {
        UF_PROFILE_FUNCTION();
        
        int width, height, depth, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = nullptr;
        /*{
            UF_PROFILE_SCOPE("stbi_load - OpenGLTexture3D::OpenGLTexture3D(const std::string&)");
            data = stbi_load(path.c_str(), &width, &height, &depth, &channels, 0);
        }*/
        UF_CORE_ASSERT(data, "Failed to load Image!");
        m_Width = width;
        m_Height = height;
        m_Depth = depth;

        GLenum internalFormat = 0, dataFormat = 0;
        if(channels == 4) {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        } else if(channels == 3) {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        m_InternalFormat = internalFormat;
        m_DataFormat = dataFormat;

        UF_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

        glCreateTextures(GL_TEXTURE_3D, 1, &m_RendererID);
        glTextureStorage3D(m_RendererID, 1, internalFormat, m_Width, m_Height, m_Depth);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage3D(m_RendererID, 0, 0, 0, 0, m_Width, m_Height, m_Depth, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture3D::~OpenGLTexture3D() {
        UF_PROFILE_FUNCTION();
        
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture3D::Bind(uint32_t slot) const {
        UF_PROFILE_FUNCTION();
        
        //glBindTextureUnit(slot, m_RendererID);
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_3D, m_RendererID);
    }

    void OpenGLTexture3D::Resize(uint32_t width, uint32_t height, uint32_t depth) {
        UF_PROFILE_FUNCTION();
        
        unsigned int type = 0;
        switch (m_InternalFormat) {
        case GL_RGBA:
            type = GL_UNSIGNED_BYTE;
            break;
        case GL_RGB:
            type = GL_UNSIGNED_BYTE;
            break;
        case GL_RGBA16F:
            type = GL_FLOAT;
            break;
        case GL_RGB16F:
            type = GL_FLOAT;
            break;
        }

        glDeleteTextures(1, &m_RendererID);
        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_3D, m_RendererID);
        glTexImage3D(GL_TEXTURE_3D, 0, m_InternalFormat, width, height, depth, 0, m_DataFormat, type, nullptr);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    void OpenGLTexture3D::SetData(void* data, uint32_t size) {
        UF_PROFILE_FUNCTION();
        
        uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
        UF_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
        glTextureSubImage3D(m_RendererID, 0, 0, 0, 0, m_Width, m_Height, m_Depth, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }
}