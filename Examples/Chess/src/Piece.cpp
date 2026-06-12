#include "Piece.h"

#include "Action.h"
#include "Board.h"

bool Piece::CanMove(const Board& board, const glm::ivec2 pos) {
    return board.GetTeam(pos) == 0;
}
bool Piece::CanCapture(const Board& board, const glm::ivec2 pos, uint32_t team) {
    return (board.GetTeam(pos) != team && board.GetId(pos) != 0);
}

void Piece::Jump(const Board& board, const glm::ivec2 pos, const glm::ivec2 dir, std::vector<Move>& moves) {
    const uint32_t team = board.GetPiece(pos)->team;
    glm::ivec2 dest = pos + dir;

    if(board.InBounds(dest)) {
        if(board.GetTeam(dest) != team) {
            moves.push_back(Move::moveOrCapture(board, pos, dest));
        }
    }
}
void Piece::Jump(const Board& board, const glm::ivec2 pos, const std::vector<glm::ivec2> dirs, std::vector<Move>& moves) {
    const uint32_t team = board.GetPiece(pos)->team;
    glm::ivec2 dest;

    for(auto dir : dirs) {
        dest = pos + dir;
        if(board.InBounds(dest)) {
            if(board.GetTeam(dest) != team) {
                moves.push_back(Move::moveOrCapture(board, pos, dest));
            }
        }
    }
}

void Piece::Slide(const Board& board, const glm::ivec2 pos, const glm::ivec2 dir, std::vector<Move>& moves) {
    const uint32_t team = board.GetPiece(pos)->team;
    glm::ivec2 dest = pos;

    while(true) {
        dest += dir;
        if(!board.InBounds(dest)) return;

        if(board.GetTeam(dest) != team) {
            moves.push_back(Move::moveOrCapture(board, pos, dest));
        }

        if(board.GetId(dest) != 0) return;
    }
}
void Piece::Slide(const Board& board, const glm::ivec2 pos, const std::vector<glm::ivec2> dirs, std::vector<Move>& moves) {
    const uint32_t team = board.GetPiece(pos)->team;
    glm::ivec2 dest;

    for(auto dir : dirs) {
        dest = pos;
        while(true) {
            dest += dir;
            if(!board.InBounds(dest)) break;

            if(board.GetTeam(dest) != team) {
                moves.push_back(Move::moveOrCapture(board, pos, dest));
            }

            if(board.GetId(dest) != 0) break;
        }
    }
}

void Piece::Locust(const Board& board, const glm::ivec2 pos, const glm::ivec2 dir, std::vector<Move>& moves) {
    const uint32_t team = board.GetPiece(pos)->team;
    glm::ivec2 dest = pos;

    while(true) {
        dest += dir;
        if(!board.InBounds(dest)) return;

        if(board.GetId(dest) != 0) {
            dest += dir;
            if(!board.InBounds(dest)) return;

            moves.push_back(Move::moveOrCapture(board, pos, dest));
            return;
        }
    }
}
void Piece::Locust(const Board& board, const glm::ivec2 pos, const std::vector<glm::ivec2> dirs, std::vector<Move>& moves) {
    const uint32_t team = board.GetPiece(pos)->team;
    glm::ivec2 dest;

    for(auto dir : dirs) {
        dest = pos;
        while(true) {
            dest += dir;
            if(!board.InBounds(dest)) break;

            if(board.GetId(dest) != 0) {
                dest += dir;
                if(!board.InBounds(dest)) break;
                
                moves.push_back(Move::moveOrCapture(board, pos, dest));
                break;
            }
        }
    }
}

std::vector<Move> Piece::Combine(const std::vector<Move> A, const std::vector<Move> B) {
    std::vector<Move> AB;
    AB.reserve(A.size() + B.size());
    AB.insert(AB.end(), A.begin(), A.end());
    AB.insert(AB.end(), B.begin(), B.end());
    return AB;
}

