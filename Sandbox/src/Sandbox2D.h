#pragma once

#include "UniFox.h"

class Sandbox2D : public UniFox::Layer {
public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(UniFox::Duration dt) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(UniFox::Event& e) override;
private:
    UniFox::OrthographicCameraController m_CameraController;

    glm::vec4 m_Color;
    UniFox::Ref<UniFox::Texture2D> m_Texture54, m_TextureChecker;
};