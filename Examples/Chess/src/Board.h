#pragma once
#include "UniFox.h"

#include "Action.h"
#include "Team.h"
#include "PieceRegistry.h"
class Piece;

class Board {
public:
    Board();
public:
    void Reset(const uint32_t* position = nullptr, const uint32_t* teams = nullptr);
    void AddPiece(const uint32_t id, const glm::ivec2 pos, const uint32_t team);
    void SetPiece(const glm::ivec2 pos, const UniFox::Ref<Piece> piece);
    UniFox::Ref<Piece> CreatePiece(const std::string& name, const uint32_t team) const;

    bool InBounds(const glm::ivec2 pos) const;
    bool IsSquareSafe(const glm::ivec2 pos, const uint32_t team) const;
    bool IsCheck(const uint32_t team) const;
    bool IsMate(const uint32_t team);

    std::vector<glm::ivec2> FindPiece(const uint32_t type, const uint32_t team) const;
    std::vector<Move> GetMoves(const glm::ivec2 pos) const;
    std::vector<Move> GetValidMoves(const glm::ivec2 pos);

    void SetTurn(const uint32_t turn);
    void NextTurn();
    void PreviousTurn();

    uint32_t GetId(const std::string name) const;

    UniFox::Ref<Piece>* GetPieces() const;
    UniFox::Ref<Piece> GetPiece(const glm::ivec2 pos) const;
    uint32_t GetTeam(const glm::ivec2 pos) const;
    uint32_t GetId(const glm::ivec2 pos) const;

    glm::ivec2 GetSize() const;
    uint32_t GetTurn() const;
    Team GetTeam(const uint32_t i) const;

    uint32_t GetIndex(const glm::ivec2 pos) const;
    glm::ivec2 GetCoord(const uint32_t pos) const;
    glm::ivec2 GetGridPos(const glm::vec2 pos) const;
private:
    UniFox::Ref<Piece>* m_Pieces;
    uint32_t m_Turn;
    glm::ivec2 m_Size;

    std::vector<Team> m_Teams;

    PieceRegistry m_Registry;
};