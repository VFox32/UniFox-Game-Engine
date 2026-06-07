#pragma once
#include "UniFox.h"

#include "Action.h"
class Board;

enum class PieceType {
    None = 0,
    King,
    Queen,
    Bishop,
    Knight,
    Rook,
    Pawn
};

class Piece {
public:
    ~Piece() = default;
    Piece(const PieceType Type, const uint32_t Team) : type(Type), team(Team) {}
    virtual std::vector<Move> GetMoves(const Board& board, const glm::ivec2 pos) const = 0;

    static Piece* Create(const PieceType type, const uint32_t team);
public:
    uint32_t team = 0;
    PieceType type = PieceType::None;
    uint32_t moves = 0;
};

class King : public Piece {
public:
    King(const PieceType Type, const uint32_t Team) : Piece(Type, Team) {}
    virtual std::vector<Move> GetMoves(const Board& board, const glm::ivec2 pos) const override;
};

class Queen : public Piece {
public:
    Queen(const PieceType Type, const uint32_t Team) : Piece(Type, Team) {}
    virtual std::vector<Move> GetMoves(const Board& board, const glm::ivec2 pos) const override;
};

class Bishop : public Piece {
public:
    Bishop(const PieceType Type, const uint32_t Team) : Piece(Type, Team) {}
    virtual std::vector<Move> GetMoves(const Board& board, const glm::ivec2 pos) const override;
};

class Knight : public Piece {
public:
    Knight(const PieceType Type, const uint32_t Team) : Piece(Type, Team) {}
    virtual std::vector<Move> GetMoves(const Board& board, const glm::ivec2 pos) const override;
};

class Rook : public Piece {
public:
    Rook(const PieceType Type, const uint32_t Team) : Piece(Type, Team) {}
    virtual std::vector<Move> GetMoves(const Board& board, const glm::ivec2 pos) const override;
};

class Pawn : public Piece {
public:
    Pawn(const PieceType Type, const uint32_t Team) : Piece(Type, Team) {}
    virtual std::vector<Move> GetMoves(const Board& board, const glm::ivec2 pos) const override;
};