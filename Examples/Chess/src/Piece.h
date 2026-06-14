#pragma once
#include "UniFox.h"

#include "Action.h"
class Board;

class Piece {
public:
    ~Piece() = default;
    Piece(const uint32_t Id, const uint32_t Team) : id(Id), team(Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const = 0;
public:
    uint32_t team = 0;
    uint32_t id = 0;
    uint32_t moves = 0;
    glm::ivec2 dist = {0, 0};
protected:
    static bool CanMove(const Board& board, const glm::ivec2 pos);
    static bool CanCapture(const Board& board, const glm::ivec2 pos, uint32_t team);

    static void Slide(const Board& board, const glm::ivec2 pos, const glm::ivec2 dir, std::vector<Move>& moves);
    static void Jump(const Board& board, const glm::ivec2 pos, const glm::ivec2 dir, std::vector<Move>& moves);
    static void Locust(const Board& board, const glm::ivec2 pos, const glm::ivec2 dir, std::vector<Move>& moves);

    static void Slide(const Board& board, const glm::ivec2 pos, const std::vector<glm::ivec2> dirs, std::vector<Move>& moves);
    static void Jump(const Board& board, const glm::ivec2 pos, const std::vector<glm::ivec2> dirs, std::vector<Move>& moves);
    static void Locust(const Board& board, const glm::ivec2 pos, std::vector<glm::ivec2> dirs, std::vector<Move>& moves);

    static std::vector<Move> Combine(const std::vector<Move> A, const std::vector<Move> B);
};



#define piece(name) class name : public Piece { \
public: \
    name(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {} \
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);} \
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves); \
}

#pragma region Standard
piece(King);

piece(Queen);

piece(Bishop);

piece(Knight);

piece(Rook);

piece(Pawn);
#pragma endregion

#pragma region Leaper
// 3+1
piece(Camel);

// 1+0
piece(Wazir);

// 1+1
piece(Ferz); // aka: minister, guard, advisor, general, counsellor

// 2+2
piece(Elephant); // aka: alfil

// 2+0
piece(WarMachine); // aka: dabbaba, war engine

// 3+2
piece(Zebra);

// 4+1
piece(Giraffe);

// 4+2
piece(Stag);

// 4+3
piece(Antelope);

// 3+3
piece(Tripper);

// 4+4
piece(Commuter);

// 3+0
piece(ThreeLeaper);

// 4+0
piece(FourLeaper);

// blockable knight
piece(Horse); // aka: xiangqui horse, horse xiangki
#pragma endregion

#pragma region Rider
piece(KnightRider);

piece(CamelRider);
#pragma endregion


#pragma region Locust
// queen
piece(Grasshopper);
#pragma endregion

#pragma region Variant
// only straight forward
piece(Soldier);

// pawn, only diagonal
piece(StoneGeneral);

// pawn, move&capture in all 3 dirs
piece(Sergeant);

// pawn, capture front move diagonal
piece(Berolina);
#pragma endregion

#pragma region Compuond
// Rook + knight
piece(Chancellor); // aka: marshall, empress, hawk, champion

// bishop + knight
piece(Cardinal); // aka: archbishop, princess, centaur, vizir

// queen + knight
piece(Amazon); // aka: dragon

// king + knight
piece(General); // aka: knighted king

// knight + camel
piece(Wildebeest); // aka: gnu, unicorn

// rook + king
piece(DragonKing);

// bishop + king
piece(DragonHorse);

// ferz + war machine
piece(Spider);
#pragma endregion