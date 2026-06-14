#pragma once
#include "UniFox.h"

class Board;
class Piece;
enum class PieceType;

class Action {
public:
    Action(uint32_t Type)
        : type(Type) {}
    virtual void Do(Board& board) = 0;
    virtual void Undo(Board& board) = 0;

    static void Serialize(UniFox::StreamWriter* serializer, const Action* instance);
    static void Deserialize(UniFox::StreamReader* deserializer, UniFox::Ref<Action> instance);

    uint32_t type = 0;
};

class MovePieceAction : public Action {
public:
    MovePieceAction(glm::ivec2 Source, glm::ivec2 Dest)
        : Action(1), source(Source), dest(Dest) {}
    
    glm::ivec2 source;
    glm::ivec2 dest;
    virtual void Do(Board& board) override;
    virtual void Undo(Board& board) override;

    static void Serialize(UniFox::StreamWriter* serializer, const MovePieceAction* instance);
    static void Deserialize(UniFox::StreamReader* deserializer, MovePieceAction& instance);
};

class RemovePieceAction : public Action {
public:
    RemovePieceAction(glm::ivec2 Pos) 
        : Action(2), pos(Pos) {}

    glm::ivec2 pos;
    UniFox::Ref<Piece> piece;
    virtual void Do(Board& board) override;
    virtual void Undo(Board& board) override;

    static void Serialize(UniFox::StreamWriter* serializer, const RemovePieceAction& instance);
    static void Deserialize(UniFox::StreamReader* deserializer, RemovePieceAction& instance);
};

class CreatePieceAction : public Action {
public:
    CreatePieceAction(glm::ivec2 Pos, UniFox::Ref<Piece> Piece) 
        : Action(3), pos(Pos), piece(Piece) {}

    glm::ivec2 pos;
    UniFox::Ref<Piece> piece;
    virtual void Do(Board& board) override;
    virtual void Undo(Board& board) override;

    static void Serialize(UniFox::StreamWriter* serializer, const CreatePieceAction& instance);
    static void Deserialize(UniFox::StreamReader* deserializer, CreatePieceAction& instance);
};

class Move {
public:
    Move(glm::ivec2 Src = glm::ivec2(0), glm::ivec2 Dest = glm::ivec2(0))
        : src(Src), dest(Dest) {}

    glm::ivec2 src;
    glm::ivec2 dest;
    std::vector<UniFox::Ref<Action>> actions;
    
    void Do(Board& board);
    void Undo(Board& board);

    static Move move(glm::ivec2 src, glm::ivec2 dest);
    static Move capture(glm::ivec2 src, glm::ivec2 dest);
    static Move moveOrCapture(const Board& board, glm::ivec2 src, glm::ivec2 dest);

    static void Serialize(UniFox::StreamWriter* serializer, const Move& instance);
    static void Deserialize(UniFox::StreamReader* deserializer, Move& instance);
};