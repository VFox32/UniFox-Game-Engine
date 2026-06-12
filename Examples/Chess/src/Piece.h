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

#pragma region Standard
class King : public Piece {
public:
    King(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

class Queen : public Piece {
public:
    Queen(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

class Bishop : public Piece {
public:
    Bishop(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

class Knight : public Piece {
public:
    Knight(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

class Rook : public Piece {
public:
    Rook(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

class Pawn : public Piece {
public:
    Pawn(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};
#pragma endregion

#pragma region Leaper
// 3+1
class Camel : public Piece {
public:
    Camel(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

// 1+0
class Wazir : public Piece {
public:
    Wazir(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

// 1+1
// aka: minister, guard, advisor, general, counsellor
class Ferz : public Piece {
public:
    Ferz(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

// 2+2
// aka: alfil
class Elephant : public Piece {
public:
    Elephant(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

// 2+0
// aka: dabbaba, war engine
class WarMachine : public Piece {
public:
    WarMachine(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

// 3+2
class Zebra : public Piece {
public:
    Zebra(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

// 4+1
class Giraffe : public Piece {
public:
    Giraffe(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

// 4+2
class Stag : public Piece {
public:
    Stag(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

// 4+3
class Antelope : public Piece {
public:
    Antelope(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

// 3+3
class Tripper : public Piece {
public:
    Tripper(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

// 4+4
class Commuter : public Piece {
public:
    Commuter(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

// 3+0
class ThreeLeaper : public Piece {
public:
    ThreeLeaper(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

// 4+0
class FourLeaper : public Piece {
public:
    FourLeaper(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

// blockable knight
// aka: xiangqui horse, horse xiangki
class Horse : public Piece {
public:
    Horse(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};
#pragma endregion

#pragma region Rider
class KnightRider : public Piece {
public:
    KnightRider(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

class CamelRider : public Piece {
public:
    CamelRider(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};
#pragma endregion


#pragma region Locust
// queen
class Grasshopper : public Piece {
public:
    Grasshopper(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};
#pragma endregion

#pragma region Variant
// only straight forward
class Soldier : public Piece {
public:
    Soldier(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

// pawn, only diagonal
class StoneGeneral : public Piece {
public:
    StoneGeneral(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

// pawn, move&capture in all 3 dirs
class Sergeant : public Piece {
public:
    Sergeant(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

// pawn, capture front move diagonal
class Berolina : public Piece {
public:
    Berolina(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};
#pragma endregion

#pragma region Compuond
// Rook + knight
// aka: marshall, empress, hawk, champion
class Chancellor : public Piece {
public:
    Chancellor(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

// bishop + knight
// aka: archbishop, princess, centaur, vizir
class Cardinal : public Piece {
public:
    Cardinal(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

// queen + knight
// aka: dragon
class Amazon : public Piece {
public:
    Amazon(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

// king + knight
// aka: knighted king
class General : public Piece {
public:
    General(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

// knight + camel
// aka: gnu, unicorn
class Wildebeest : public Piece {
public:
    Wildebeest(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

// rook + king
class DragonKing : public Piece {
public:
    DragonKing(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};

// bishop + king
class DragonHorse : public Piece {
public:
    DragonHorse(const uint32_t Id, const uint32_t Team) : Piece(Id, Team) {}
    virtual void GetMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves) const override {GenerateMoves(board, pos, moves);}
    static void GenerateMoves(const Board& board, const glm::ivec2 pos, std::vector<Move>& moves);
};
#pragma endregion