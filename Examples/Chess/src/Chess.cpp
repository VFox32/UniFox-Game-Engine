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
    m_PieceTextures.resize(50);
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
    m_PieceTextures[m_Board.GetId("Soldier")] = UniFox::Texture2D::Create("assets/textures/extended/wverticalmover.png"); //
    m_PieceTextures[m_Board.GetId("StoneGeneral")] = UniFox::Texture2D::Create("assets/textures/extended/wcoppergeneral.png"); //
    m_PieceTextures[m_Board.GetId("Sergeant")] = UniFox::Texture2D::Create("assets/textures/extended/wsergeant.png");
    m_PieceTextures[m_Board.GetId("Wildebeest")] = UniFox::Texture2D::Create("assets/textures/extended/wwildebeest.png");
    m_PieceTextures[m_Board.GetId("Berolina")] = UniFox::Texture2D::Create("assets/textures/extended/wberolinapawn.png");
    m_PieceTextures[m_Board.GetId("Spider")] = UniFox::Texture2D::Create("assets/textures/extended/wspider.png");
}

void Chess::OnDetach() {
}

void Chess::OnUpdate(UniFox::Duration dt) {
    m_CameraController.OnUpdate(dt);

    UniFox::RenderCommand::SetClearColor({0.05, 0.05, 0.05, 1.0});
    UniFox::RenderCommand::Clear();

    UniFox::Renderer2D::BeginScene(m_CameraController.GetCamera());

    UniFox::Renderer2D::DrawQuad({m_Board.GetSize().x / 2, m_Board.GetSize().y / 2, -0.1}, {m_Board.GetSize().x + 0.5, m_Board.GetSize().y + 0.5}, 0, glm::vec4(0.3, 0.15, 0.07, 1.0));

    glm::vec4 tint = glm::vec4(1);
    for(float x = 0; x < m_Board.GetSize().x; x++)
    for(float y = 0; y < m_Board.GetSize().y; y++) {
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

    for(uint64_t i = 0; i < m_Board.GetSize().x*m_Board.GetSize().y; i++) {
        glm::ivec2 coord = m_Board.GetCoord(i);
        if(m_Board.GetPiece(coord) == nullptr) continue;
        if(coord != m_Selected) {
            glm::vec2 pos = glm::vec2(i % m_Board.GetSize().x, i / m_Board.GetSize().x);
            UniFox::Renderer2D::DrawQuad({pos.x+0.5, pos.y+0.5, 0.1}, {1, 1}, 0, m_PieceTextures[m_Board.GetId(pos)], m_Board.GetTeam(m_Board.GetTeam(pos)).color);
        }
    }
    if(m_Board.InBounds(m_Selected)) {
        UniFox::Renderer2D::DrawQuad({GetWorldPos().x, GetWorldPos().y, 0.2}, {1.1, 1.1}, 0, m_PieceTextures[m_Board.GetPiece(m_Selected)->id], m_Board.GetTeam(m_Board.GetTeam(m_Selected)).color);
    }

    if(m_Choice) {
        glm::vec2 pos = (glm::vec2)m_Moves[0].dest + glm::vec2(m_Moves.size() / 2.0, 1);
        UniFox::Renderer2D::DrawQuad({pos.x, pos.y+0.5, 0.5}, {m_Moves.size()+0.5, 1.5}, 0, {0.3, 0.15, 0.07, 1.0});
        tint = glm::vec4(1);
        for(uint32_t i = 0; i < m_Moves.size(); i++) {
            pos = m_Moves[0].dest + glm::ivec2(i, 1);
            if(m_Board.GetGridPos(pos) == m_Board.GetGridPos(GetWorldPos())) {
                tint = {2.0, 4.0, 1.0, 1.0};
            } else {
                tint = {1, 1, 1, 1};
            }
            if((int)(pos.x + pos.y) % 2 == 0)
                UniFox::Renderer2D::DrawQuad({pos.x+0.5, pos.y+0.5, 0.6}, {1, 1}, 0, glm::vec4(0.2, 0.1, 0.05, 1) * tint);
            else {
                UniFox::Renderer2D::DrawQuad({pos.x+0.5, pos.y+0.5, 0.6}, {1, 1}, 0, glm::vec4(0.4, 0.2, 0.1, 1) * tint);
            }
            UniFox::Renderer2D::DrawQuad({pos.x+0.5, pos.y+0.5, 0.7}, {1, 1}, 0, m_PieceTextures[i + 2], m_Board.GetTeam(m_Board.GetTeam(m_Selected)).color);
        }
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
            m_Board.PreviousTurn();

            m_Info = "";
            if(m_Board.IsMate(m_Board.GetTurn())) {
                m_Info = "Checkmate";
            } else if(m_Board.IsCheck(m_Board.GetTurn())) {
                m_Info = "Check";
            }
        }
    }
    if(ImGui::Button("Redo")) {
        if(m_UndoHistory.size() > 0) {
            Move move = m_UndoHistory.back();
            move.Do(m_Board);
            m_History.push_back(move);
            m_UndoHistory.pop_back();
            m_Board.NextTurn();
            
            m_Info = "";
            if(m_Board.IsMate(m_Board.GetTurn())) {
                m_Info = "Checkmate";
            } else if(m_Board.IsCheck(m_Board.GetTurn())) {
                m_Info = "Check";
            }
        }
    }
    if(ImGui::Button("Reset")) {
        m_Board.Reset();
        m_History.clear();
        m_UndoHistory.clear();
        m_Selected = {-1, -1};
        m_Choice = false;
        m_Info = "";
    }
    ImGui::Text("%s's turn", m_Board.GetTeam(m_Board.GetTurn()).name.c_str());
    ImGui::Text("%s", m_Info.c_str());
    ImGui::End();
}

