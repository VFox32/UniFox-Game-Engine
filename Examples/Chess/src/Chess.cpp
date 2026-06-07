#include "Chess.h"

Chess::Chess() 
    : m_CameraController(16.0 / 9.0, false, 5.0) {
}

void Chess::OnAttach() {
}

void Chess::OnDetach() {
}

void Chess::OnUpdate(UniFox::Duration dt) {
    m_CameraController.OnUpdate(dt);

    UniFox::RenderCommand::SetClearColor({0.05, 0.05, 0.05, 1.0});
    UniFox::RenderCommand::Clear();

    UniFox::Renderer2D::BeginScene(m_CameraController.GetCamera());
    m_Board.OnRender(m_CameraController.GetCamera().GetViewProjectionMatrix());
    UniFox::Renderer2D::EndScene();
}

void Chess::OnImGuiRender() {
    m_Board.OnImguiRender();
}

void Chess::OnEvent(UniFox::Event& e) {
    m_Board.OnEvent(e);
}