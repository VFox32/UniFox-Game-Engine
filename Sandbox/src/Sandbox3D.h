#pragma once

#include "UniFox.h"

#include "Particle.h"
#include <vector>

class Sandbox3D : public UniFox::Layer {
public:
    Sandbox3D();
    virtual ~Sandbox3D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(UniFox::Duration dt) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(UniFox::Event& e) override;
private:
    UniFox::PerspectiveCameraController m_CameraController;

    UniFox::Ref<UniFox::Shader> m_Shader;
    UniFox::Ref<UniFox::VertexArray> m_VAO;

    UniFox::Ref<UniFox::Shader> m_ParticleShader;
    UniFox::Ref<UniFox::VertexArray> m_ParticleVAO;

    UniFox::Ref<UniFox::Texture2D> m_Texture1;
    UniFox::Ref<UniFox::Texture2D> m_Texture2;

    Emitter* m_Emitter;
};