#pragma region Standard
void King::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    const uint32_t team = board.GetPiece(pos)->team;
    glm::ivec2 dest;

    Piece::Jump(board, pos, {
        { 1,  0},
        {-1,  0},
        { 0,  1},
        { 0, -1},
        { 1,  1},
        { 1, -1},
        {-1,  1},
        {-1, -1}
    }, moves);

    //casteling
    dest = {0, pos.y};
    if(board.GetPiece(pos)->moves == 0 &&
        board.GetId(dest) == board.GetId("Rook") &&
        board.GetPiece(dest)->moves == 0 &&
        board.GetPiece({1, pos.y}) == nullptr &&
        board.GetPiece({2, pos.y}) == nullptr &&
        board.GetPiece({3, pos.y}) == nullptr &&
        board.IsSquareSafe({1, pos.y}, team) &&
        board.IsSquareSafe({2, pos.y}, team) &&
        board.IsSquareSafe({3, pos.y}, team)) {
            Move move = Move(pos, {2, pos.y});
            move.actions.push_back(new MovePieceAction(pos, glm::ivec2(2, pos.y)));
            move.actions.push_back(new MovePieceAction(dest, glm::ivec2(3, pos.y)));
            moves.push_back(move);
    }
    dest = {7, pos.y};
    if(board.GetPiece(pos)->moves == 0 &&
        board.GetId(dest) == board.GetId("Rook") &&
        board.GetPiece(dest)->moves == 0 &&
        board.GetPiece({6, pos.y}) == nullptr &&
        board.GetPiece({5, pos.y}) == nullptr &&
        board.IsSquareSafe({6, pos.y}, team) &&
        board.IsSquareSafe({5, pos.y}, team)) {
            Move move = Move(pos, {6, pos.y});
            move.actions.push_back(new MovePieceAction(pos, glm::ivec2(6, pos.y)));
            move.actions.push_back(new MovePieceAction(dest, glm::ivec2(5, pos.y)));
            moves.push_back(move);
    }
}

void Queen::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    Bishop::GenerateMoves(board, pos, moves);
    Rook::GenerateMoves(board, pos, moves);
}

void Bishop::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    Piece::Slide(board, pos, {
        { 1,  1},
        { 1, -1},
        {-1,  1},
        {-1, -1}
    }, moves);
}

void Knight::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    Piece::Jump(board, pos, {
        { 1,  2},
        { 2,  1},
        { 1, -2},
        { 2, -1},
        {-1,  2},
        {-2,  1},
        {-1, -2},
        {-2, -1}
    }, moves);
}

void Rook::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    Piece::Slide(board, pos, {
        { 1,  0},
        {-1,  0},
        { 0,  1},
        { 0, -1}
    }, moves);
}

void Pawn::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    const uint32_t team = board.GetPiece(pos)->team;
    glm::ivec2 dest;

    int dir = 1, twoFromStart = 4;
    if(team == 2) {
        dir = -1;
        twoFromStart = 3;
    }
        
    dest = {pos.x, pos.y+dir};
    if(board.GetId(dest) == 0) {
        moves.push_back(Move::move(pos, dest));

        if(board.GetPiece(pos)->moves == 0) {
            dest.y += dir;
            if(board.GetId(dest) == 0) moves.push_back(Move::move(pos, dest));
        }
    }

    if(pos.x < 7) {
        dest = {pos.x+1, pos.y+dir};
        if(board.GetTeam(dest) != team && board.GetId(dest) != 0) moves.push_back(Move::capture(pos, dest));

        dest = {pos.x-1, pos.y};
        if(board.GetTeam(dest) != team &&
            board.GetId(dest) == board.GetId("Pawn") &&
            board.GetId(glm::ivec2(pos.x-1, pos.y+1)) == 0 &&
            board.GetPiece(dest)->moves == 1 &&
            pos.y == twoFromStart) {
                Move move = Move(pos, {pos.x-1, pos.y+dir});
                move.actions.push_back(new MovePieceAction(pos, glm::ivec2(pos.x-1, pos.y+dir)));
                move.actions.push_back(new RemovePieceAction(dest));
                moves.push_back(move);
        }
    }
    if(pos.x > 0) {
        dest = {pos.x-1, pos.y+dir};
        if(board.GetTeam(dest) != team && board.GetId(dest) != 0) moves.push_back(Move::capture(pos, dest));

        dest = {pos.x+1, pos.y};
        if(board.GetTeam(dest) != team &&
            board.GetId(dest) == board.GetId("Pawn") &&
            board.GetId(glm::ivec2(pos.x+1, pos.y+1)) == 0 &&
            board.GetPiece(dest)->moves == 1 &&
            pos.y == twoFromStart) {
                Move move = Move(pos, {pos.x+1, pos.y+dir});
                move.actions.push_back(new MovePieceAction(pos, glm::ivec2(pos.x+1, pos.y+dir)));
                move.actions.push_back(new RemovePieceAction(dest));
                moves.push_back(move);
        }
    }
}
#pragma endregion

