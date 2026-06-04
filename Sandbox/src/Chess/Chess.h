#pragma once
#include "UniFox.h"
#include "Piece.h"
#include "Team.h"

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
    glm::vec2 GetWorldPos() {
        glm::vec3 pos = glm::vec3(UniFox::Input::GetMouseX() / 1280, 1.0 - UniFox::Input::GetMouseY() / 720, 0.0) * 2.0f - 1.0f;
        glm::mat4 mat = m_CameraController.GetCamera().GetViewProjectionMatrix();
        mat = glm::inverse(mat);
        glm::vec4 world = mat * glm::vec4(pos, 1.0);
        return {world.x, world.y};
    }
    int GetGridPos() {
        glm::vec2 pos = GetWorldPos();
        pos = {floor(pos.x), floor(pos.y)};
        return (int)(pos.x + pos.y*8.0f);
    }
private:
    UniFox::OrthographicCameraController m_CameraController;
    std::map<PieceType, UniFox::Ref<UniFox::Texture2D>> m_PieceTextures;
    Piece* m_Board;
    std::vector<Team> m_Teams;

    bool OnMouseButtonPressed(UniFox::MouseButtonPressedEvent& e);
    bool OnMouseButtonReleased(UniFox::MouseButtonReleasedEvent& e);
    int m_Selected = -1;
    int* moves = new int[64] {};
};