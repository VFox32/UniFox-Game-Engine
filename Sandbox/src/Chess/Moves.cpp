#include "Board.h"

uint64_t Board::GetMoves(const int position) {
    if(position < 0 || GetPieces()[position] == PieceType::None) {
        return 0;
    }

    switch (GetPieces()[position]) {
    case PieceType::King:
        return GetKingMoves(position);
    case PieceType::Queen:
        return GetQueenMoves(position);
    case PieceType::Bishop:
        return GetBishopMoves(position);
    case PieceType::Knight:
        return GetKnightMoves(position);
    case PieceType::Rook:
        return GetRookMoves(position);
    case PieceType::Pawn:
        return GetPawnMoves(position);
    }

    return 0;
}

uint64_t Board::GetAllMoves(const int team) {
    uint64_t moves = 0;
    for(int pos = 0; pos < 64; pos++) {
        if(GetTeam(pos) == team) moves |= GetMoves(pos);
    }
    return moves;
}

uint64_t Board::GetKingMoves(const int position) {
    uint64_t moves = 0;
    const int team = GetTeam(position);
    const int X = position % 8; const int Y = position / 8;
    int pos = -1;

    for(int x = -1; x <= 1; x++)
    for(int y = -1; y <= 1; y++) {
        if(X+x < 0 || X+x > 7) continue;
        if(Y+y < 0 || Y+y > 7) continue;
        if(x == 0 && y == 0) continue;

        pos = X+x + (Y+y)*8;
        if(GetType(pos) == PieceType::None) {
            moves |= (1ULL << pos);
        } else if(GetTeam(pos) != team) {
            moves |= (1ULL << pos);
        }
    }

    return moves;
}

uint64_t Board::GetQueenMoves(const int position) {
    return GetRookMoves(position) | GetBishopMoves(position);
}

uint64_t Board::GetBishopMoves(const int position) {
    uint64_t moves = 0;
    const int team = GetTeam(position);
    const int X = position % 8; const int Y = position / 8;
    int pos = -1;

    for(int x = X+1, y = Y+1; x < 8 && y < 8; x++, y++) {
        pos = x + y*8;
        if(GetTeam(pos) == team) break;
        moves |= (1ULL << pos);
        if(GetType(pos) != PieceType::None) break;
    }
    for(int x = X-1, y = Y+1; x >= 0 && y < 8; x--, y++) {
        pos = x + y*8;
        if(GetTeam(pos) == team) break;
        moves |= (1ULL << pos);
        if(GetType(pos) != PieceType::None) break;
    }
    for(int x = X+1, y = Y-1; x < 8 && y >= 0; x++, y--) {
        pos = x + y*8;
        if(GetTeam(pos) == team) break;
        moves |= (1ULL << pos);
        if(GetType(pos) != PieceType::None) break;
    }
    for(int x = X-1, y = Y-1; x >= 0 && y >= 0; x--, y--) {
        pos = x + y*8;
        if(GetTeam(pos) == team) break;
        moves |= (1ULL << pos);
        if(GetType(pos) != PieceType::None) break;
    }

    return moves;
}

uint64_t Board::GetKnightMoves(const int position) {
    uint64_t moves = 0;
    const int team = GetTeam(position);
    const int X = position % 8; const int Y = position / 8;
    int pos = -1;

    // top right
    if(X <= 6 && Y <= 5) {
        pos = (X+1) + (Y+2)*8;
        if(GetTeam(pos) != team) moves |= (1ULL << pos);
    }
    if(X <= 5 && Y <= 6) {
        pos = (X+2) + (Y+1)*8;
        if(GetTeam(pos) != team) moves |= (1ULL << pos);
    }
    // bottom right
    if(X <= 5 && Y >= 1) {
        pos = (X+2) + (Y-1)*8;
        if(GetTeam(pos) != team) moves |= (1ULL << pos);
    }
    if(X <= 6 && Y >= 2) {
        pos = (X+1) + (Y-2)*8;
        if(GetTeam(pos) != team) moves |= (1ULL << pos);
    }
    // bottom left
    if(X >= 1 && Y >= 2) {
        pos = (X-1) + (Y-2)*8;
        if(GetTeam(pos) != team) moves |= (1ULL << pos);
    }
    if(X >= 2 && Y >= 1) {
        pos = (X-2) + (Y-1)*8;
        if(GetTeam(pos) != team) moves |= (1ULL << pos);
    }
    // top left
    if(X >= 2 && Y <= 6) {
        pos = (X-2) + (Y+1)*8;
        if(GetTeam(pos) != team) moves |= (1ULL << pos);
    }
    if(X >= 1 && Y <= 5) {
        pos = (X-1) + (Y+2)*8;
        if(GetTeam(pos) != team) moves |= (1ULL << pos);
    }

    return moves;
}

uint64_t Board::GetRookMoves(const int position) {
    uint64_t moves = 0;
    const int team = GetTeam(position);
    const int X = position % 8; const int Y = position / 8;
    int pos = -1;

    for(int x = X+1; x < 8; x++) {
        pos = x + Y*8;
        if(GetTeam(pos) == team) break;
        moves |= (1ULL << pos);
        if(GetType(pos) != PieceType::None) break;
    }
    for(int x = X-1; x >= 0; x--) {
        pos = x + Y*8;
        if(GetTeam(pos) == team) break;
        moves |= (1ULL << pos);
        if(GetType(pos) != PieceType::None) break;
    }
    for(int y = Y+1; y < 8; y++) {
        pos = X + y*8;
        if(GetTeam(pos) == team) break;
        moves |= (1ULL << pos);
        if(GetType(pos) != PieceType::None) break;
    }
    for(int y = Y-1; y >= 0; y--) {
        pos = X + y*8;
        if(GetTeam(pos) == team) break;
        moves |= (1ULL << pos);
        if(GetType(pos) != PieceType::None) break;
    }

    return moves;
}

uint64_t Board::GetPawnMoves(const int position) {
    uint64_t moves = 0;
    const int team = GetTeam(position);
    const int X = position % 8; const int Y = position / 8;
    int pos = -1;

    int dir = 1, start = 1;
    if(team == 2) {
        dir = -1;
        start = 6;
    }
        
    pos = X + (Y+dir)*8;
    if(GetType(pos) == PieceType::None) {
        moves |= (1ULL << pos);

        if(Y == start) {
            pos += dir * 8;
            if(GetType(pos) == PieceType::None) moves |= (1ULL << pos);;
        }
    }

    if(X < 7) {
        pos = X+1 + (Y+dir)*8;
        if(GetTeam(pos) != team && GetType(pos) != PieceType::None) moves |= (1ULL << pos);;
    }
    if(X > 0) {
        pos = X-1 + (Y+dir)*8;
        if(GetTeam(pos) != team && GetType(pos) != PieceType::None) moves |= (1ULL << pos);;
    }

    return moves;
}