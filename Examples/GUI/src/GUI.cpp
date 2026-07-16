#include "GUI.h"
#include "ufpch.h"

#include "imgui.h"

GUI::GUI()
    : m_Camera(0.0, 1080.0, 0.0, 720.0) {//m_CameraController(16.0 / 9.0, false, 5.0) {
}

void GUI::OnAttach() {
    m_UIManager = UniFox::MakeRef<UIManager>();

    UniFox::Ref<Style> style1 = UniFox::MakeRef<Style>(glm::vec4(0.8, 0.2, 0.2, 1.0), glm::vec4(0.2, 0.2, 0.8, 1.0));
    UniFox::Ref<Style> style2 = UniFox::MakeRef<Style>(glm::vec4(0.2, 0.8, 0.2, 1.0), glm::vec4(0.2, 0.2, 0.2, 1.0));

    UniFox::Ref<Container> m_Container = UniFox::MakeRef<VerticalPanel>();
    m_Container->SetProperty({
        .w = Length(LengthMode::Pixels, 300),
        .h = Length(LengthMode::Pixels, 300)
    });
    m_UIManager->AddChild(m_Container, {
        .position = {100, 100}
    });
    m_Container->SetStyle(style1);

    VerticalPanel* panel = dynamic_cast<VerticalPanel*>(m_Container.get());
    panel->SetPadding({5, 5, 5, 5});
    panel->SetMargin({5, 5, 5, 5});

    UniFox::Ref<Widget> button1 = UniFox::MakeRef<Button>(LayoutProperty{
        Length(LengthMode::Pixels, 200),
        Length(LengthMode::Pixels, 100)
    });
    button1->SetStyle(style2);
    button1->Events()->Connect<UniFox::MouseButtonPressedEvent>([](UniFox::MouseButtonPressedEvent& e) {
        std::cout << "Button 1 was pressed!\n";
        return true;
    });
    m_Container->AddChild(button1);
    UniFox::Ref<Widget> button2 = UniFox::MakeRef<Button>(LayoutProperty{
        Length(LengthMode::Pixels, 200),
        Length(LengthMode::Ratio, 100)
    });
    button2->SetStyle(style2);
    m_Container->AddChild(button2);
    VerticalPanel* c = dynamic_cast<VerticalPanel*>(m_Container.get());
    c->AddChild(button2, {
        .alignment = Alignment::Right
    });

    UniFox::Ref<Container> container = UniFox::MakeRef<HorizontalPanel>(LayoutProperty{
        Length(LengthMode::Fill),
        Length(LengthMode::Pixels, 100)
    });
    container->SetStyle(style2);
    m_Container->AddChild(container);
    HorizontalPanel* panel2 = dynamic_cast<HorizontalPanel*>(container.get());
    panel2->SetPadding({5, 5, 5, 5});
    panel2->SetMargin({5, 5, 5, 5});

    UniFox::Ref<Widget> button3 = UniFox::MakeRef<Button>(LayoutProperty{
        Length(LengthMode::Pixels, 100),
        Length(LengthMode::Pixels, 50)
    });
    button3->SetStyle(style1);
    container->AddChild(button3);
    UniFox::Ref<Widget> button4 = UniFox::MakeRef<Button>(LayoutProperty{
        Length(LengthMode::Pixels, 200),
        Length(LengthMode::Pixels, 100)
    });
    button4->SetStyle(style1);
    container->AddChild(button4);
}

void GUI::OnDetach() {
}

void GUI::OnUpdate(UniFox::Duration dt) {
    //m_CameraController.OnUpdate(dt);

    UniFox::RenderCommand::SetClearColor({0.05, 0.05, 0.05, 1.0});
    UniFox::RenderCommand::Clear();

    //UniFox::Renderer2D::BeginScene(m_CameraController.GetCamera());
    UniFox::Renderer2D::BeginScene(m_Camera);

    //UniFox::Renderer2D::DrawQuad({100 + 125, 100 + 125}, {250, 250}, 0.0f, {1.0f, 1.0f, 1.0f, 1.0f});

    m_UIManager->Draw();

    UniFox::Renderer2D::EndScene();
}

void GUI::OnImGuiRender() {
    ImGui::Begin("GUI");

    if(ImGui::Button("add button")) {
        UniFox::Ref<Widget> button = UniFox::MakeRef<Button>(LayoutProperty{
            Length(LengthMode::Pixels, 250),
            Length(LengthMode::Ratio, 0.25)
        });
        UniFox::Ref<Style> style = UniFox::MakeRef<Style>(glm::vec4(0.2, 0.2, 0.2, 1.0), glm::vec4(0.2, 0.2, 0.8, 1.0));
        button->SetStyle(style);
        //m_Container->AddChild(button);
        dynamic_cast<Container*>(m_UIManager->GetChild(0).get())->AddChild(button);
    }

    ImGui::SliderFloat("width", &m_Size.x, 0.0, 500);
    ImGui::SliderFloat("height", &m_Size.y, 0.0, 500);
    m_UIManager->GetChild(0)->SetProperty({
        .w = Length(LengthMode::Pixels, m_Size.x),
        .h = Length(LengthMode::Pixels, m_Size.y),
    });
    m_UIManager->GetChild(0)->InvalidteMeasure();

    ImGui::End();
}

void GUI::OnEvent(UniFox::Event& e) {
    UniFox::EventDispatcher dispatcher(e);
    dispatcher.Dispatch<UniFox::WindowResizeEvent>(UF_BIND_EVENT_FN(OnWindowResize));
    //m_CameraController.OnEvent(e);
    m_UIManager->OnEvent(e);
}

bool GUI::OnWindowResize(UniFox::WindowResizeEvent& e) {
    m_Camera.SetProjection(0.0, (float)e.GetWidth(), 0.0, (float)e.GetHeight());
    return false;
}