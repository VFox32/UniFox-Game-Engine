#pragma once

#ifdef UF_PLATFORM_WINDOWS
    #ifdef UF_BUILD_DLL
        #define UF_API __declspec(dllexport)
    #else
        #define UF_API __declspec(dllimport)
    #endif
#else
    #error UniFox only supports Windows
#endif

#define BIT(x) (1 << x)