void Chess::OnEvent(UniFox::Event& e) {
    UniFox::EventDispatcher dispatcher(e);
    m_CameraController.OnEvent(e);

    dispatcher.Dispatch<UniFox::MouseButtonPressedEvent>(UF_BIND_EVENT_FN(OnMouseButtonPressed));
    dispatcher.Dispatch<UniFox::MouseButtonReleasedEvent>(UF_BIND_EVENT_FN(OnMouseButtonReleased));
    dispatcher.Dispatch<UniFox::WindowResizeEvent>(UF_BIND_EVENT_FN(OnWindowResize));
}

bool Chess::OnMouseButtonPressed(UniFox::MouseButtonPressedEvent& e) {
    if(m_Choice) {
        glm::ivec2 pos = m_Board.GetGridPos(GetWorldPos());
        for(uint32_t i = 0; i < m_Moves.size(); i++) {
            glm::ivec2 goal = m_Moves[0].dest + glm::ivec2(i, 1);
            if(pos == goal) {
                m_Moves[i].Do(m_Board);
                m_History.push_back(m_Moves[i]);
                m_Board.NextTurn();

                m_Info = "";
                if(m_Board.IsMate(m_Board.GetTurn())) {
                    m_Info = "Checkmate";
                } else if(m_Board.IsCheck(m_Board.GetTurn())) {
                    m_Info = "Check";
                }

                m_Selected = {-1, -1};
                m_Moves.clear();
                break;
            }
        }

        return true;
    }

    if(m_Board.InBounds(m_Selected)) return true;

    glm::ivec2 pos = m_Board.GetGridPos(GetWorldPos());
    if(!m_Board.InBounds(pos)) return false;

    if(m_Board.GetPiece(pos) == nullptr) return true;

    if(m_Board.GetTeam(pos) == m_Board.GetTurn()) {
        m_Selected = pos;

        m_Moves = m_Board.GetValidMoves(pos);
    }

    return true;
}
bool Chess::OnMouseButtonReleased(UniFox::MouseButtonReleasedEvent& e) {
    if(m_Choice) {
        m_Choice = false;
    }
    if(!m_Board.InBounds(m_Selected)) return true;

    glm::ivec2 pos = m_Board.GetGridPos(GetWorldPos());
    if(!m_Board.InBounds(pos)) {
        m_Selected = {-1, -1};
        m_Moves.clear();
        return false;
    }
    
    std::vector<Move> moves;
    for(auto move : m_Moves) {
        if(move.dest == pos) {
            moves.push_back(move);
        }
    }
    if(moves.size() == 1) {
        //UniFox::Buffer buffer = UniFox::Buffer(128);
        //UniFox::MemoryStreamWriter writer = UniFox::MemoryStreamWriter(buffer);
        //writer.WriteObject(moves[0]);
        //Move move;
        //UniFox::MemoryStreamReader reader = UniFox::MemoryStreamReader(buffer);
        //reader.ReadObject(move);
        Move move = moves[0];
        move.Do(m_Board);
        m_History.push_back(move);
        //moves[0].Do(m_Board);
        //m_History.push_back(moves[0]);
        m_Board.NextTurn();

        m_Info = "";
        if(m_Board.IsMate(m_Board.GetTurn())) {
            m_Info = "Checkmate";
        } else if(m_Board.IsCheck(m_Board.GetTurn())) {
            m_Info = "Check";
        }

        m_Selected = {-1, -1};
        m_Moves.clear();
        return true;
    } else {
        m_Moves = moves;
        if(moves.size() > 1) m_Choice = true;
        if(moves.size() == 0) m_Selected = {-1, -1};
        return true;
    }

    return true;
}
bool Chess::OnWindowResize(UniFox::WindowResizeEvent& e) {
    m_WindowSize = {e.GetWidth(), e.GetHeight()};
    return false;
}

glm::vec2 Chess::GetWorldPos() const {
    glm::vec3 pos = glm::vec3(UniFox::Input::GetMouseX() / m_WindowSize.x, 1.0 - UniFox::Input::GetMouseY() / m_WindowSize.y, 0.0) * 2.0f - 1.0f;
    glm::vec4 world = glm::inverse(m_CameraController.GetCamera().GetViewProjectionMatrix()) * glm::vec4(pos, 1.0);
    return {world.x, world.y};
}