#include "Board.h"

#include "Piece.h"
#include "Action.h"

#include "imgui.h"

void Board::AddPiece(PieceType type, glm::ivec2 pos, int team) {
    uint32_t i = GetIndex(pos);
    m_Pieces[i] = Piece::Create(type, team);
}
uint64_t Board::GetTeam(const glm::ivec2 pos) const {
    uint32_t i = GetIndex(pos);
    if(m_Pieces[i] != nullptr)
        return m_Pieces[i]->team;
    else
        return 0;
}
PieceType Board::GetType(const glm::ivec2 pos) const {
    uint32_t i = GetIndex(pos);
    if(m_Pieces[i] != nullptr)
        return m_Pieces[i]->type;
    else
        return PieceType::None;
}
glm::ivec2 Board::GetGridPos(const glm::vec2 pos) {
    glm::ivec2 grid = {floor(pos.x), floor(pos.y)};
    return grid;
}

Board::Board() {
    AddPiece(PieceType::Rook,   {0, 0}, 1);
    AddPiece(PieceType::Knight, {1, 0}, 1);
    AddPiece(PieceType::Bishop, {2, 0}, 1);
    AddPiece(PieceType::Queen,  {3, 0}, 1);
    AddPiece(PieceType::King,   {4, 0}, 1);
    AddPiece(PieceType::Bishop, {5, 0}, 1);
    AddPiece(PieceType::Knight, {6, 0}, 1);
    AddPiece(PieceType::Rook,   {7, 0}, 1);
    AddPiece(PieceType::Pawn,   {0, 1}, 1);
    AddPiece(PieceType::Pawn,   {1, 1}, 1);
    AddPiece(PieceType::Pawn,   {2, 1}, 1);
    AddPiece(PieceType::Pawn,   {3, 1}, 1);
    AddPiece(PieceType::Pawn,   {4, 1}, 1);
    AddPiece(PieceType::Pawn,   {5, 1}, 1);
    AddPiece(PieceType::Pawn,   {6, 1}, 1);
    AddPiece(PieceType::Pawn,   {7, 1}, 1);

    AddPiece(PieceType::Rook,   {0, 7}, 2);
    AddPiece(PieceType::Knight, {1, 7}, 2);
    AddPiece(PieceType::Bishop, {2, 7}, 2);
    AddPiece(PieceType::Queen,  {3, 7}, 2);
    AddPiece(PieceType::King,   {4, 7}, 2);
    AddPiece(PieceType::Bishop, {5, 7}, 2);
    AddPiece(PieceType::Knight, {6, 7}, 2);
    AddPiece(PieceType::Rook,   {7, 7}, 2);
    AddPiece(PieceType::Pawn,   {0, 6}, 2);
    AddPiece(PieceType::Pawn,   {1, 6}, 2);
    AddPiece(PieceType::Pawn,   {2, 6}, 2);
    AddPiece(PieceType::Pawn,   {3, 6}, 2);
    AddPiece(PieceType::Pawn,   {4, 6}, 2);
    AddPiece(PieceType::Pawn,   {5, 6}, 2);
    AddPiece(PieceType::Pawn,   {6, 6}, 2);
    AddPiece(PieceType::Pawn,   {7, 6}, 2);
}

Piece* Board::GetPiece(const glm::ivec2 pos) const {
    uint32_t index = pos.x + pos.y*8;
    return m_Pieces[index];
}
Piece* Board::GetPiece(const uint32_t pos) const {
    return m_Pieces[pos];
}
void Board::SetPiece(const glm::ivec2 pos, Piece* piece) {
    uint32_t index = pos.x + pos.y*8;
    m_Pieces[index] = piece;
}

bool Board::IsSquareSafe(const glm::ivec2 pos, const uint32_t team) const {
    for(int i = 0; i < 64; i++) {
        if(m_Pieces[i] &&
            m_Pieces[i]->team != team) {
            for(auto move : m_Pieces[i]->GetMoves(*this, GetCoord(i))) {
                if(move.dest == pos) return false;
            }
        }
    }
    return true;
}

std::vector<glm::ivec2> Board::FindPiece(PieceType type, uint32_t team) const {
    std::vector<glm::ivec2> coords;
    for(int i = 0; i < 64; i++) {
        if(m_Pieces[i] &&
            m_Pieces[i]->team == team &&
            m_Pieces[i]->type == type) {
                coords.push_back(GetCoord(i));
        }
    }
    return coords;
}

bool Board::IsCheck(const uint32_t team) const {
    glm::ivec2 kingPos = FindPiece(PieceType::King, team)[0];
    return !IsSquareSafe(kingPos, team);
}

bool Board::IsMate(const uint32_t team) {
    for(int i = 0; i < 64; i++) {
        if(m_Pieces[i] &&
            m_Pieces[i]->team != team) {
            std::vector<Move> moves = m_Pieces[i]->GetMoves(*this, GetCoord(i));
            for(auto move : moves) {
                move.Do(*this);

                std::vector<glm::ivec2> kings = FindPiece(PieceType::King, team);
                if(kings.size() == 0) {
                    move.Undo(*this);
                    continue;
                }
                glm::ivec2 kingPos = kings[0];
                if(IsSquareSafe(kingPos, team)) {
                    move.Undo(*this);
                    return false;
                }
                
                move.Undo(*this);
            }
        }
    }
    return true;
}

std::vector<Move> Board::GetMoves(glm::ivec2 pos) const {
    return m_Pieces[GetIndex(pos)]->GetMoves(*this, pos);
}
std::vector<Move> Board::GetValidMoves(glm::ivec2 pos) {
    uint32_t team = m_Pieces[GetIndex(pos)]->team;
    std::vector<Move> validMoves;
    std::vector<Move> moves = m_Pieces[GetIndex(pos)]->GetMoves(*this, pos);
    for(Move move : moves) {
        move.Do(*this);
        if(!IsCheck(team)) validMoves.push_back(move);
        move.Undo(*this);
    }
    return validMoves;
}