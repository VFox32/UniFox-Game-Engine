#pragma once
#include "ufpch.h"

#include "Application.h"

#ifdef UF_PLATFORM_WINDOWS
    extern UniFox::Application* UniFox::CreateApplication();

    int main(int argc, char** arcv) {
        UniFox::Log::Init();
        UF_CORE_WARN("Initialized Log!");
        UF_CLIENT_INFO("Hello World!");

        UniFox::Application* app = UniFox::CreateApplication();
        app->Run();
        delete app;
    }
#endif