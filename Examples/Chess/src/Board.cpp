#include "Board.h"

#include "Piece.h"
#include "Action.h"

#include "imgui.h"

Board::Board() {
    m_Teams.push_back(Team("None", {0.5, 0.5, 0.5, 1.0}, {0, 0}));
    m_Teams.push_back(Team("VFox", {0.8, 0.8, 0.8, 1.0}, {0, 1}));
    m_Teams.push_back(Team("54p_", {0.2, 0.2, 0.2, 1.0}, {0,-1}));

    m_Size = {8, 8};

    uint32_t kingId = m_Registry.Register<King>("King");
    uint32_t queenId = m_Registry.Register<Queen>("Queen");
    uint32_t bishopId = m_Registry.Register<Bishop>("Bishop");
    uint32_t knightId = m_Registry.Register<Knight>("Knight");
    uint32_t rookId = m_Registry.Register<Rook>("Rook");
    uint32_t pawnId = m_Registry.Register<Pawn>("Pawn");

    m_Registry.Register<Camel>("Camel");
    m_Registry.Register<Chancellor>("Chancellor");
    m_Registry.Register<Cardinal>("Cardinal");
    m_Registry.Register<Amazon>("Amazon");
    m_Registry.Register<Grasshopper>("Grasshopper");
    m_Registry.Register<KnightRider>("KnightRider");
    m_Registry.Register<CamelRider>("CamelRider");
    m_Registry.Register<Wazir>("Wazir");
    m_Registry.Register<Ferz>("Ferz");
    m_Registry.Register<Elephant>("Elephant");
    m_Registry.Register<WarMachine>("WarMachine");
    m_Registry.Register<Horse>("Horse");
    m_Registry.Register<General>("General");
    m_Registry.Register<Soldier>("Soldier");
    m_Registry.Register<StoneGeneral>("StoneGeneral");
    m_Registry.Register<Sergeant>("Sergeant");
    m_Registry.Register<Wildebeest>("Wildebeest");
    m_Registry.Register<Berolina>("Berolina");
    m_Registry.Register<Spider>("Spider");

    Reset();
}

void Board::Reset(const uint32_t* pieces, const uint32_t* teams) {
    m_Turn = 1;

    uint32_t king = m_Registry.GetId("King");
    uint32_t queen = m_Registry.GetId("Queen");
    uint32_t bishop = m_Registry.GetId("Bishop");
    uint32_t knight = m_Registry.GetId("Knight");
    uint32_t rook = m_Registry.GetId("Rook");
    uint32_t pawn = m_Registry.GetId("Pawn");
    uint32_t camel = m_Registry.GetId("Camel");

    pieces = new uint32_t[m_Size.x*m_Size.y] {
        rook, knight, bishop, queen, king, bishop, knight, rook,
        pawn, pawn, pawn, pawn, pawn, pawn, pawn, pawn,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        pawn, pawn, pawn, pawn, pawn, pawn, pawn, pawn,
        rook, knight, bishop, queen, king, bishop, knight, rook
    };
    teams = new uint32_t[m_Size.x*m_Size.y] {
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2
    };
    /*pieces = new uint32_t[m_Size.x*m_Size.y] {
        rook, knight, bishop, queen, king, bishop, knight, rook,
        pawn, pawn, pawn, pawn, pawn, pawn, pawn, pawn,
        7, 8, 9, 10, 11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22,
        23, 24, 25, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        pawn, pawn, pawn, pawn, pawn, pawn, pawn, pawn,
        rook, knight, bishop, queen, king, bishop, knight, rook
    };
    teams = new uint32_t[m_Size.x*m_Size.y] {
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0,
        2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2
    };*/

    m_Pieces = new UniFox::Ref<Piece>[m_Size.x*m_Size.y];

    for(uint32_t i = 0; i < m_Size.x*m_Size.y; i++) {
        if(pieces[i] == 0) {
            m_Pieces[i] = nullptr;
        } else {
            m_Pieces[i] = m_Registry.Create(pieces[i], teams[i]);
        }
    }
}
void Board::AddPiece(const uint32_t id, const glm::ivec2 pos, const uint32_t team) {
    uint32_t i = GetIndex(pos);
    m_Pieces[i] = m_Registry.Create(id, team);
}
void Board::SetPiece(const glm::ivec2 pos, const UniFox::Ref<Piece> piece) {
    uint32_t index = pos.x + pos.y*m_Size.x;
    m_Pieces[index] = piece;
}

UniFox::Ref<Piece> Board::CreatePiece(const std::string& name, const uint32_t team) const {
    return m_Registry.Create(GetId(name), team);
}

