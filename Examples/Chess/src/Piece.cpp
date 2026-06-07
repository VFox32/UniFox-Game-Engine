#include "Piece.h"

#include "Action.h"
#include "Board.h"


Piece* Piece::Create(const PieceType type, const uint32_t team) {
    switch (type){
    case PieceType::King:
        return new King(type, team);
    case PieceType::Queen:
        return new Queen(type, team);
    case PieceType::Bishop:
        return new Bishop(type, team);
    case PieceType::Knight:
        return new Knight(type, team);
    case PieceType::Rook:
        return new Rook(type, team);
    case PieceType::Pawn:
        return new Pawn(type, team);
    default:
        return nullptr;
    }
}

std::vector<Move> King::GetMoves(const Board& board, const glm::ivec2 pos) const {
    std::vector<Move> moves;
    const uint32_t team = board.GetPiece(pos)->team;
    glm::ivec2 dest;

    for(int x = -1; x <= 1; x++)
    for(int y = -1; y <= 1; y++) {
        if(pos.x+x < 0 || pos.x+x > 7) continue;
        if(pos.y+y < 0 || pos.y+y > 7) continue;
        if(x == 0 && y == 0) continue;

        dest = {pos.x+x, pos.y+y};
        if(board.GetTeam(dest) != team) moves.push_back(Move::moveOrCapture(board, pos, dest));
    }

    //casteling
    dest = {0, pos.y};
    if(board.GetPiece(pos)->moves == 0 &&
        board.GetType(dest) == PieceType::Rook &&
        board.GetPiece(dest)->moves == 0 &&
        board.GetPiece({1, pos.y}) == nullptr &&
        board.GetPiece({2, pos.y}) == nullptr &&
        board.GetPiece({3, pos.y}) == nullptr) {
            Move move = Move(pos, {2, pos.y});
            move.actions.push_back(UniFox::MakeRef<MovePieceAction>(pos, glm::ivec2(2, pos.y)));
            move.actions.push_back(UniFox::MakeRef<MovePieceAction>(dest, glm::ivec2(3, pos.y)));
            moves.push_back(move);
    }
    dest = {7, pos.y};
    if(board.GetPiece(pos)->moves == 0 &&
        board.GetType(dest) == PieceType::Rook &&
        board.GetPiece(dest)->moves == 0 &&
        board.GetPiece({6, pos.y}) == nullptr &&
        board.GetPiece({5, pos.y}) == nullptr) {
            Move move = Move(pos, {6, pos.y});
            move.actions.push_back(UniFox::MakeRef<MovePieceAction>(pos, glm::ivec2(6, pos.y)));
            move.actions.push_back(UniFox::MakeRef<MovePieceAction>(dest, glm::ivec2(5, pos.y)));
            moves.push_back(move);
    }

    return moves;
}

std::vector<Move> Queen::GetMoves(const Board& board, const glm::ivec2 pos) const {
    std::vector<Move> moves;
    const uint32_t team = board.GetPiece(pos)->team;
    glm::ivec2 dest;

    for(int x = pos.x+1, y = pos.y+1; x < 8 && y < 8; x++, y++) {
        dest = {x, y};
        if(board.GetTeam(dest) == team) break;
        moves.push_back(Move::moveOrCapture(board, pos, dest));
        if(board.GetType(dest) != PieceType::None) break;
    }
    for(int x = pos.x-1, y = pos.y+1; x >= 0 && y < 8; x--, y++) {
        dest = {x, y};
        if(board.GetTeam(dest) == team) break;
        moves.push_back(Move::moveOrCapture(board, pos, dest));
        if(board.GetType(dest) != PieceType::None) break;
    }
    for(int x = pos.x+1, y = pos.y-1; x < 8 && y >= 0; x++, y--) {
        dest = {x, y};
        if(board.GetTeam(dest) == team) break;
        moves.push_back(Move::moveOrCapture(board, pos, dest));
        if(board.GetType(dest) != PieceType::None) break;
    }
    for(int x = pos.x-1, y = pos.y-1; x >= 0 && y >= 0; x--, y--) {
        dest = {x, y};
        if(board.GetTeam(dest) == team) break;
        moves.push_back(Move::moveOrCapture(board, pos, dest));
        if(board.GetType(dest) != PieceType::None) break;
    }

    for(int x = pos.x+1; x < 8; x++) {
        dest = {x, pos.y};
        if(board.GetTeam(dest) == team) break;
        moves.push_back(Move::moveOrCapture(board, pos, dest));
        if(board.GetType(dest) != PieceType::None) break;
    }
    for(int x = pos.x-1; x >= 0; x--) {
        dest = {x, pos.y};
        if(board.GetTeam(dest) == team) break;
        moves.push_back(Move::moveOrCapture(board, pos, dest));
        if(board.GetType(dest) != PieceType::None) break;
    }
    for(int y = pos.y+1; y < 8; y++) {
        dest = {pos.x, y};
        if(board.GetTeam(dest) == team) break;
        moves.push_back(Move::moveOrCapture(board, pos, dest));
        if(board.GetType(dest) != PieceType::None) break;
    }
    for(int y = pos.y-1; y >= 0; y--) {
        dest = {pos.x, y};
        if(board.GetTeam(dest) == team) break;
        moves.push_back(Move::moveOrCapture(board, pos, dest));
        if(board.GetType(dest) != PieceType::None) break;
    }

    return moves;
}

