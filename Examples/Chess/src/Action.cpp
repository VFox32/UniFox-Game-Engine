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
    for(auto action : actions) {
        action->Do(board);
    }
}
void Move::Undo(Board& board) {
    for (auto action = actions.rbegin(); action != actions.rend(); ++action) {
        action->get()->Undo(board);
    }
}

Move Move::move(glm::ivec2 src, glm::ivec2 dest) {
    Move move = Move(src, dest);
    move.actions.push_back(UniFox::MakeRef<MovePieceAction>(src, dest));
    return move;
}
Move Move::capture(glm::ivec2 src, glm::ivec2 dest) {
    Move move = Move(src, dest);
    move.actions.push_back(UniFox::MakeRef<RemovePieceAction>(dest));
    move.actions.push_back(UniFox::MakeRef<MovePieceAction>(src, dest));
    return move;
}
Move Move::moveOrCapture(Board board, glm::ivec2 src, glm::ivec2 dest) {
    if(board.GetType(dest) != PieceType::None) {
        return capture(src, dest);
    } else {
        return move(src, dest);
    }
}