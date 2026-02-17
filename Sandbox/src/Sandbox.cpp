
#include <UniFox.h>

#include "imgui.h"

class ExampleLayer : public UniFox::Layer {
public:
    ExampleLayer() 
        : Layer("Example") {
    }

    void OnUpdate() override {
        if(UniFox::Input::IsKeyPressed(UF_KEY_TAB)) {
            UF_TRACE("Tab key is pressed!");
        }
    }

    virtual void OnImGuiRender() override {
        ImGui::Begin("Test");
        ImGui::Text("Hello World!");
        ImGui::End();
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
    }
    ~Sandbox() {

    }
};

UniFox::Application* UniFox::CreateApplication() {
    return new Sandbox();
}