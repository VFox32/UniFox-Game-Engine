#pragma once
#include "UniFox.h"

#include "Action.h"
#include "Team.h"
#include "PieceRegistry.h"
class Piece;

class Board {
public:
    Board();
    ~Board();
public:
    void AddPiece(uint32_t id, glm::ivec2 pos, int team);

    uint32_t GetTeam(const glm::ivec2 pos) const;
    uint32_t GetId(const glm::ivec2 pos) const;
    uint32_t GetId(const std::string name) const;
    Piece* GetPiece(const glm::ivec2 pos) const;
    Piece* GetPiece(const uint32_t pos) const;
    Piece** GetPieces() const {return m_Pieces;}

    void SetPiece(const glm::ivec2 pos, Piece* piece);
    void Reset(uint32_t* position = nullptr, uint32_t* teams = nullptr);

    static uint32_t GetIndex(const glm::ivec2 pos) {return pos.x + pos.y*8;}
    static glm::ivec2 GetCoord(const uint32_t pos) {return {pos % 8, pos / 8};}
    static glm::ivec2 GetGridPos(const glm::vec2 pos);
    static bool InBounds(const glm::ivec2 pos);

    bool IsSquareSafe(const glm::ivec2 pos, const uint32_t team) const;
    std::vector<glm::ivec2> FindPiece(uint32_t type, uint32_t team) const;
    std::vector<Move> GetMoves(glm::ivec2 pos) const;
    std::vector<Move> GetValidMoves(glm::ivec2 pos);

    bool IsCheck(const uint32_t team) const;
    bool IsMate(const uint32_t team);

    uint32_t GetTurn() const;
    void SetTurn(uint32_t turn);
    void NextTurn();
    void PreviousTurn();
private:
    Piece** m_Pieces;
    uint32_t m_Turn;

    PieceRegistry m_Registry;
};