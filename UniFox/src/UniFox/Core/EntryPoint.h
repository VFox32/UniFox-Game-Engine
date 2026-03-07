#pragma once

#include "UniFox/Core/Application.h"

#ifdef UF_PLATFORM_WINDOWS
    extern UniFox::Ref<UniFox::Application> UniFox::CreateApplication();

    int main(int argc, char** arcv) {
        UniFox::Log::Init();
        UF_CORE_WARN("Initialized Log!");

        UniFox::Ref<UniFox::Application> app = UniFox::CreateApplication();
        app->Run();
    }
#endif