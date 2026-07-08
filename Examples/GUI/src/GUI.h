#pragma once
#include "UniFox.h"

#include "Widget.h"
#include "Container.h"

class GUI : public UniFox::Layer {
public:
    GUI();
    virtual ~GUI() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(UniFox::Duration dt) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(UniFox::Event& e) override;

private:
    UniFox::OrthographicCameraController m_CameraController;

    UniFox::Ref<Container> m_Container;
    glm::vec2 m_Size = {3, 3};
};