#pragma region Leaper
void Camel::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    Piece::Jump(board, pos, {
        { 1,  3},
        { 3,  1},
        { 1, -3},
        { 3, -1},
        {-1,  3},
        {-3,  1},
        {-1, -3},
        {-3, -1}
    }, moves);
}

void Wazir::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    Piece::Jump(board, pos, {
        { 0,  1},
        { 0, -1},
        { 1,  1},
        {-1, -1}
    }, moves);
}

void Ferz::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    Piece::Jump(board, pos, {
        { 1,  0},
        {-1,  0},
        { 0,  1},
        { 0, -1},
        { 1,  1},
        { 1, -1},
        {-1,  1},
        {-1, -1}
    }, moves);
}

void WarMachine::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    Piece::Slide(board, pos, {
        { 2,  0},
        {-2,  0},
        { 0,  2},
        { 0, -2}
    }, moves);
}

void Horse::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    uint32_t team = board.GetTeam(pos);
    glm::ivec2 dest;

    if(board.GetId(glm::ivec2(pos.x+1, pos.y)) == 0) {
        dest = {pos.x+2, pos.y+1};
        if(board.GetTeam(dest) != team) moves.push_back(Move::moveOrCapture(board, pos, dest));
        dest = {pos.x+2, pos.y-1};
        if(board.GetTeam(dest) != team) moves.push_back(Move::moveOrCapture(board, pos, dest));
    }
    if(board.GetId(glm::ivec2(pos.x-1, pos.y)) == 0) {
        dest = {pos.x-2, pos.y+1};
        if(board.GetTeam(dest) != team) moves.push_back(Move::moveOrCapture(board, pos, dest));
        dest = {pos.x-2, pos.y-1};
        if(board.GetTeam(dest) != team) moves.push_back(Move::moveOrCapture(board, pos, dest));
    }
    if(board.GetId(glm::ivec2(pos.x, pos.y+1)) == 0) {
        dest = {pos.x+1, pos.y+2};
        if(board.GetTeam(dest) != team) moves.push_back(Move::moveOrCapture(board, pos, dest));
        dest = {pos.x-1, pos.y+2};
        if(board.GetTeam(dest) != team) moves.push_back(Move::moveOrCapture(board, pos, dest));
    }
    if(board.GetId(glm::ivec2(pos.x, pos.y-1)) == 0) {
        dest = {pos.x+1, pos.y-2};
        if(board.GetTeam(dest) != team) moves.push_back(Move::moveOrCapture(board, pos, dest));
        dest = {pos.x-1, pos.y-2};
        if(board.GetTeam(dest) != team) moves.push_back(Move::moveOrCapture(board, pos, dest));
    }
}
#pragma endregion

