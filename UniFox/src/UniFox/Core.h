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

#ifdef UF_ENABLE_ASSERTS
    #define UF_ASSERT(x, ...) if(!(x)) {UF_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}
    #define UF_CORE_ASSERT(x, ...) if(!(x)) {UF_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}
#else
    #define UF_ASSERT(x, ...)
    #define UF_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define UF_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)