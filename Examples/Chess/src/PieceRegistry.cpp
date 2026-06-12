#include "PieceRegistry.h"

PieceRegistry::PieceRegistry() {
    m_Pieces.push_back({
        "None",
        [](uint32_t id, uint32_t team){return nullptr; }
    });
}

Piece* PieceRegistry::Create(const uint32_t id, const uint32_t team) const {
    return m_Pieces[id].create(id, team);
}

std::string PieceRegistry::GetName(const uint32_t id) const {
    return m_Pieces[id].name;
}
uint32_t PieceRegistry::GetId(const std::string& name) const {
    for(uint32_t i = 0; i < m_Pieces.size(); i++) {
        if(m_Pieces[i].name == name) return i;
    }
    return 0;
}