#pragma once

#include "UniFox/Renderer/Shader.h"

namespace UniFox {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& vertexSrc, const std::string fragmentSrc);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void UploadUniformFloat (const std::string& name, const glm::vec1& vector) const override;
        virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& vector) const override;
        virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& vector) const override;
        virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& vector) const override;

        virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const override;
        virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const override;
    private:
        uint32_t m_RendererID;
    };
}