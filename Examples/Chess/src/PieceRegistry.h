#pragma once
#include "UniFox.h"

#include "Piece.h"

class PieceInfo {
public:
    std::string name;
    std::function<Piece*(uint32_t id, uint32_t team)> create;
};

class PieceRegistry {
public:
    PieceRegistry();

    template<typename T>
    uint32_t Register(const std::string name) {
        uint32_t id = m_Pieces.size();

        m_Pieces.push_back(PieceInfo{
            name,
            [](uint32_t id, uint32_t team){return new T(id, team); }
        });

        return id;
    }

    Piece* Create(const uint32_t id, const uint32_t team) const;

    std::string GetName(const uint32_t id) const;
    uint32_t GetId(const std::string& name) const;
private:
    std::vector<PieceInfo> m_Pieces;
};