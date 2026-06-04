#include "Piece.h"

int* Piece::GetMoves(const Piece* state, const int position) {
    if(position < 0 || state[position].GetType() == PieceType::None) {
        return new int[64] {};
    }
    switch (state[position].GetType()) {
    case PieceType::King:
        return King::GetMoves(state, position);
    case PieceType::Queen:
        return Queen::GetMoves(state, position);
    case PieceType::Bishop:
        return Bishop::GetMoves(state, position);
    case PieceType::Knight:
        return Knight::GetMoves(state, position);
    case PieceType::Rook:
        return Rook::GetMoves(state, position);
    case PieceType::Pawn:
        return Pawn::GetMoves(state, position);
    }
}

int* King::GetMoves(const Piece* state, const int position) {
    int* moves = new int[64] {};
    const int team = state[position].GetTeam();
    const int X = glm::mod((float)position, 8.0f); const int Y = position / 8;
    int pos = -1;

    for(int x = -1; x <= 1; x++)
    for(int y = -1; y <= 1; y++) {
        if(X+x < 0 || X+x > 7) continue;
        if(Y+y < 0 || Y+y > 7) continue;
        if(x == 0 && y == 0) continue;

        pos = X+x + (Y+y)*8;
        if(state[pos].GetType() == PieceType::None) {
            moves[pos] = 1;
        } else {
            if(state[pos].GetTeam() != team) {
                moves[pos] = 1;
            } else {
                moves[pos] = 0;
            }
        }
    }

    return moves;
}

int* Queen::GetMoves(const Piece* state, const int position) {
    int* moves = new int[64] {};
    const int team = state[position].GetTeam();
    const int X = glm::mod((float)position, 8.0f); const int Y = position / 8;
    int pos = -1;

    for(int x = X+1; x < 8; x++) {
        pos = x + Y*8;
        if(state[pos].GetTeam() == team) break;
        moves[pos] = 1;
        if(state[pos].GetType() != PieceType::None) break;
    }
    for(int x = X-1; x >= 0; x--) {
        pos = x + Y*8;
        if(state[pos].GetTeam() == team) break;
        moves[pos] = 1;
        if(state[pos].GetType() != PieceType::None) break;
    }
    for(int y = Y+1; y < 8; y++) {
        pos = X + y*8;
        if(state[pos].GetTeam() == team) break;
        moves[pos] = 1;
        if(state[pos].GetType() != PieceType::None) break;
    }
    for(int y = Y-1; y >= 0; y--) {
        pos = X + y*8;
        if(state[pos].GetTeam() == team) break;
        moves[pos] = 1;
        if(state[pos].GetType() != PieceType::None) break;
    }

    for(int x = X+1, y = Y+1; x < 8 && y < 8; x++, y++) {
        pos = x + y*8;
        if(state[pos].GetTeam() == team) break;
        moves[pos] = 1;
        if(state[pos].GetType() != PieceType::None) break;
    }
    for(int x = X-1, y = Y+1; x >= 0 && y < 8; x--, y++) {
        pos = x + y*8;
        if(state[pos].GetTeam() == team) break;
        moves[pos] = 1;
        if(state[pos].GetType() != PieceType::None) break;
    }
    for(int x = X+1, y = Y-1; x < 8 && y >= 0; x++, y--) {
        pos = x + y*8;
        if(state[pos].GetTeam() == team) break;
        moves[pos] = 1;
        if(state[pos].GetType() != PieceType::None) break;
    }
    for(int x = X-1, y = Y-1; x >= 0 && y >= 0; x--, y--) {
        pos = x + y*8;
        if(state[pos].GetTeam() == team) break;
        moves[pos] = 1;
        if(state[pos].GetType() != PieceType::None) break;
    }

    return moves;
}

int* Bishop::GetMoves(const Piece* state, const int position) {
    int* moves = new int[64] {};
    const int team = state[position].GetTeam();
    const int X = glm::mod((float)position, 8.0f); const int Y = position / 8;
    int pos = -1;

    for(int x = X+1, y = Y+1; x < 8 && y < 8; x++, y++) {
        pos = x + y*8;
        if(state[pos].GetTeam() == team) break;
        moves[pos] = 1;
        if(state[pos].GetType() != PieceType::None) break;
    }
    for(int x = X-1, y = Y+1; x >= 0 && y < 8; x--, y++) {
        pos = x + y*8;
        if(state[pos].GetTeam() == team) break;
        moves[pos] = 1;
        if(state[pos].GetType() != PieceType::None) break;
    }
    for(int x = X+1, y = Y-1; x < 8 && y >= 0; x++, y--) {
        pos = x + y*8;
        if(state[pos].GetTeam() == team) break;
        moves[pos] = 1;
        if(state[pos].GetType() != PieceType::None) break;
    }
    for(int x = X-1, y = Y-1; x >= 0 && y >= 0; x--, y--) {
        pos = x + y*8;
        if(state[pos].GetTeam() == team) break;
        moves[pos] = 1;
        if(state[pos].GetType() != PieceType::None) break;
    }

    return moves;
}

