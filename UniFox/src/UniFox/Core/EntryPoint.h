#pragma once

#include "UniFox/Core/Application.h"

#ifdef UF_PLATFORM_WINDOWS
    extern UniFox::Application* UniFox::CreateApplication();

    int main(int argc, char** arcv) {
        UniFox::Log::Init();

        UF_PROFILE_BEGIN_SESSION("Startup", "UniFoxProfile-Startup.json");
        auto app = UniFox::CreateApplication();
        UF_PROFILE_END_SESSION();

        UF_PROFILE_BEGIN_SESSION("Startup", "UniFoxProfile-Runtime.json");
        app->Run();
        UF_PROFILE_END_SESSION();
        
        UF_PROFILE_BEGIN_SESSION("Startup", "UniFoxProfile-Shutdown.json");
        delete app;
        UF_PROFILE_END_SESSION();
    }
#endif