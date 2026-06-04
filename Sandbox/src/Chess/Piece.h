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

class Piece {
public:
    ~Piece() = default;

    Piece() 
        : m_Type(PieceType::None), m_Team(-1) {
    }
    Piece(PieceType type, int team) 
        : m_Type(type), m_Team(team) {
    }

    PieceType GetType() const {return m_Type;}
    int GetTeam() const {return m_Team;}

    static uint64_t GetMoves(const Piece* state, const int position);
protected:
    PieceType m_Type;
    int m_Team;
};

class King : public Piece {
public:
    King(int team) {
        m_Type = PieceType::King;
        m_Team = team;
    }

    static uint64_t GetMoves(const Piece* state, const int position);
};
class Queen : public Piece {
public:
    Queen(int team) {
        m_Type = PieceType::Queen;
        m_Team = team;
    }
    
    static uint64_t GetMoves(const Piece* state, const int position);
};
class Bishop : public Piece {
public:
    Bishop(int team) {
        m_Type = PieceType::Bishop;
        m_Team = team;
    }

    static uint64_t GetMoves(const Piece* state, const int position);
};
class Knight : public Piece {
public:
    Knight(int team) {
        m_Type = PieceType::Knight;
        m_Team = team;
    }
    
    static uint64_t GetMoves(const Piece* state, const int position);
};
class Rook : public Piece {
public:
    Rook(int team) {
        m_Type = PieceType::Rook;
        m_Team = team;
    }
    
    static uint64_t GetMoves(const Piece* state, const int position);
};
class Pawn : public Piece {
public:
    Pawn(int team) {
        m_Type = PieceType::Pawn;
        m_Team = team;
    }
    
    static uint64_t GetMoves(const Piece* state, const int position);
};