int* Knight::GetMoves(const Piece* state, const int position) {
    int* moves = new int[64] {};
    const int team = state[position].GetTeam();
    const int X = glm::mod((float)position, 8.0f); const int Y = position / 8;
    int pos = -1;

    // top right
    if(X <= 6 && Y <= 5) {
        pos = (X+1) + (Y+2)*8;
        if(state[pos].GetTeam() != team) moves[pos] = 1;
    }
    if(X <= 5 && Y <= 6) {
        pos = (X+2) + (Y+1)*8;
        if(state[pos].GetTeam() != team) moves[pos] = 1;
    }
    // bottom right
    if(X <= 5 && Y >= 1) {
        pos = (X+2) + (Y-1)*8;
        if(state[pos].GetTeam() != team) moves[pos] = 1;
    }
    if(X <= 6 && Y >= 2) {
        pos = (X+1) + (Y-2)*8;
        if(state[pos].GetTeam() != team) moves[pos] = 1;
    }
    // bottom left
    if(X >= 1 && Y >= 2) {
        pos = (X-1) + (Y-2)*8;
        if(state[pos].GetTeam() != team) moves[pos] = 1;
    }
    if(X >= 2 && Y >= 1) {
        pos = (X-2) + (Y-1)*8;
        if(state[pos].GetTeam() != team) moves[pos] = 1;
    }
    // top left
    if(X >= 2 && Y <= 6) {
        pos = (X-2) + (Y+1)*8;
        if(state[pos].GetTeam() != team) moves[pos] = 1;
    }
    if(X >= 1 && Y <= 5) {
        pos = (X-1) + (Y+2)*8;
        if(state[pos].GetTeam() != team) moves[pos] = 1;
    }

    return moves;
}

int* Rook::GetMoves(const Piece* state, const int position) {
    int* moves = new int[64] {};
    const int team = state[position].GetTeam();
    const int X = glm::mod((float)position, 8.0f); const int Y = position / 8;
    int pos = -1;

    for(int x = X+1; x < 8; x++) {
        pos = x + Y*8;
        if(state[pos].GetTeam() == team) break;
        moves[pos] = 1;
        if(state[pos].GetType() != PieceType::None) break;
    }
    for(int x = X-1; x >= 0; x--) {
        pos = x + Y*8;
        if(state[pos].GetTeam() == team) break;
        moves[pos] = 1;
        if(state[pos].GetType() != PieceType::None) break;
    }
    for(int y = Y+1; y < 8; y++) {
        pos = X + y*8;
        if(state[pos].GetTeam() == team) break;
        moves[pos] = 1;
        if(state[pos].GetType() != PieceType::None) break;
    }
    for(int y = Y-1; y >= 0; y--) {
        pos = X + y*8;
        if(state[pos].GetTeam() == team) break;
        moves[pos] = 1;
        if(state[pos].GetType() != PieceType::None) break;
    }

    return moves;
}

int* Pawn::GetMoves(const Piece* state, const int position) {
    int* moves = new int[64] {};
    const int team = state[position].GetTeam();
    const int X = glm::mod((float)position, 8.0f); const int Y = position / 8;
    int pos = -1;

    int dir = 1, start = 1;
    if(team == 1) {
        dir = -1;
        start = 6;
    }
        
    pos = X + (Y+dir)*8;
    if(state[pos].GetType() == PieceType::None) {
        moves[pos] = 1;

        if(Y == start) {
            pos += dir * 8;
            if(state[pos].GetType() == PieceType::None) moves[pos] = 1;
        }
    }

    if(X < 7) {
        pos = X+1 + (Y+dir)*8;
        if(state[pos].GetTeam() != team && state[pos].GetType() != PieceType::None) moves[pos] = 1;
    }
    if(X > 0) {
        pos = X-1 + (Y+dir)*8;
        if(state[pos].GetTeam() != team && state[pos].GetType() != PieceType::None) moves[pos] = 1;
    }

    return moves;
}