std::vector<Move> Bishop::GetMoves(const Board& board, const glm::ivec2 pos) const {
    std::vector<Move> moves;
    const uint32_t team = board.GetPiece(pos)->team;
    glm::ivec2 dest;

    for(int x = pos.x+1, y = pos.y+1; x < 8 && y < 8; x++, y++) {
        dest = {x, y};
        if(board.GetTeam(dest) == team) break;
        moves.push_back(Move::moveOrCapture(board, pos, dest));
        if(board.GetType(dest) != PieceType::None) break;
    }
    for(int x = pos.x-1, y = pos.y+1; x >= 0 && y < 8; x--, y++) {
        dest = {x, y};
        if(board.GetTeam(dest) == team) break;
        moves.push_back(Move::moveOrCapture(board, pos, dest));
        if(board.GetType(dest) != PieceType::None) break;
    }
    for(int x = pos.x+1, y = pos.y-1; x < 8 && y >= 0; x++, y--) {
        dest = {x, y};
        if(board.GetTeam(dest) == team) break;
        moves.push_back(Move::moveOrCapture(board, pos, dest));
        if(board.GetType(dest) != PieceType::None) break;
    }
    for(int x = pos.x-1, y = pos.y-1; x >= 0 && y >= 0; x--, y--) {
        dest = {x, y};
        if(board.GetTeam(dest) == team) break;
        moves.push_back(Move::moveOrCapture(board, pos, dest));
        if(board.GetType(dest) != PieceType::None) break;
    }

    return moves;
}

std::vector<Move> Knight::GetMoves(const Board& board, const glm::ivec2 pos) const {
    std::vector<Move> moves;
    const uint32_t team = board.GetPiece(pos)->team;
    glm::ivec2 dest;

    // top right
    if(pos.x <= 6 && pos.y <= 5) {
        dest = {pos.x+1, pos.y+2};
        if(board.GetTeam(dest) != team) moves.push_back(Move::moveOrCapture(board, pos, dest));
    }
    if(pos.x <= 5 && pos.y <= 6) {
        dest = {pos.x+2, pos.y+1};
        if(board.GetTeam(dest) != team) moves.push_back(Move::moveOrCapture(board, pos, dest));
    }
    // bottom right
    if(pos.x <= 5 && pos.y >= 1) {
        dest = {pos.x+2, pos.y-1};
        if(board.GetTeam(dest) != team) moves.push_back(Move::moveOrCapture(board, pos, dest));
    }
    if(pos.x <= 6 && pos.y >= 2) {
        dest = {pos.x+1, pos.y-2};
        if(board.GetTeam(dest) != team) moves.push_back(Move::moveOrCapture(board, pos, dest));
    }
    // bottom left
    if(pos.x >= 1 && pos.y >= 2) {
        dest = {pos.x-1, pos.y-2};
        if(board.GetTeam(dest) != team) moves.push_back(Move::moveOrCapture(board, pos, dest));
    }
    if(pos.x >= 2 && pos.y >= 1) {
        dest = {pos.x-2, pos.y-1};
        if(board.GetTeam(dest) != team) moves.push_back(Move::moveOrCapture(board, pos, dest));
    }
    // top left
    if(pos.x >= 2 && pos.y <= 6) {
        dest = {pos.x-2, pos.y+1};
        if(board.GetTeam(dest) != team) moves.push_back(Move::moveOrCapture(board, pos, dest));
    }
    if(pos.x >= 1 && pos.y <= 5) {
        dest = {pos.x-1, pos.y+2};
        if(board.GetTeam(dest) != team) moves.push_back(Move::moveOrCapture(board, pos, dest));
    }

    return moves;
}

