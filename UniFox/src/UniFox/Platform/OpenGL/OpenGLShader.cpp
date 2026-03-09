#include "ufpch.h"
#include "UniFox/Platform/OpenGL/OpenGLShader.h"

#include "UniFox/Core/Core.h"
#include "UniFox/Core/Log.h"

#include <fstream>
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

namespace UniFox {
    static GLenum ShaderTypeFromString(const std::string& type) {
        if(type == "vertex") return GL_VERTEX_SHADER;
        if(type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;
        UF_CORE_ASSERT(false, "Unknown shader type!");
        return 0;
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source) {
        std::unordered_map<GLenum, std::string> shaderSources;

        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken, 0);
        while(pos != std::string::npos) {
            size_t eol = source.find_first_of("\r\n", pos);
            UF_CORE_ASSERT(eol != std::string::npos, "Syntax error");
            size_t begin = pos + typeTokenLength + 1;
            std::string type = source.substr(begin, eol - begin);
            UF_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified!");

            size_t nextLinePos = source.find_first_of("\r\n", eol);
            pos = source.find(typeToken, nextLinePos);
            shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos,
                pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
        }

        return shaderSources;
    }

    OpenGLShader::OpenGLShader(const std::string& filepath) {
        std::string source = ReadFile(filepath);
        std::unordered_map<GLenum, std::string> shaderSources = PreProcess(source);
        Compile(shaderSources);

        std::size_t lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        std::size_t lastDot = filepath.rfind(".");
        std::size_t count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
        m_Name = filepath.substr(lastSlash, count);
    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) 
        : m_Name(name) {
        std::unordered_map<GLenum, std::string> shaderSources;

        shaderSources[GL_VERTEX_SHADER] = vertexSrc;
        shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;

        Compile(shaderSources);
    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(m_RendererID);
    }

    std::string OpenGLShader::ReadFile(const std::string& filepath) {
        std::string result;
        std::ifstream in(filepath, std::ios::in | std::ios::binary);

        if(in) {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
        } else {
            UF_CORE_ERROR("Could not open file '{0}'", filepath);
        }

        return result;
    }

    void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources) {
        UF_CORE_ASSERT(shaderSources.size() <= 4, "Too many Shaders!");
        GLuint program = glCreateProgram();
        std::array<GLuint, 4> glShaderIDs;
        int glShaderIDsIndex = 0;

        for(auto& kv : shaderSources) {
            GLenum type = kv.first;
            const std::string& source = kv.second;
            
            GLuint shader = glCreateShader(type);

            const GLchar* sourceCStr = source.c_str();
            glShaderSource(shader, 1, &sourceCStr, nullptr);

            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if(isCompiled == GL_FALSE) {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
                
                glDeleteShader(shader);

                UF_CORE_ERROR("{0}", infoLog.data());
                UF_CORE_ASSERT(false, "Shader compilation failure!")
                break;
            }

            glAttachShader(program, shader);
            glShaderIDs[glShaderIDsIndex++] = shader;
        }

        glLinkProgram(program);

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
            
            glDeleteProgram(program);
            for(auto id : glShaderIDs) {
                glDeleteShader(id);
            }

            UF_CORE_ERROR("{0}", infoLog.data());
            UF_CORE_ASSERT(false, "Shader link failure!");
            return;
        }

        for(auto id : glShaderIDs) {
            glDetachShader(program, id);
            glDeleteShader(id);
        }

        m_RendererID = program;
    }

    void OpenGLShader::Bind() const {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const {
        glUseProgram(0);
    }

    void OpenGLShader::SetInt(const std::string& name, const int& value) {
        UploadUniformInt(name, value);
    }

    void OpenGLShader::SetFloat(const std::string& name, const float& value) {
        UploadUniformFloat(name, value);
    }

    void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& vector) {
        UploadUniformFloat2(name, vector);
    }

    void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& vector) {
        UploadUniformFloat3(name, vector);
    }

    void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& vector) {
        UploadUniformFloat4(name, vector);
    }

    void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& matrix) {
        UploadUniformMat3(name, matrix);
    }

    void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& matrix) {
        UploadUniformMat4(name, matrix);
    }
    
    void OpenGLShader::UploadUniformInt (const std::string& name, const int& value) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::UploadUniformFloat (const std::string& name, const float& value) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1f(location, value);
    }
    void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& vector) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform2f(location, vector.x, vector.y);
    }
    void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& vector) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform3f(location, vector.x, vector.y, vector.z);
    }
    void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& vector) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
    }

    void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
    void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

}