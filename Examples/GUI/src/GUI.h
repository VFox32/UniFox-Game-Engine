#pragma once
#include "UniFox.h"

//#include "Widget.h"
//#include "Container.h"
#include "UIManager.h"

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
    bool OnWindowResize(UniFox::WindowResizeEvent& e);
private:
    //UniFox::OrthographicCameraController m_CameraController;
    UniFox::OrthographicCamera m_Camera;

    UniFox::Ref<UIManager> m_UIManager;
    glm::vec2 m_Size = {300, 300};
};