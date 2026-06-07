#pragma once
#include "UniFox.h"

#include "Action.h"
#include "Team.h"
class Piece;
enum class PieceType;

class Board {
public:
    Board();

    void OnRender(glm::mat4 mat);
    void OnEvent(UniFox::Event& e);
    void OnImguiRender();
public:
    void AddPiece(PieceType type, glm::ivec2 pos, int team);

    uint64_t GetTeam(const glm::ivec2 pos) const;
    PieceType GetType(const glm::ivec2 pos) const;
    Piece** GetPieces() const {return m_Pieces;}

    Piece* GetPiece(const glm::ivec2 pos) const;
    void SetPiece(const glm::ivec2 pos, Piece* piece);
    static uint32_t GetIndex(const glm::ivec2 pos) {return pos.x + pos.y*8;}
    static glm::ivec2 GetCoord(const uint32_t pos) {return {pos % 8, pos / 8};}

    bool IsSquareSafe(const glm::ivec2 pos, const uint32_t team) const;
    std::vector<glm::ivec2> FindPiece(PieceType type, uint32_t team) const;
public:
    glm::vec2 GetWorldPos(); 
    glm::ivec2 GetGridPos();
private:
    Piece** m_Pieces = new Piece*[64] {};
    std::vector<Move> m_Moves;
    std::vector<Team> m_Teams;

    std::vector<Move> m_History;
    std::vector<Move> m_UndoHistory;

    int m_Selected = -1;
    uint64_t m_Turn = 0;
    std::string m_Info = "";

    bool OnMouseButtonPressed(UniFox::MouseButtonPressedEvent& e);
    bool OnMouseButtonReleased(UniFox::MouseButtonReleasedEvent& e);

    glm::mat4 mat;
    std::map<PieceType, UniFox::Ref<UniFox::Texture2D>> m_PieceTextures;
};