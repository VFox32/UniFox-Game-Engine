
#include <UniFox.h>

class ExampleLayer : public UniFox::Layer {
public:
    ExampleLayer() 
        : Layer("Example") {
    }

    void OnUpdate() {
        UF_INFO("ExampleLayer::Update");
    }

    void OnEvent(UniFox::Event& event) override {
        UF_TRACE("{0}", event);
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