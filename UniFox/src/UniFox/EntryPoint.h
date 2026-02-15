#pragma once

#include "Application.h"

#ifdef UF_PLATFORM_WINDOWS
    extern UniFox::Application* UniFox::CreateApplication();

    int main(int argc, char** arcv) {
        auto app = UniFox::CreateApplication();
        app->Run();
        delete app;
    }
#endif