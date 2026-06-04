#pragma once
#include "UniFox.h"

#include "Board.h"

class Chess : public UniFox::Layer {
public:
    Chess();
    virtual ~Chess() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(UniFox::Duration dt) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(UniFox::Event& e) override;
private:
    UniFox::OrthographicCameraController m_CameraController;

    Board m_Board;
};