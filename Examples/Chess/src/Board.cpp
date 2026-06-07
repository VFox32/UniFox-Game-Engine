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
glm::vec2 Board::GetWorldPos() {
    glm::vec3 pos = glm::vec3(UniFox::Input::GetMouseX() / 1280, 1.0 - UniFox::Input::GetMouseY() / 720, 0.0) * 2.0f - 1.0f;
    glm::vec4 world = mat * glm::vec4(pos, 1.0);
    return {world.x, world.y};
}
glm::ivec2 Board::GetGridPos() {
    glm::vec2 pos = GetWorldPos();
    glm::ivec2 grid = {floor(pos.x), floor(pos.y)};
    return grid;
}

Board::Board() {
    m_PieceTextures[PieceType::King  ] = UniFox::Texture2D::Create("assets/textures/wk.png");
    m_PieceTextures[PieceType::Queen ] = UniFox::Texture2D::Create("assets/textures/wq.png");
    m_PieceTextures[PieceType::Bishop] = UniFox::Texture2D::Create("assets/textures/wb.png");
    m_PieceTextures[PieceType::Knight] = UniFox::Texture2D::Create("assets/textures/wn.png");
    m_PieceTextures[PieceType::Rook  ] = UniFox::Texture2D::Create("assets/textures/wr.png");
    m_PieceTextures[PieceType::Pawn  ] = UniFox::Texture2D::Create("assets/textures/wp.png");

    m_Teams.push_back(Team("None", {0.5, 0.5, 0.5}));
    m_Teams.push_back(Team("VFox", {0.8, 0.8, 0.8}));
    m_Teams.push_back(Team("54p_", {0.2, 0.2, 0.2}));

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
void Board::SetPiece(const glm::ivec2 pos, Piece* piece) {
    uint32_t index = pos.x + pos.y*8;
    m_Pieces[index] = piece;
}

void Board::OnRender(glm::mat4 matrix) {
    mat = glm::inverse(matrix);

    UniFox::Renderer2D::DrawQuad({4.0, 4.0, -0.1}, {8.5, 8.5}, 0, glm::vec4(0.3, 0.15, 0.07, 1.0));

    glm::vec4 tint = glm::vec4(1);
    for(float x = 0; x < 8; x++)
    for(float y = 0; y < 8; y++) {
        tint = glm::vec4(1);
        for(auto move : m_Moves) {
            if(move.dest == glm::ivec2(x, y)) {
                tint = glm::vec4(0.1, 0.8, 0.2, 1.0);
                break;
            }
        }

        if((int)(x + y) % 2 == 0)
            UniFox::Renderer2D::DrawQuad({x+0.5, y+0.5, 0}, {1, 1}, 0, glm::vec4(0.2, 0.1, 0.05, 1) * tint);
        else {
            UniFox::Renderer2D::DrawQuad({x+0.5, y+0.5, 0}, {1, 1}, 0, glm::vec4(0.4, 0.2, 0.1, 1) * tint);
        }
    }

    for(uint64_t i = 0; i < 64; i++) {
        if(m_Pieces[i] == nullptr) continue;
        if(i != m_Selected) {
            glm::vec2 pos = glm::vec2(i % 8, i / 8);
            UniFox::Renderer2D::DrawQuad({pos.x+0.5, pos.y+0.5, 0.1}, {1, 1}, 0, m_PieceTextures[m_Pieces[i]->type], {m_Teams[m_Pieces[i]->team].color, 1.0});
        }
    }
    if(m_Selected >= 0) {
        UniFox::Renderer2D::DrawQuad({GetWorldPos().x, GetWorldPos().y, 0.2}, {1.1, 1.1}, 0, m_PieceTextures[m_Pieces[m_Selected]->type], {m_Teams[m_Pieces[m_Selected]->team].color, 1.0});
    }
}

void Board::OnEvent(UniFox::Event& e) {
    UniFox::EventDispatcher dispatcher(e);

    dispatcher.Dispatch<UniFox::MouseButtonPressedEvent>(UF_BIND_EVENT_FN(OnMouseButtonPressed));
    dispatcher.Dispatch<UniFox::MouseButtonReleasedEvent>(UF_BIND_EVENT_FN(OnMouseButtonReleased));
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

bool Board::OnMouseButtonPressed(UniFox::MouseButtonPressedEvent& e) {
    if(m_Selected >= 0) return true;

    glm::ivec2 pos = GetGridPos();
    if(pos.x < 0 || pos.x > 7 || pos.y < 0 || pos.y > 7) return false;

    if(m_Pieces[GetIndex(pos)] == nullptr) return true;
    if(GetTeam(pos) == m_Turn + 1) {
        m_Selected = GetIndex(pos);
        m_Moves.clear();
        std::vector<Move> protoMove = m_Pieces[m_Selected]->GetMoves(*this, pos);

        for(Move move : protoMove) {
            move.Do(*this);

            glm::ivec2 kingPos = FindPiece(PieceType::King, m_Turn + 1)[0];
            if(IsSquareSafe(kingPos, m_Turn + 1)) m_Moves.push_back(move);

            move.Undo(*this);
        }
    }

    return true;
}

bool Board::OnMouseButtonReleased(UniFox::MouseButtonReleasedEvent& e) {
    if(m_Selected < 0) return true;

    glm::ivec2 pos = GetGridPos();
    if(pos.x < 0 || pos.x > 7 || pos.y < 0 || pos.y > 7) return false;

    for(auto move : m_Moves) {
        if(move.dest == pos) {
            move.Do(*this);
            m_History.push_back(move);
            m_UndoHistory.clear();
            m_Turn = (m_Turn + 1) % 2;
            m_Info = "";

            glm::ivec2 kingPos = FindPiece(PieceType::King, m_Turn + 1)[0];
            if(!IsSquareSafe(kingPos, m_Turn + 1))m_Info = "Check";

            bool mate = true;
            for(int i = 0; i < 64 && mate; i++) {
                if(m_Pieces[i] &&
                    m_Pieces[i]->team == m_Turn + 1) {
                    std::vector<Move> moves = m_Pieces[i]->GetMoves(*this, GetCoord(i));
                    for(auto move : moves) {
                        move.Do(*this);

                        kingPos = FindPiece(PieceType::King, m_Turn + 1)[0];
                        if(IsSquareSafe(kingPos, m_Turn + 1)) mate = false;

                        move.Undo(*this);
                        if(!mate) break;
                    }
                }
            }
            if(mate) m_Info = "Checkmate";

            break;
        }
    }

    m_Selected = -1;
    m_Moves.clear();

    return true;
}

void Board::OnImguiRender() {
    ImGui::Begin("Chess");
    if(ImGui::Button("Undo")) {
        if(m_History.size() > 0) {
            Move move = m_History.back();
            move.Undo(*this);
            m_UndoHistory.push_back(move);
            m_History.pop_back();
            m_Turn = (m_Turn+1) % 2;
        }
    }
    if(ImGui::Button("Redo")) {
        if(m_UndoHistory.size() > 0) {
            Move move = m_UndoHistory.back();
            move.Do(*this);
            m_History.push_back(move);
            m_UndoHistory.pop_back();
            m_Turn = (m_Turn+1) % 2;
        }
    }
    if(ImGui::Button("Reset")) {
        while(m_History.size() > 0) {
            Move move = m_History.back();
            move.Undo(*this);
            m_History.pop_back();
        }
        m_History.clear();
        m_UndoHistory.clear();
        m_Turn = 0;
    }
    ImGui::Text("%s's turn", m_Teams[m_Turn + 1].name.c_str());
    ImGui::Text("%s", m_Info.c_str());
    ImGui::End();
}