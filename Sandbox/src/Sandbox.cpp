
#include <UniFox.h>

class Sandbox : public UniFox::Application {
public:
    Sandbox() {

    }
    ~Sandbox() {

    }
};

UniFox::Application* UniFox::CreateApplication() {
    return new Sandbox();
}