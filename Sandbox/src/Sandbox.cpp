
#include <UniFox.h>

class ExampleLayer : public UniFox::Layer {
public:
    ExampleLayer() 
        : Layer("Example") {
    }

    void OnUpdate() {
        if(UniFox::Input::IsKeyPressed(UF_KEY_TAB)) {
            UF_TRACE("Tab key is pressed!");
        }
    }

    void OnEvent(UniFox::Event& event) override {
        if(event.GetEventType() == UniFox::EventType::KeyPressed) {
            UniFox::KeyPressedEvent& e = (UniFox::KeyPressedEvent&)event;
            UF_INFO("{0}", (char)e.GetKeyCode());
        }
    }
};

class Sandbox : public UniFox::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
        PushOverlay(new UniFox::ImGuiLayer());
    }
    ~Sandbox() {

    }
};

UniFox::Application* UniFox::CreateApplication() {
    return new Sandbox();
}