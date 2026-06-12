#include "Chess.h"

#include "imgui.h"

#include "Board.h"
#include "Piece.h"
#include "Action.h"
#include "Team.h"

Chess::Chess() 
    : m_CameraController(16.0 / 9.0, false, 5.0) {
}

void Chess::OnAttach() {
    m_PieceTextures.resize(25);
    m_PieceTextures[0] = UniFox::Texture2D::Create(0, 0, 0);
    m_PieceTextures[m_Board.GetId("King")] = UniFox::Texture2D::Create("assets/textures/extended/wking.png");
    m_PieceTextures[m_Board.GetId("Queen")] = UniFox::Texture2D::Create("assets/textures/extended/wqueen.png");
    m_PieceTextures[m_Board.GetId("Bishop")] = UniFox::Texture2D::Create("assets/textures/extended/wbishop.png");
    m_PieceTextures[m_Board.GetId("Knight")] = UniFox::Texture2D::Create("assets/textures/extended/wknight.png");
    m_PieceTextures[m_Board.GetId("Rook")] = UniFox::Texture2D::Create("assets/textures/extended/wrook.png");
    m_PieceTextures[m_Board.GetId("Pawn")] = UniFox::Texture2D::Create("assets/textures/extended/wpawn.png");
    
    m_PieceTextures[m_Board.GetId("Camel")] = UniFox::Texture2D::Create("assets/textures/extended/wcamel.png");
    m_PieceTextures[m_Board.GetId("Chancellor")] = UniFox::Texture2D::Create("assets/textures/extended/wchancellor.png");
    m_PieceTextures[m_Board.GetId("Cardinal")] = UniFox::Texture2D::Create("assets/textures/extended/wcardinal.png");
    m_PieceTextures[m_Board.GetId("Amazon")] = UniFox::Texture2D::Create("assets/textures/extended/wamazon.png");
    m_PieceTextures[m_Board.GetId("Grasshopper")] = UniFox::Texture2D::Create("assets/textures/extended/wgrasshopper.png");
    m_PieceTextures[m_Board.GetId("KnightRider")] = UniFox::Texture2D::Create("assets/textures/extended/wnightrider.png");
    m_PieceTextures[m_Board.GetId("CamelRider")] = UniFox::Texture2D::Create("assets/textures/extended/wcamelrider.png");
    m_PieceTextures[m_Board.GetId("Wazir")] = UniFox::Texture2D::Create("assets/textures/extended/wwazir.png");
    m_PieceTextures[m_Board.GetId("Ferz")] = UniFox::Texture2D::Create("assets/textures/extended/wferz.png");
    m_PieceTextures[m_Board.GetId("Elephant")] = UniFox::Texture2D::Create("assets/textures/extended/welephant.png");
    m_PieceTextures[m_Board.GetId("WarMachine")] = UniFox::Texture2D::Create("assets/textures/extended/wwarmachine.png");
    m_PieceTextures[m_Board.GetId("Horse")] = UniFox::Texture2D::Create("assets/textures/extended/whorse.png");
    m_PieceTextures[m_Board.GetId("General")] = UniFox::Texture2D::Create("assets/textures/extended/wgeneral.png");
    m_PieceTextures[m_Board.GetId("Soldier")] = UniFox::Texture2D::Create("assets/textures/extended/wcannon.png"); //
    m_PieceTextures[m_Board.GetId("StoneGeneral")] = UniFox::Texture2D::Create("assets/textures/extended/wcannon.png"); //
    m_PieceTextures[m_Board.GetId("Sergeant")] = UniFox::Texture2D::Create("assets/textures/extended/wsergeant.png");
    m_PieceTextures[m_Board.GetId("Wildebeest")] = UniFox::Texture2D::Create("assets/textures/extended/wwildebeest.png");
    m_PieceTextures[m_Board.GetId("Berolina")] = UniFox::Texture2D::Create("assets/textures/extended/wberolinapawn.png");

    m_Teams.push_back(Team("None", {0.5, 0.5, 0.5}));
    m_Teams.push_back(Team("VFox", {0.8, 0.8, 0.8}));
    m_Teams.push_back(Team("54p_", {0.2, 0.2, 0.2}));
}

void Chess::OnDetach() {
    m_Moves.clear();
    m_Teams.clear();
    m_History.clear();
    m_UndoHistory.clear();
    m_PieceTextures.clear();
}

