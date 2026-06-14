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
    glm::vec2 GetWorldPos() const;

    bool OnMouseButtonPressed(UniFox::MouseButtonPressedEvent& e);
    bool OnMouseButtonReleased(UniFox::MouseButtonReleasedEvent& e);
    bool OnWindowResize(UniFox::WindowResizeEvent& e);
private:
    UniFox::OrthographicCameraController m_CameraController;

    Board m_Board;
    glm::ivec2 m_Selected = {-1, -1};
    bool m_Choice = false;
    std::vector<Move> m_Moves;

    std::vector<Move> m_History;
    std::vector<Move> m_UndoHistory;
    
    std::string m_Info = "";
    
    std::vector<UniFox::Ref<UniFox::Texture2D>> m_PieceTextures;
    glm::vec2 m_WindowSize = {1080, 720};
};