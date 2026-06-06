#include <UniFox.h>
#include <UniFox/Core/EntryPoint.h>

#include "Chess.h"

class Sandbox : public UniFox::Application {
public:
    Sandbox() {
        UF_PROFILE_FUNCTION();

        PushLayer(UniFox::MakeRef<Chess>());
    }
    ~Sandbox() {
        UF_PROFILE_FUNCTION();
    }
};

UniFox::Application* UniFox::CreateApplication() {
    return new Sandbox();
}