#include <UniFox.h>
#include <UniFox/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "Sandbox3D.h"
#include "Terrain.h"

class Sandbox : public UniFox::Application {
public:
    Sandbox() {
        UF_PROFILE_FUNCTION();

        //PushLayer(UniFox::MakeRef<Sandbox2D>());
        //PushLayer(UniFox::MakeRef<Sandbox3D>());
        PushLayer(UniFox::MakeRef<Terrain>());
    }
    ~Sandbox() {
        UF_PROFILE_FUNCTION();
    }
};

UniFox::Application* UniFox::CreateApplication() {
    return new Sandbox();
}