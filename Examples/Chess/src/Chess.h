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
private:
    UniFox::OrthographicCameraController m_CameraController;

    Board m_Board;
    int m_Selected = -1;
    std::vector<Move> m_Moves;
    std::vector<Team> m_Teams;

    std::vector<Move> m_History;
    std::vector<Move> m_UndoHistory;
    
    uint64_t m_Turn = 0;
    std::string m_Info = "";
    
    std::map<PieceType, UniFox::Ref<UniFox::Texture2D>> m_PieceTextures;
};