bool Board::InBounds(const glm::ivec2 pos) const {
    return (pos.x >= 0 && pos.x < m_Size.x && pos.y >= 0 && pos.y < m_Size.y);
}
bool Board::IsSquareSafe(const glm::ivec2 pos, const uint32_t team) const {
    std::vector<Move> moves;
    for(int i = 0; i < m_Size.x*m_Size.y; i++) {
        if(m_Pieces[i] &&
            m_Pieces[i]->team != team) {
            moves.clear();
            m_Pieces[i]->GetMoves(*this, GetCoord(i), moves);
            for(auto move : moves) {
                if(move.dest == pos) return false;
            }
        }
    }
    return true;
}
bool Board::IsCheck(const uint32_t team) const {
    std::vector<glm::ivec2> kingPos = FindPiece(m_Registry.GetId("King"), team);
    if(kingPos.size() == 0) return false;
    return !IsSquareSafe(kingPos[0], team);
}
bool Board::IsMate(const uint32_t team) {
    for(int i = 0; i < m_Size.x*m_Size.y; i++) {
        if(m_Pieces[i] &&
            m_Pieces[i]->team == team) {
            std::vector<Move> moves;
            m_Pieces[i]->GetMoves(*this, GetCoord(i), moves);
            for(auto move : moves) {
                move.Do(*this);

                if(!IsCheck(team)) {
                    move.Undo(*this);
                    return false;
                }
                
                move.Undo(*this);
            }
        }
    }
    return true;
}

std::vector<glm::ivec2> Board::FindPiece(const uint32_t id, const uint32_t team) const {
    std::vector<glm::ivec2> coords;
    for(int i = 0; i < m_Size.x*m_Size.y; i++) {
        if(m_Pieces[i] &&
            m_Pieces[i]->team == team &&
            m_Pieces[i]->id == id) {
                coords.push_back(GetCoord(i));
        }
    }
    return coords;
}
std::vector<Move> Board::GetMoves(const glm::ivec2 pos) const {
    std::vector<Move> moves;
    m_Pieces[GetIndex(pos)]->GetMoves(*this, pos, moves);
    return moves;
}
std::vector<Move> Board::GetValidMoves(const glm::ivec2 pos) {
    uint32_t team = m_Pieces[GetIndex(pos)]->team;
    std::vector<Move> validMoves;
    std::vector<Move> moves;
    uint32_t id = GetId(pos);
    m_Pieces[GetIndex(pos)]->GetMoves(*this, pos, moves);
    for(Move move : moves) {
        move.Do(*this);
        if(!IsCheck(team)) validMoves.push_back(move);
        move.Undo(*this);
    }
    return validMoves;
}

void Board::SetTurn(const uint32_t turn) {
    m_Turn = turn;
}
void Board::NextTurn() {
    m_Turn = m_Turn % (m_Teams.size() - 1) + 1;
}
void Board::PreviousTurn() {
    m_Turn = (m_Turn + (m_Teams.size() - 3)) % (m_Teams.size() - 1) + 1;
}

uint32_t Board::GetId(const std::string name) const {
    return m_Registry.GetId(name);
}

UniFox::Ref<Piece>* Board::GetPieces() const {
    return m_Pieces;
}
UniFox::Ref<Piece> Board::GetPiece(const glm::ivec2 pos) const {
    uint32_t index = pos.x + pos.y*m_Size.x;
    return m_Pieces[index];
}
uint32_t Board::GetTeam(const glm::ivec2 pos) const {
    uint32_t i = GetIndex(pos);
    if(m_Pieces[i]) {        
        return m_Pieces[i]->team;
    }
    return 0;
}
uint32_t Board::GetId(const glm::ivec2 pos) const {
    uint32_t i = GetIndex(pos);
    if(m_Pieces[i])
        return m_Pieces[i]->id;
    else
        return 0;
}

glm::ivec2 Board::GetSize() const {
    return m_Size;
}
uint32_t Board::GetTurn() const {
    return m_Turn;
}
Team Board::GetTeam(uint32_t i) const {
    return m_Teams[i];
}

uint32_t Board::GetIndex(const glm::ivec2 pos) const {
    return pos.x + pos.y*m_Size.x;
}
glm::ivec2 Board::GetCoord(const uint32_t pos) const {
    return {pos % m_Size.x, pos / m_Size.x};
}
glm::ivec2 Board::GetGridPos(const glm::vec2 pos) const {
    glm::ivec2 grid = {floor(pos.x), floor(pos.y)};
    return grid;
}