#include "Board.h"

Board::Board() {
    m_PieceTextures[PieceType::King  ] = UniFox::Texture2D::Create("assets/textures/wk.png");
    m_PieceTextures[PieceType::Queen ] = UniFox::Texture2D::Create("assets/textures/wq.png");
    m_PieceTextures[PieceType::Bishop] = UniFox::Texture2D::Create("assets/textures/wb.png");
    m_PieceTextures[PieceType::Knight] = UniFox::Texture2D::Create("assets/textures/wn.png");
    m_PieceTextures[PieceType::Rook  ] = UniFox::Texture2D::Create("assets/textures/wr.png");
    m_PieceTextures[PieceType::Pawn  ] = UniFox::Texture2D::Create("assets/textures/wp.png");

    AddPiece(PieceType::Rook,    0, 0);
    AddPiece(PieceType::Knight,  1, 0);
    AddPiece(PieceType::Bishop,  2, 0);
    AddPiece(PieceType::Queen,   3, 0);
    AddPiece(PieceType::King,    4, 0);
    AddPiece(PieceType::Bishop,  5, 0);
    AddPiece(PieceType::Knight,  6, 0);
    AddPiece(PieceType::Rook,    7, 0);
    AddPiece(PieceType::Pawn,    8, 0);
    AddPiece(PieceType::Pawn,    9, 0);
    AddPiece(PieceType::Pawn,   10, 0);
    AddPiece(PieceType::Pawn,   11, 0);
    AddPiece(PieceType::Pawn,   12, 0);
    AddPiece(PieceType::Pawn,   13, 0);
    AddPiece(PieceType::Pawn,   14, 0);
    AddPiece(PieceType::Pawn,   15, 0);

    AddPiece(PieceType::Rook,   63, 1);
    AddPiece(PieceType::Knight, 62, 1);
    AddPiece(PieceType::Bishop, 61, 1);
    AddPiece(PieceType::King,   60, 1);
    AddPiece(PieceType::Queen,  59, 1);
    AddPiece(PieceType::Bishop, 58, 1);
    AddPiece(PieceType::Knight, 57, 1);
    AddPiece(PieceType::Rook,   56, 1);
    AddPiece(PieceType::Pawn,   55, 1);
    AddPiece(PieceType::Pawn,   54, 1);
    AddPiece(PieceType::Pawn,   53, 1);
    AddPiece(PieceType::Pawn,   52, 1);
    AddPiece(PieceType::Pawn,   51, 1);
    AddPiece(PieceType::Pawn,   50, 1);
    AddPiece(PieceType::Pawn,   49, 1);
    AddPiece(PieceType::Pawn,   48, 1);
}

void Board::OnRender(glm::mat4 matrix) {
    mat = glm::inverse(matrix);

    UniFox::Renderer2D::DrawQuad({4.0, 4.0, -0.1}, {8.5, 8.5}, 0, glm::vec4(0.3, 0.15, 0.07, 1.0));

    glm::vec4 tint = glm::vec4(1);
    for(float x = 0; x < 8; x++)
    for(float y = 0; y < 8; y++) {
        uint64_t i = x + y*8;
        if((m_Moves & (1ULL << i)) == 0) tint = glm::vec4(1);
        else tint = glm::vec4(0.1, 0.8, 0.2, 1.0);

        if((int)(x + y) % 2 == 0)
            UniFox::Renderer2D::DrawQuad({x+0.5, y+0.5, 0}, {1, 1}, 0, glm::vec4(0.2, 0.1, 0.05, 1) * tint);
        else {
            UniFox::Renderer2D::DrawQuad({x+0.5, y+0.5, 0}, {1, 1}, 0, glm::vec4(0.4, 0.2, 0.1, 1) * tint);
        }
    }

    for(uint64_t i = 0; i < 64; i++) {
        if(m_Pieces[i] == PieceType::None) continue;
        if(m_MaskWhite & (1ULL << i)) tint = glm::vec4(0.8, 0.8, 0.8, 1.0);
        else tint = glm::vec4(0.2, 0.2, 0.2, 1.0);
        if(i != m_Selected) {
            glm::vec2 pos = glm::vec2(i % 8, i / 8);
            UniFox::Renderer2D::DrawQuad({pos.x+0.5, pos.y+0.5, 0.1}, {1, 1}, 0, m_PieceTextures[m_Pieces[i]], tint);
        }
    }
    if(m_Selected >= 0) {
        if(m_MaskWhite & (1ULL << m_Selected)) tint = glm::vec4(0.8, 0.8, 0.8, 1.0);
        else tint = glm::vec4(0.2, 0.2, 0.2, 1.0);
        UniFox::Renderer2D::DrawQuad({GetWorldPos().x, GetWorldPos().y, 0.2}, {1.1, 1.1}, 0, m_PieceTextures[m_Pieces[m_Selected]], tint);
    }
}

void Board::OnEvent(UniFox::Event& e) {
    UniFox::EventDispatcher dispatcher(e);

    dispatcher.Dispatch<UniFox::MouseButtonPressedEvent>(UF_BIND_EVENT_FN(OnMouseButtonPressed));
    dispatcher.Dispatch<UniFox::MouseButtonReleasedEvent>(UF_BIND_EVENT_FN(OnMouseButtonReleased));
}

bool Board::OnMouseButtonPressed(UniFox::MouseButtonPressedEvent& e) {
    if(m_Selected >= 0) return true;

    uint64_t pos = GetGridPos();
    if(GetTeam(pos) == m_Turn+1) {
        m_Selected = pos;
        m_Moves = GetMoves(pos);
    }
    return true;
}

bool Board::OnMouseButtonReleased(UniFox::MouseButtonReleasedEvent& e) {
    if(m_Selected < 0) return true;

    uint64_t pos = GetGridPos();

    // if current square, skip
    if(pos == m_Selected) {
        m_Selected = -1;
        m_Moves = 0;
        return true;
    }

    if(m_Moves & (1ULL << pos)) {
        m_Pieces[pos] = m_Pieces[m_Selected];
        m_Pieces[m_Selected] = PieceType::None;
        uint64_t maskOld = 1ULL << m_Selected;
        uint64_t maskNew = 1ULL << pos;
        if(m_MaskWhite & maskOld) {
            m_MaskWhite ^= maskOld;
            m_MaskWhite |= maskNew;
            m_MaskBlack &= ~maskNew;
        } else {
            m_MaskBlack ^= maskOld;
            m_MaskBlack |= maskNew;
            m_MaskWhite &= ~maskNew;
        }
        m_Turn = (m_Turn + 1) % 2;
    }
    m_Selected = -1;
    m_Moves = 0;

    return true;
}