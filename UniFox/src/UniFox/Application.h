#pragma once
#include "ufpch.h"

#include "Core.h"

namespace UniFox {

    class UF_API Application {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    Application* CreateApplication();

}