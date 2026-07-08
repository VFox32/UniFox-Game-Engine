#include "GUI.h"
#include "ufpch.h"

#include "imgui.h"

GUI::GUI()
    : m_CameraController(16.0 / 9.0, false, 5.0) {
}

void GUI::OnAttach() {
    UniFox::Ref<Style> style1 = UniFox::MakeRef<Style>(glm::vec4(0.8, 0.2, 0.2, 1.0), glm::vec4(0.2, 0.2, 0.8, 1.0));
    UniFox::Ref<Style> style2 = UniFox::MakeRef<Style>(glm::vec4(0.2, 0.8, 0.2, 1.0), glm::vec4(0.2, 0.2, 0.2, 1.0));

    m_Container = UniFox::MakeRef<VerticalPanel>();
    m_Container->SetStyle(style1);
    VerticalPanel* panel = dynamic_cast<VerticalPanel*>(m_Container.get());
    panel->SetPadding({0.1, 0.1, 0.1, 0.1});
    panel->SetMargin({0.1, 0.1, 0.1, 0.1});

    UniFox::Ref<Widget> button1 = UniFox::MakeRef<Button>(LayoutProperty{
        Length(LengthMode::Pixels, 2.5f),
        Length(LengthMode::Pixels, 1.0f)
    });
    button1->SetStyle(style1);
    m_Container->AddChild(button1);
    UniFox::Ref<Widget> button2 = UniFox::MakeRef<Button>(LayoutProperty{
        Length(LengthMode::Pixels, 2.0f),
        Length(LengthMode::Ratio, 0.2f)
    });
    button2->SetStyle(style1);
    //m_Container->AddChild(button2);
    VerticalPanel* c = dynamic_cast<VerticalPanel*>(m_Container.get());
    c->AddChild(button2, {
        .alignment = Alignment::Right
    });

    UniFox::Ref<Container> container = UniFox::MakeRef<HorizontalPanel>(LayoutProperty{
        Length(LengthMode::Fill),
        Length(LengthMode::Pixels, 1.0f)
    });
    container->SetStyle(style2);
    m_Container->AddChild(container);
    HorizontalPanel* panel2 = dynamic_cast<HorizontalPanel*>(container.get());
    panel2->SetPadding({0.1, 0.1, 0.1, 0.1});
    panel2->SetMargin({0.1, 0.1, 0.1, 0.1});

    UniFox::Ref<Widget> button3 = UniFox::MakeRef<Button>(LayoutProperty{
        Length(LengthMode::Pixels, 1.0f),
        Length(LengthMode::Pixels, 0.5f)
    });
    button3->SetStyle(style2);
    container->AddChild(button3);
    UniFox::Ref<Widget> button4 = UniFox::MakeRef<Button>(LayoutProperty{
        Length(LengthMode::Pixels, 2.0f),
        Length(LengthMode::Pixels, 1.0f)
    });
    button4->SetStyle(style2);
    container->AddChild(button4);
}

void GUI::OnDetach() {
}

void GUI::OnUpdate(UniFox::Duration dt) {
    m_CameraController.OnUpdate(dt);

    UniFox::RenderCommand::SetClearColor({0.05, 0.05, 0.05, 1.0});
    UniFox::RenderCommand::Clear();

    UniFox::Renderer2D::BeginScene(m_CameraController.GetCamera());

    UniFox::Renderer2D::DrawQuad({-1, -1, -1}, {1, 1}, 0, {1.0, 1.0, 1.0, 1.0});

    Constraint c = Constraint(m_Size, m_Size);
    glm::vec2 size = m_Container->Measure(c);
    Rect r = Rect({0, 0}, size);
    m_Container->SetArrangement({r});
    m_Container->Arrange(r);
    m_Container->Draw(0.0);

    UniFox::Renderer2D::EndScene();
}

void GUI::OnImGuiRender() {
    ImGui::Begin("GUI");

    if(ImGui::Button("add button")) {
        UniFox::Ref<Widget> button = UniFox::MakeRef<Button>(LayoutProperty{
            Length(LengthMode::Pixels, 2.5f),
            Length(LengthMode::Ratio, 0.25)
        });
        UniFox::Ref<Style> style = UniFox::MakeRef<Style>(glm::vec4(0.2, 0.2, 0.2, 1.0), glm::vec4(0.2, 0.2, 0.8, 1.0));
        button->SetStyle(style);
        m_Container->AddChild(button);
    }

    ImGui::SliderFloat("width", &m_Size.x, 0.0, 5.0);
    ImGui::SliderFloat("height", &m_Size.y, 0.0, 5.0);
    m_Container->InvalidteMeasure();

    ImGui::End();
}

void GUI::OnEvent(UniFox::Event& e) {
    UniFox::EventDispatcher dispatcher(e);
    m_CameraController.OnEvent(e);
}