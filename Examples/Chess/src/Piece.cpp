#include "Piece.h"

#include "Action.h"
#include "Board.h"

#pragma region Helpers
bool Piece::CanMove(const Board& board, const glm::ivec2 pos) {
    return board.GetTeam(pos) == 0;
}
bool Piece::CanCapture(const Board& board, const glm::ivec2 pos, uint32_t team) {
    return (board.GetTeam(pos) != team && board.GetId(pos) != 0);
}

void Piece::Jump(const Board& board, const glm::ivec2 pos, const glm::ivec2 dir, std::vector<Move>& moves) {
    const uint32_t team = board.GetTeam(pos);
    glm::ivec2 dest = pos + dir;

    if(board.InBounds(dest)) {
        if(board.GetTeam(dest) != team) {
            moves.push_back(Move::moveOrCapture(board, pos, dest));
        }
    }
}
void Piece::Jump(const Board& board, const glm::ivec2 pos, const std::vector<glm::ivec2> dirs, std::vector<Move>& moves) {
    const uint32_t team = board.GetTeam(pos);
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
    const uint32_t team = board.GetTeam(pos);
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
    const uint32_t team = board.GetTeam(pos);
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
    const uint32_t team = board.GetTeam(pos);
    glm::ivec2 dest = pos;

    while(true) {
        dest += dir;
        if(!board.InBounds(dest)) return;

        if(board.GetId(dest) != 0) {
            dest += dir;
            if(!board.InBounds(dest)) return;

            if(board.GetTeam(dest) != team) {
                moves.push_back(Move::moveOrCapture(board, pos, dest));
            }
            return;
        }
    }
}
void Piece::Locust(const Board& board, const glm::ivec2 pos, const std::vector<glm::ivec2> dirs, std::vector<Move>& moves) {
    const uint32_t team = board.GetTeam(pos);
    glm::ivec2 dest;

    for(auto dir : dirs) {
        dest = pos;
        while(true) {
            dest += dir;
            if(!board.InBounds(dest)) break;

            if(board.GetId(dest) != 0) {
                dest += dir;
                if(!board.InBounds(dest)) break;
                
                if(board.GetTeam(dest) != team) {
                    moves.push_back(Move::moveOrCapture(board, pos, dest));
                }
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
#pragma endregion

#pragma region Standard
void King::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    const uint32_t team = board.GetTeam(pos);
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
            move.actions.push_back(UniFox::MakeRef<MovePieceAction>(pos, glm::ivec2(2, pos.y)));
            move.actions.push_back(UniFox::MakeRef<MovePieceAction>(dest, glm::ivec2(3, pos.y)));
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
            move.actions.push_back(UniFox::MakeRef<MovePieceAction>(pos, glm::ivec2(6, pos.y)));
            move.actions.push_back(UniFox::MakeRef<MovePieceAction>(dest, glm::ivec2(5, pos.y)));
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
    const uint32_t team = board.GetTeam(pos);
    glm::ivec2 dest;

    glm::ivec2 dir = board.GetTeam(team).dir;
    glm::ivec2 right = {dir.y, -dir.x};

    std::vector<std::string> promotion = {"Queen", "Bishop", "Knight", "Rook"};

    // two move at start
    if(board.GetPiece(pos)->moves == 0) {
        dest = pos + dir + dir;
        if(board.GetId(pos + dir) == 0 && board.GetId(dest) == 0) {
            moves.push_back(Move::move(pos, dest));
        }
    }

    // march forward
    dest = pos + dir;
    if(board.GetId(dest) == 0) {
        if(board.InBounds(dest + dir)) {
            moves.push_back(Move::move(pos, dest));
        } else {
            // promote
            for(auto name : promotion) {
                Move move(pos, dest);
                UniFox::Ref<Piece> piece = board.CreatePiece(name, team);
                move.actions.push_back(UniFox::MakeRef<RemovePieceAction>(pos));
                move.actions.push_back(UniFox::MakeRef<CreatePieceAction>(dest, piece));
                moves.push_back(move);
            }
        }
    }

    // front right
    dest = pos + dir + right;
    if(board.InBounds(dest)) {
        // normal
        if(board.GetId(dest) != 0 && board.GetTeam(dest) != team) {
            if(board.InBounds(dest + dir)) {
                moves.push_back(Move::capture(pos, dest));
            } else {
                for(auto name : promotion) {
                    Move move(pos, dest);
                    UniFox::Ref<Piece> piece = board.CreatePiece(name, team);
                    move.actions.push_back(UniFox::MakeRef<RemovePieceAction>(pos));
                    move.actions.push_back(UniFox::MakeRef<RemovePieceAction>(dest));
                    move.actions.push_back(UniFox::MakeRef<CreatePieceAction>(dest, piece));
                    moves.push_back(move);
                }
            }
        }
        // en passant
        glm::ivec2 pawn = dest - dir;
        if(board.InBounds(pawn)) {
            if(board.GetId(pawn) == board.GetId("Pawn") &&
                board.GetTeam(pawn) != team &&
                board.GetId(dest) == 0 &&
                board.GetPiece(pawn)->moves == 1 &&
                board.GetPiece(pawn)->dist == 2 * board.GetTeam(board.GetTeam(pawn)).dir) {
                    if(board.InBounds(dest + dir)) {
                        Move move(pos, dest);
                        move.actions.push_back(UniFox::MakeRef<RemovePieceAction>(pawn));
                        move.actions.push_back(UniFox::MakeRef<MovePieceAction>(pos, dest));
                        moves.push_back(move);
                    } else {
                        for(auto name : promotion) {
                            Move move(pos, dest);
                            UniFox::Ref<Piece> piece = board.CreatePiece(name, team);
                            move.actions.push_back(UniFox::MakeRef<RemovePieceAction>(pos));
                            move.actions.push_back(UniFox::MakeRef<RemovePieceAction>(pawn));
                            move.actions.push_back(UniFox::MakeRef<CreatePieceAction>(dest, piece));
                            moves.push_back(move);
                        }
                    }
            }
        }
    }

    // front left
    dest = pos + dir - right;
    if(board.InBounds(dest)) {
        // normal
        if(board.GetId(dest) != 0 && board.GetTeam(dest) != team) {
            if(board.InBounds(dest + dir)) {
                moves.push_back(Move::capture(pos, dest));
            } else {
                for(auto name : promotion) {
                    Move move(pos, dest);
                    UniFox::Ref<Piece> piece = board.CreatePiece(name, team);
                    move.actions.push_back(UniFox::MakeRef<RemovePieceAction>(pos));
                    move.actions.push_back(UniFox::MakeRef<RemovePieceAction>(dest));
                    move.actions.push_back(UniFox::MakeRef<CreatePieceAction>(dest, piece));
                    moves.push_back(move);
                }
            }
        }
        // en passant
        glm::ivec2 pawn = dest - dir;
        if(board.InBounds(pawn)) {
            if(board.GetId(pawn) == board.GetId("Pawn") &&
                board.GetTeam(pawn) != team &&
                board.GetId(dest) == 0 &&
                board.GetPiece(pawn)->moves == 1 &&
                board.GetPiece(pawn)->dist == 2 * board.GetTeam(board.GetTeam(pawn)).dir) {
                    if(board.InBounds(dest + dir)) {
                        Move move(pos, dest);
                        move.actions.push_back(UniFox::MakeRef<RemovePieceAction>(pawn));
                        move.actions.push_back(UniFox::MakeRef<MovePieceAction>(pos, dest));
                        moves.push_back(move);
                    } else {
                        for(auto name : promotion) {
                            Move move(pos, dest);
                            UniFox::Ref<Piece> piece = board.CreatePiece(name, team);
                            move.actions.push_back(UniFox::MakeRef<RemovePieceAction>(pos));
                            move.actions.push_back(UniFox::MakeRef<RemovePieceAction>(pawn));
                            move.actions.push_back(UniFox::MakeRef<CreatePieceAction>(dest, piece));
                            moves.push_back(move);
                        }
                    }
            }
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
    Piece::Jump(board, pos, {
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

void Spider::GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) {
    Ferz::GenerateMoves(board, pos, moves);
    WarMachine:GenerateMoves(board, pos, moves);
}
#pragma endregion