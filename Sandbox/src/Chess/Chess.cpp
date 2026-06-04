#include "Chess.h"
#include "Piece.h"

Chess::Chess() 
    : m_CameraController(16.0 / 9.0, false, 5.0) {
}

void Chess::OnAttach() {
    m_PieceTextures[PieceType::King  ] = UniFox::Texture2D::Create("assets/textures/wk.png");
    m_PieceTextures[PieceType::Queen ] = UniFox::Texture2D::Create("assets/textures/wq.png");
    m_PieceTextures[PieceType::Bishop] = UniFox::Texture2D::Create("assets/textures/wb.png");
    m_PieceTextures[PieceType::Knight] = UniFox::Texture2D::Create("assets/textures/wn.png");
    m_PieceTextures[PieceType::Rook  ] = UniFox::Texture2D::Create("assets/textures/wr.png");
    m_PieceTextures[PieceType::Pawn  ] = UniFox::Texture2D::Create("assets/textures/wp.png");

    m_Teams.push_back(Team({1.0, 1.0, 1.0, 1}));
    m_Teams.push_back(Team({0.2, 0.2, 0.2, 1}));

    m_Board = new Piece[64];
    m_Board[ 0]  = Piece(PieceType::Rook,   0);
    m_Board[ 1]  = Piece(PieceType::Knight, 0);
    m_Board[ 2]  = Piece(PieceType::Bishop, 0);
    m_Board[ 3]  = Piece(PieceType::Queen,  0);
    m_Board[ 4]  = Piece(PieceType::King,   0);
    m_Board[ 5]  = Piece(PieceType::Bishop, 0);
    m_Board[ 6]  = Piece(PieceType::Knight, 0);
    m_Board[ 7]  = Piece(PieceType::Rook,   0);
    m_Board[ 8]  = Piece(PieceType::Pawn,   0);
    m_Board[ 9]  = Piece(PieceType::Pawn,   0);
    m_Board[10]  = Piece(PieceType::Pawn,   0);
    m_Board[11]  = Piece(PieceType::Pawn,   0);
    m_Board[12]  = Piece(PieceType::Pawn,   0);
    m_Board[13]  = Piece(PieceType::Pawn,   0);
    m_Board[14]  = Piece(PieceType::Pawn,   0);
    m_Board[15]  = Piece(PieceType::Pawn,   0);

    m_Board[63]  = Piece(PieceType::Rook,   1);
    m_Board[62]  = Piece(PieceType::Knight, 1);
    m_Board[61]  = Piece(PieceType::Bishop, 1);
    m_Board[60]  = Piece(PieceType::King,   1);
    m_Board[59]  = Piece(PieceType::Queen,  1);
    m_Board[58]  = Piece(PieceType::Bishop, 1);
    m_Board[57]  = Piece(PieceType::Knight, 1);
    m_Board[56]  = Piece(PieceType::Rook,   1);
    m_Board[55]  = Piece(PieceType::Pawn,   1);
    m_Board[54]  = Piece(PieceType::Pawn,   1);
    m_Board[53]  = Piece(PieceType::Pawn,   1);
    m_Board[52]  = Piece(PieceType::Pawn,   1);
    m_Board[51]  = Piece(PieceType::Pawn,   1);
    m_Board[50]  = Piece(PieceType::Pawn,   1);
    m_Board[49]  = Piece(PieceType::Pawn,   1);
    m_Board[48]  = Piece(PieceType::Pawn,   1);
}

void Chess::OnDetach() {

}

void Chess::OnUpdate(UniFox::Duration dt) {
    m_CameraController.OnUpdate(dt);

    UniFox::RenderCommand::SetClearColor({0.5, 0.5, 0.5, 1.0});
    UniFox::RenderCommand::Clear();

    UniFox::Renderer2D::BeginScene(m_CameraController.GetCamera());
    glm::vec4 tint = glm::vec4(1);
    for(float x = 0; x < 8; x++)
    for(float y = 0; y < 8; y++) {
        int i = x + y*8;
        if(moves[i] == 0) tint = glm::vec4(1);
        else tint = glm::vec4(0.1, 0.8, 0.2, 1.0);

        if((int)(x + y) % 2 == 0)
            UniFox::Renderer2D::DrawQuad({x+0.5, y+0.5, 0}, {1, 1}, 0, glm::vec4(0.2, 0.1, 0.05, 1) * tint);
        else {
            UniFox::Renderer2D::DrawQuad({x+0.5, y+0.5, 0}, {1, 1}, 0, glm::vec4(0.4, 0.2, 0.1, 1) * tint);
        }
    }
    for(int i = 0; i < 64; i++) {
        if(m_Board[i].GetType() == PieceType::None) continue;
        if(i == m_Selected) {
            UniFox::Renderer2D::DrawQuad({GetWorldPos().x, GetWorldPos().y, 0.2}, {1.1, 1.1}, 0, m_PieceTextures[m_Board[i].GetType()], m_Teams[m_Board[i].GetTeam()].GetColor());
        } else {
            glm::vec2 pos = glm::vec2(glm::mod((float)i, 8.0f), i / 8);
            UniFox::Renderer2D::DrawQuad({pos.x+0.5, pos.y+0.5, 0.1}, {1, 1}, 0, m_PieceTextures[m_Board[i].GetType()], m_Teams[m_Board[i].GetTeam()].GetColor());
        }
    }
    UniFox::Renderer2D::EndScene();
}

void Chess::OnImGuiRender() {

}

void Chess::OnEvent(UniFox::Event& e) {
    UniFox::EventDispatcher dispatcher(e);

    dispatcher.Dispatch<UniFox::MouseButtonPressedEvent>(UF_BIND_EVENT_FN(OnMouseButtonPressed));
    dispatcher.Dispatch<UniFox::MouseButtonReleasedEvent>(UF_BIND_EVENT_FN(OnMouseButtonReleased));
}

bool Chess::OnMouseButtonPressed(UniFox::MouseButtonPressedEvent& e) {
    if(m_Selected >= 0) return true;

    int pos = GetGridPos();
    if(m_Board[pos].GetType() != PieceType::None) {
        m_Selected = pos;
        moves = Piece::GetMoves(m_Board, pos);
    }

    return true;
}

bool Chess::OnMouseButtonReleased(UniFox::MouseButtonReleasedEvent& e) {
    if(m_Selected < 0) return true;

    int pos = GetGridPos();

    // if current square, skip
    if(pos == m_Selected) {
        m_Selected = -1;
        moves = new int[64] {};
        return true;
    }

    if(moves[pos] == 1) {
        m_Board[pos] = m_Board[m_Selected];
        m_Board[m_Selected] = Piece();
    }
    m_Selected = -1;
    moves = new int[64] {};

    return true;
}