#include "Action.h"

#include "Board.h"
#include "Piece.h"

void MovePieceAction::Do(Board& board) {
    board.GetPiece(source)->moves += 1;
    board.SetPiece(dest, board.GetPiece(source));
    board.SetPiece(source, nullptr);
}
void MovePieceAction::Undo(Board& board) {
    board.GetPiece(dest)->moves -= 1;
    board.SetPiece(source, board.GetPiece(dest));
    board.SetPiece(dest, nullptr);
}

void RemovePieceAction::Do(Board& board) {
    piece = board.GetPiece(pos);
    board.SetPiece(pos, nullptr);
}
void RemovePieceAction::Undo(Board& board) {
    board.SetPiece(pos, piece);
}

void CreatePieceAction::Do(Board& board) {
    board.SetPiece(pos, piece);
}
void CreatePieceAction::Undo(Board& board) {
    board.SetPiece(pos, nullptr);
}

void Move::Do(Board& board) {
    for(int i = 0; i < actions.size(); i++) {
        actions[i]->Do(board);
    }
}
void Move::Undo(Board& board) {
    for(int i = actions.size() - 1; i >= 0; i--) {
        actions[i]->Undo(board);
    }
}

Move Move::move(glm::ivec2 src, glm::ivec2 dest) {
    Move move = Move(src, dest);
    move.actions.push_back(new MovePieceAction(src, dest));
    return move;
}
Move Move::capture(glm::ivec2 src, glm::ivec2 dest) {
    Move move = Move(src, dest);
    move.actions.push_back(new RemovePieceAction(dest));
    move.actions.push_back(new MovePieceAction(src, dest));
    return move;
}
Move Move::moveOrCapture(Board board, glm::ivec2 src, glm::ivec2 dest) {
    if(board.GetType(dest) != PieceType::None) {
        return capture(src, dest);
    } else {
        return move(src, dest);
    }
}



void Action::Serialize(UniFox::StreamWriter* serializer, const Action& instance) {
    serializer->WriteRaw(instance.type);

    switch (instance.type)
    {
    case ActionType::None:
        break;
    case ActionType::Move:
        serializer->WriteObject((MovePieceAction&)instance);
        break;
    case ActionType::Remove:
        serializer->WriteObject((RemovePieceAction&)instance);
        break;
    case ActionType::Create:
        serializer->WriteObject((CreatePieceAction&)instance);
        break;
    }
}
void Action::Deserialize(UniFox::StreamReader* deserializer, Action& instance) {
    deserializer->ReadRaw(instance.type);

    switch (instance.type)
    {
    case ActionType::None:
        break;
    case ActionType::Move:
        deserializer->ReadObject((MovePieceAction&)instance);
        break;
    case ActionType::Remove:
        deserializer->ReadObject((RemovePieceAction&)instance);
        break;
    case ActionType::Create:
        deserializer->ReadObject((CreatePieceAction&)instance);
        break;
    }
}

void MovePieceAction::Serialize(UniFox::StreamWriter* serializer, const MovePieceAction& instance) {
    serializer->WriteRaw(instance.source);
    serializer->WriteRaw(instance.dest);
}
void MovePieceAction::Deserialize(UniFox::StreamReader* deserializer, MovePieceAction& instance) {
    instance.type = ActionType::Move;
    deserializer->ReadRaw(instance.source);
    deserializer->ReadRaw(instance.dest);
}

void RemovePieceAction::Serialize(UniFox::StreamWriter* serializer, const RemovePieceAction& instance) {
    serializer->WriteRaw(instance.pos);
    serializer->WriteRaw(instance.piece);
}
void RemovePieceAction::Deserialize(UniFox::StreamReader* deserializer, RemovePieceAction& instance) {
    instance.type = ActionType::Move;
    deserializer->ReadRaw(instance.pos);
    deserializer->ReadRaw(instance.piece);
}

void CreatePieceAction::Serialize(UniFox::StreamWriter* serializer, const CreatePieceAction& instance) {
    serializer->WriteRaw(instance.pos);
    serializer->WriteRaw(instance.piece);
}
void CreatePieceAction::Deserialize(UniFox::StreamReader* deserializer, CreatePieceAction& instance) {
    instance.type = ActionType::Move;
    deserializer->ReadRaw(instance.pos);
    deserializer->ReadRaw(instance.piece);
}

void Move::Serialize(UniFox::StreamWriter* serializer, const Move& instance) {
    serializer->WriteRaw(instance.src);
    serializer->WriteRaw(instance.dest);

    uint32_t size = instance.actions.size();
    serializer->WriteRaw(size);
    for(uint32_t i = 0; i < size; i++) {
        Action::Serialize(serializer, *instance.actions[i]);
    }
}
void Move::Deserialize(UniFox::StreamReader* deserializer, Move& instance) {
    deserializer->ReadRaw(instance.src);
    deserializer->ReadRaw(instance.dest);
    
    uint32_t size = 0;
    deserializer->ReadRaw(size);
    instance.actions.reserve(size);
    for(uint32_t i = 0; i < size; i++) {
        Action::Deserialize(deserializer, *instance.actions[i]);
    }
}