#pragma once
#include "UniFox.h"

#include "Piece.h"

class Board {
public:
    Board();

    void OnRender(glm::mat4 mat);
    void OnEvent(UniFox::Event& e);
private:
    bool AddPiece(PieceType type, int pos, int team) {
        uint64_t mask = 1ULL << pos;
        if((m_MaskWhite | m_MaskBlack) & mask) return false;
        if(team == 0) {
            m_MaskWhite |= mask;
        } else {
            m_MaskBlack |= mask;
        }
        m_Pieces[pos] = Piece(type, team);
        return true;
    }

    glm::vec2 GetWorldPos() {
        glm::vec3 pos = glm::vec3(UniFox::Input::GetMouseX() / 1280, 1.0 - UniFox::Input::GetMouseY() / 720, 0.0) * 2.0f - 1.0f;
        glm::vec4 world = mat * glm::vec4(pos, 1.0);
        return {world.x, world.y};
    }
    uint64_t GetGridPos() {
        glm::vec2 pos = GetWorldPos();
        pos = {floor(pos.x), floor(pos.y)};
        return (uint64_t)(pos.x + pos.y*8.0f);
    }
private:
    uint64_t m_MaskWhite = 0;
    uint64_t m_MaskBlack = 0;
    uint64_t m_Moves = 0;

    Piece* m_Pieces = new Piece[64] {};

    int m_Selected = -1;

    bool OnMouseButtonPressed(UniFox::MouseButtonPressedEvent& e);
    bool OnMouseButtonReleased(UniFox::MouseButtonReleasedEvent& e);

    glm::mat4 mat;
    std::map<PieceType, UniFox::Ref<UniFox::Texture2D>> m_PieceTextures;
};