#pragma region Rider
void KnightRider::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    Piece::Slide(board, pos, {
        { 1,  2},
        { 2,  1},
        { 1, -2},
        { 2, -1},
        {-1,  2},
        {-2,  1},
        {-1, -2},
        {-2, -1}
    }, moves);
}

void CamelRider::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    Piece::Slide(board, pos, {
        { 1,  3},
        { 3,  1},
        { 1, -3},
        { 3, -1},
        {-1,  3},
        {-3,  1},
        {-1, -3},
        {-3, -1}
    }, moves);
}

void Elephant::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    Piece::Jump(board, pos, {
        { 2,  2},
        { 2, -2},
        {-2,  2},
        {-2, -2}
    }, moves);
}
#pragma endregion

#pragma region Locust
void Grasshopper::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    Piece::Locust(board, pos, {
        { 1,  0},
        {-1,  0},
        { 0,  1},
        { 0, -1},
        { 1,  1},
        { 1, -1},
        {-1,  1},
        {-1, -1}
    }, moves);
}
#pragma endregion

#pragma region Variant
void Soldier::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    uint32_t team = board.GetTeam(pos);
    glm::ivec2 dest;

    int dir = 1;
    if(team == 2) dir = -1;

    dest = {pos.x, pos.y+dir};
    if(board.InBounds(dest) && CanMove(board, dest)) moves.push_back(Move::moveOrCapture(board, pos, dest));
}

void StoneGeneral::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    uint32_t team = board.GetTeam(pos);
    glm::ivec2 dest;

    int dir = 1;
    if(team == 2) dir = -1;

    dest = {pos.x+1, pos.y+dir};
    if(board.InBounds(dest)) moves.push_back(Move::moveOrCapture(board, pos, dest));
    dest = {pos.x-1, pos.y+dir};
    if(board.InBounds(dest)) moves.push_back(Move::moveOrCapture(board, pos, dest));
}

void Sergeant::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    uint32_t team = board.GetTeam(pos);
    glm::ivec2 dest;

    int dir = 1;
    if(team == 2) dir = -1;

    dest = {pos.x, pos.y+dir};
    if(board.InBounds(dest)) moves.push_back(Move::moveOrCapture(board, pos, dest));
    dest = {pos.x+1, pos.y+dir};
    if(board.InBounds(dest)) moves.push_back(Move::moveOrCapture(board, pos, dest));
    dest = {pos.x-1, pos.y+dir};
    if(board.InBounds(dest)) moves.push_back(Move::moveOrCapture(board, pos, dest));
}

void Berolina::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    uint32_t team = board.GetTeam(pos);
    glm::ivec2 dest;

    int dir = 1;
    if(team == 2) dir = -1;

    dest = {pos.x, pos.y+dir};
    if(board.InBounds(dest) && board.GetId(dest) != 0) moves.push_back(Move::capture(pos, dest));
    dest = {pos.x+1, pos.y+dir};
    if(board.InBounds(dest) && board.GetId(dest) == 0) moves.push_back(Move::move(pos, dest));
    dest = {pos.x-1, pos.y+dir};
    if(board.InBounds(dest) && board.GetId(dest) == 0) moves.push_back(Move::move(pos, dest));
}
#pragma endregion

#pragma region Compund
void Chancellor::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    Rook::GenerateMoves(board, pos, moves);
    Knight::GenerateMoves(board, pos, moves);
}

void Cardinal::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    Bishop::GenerateMoves(board, pos, moves);
    Knight::GenerateMoves(board, pos, moves);
}

void Amazon::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    Bishop::GenerateMoves(board, pos, moves);
    Rook::GenerateMoves(board, pos, moves);
    Knight::GenerateMoves(board, pos, moves);
}

void General::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    Ferz::GenerateMoves(board, pos, moves);
    Knight::GenerateMoves(board, pos, moves);
}

void Wildebeest::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    Knight::GenerateMoves(board, pos, moves);
    Camel::GenerateMoves(board, pos, moves);
}
#pragma endregion