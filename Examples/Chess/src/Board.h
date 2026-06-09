#pragma once
#include "UniFox.h"

#include "Action.h"
#include "Team.h"
class Piece;
enum class PieceType;

class Board {
public:
    Board();
public:
    void AddPiece(PieceType type, glm::ivec2 pos, int team);

    uint64_t GetTeam(const glm::ivec2 pos) const;
    PieceType GetType(const glm::ivec2 pos) const;
    Piece* GetPiece(const glm::ivec2 pos) const;
    Piece* GetPiece(const uint32_t pos) const;
    Piece** GetPieces() const {return m_Pieces;}

    void SetPiece(const glm::ivec2 pos, Piece* piece);

    static uint32_t GetIndex(const glm::ivec2 pos) {return pos.x + pos.y*8;}
    static glm::ivec2 GetCoord(const uint32_t pos) {return {pos % 8, pos / 8};}
    static glm::ivec2 GetGridPos(const glm::vec2 pos);

    bool IsSquareSafe(const glm::ivec2 pos, const uint32_t team) const;
    std::vector<glm::ivec2> FindPiece(PieceType type, uint32_t team) const;
    std::vector<Move> GetMoves(glm::ivec2 pos) const;
    std::vector<Move> GetValidMoves(glm::ivec2 pos);

    bool IsCheck(const uint32_t team) const;
    bool IsMate(const uint32_t team);

    uint32_t GetTurn() const;
    void SetTurn(uint32_t turn);
    void NextTurn();
    void PreviousTurn();
private:
    Piece** m_Pieces = new Piece*[64] {};
    uint32_t m_Turn;
};