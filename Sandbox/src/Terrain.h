#pragma once
#include "UniFox.h"

#include "Chunk.h"

class Terrain : public UniFox::Layer {
public:
    Terrain();
    virtual ~Terrain() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(UniFox::Duration dt) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(UniFox::Event& e) override;
private:
    UniFox::PerspectiveCameraController m_CameraController;

    UniFox::Ref<UniFox::Texture2D> m_Texture;
    UniFox::Ref<UniFox::Shader> m_Shader;

    std::vector<Chunk> m_Chunks;
};