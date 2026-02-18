#pragma once

#include "UniFox/Renderer/Shader.h"

namespace UniFox {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& vertexSrc, const std::string fragmentSrc);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void Unbind() const override;
    private:
        uint32_t m_RendererID;
    };
}