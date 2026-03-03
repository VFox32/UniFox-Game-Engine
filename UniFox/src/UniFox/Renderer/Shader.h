#pragma once

#include <string>
#include <cstdint>

#include "glm/glm.hpp"

namespace UniFox {
    class Shader {
    public:
        virtual ~Shader() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        
        static Shader* Create(const std::string& vertexSrc, const std::string fragmentSrc);

        virtual void UploadUniformFloat (const std::string& name, const glm::vec1& vector) const = 0;
        virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& vector) const = 0;
        virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& vector) const = 0;
        virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& vector) const = 0;

        virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const = 0;
        virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const = 0;
    private:
        uint32_t m_RendererID;
    };
}
