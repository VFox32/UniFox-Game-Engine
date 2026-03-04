#include "ufpch.h"
#include "Shader.h"

#include "UniFox/Core/Core.h"

#include "Renderer.h"
#include "UniFox/Platform/OpenGL/OpenGLShader.h"

namespace UniFox {
    Ref<Shader> Shader::Create(const std::string& filepath) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None : UF_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
            case RendererAPI::API::OpenGL : return MakeRef<OpenGLShader>(filepath);
        }
        UF_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None : UF_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
            case RendererAPI::API::OpenGL : return MakeRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }
        UF_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    
    void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader) {
        UF_CORE_ASSERT(!Exists(name), "Shader already exists!");
        m_Shaders[name] = shader;
    }
    
    void ShaderLibrary::Add(const Ref<Shader>& shader) {
        std::string name = shader->GetName();
        Add(name, shader);
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& filepath) {
        Ref<Shader> shader = Shader::Create(filepath);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath) {
        Ref<Shader> shader = Shader::Create(filepath);
        Add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string& name) {
        UF_CORE_ASSERT(Exists(name), "Shader does not exist!");
        return m_Shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string& name) {
        return m_Shaders.find(name) != m_Shaders.end();
    }
}