#pragma once
#include "UniFox.h"

enum class PieceType {
    None = 0,
    King,
    Queen,
    Bishop,
    Knight,
    Rook,
    Pawn
};

class Board {
public:
    Board();

    void OnRender(glm::mat4 mat);
    void OnEvent(UniFox::Event& e);
public:
    bool AddPiece(PieceType type, int pos, int team) {
        uint64_t mask = 1ULL << pos;
        if((m_MaskWhite | m_MaskBlack) & mask) return false;
        if(team == 0) {
            m_MaskWhite |= mask;
        } else {
            m_MaskBlack |= mask;
        }
        m_Pieces[pos] = type;
        return true;
    }

    uint64_t GetMoves(const int position);
    uint64_t GetAllMoves(const int team);

    uint64_t GetWhiteMask() const {return m_MaskWhite;}
    uint64_t GetBlacMask() const {return m_MaskBlack;}
    uint64_t GetPieceMask() const {return m_MaskWhite | m_MaskBlack;}
    uint64_t GetTeam(const uint64_t pos) const {
        if(m_MaskWhite & (1ULL << pos)) return 1;
        else if(m_MaskBlack & (1ULL << pos)) return 2;
        return 0;
    }
    PieceType GetType(const uint64_t pos) const {return m_Pieces[pos];}
    PieceType* GetPieces() const {return m_Pieces;}

private:
    uint64_t GetKingMoves  (const int position);
    uint64_t GetQueenMoves (const int position);
    uint64_t GetBishopMoves(const int position);
    uint64_t GetKnightMoves(const int position);
    uint64_t GetRookMoves  (const int position);
    uint64_t GetPawnMoves  (const int position);

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

    PieceType* m_Pieces = new PieceType[64] {};

    int m_Selected = -1;
    uint64_t m_Turn = 0;

    bool OnMouseButtonPressed(UniFox::MouseButtonPressedEvent& e);
    bool OnMouseButtonReleased(UniFox::MouseButtonReleasedEvent& e);

    glm::mat4 mat;
    std::map<PieceType, UniFox::Ref<UniFox::Texture2D>> m_PieceTextures;
};