std::vector<Move> Rook::GetMoves(const Board& board, const glm::ivec2 pos) const {
    std::vector<Move> moves;
    const uint32_t team = board.GetPiece(pos)->team;
    glm::ivec2 dest;

    for(int x = pos.x+1; x < 8; x++) {
        dest = {x, pos.y};
        if(board.GetTeam(dest) == team) break;
        moves.push_back(Move::moveOrCapture(board, pos, dest));
        if(board.GetType(dest) != PieceType::None) break;
    }
    for(int x = pos.x-1; x >= 0; x--) {
        dest = {x, pos.y};
        if(board.GetTeam(dest) == team) break;
        moves.push_back(Move::moveOrCapture(board, pos, dest));
        if(board.GetType(dest) != PieceType::None) break;
    }
    for(int y = pos.y+1; y < 8; y++) {
        dest = {pos.x, y};
        if(board.GetTeam(dest) == team) break;
        moves.push_back(Move::moveOrCapture(board, pos, dest));
        if(board.GetType(dest) != PieceType::None) break;
    }
    for(int y = pos.y-1; y >= 0; y--) {
        dest = {pos.x, y};
        if(board.GetTeam(dest) == team) break;
        moves.push_back(Move::moveOrCapture(board, pos, dest));
        if(board.GetType(dest) != PieceType::None) break;
    }

    return moves;
}

std::vector<Move> Pawn::GetMoves(const Board& board, const glm::ivec2 pos) const {
    std::vector<Move> moves;
    const uint32_t team = board.GetPiece(pos)->team;
    glm::ivec2 dest;

    int dir = 1, twoFromStart = 4;
    if(team == 2) {
        dir = -1;
        twoFromStart = 3;
    }
        
    dest = {pos.x, pos.y+dir};
    if(board.GetType(dest) == PieceType::None) {
        moves.push_back(Move::move(pos, dest));

        if(board.GetPiece(pos)->moves == 0) {
            dest.y += dir;
            if(board.GetType(dest) == PieceType::None) moves.push_back(Move::move(pos, dest));
        }
    }

    if(pos.x < 7) {
        dest = {pos.x+1, pos.y+dir};
        if(board.GetTeam(dest) != team && board.GetType(dest) != PieceType::None) moves.push_back(Move::capture(pos, dest));

        dest = {pos.x-1, pos.y};
        if(board.GetTeam(dest) != team &&
            board.GetType(dest) == PieceType::Pawn &&
            board.GetType({pos.x-1, pos.y+1}) == PieceType::None &&
            board.GetPiece(dest)->moves == 1 &&
            pos.y == twoFromStart) {
                Move move = Move(pos, {pos.x-1, pos.y+dir});
                move.actions.push_back(UniFox::MakeRef<MovePieceAction>(pos, glm::ivec2(pos.x-1, pos.y+dir)));
                move.actions.push_back(UniFox::MakeRef<RemovePieceAction>(dest));
                moves.push_back(move);
        }
    }
    if(pos.x > 0) {
        dest = {pos.x-1, pos.y+dir};
        if(board.GetTeam(dest) != team && board.GetType(dest) != PieceType::None) moves.push_back(Move::capture(pos, dest));

        dest = {pos.x+1, pos.y};
        if(board.GetTeam(dest) != team &&
            board.GetType(dest) == PieceType::Pawn &&
            board.GetType({pos.x+1, pos.y+1}) == PieceType::None &&
            board.GetPiece(dest)->moves == 1 &&
            pos.y == twoFromStart) {
                Move move = Move(pos, {pos.x+1, pos.y+dir});
                move.actions.push_back(UniFox::MakeRef<MovePieceAction>(pos, glm::ivec2(pos.x+1, pos.y+dir)));
                move.actions.push_back(UniFox::MakeRef<RemovePieceAction>(dest));
                moves.push_back(move);
        }
    }

    return moves;
}