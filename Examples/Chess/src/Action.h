#pragma once
#include "UniFox.h"

class Board;
class Piece;
enum class PieceType;

class Action {
public:
    ~Action() = default;
    virtual void Do(Board& board) = 0;
    virtual void Undo(Board& board) = 0;
};

class MovePieceAction : public Action {
public:
    MovePieceAction(glm::ivec2 Source, glm::ivec2 Dest)
        : source(Source), dest(Dest) {}
    
    glm::ivec2 source;
    glm::ivec2 dest;
    virtual void Do(Board& board) override;
    virtual void Undo(Board& board) override;
};

class RemovePieceAction : public Action {
public:
    RemovePieceAction(glm::ivec2 Pos) 
        : pos(Pos) {}

    glm::ivec2 pos;
    Piece* piece;
    virtual void Do(Board& board) override;
    virtual void Undo(Board& board) override;
};

class CreatePieceAction : public Action {
public:
    CreatePieceAction(glm::ivec2 Pos, Piece* Piece) 
        : pos(Pos), piece(Piece) {}

    glm::ivec2 pos;
    Piece* piece;
    virtual void Do(Board& board) override;
    virtual void Undo(Board& board) override;
};

class Move {
public:
    Move(glm::ivec2 Src = glm::ivec2(0), glm::ivec2 Dest = glm::ivec2(0))
        : src(Src), dest(Dest) {}
    ~Move() = default;

    glm::ivec2 src;
    glm::ivec2 dest;
    std::vector<UniFox::Ref<Action>> actions;
    
    void Do(Board& board);
    void Undo(Board& board);

    static Move move(glm::ivec2 src, glm::ivec2 dest);
    static Move capture(glm::ivec2 src, glm::ivec2 dest);
    static Move moveOrCapture(Board board, glm::ivec2 src, glm::ivec2 dest);
};