void Chess::OnUpdate(UniFox::Duration dt) {
    m_CameraController.OnUpdate(dt);

    UniFox::RenderCommand::SetClearColor({0.05, 0.05, 0.05, 1.0});
    UniFox::RenderCommand::Clear();

    UniFox::Renderer2D::BeginScene(m_CameraController.GetCamera());

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
        if(m_Board.GetPiece(i) == nullptr) continue;
        if(i != m_Selected) {
            glm::vec2 pos = glm::vec2(i % 8, i / 8);
            UniFox::Renderer2D::DrawQuad({pos.x+0.5, pos.y+0.5, 0.1}, {1, 1}, 0, m_PieceTextures[m_Board.GetPiece(i)->id], {m_Teams[m_Board.GetPiece(i)->team].color, 1.0});
        }
    }
    if(m_Selected >= 0) {
        UniFox::Renderer2D::DrawQuad({GetWorldPos().x, GetWorldPos().y, 0.2}, {1.1, 1.1}, 0, m_PieceTextures[m_Board.GetPiece(m_Selected)->id], {m_Teams[m_Board.GetPiece(m_Selected)->team].color, 1.0});
    }

    UniFox::Renderer2D::EndScene();
}

void Chess::OnImGuiRender() {
    ImGui::Begin("Chess");
    if(ImGui::Button("Undo")) {
        if(m_History.size() > 0) {
            Move move = m_History.back();
            move.Undo(m_Board);
            m_UndoHistory.push_back(move);
            m_History.pop_back();
            m_Turn = (m_Turn+1) % 2;
        }
    }
    if(ImGui::Button("Redo")) {
        if(m_UndoHistory.size() > 0) {
            Move move = m_UndoHistory.back();
            move.Do(m_Board);
            m_History.push_back(move);
            m_UndoHistory.pop_back();
            m_Turn = (m_Turn+1) % 2;
        }
    }
    if(ImGui::Button("Reset")) {
        while(m_History.size() > 0) {
            Move move = m_History.back();
            move.Undo(m_Board);
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

void Chess::OnEvent(UniFox::Event& e) {
    UniFox::EventDispatcher dispatcher(e);

    dispatcher.Dispatch<UniFox::MouseButtonPressedEvent>(UF_BIND_EVENT_FN(OnMouseButtonPressed));
    dispatcher.Dispatch<UniFox::MouseButtonReleasedEvent>(UF_BIND_EVENT_FN(OnMouseButtonReleased));
}

bool Chess::OnMouseButtonPressed(UniFox::MouseButtonPressedEvent& e) {
    if(m_Selected >= 0) return true;

    glm::ivec2 pos = m_Board.GetGridPos(GetWorldPos());
    if(pos.x < 0 || pos.x > 7 || pos.y < 0 || pos.y > 7) return false;

    if(m_Board.GetPiece(pos) == nullptr) return true;

    if(m_Board.GetTeam(pos) == m_Turn + 1) {
        m_Selected = m_Board.GetIndex(pos);

        m_Moves = m_Board.GetValidMoves(pos);
    }

    return true;
}
bool Chess::OnMouseButtonReleased(UniFox::MouseButtonReleasedEvent& e) {
    if(m_Selected < 0) return true;

    glm::ivec2 pos = m_Board.GetGridPos(GetWorldPos());
    if(pos.x < 0 || pos.x > 7 || pos.y < 0 || pos.y > 7) {
        m_Selected = -1;
        m_Moves.clear();
        return false;
    }
    
    for(auto move : m_Moves) {
        if(move.dest == pos) {
            move.Do(m_Board);
            m_History.push_back(move);
            m_Turn = (m_Turn + 1) % 2;

            m_Info = "";
            if(m_Board.IsMate(m_Turn + 1)) {
                m_Info = "Checkmate";
            } else if(m_Board.IsCheck(m_Turn + 1)) {
                m_Info = "Check";
            }

            break;
        }
    }

    m_Selected = -1;
    m_Moves.clear();

    return true;
}

glm::vec2 Chess::GetWorldPos() const {
    glm::vec3 pos = glm::vec3(UniFox::Input::GetMouseX() / 1280, 1.0 - UniFox::Input::GetMouseY() / 720, 0.0) * 2.0f - 1.0f;
    glm::vec4 world = glm::inverse(m_CameraController.GetCamera().GetViewProjectionMatrix()) * glm::vec4(pos, 1.0);
    return {world.x, world.y};
}