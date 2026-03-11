#include <UniFox.h>
#include <UniFox/Core/EntryPoint.h>

#include "Sandbox2D.h"

class Sandbox : public UniFox::Application {
public:
    Sandbox() {
        UF_PROFILE_FUNCTION();

        PushLayer(UniFox::MakeRef<Sandbox2D>());
    }
    ~Sandbox() {
        UF_PROFILE_FUNCTION();
    }
};

UniFox::Application* UniFox::CreateApplication() {
    return new Sandbox();
}