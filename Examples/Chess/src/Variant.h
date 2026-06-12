#pragma once
#include "UniFox.h"

#include "Board.h"

class Variant {
public:
    Variant(const uint32_t width, const uint32_t height)
        : m_Width(width), m_Height(height) {}
protected:
    uint32_t m_Width, m_Height;
};

class Standard : public Variant {
public:
    Standard(Board& board)
        : Variant(8, 8) {

        /*m_Pieces = new uint32_t[64] {
            rook, knight, bishop, queen, king, bishop, knight, rook,
            pawn, pawn, pawn, pawn, pawn, pawn, pawn, pawn,
            0, 0, 0, 0, 0, 0, 0, 0,
            7, 8, 9, 10, 11, 12, 13, 14,
            15, 16, 17, 18, 19, 20, 21, 22,
            23, 24, 0, 0, 0, 0, 0, 0,
            pawn, pawn, pawn, pawn, pawn, pawn, pawn, pawn,
            rook, knight, bishop, queen, king, bishop, knight, rook
        };
        m_Teams = new uint32_t[64] {
            1, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            2, 2, 2, 2, 2, 2, 2, 2,
            2, 2, 2, 2, 2, 2, 2, 2
        };*/
    }
private:
    const uint32_t* m_Pieces; 
    const uint32_t* m_Teams; 
};