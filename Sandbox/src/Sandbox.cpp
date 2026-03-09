#include <UniFox.h>
#include <UniFox/Core/EntryPoint.h>

#include "Sandbox2D.h"

class Sandbox : public UniFox::Application {
public:
    Sandbox() {
        PushLayer(UniFox::MakeRef<Sandbox2D>());
    }
    ~Sandbox() {

    }
};

UniFox::Ref<UniFox::Application> UniFox::CreateApplication() {
    return UniFox::MakeRef<Sandbox>();
}