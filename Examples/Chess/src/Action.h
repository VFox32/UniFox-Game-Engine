#pragma once
#include "UniFox.h"

class Board;
class Piece;
enum class PieceType;

enum class ActionType {
    None = 0,
    Move,
    Remove,
    Create
};

class Action {
public:
    Action(ActionType Type)
        : type(Type) {}
    ~Action() = default;
    virtual void Do(Board& board) = 0;
    virtual void Undo(Board& board) = 0;

    static void Serialize(UniFox::StreamWriter* serializer, const Action& instance);
    static void Deserialize(UniFox::StreamReader* deserializer, Action& instance);

    ActionType type;
};

class MovePieceAction : public Action {
public:
    MovePieceAction(glm::ivec2 Source, glm::ivec2 Dest)
        : Action(ActionType::Move), source(Source), dest(Dest) {}
    
    glm::ivec2 source;
    glm::ivec2 dest;
    virtual void Do(Board& board) override;
    virtual void Undo(Board& board) override;

    static void Serialize(UniFox::StreamWriter* serializer, const MovePieceAction& instance);
    static void Deserialize(UniFox::StreamReader* deserializer, MovePieceAction& instance);
};

class RemovePieceAction : public Action {
public:
    RemovePieceAction(glm::ivec2 Pos) 
        : Action(ActionType::Remove), pos(Pos) {}

    glm::ivec2 pos;
    Piece* piece;
    virtual void Do(Board& board) override;
    virtual void Undo(Board& board) override;

    static void Serialize(UniFox::StreamWriter* serializer, const RemovePieceAction& instance);
    static void Deserialize(UniFox::StreamReader* deserializer, RemovePieceAction& instance);
};

class CreatePieceAction : public Action {
public:
    CreatePieceAction(glm::ivec2 Pos, Piece* Piece) 
        : Action(ActionType::Create), pos(Pos), piece(Piece) {}

    glm::ivec2 pos;
    Piece* piece;
    virtual void Do(Board& board) override;
    virtual void Undo(Board& board) override;

    static void Serialize(UniFox::StreamWriter* serializer, const CreatePieceAction& instance);
    static void Deserialize(UniFox::StreamReader* deserializer, CreatePieceAction& instance);
};

class Move {
public:
    Move(glm::ivec2 Src = glm::ivec2(0), glm::ivec2 Dest = glm::ivec2(0))
        : src(Src), dest(Dest) {}
    ~Move() = default;

    glm::ivec2 src;
    glm::ivec2 dest;
    std::vector<Action*> actions;
    
    void Do(Board& board);
    void Undo(Board& board);

    static Move move(glm::ivec2 src, glm::ivec2 dest);
    static Move capture(glm::ivec2 src, glm::ivec2 dest);
    static Move moveOrCapture(Board board, glm::ivec2 src, glm::ivec2 dest);

    static void Serialize(UniFox::StreamWriter* serializer, const Move& instance);
    static void Deserialize(UniFox::StreamReader* deserializer, Move& instance);
};