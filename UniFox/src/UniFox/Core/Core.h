#pragma once

#include <memory>
#include "UniFox/Core/Log.h"
#include "UniFox/Core/PlatformDetection.h"

#ifdef UF_DEBUG
    #define UF_ENABLE_ASSERTS
#endif

#ifdef UF_PLATFORM_WINDOWS
    #define UF_DEBUGBREAK __debugbreak()
#else
    #define UF_DEBUGBREAK __builtin_trap()
#endif

#ifdef UF_ENABLE_ASSERTS
    #define UF_ASSERT(x, ...) if(!(x)) {UF_ERROR("Assertion Failed: {0}", __VA_ARGS__); UF_DEBUGBREAK;}
    #define UF_CORE_ASSERT(x, ...) if(!(x)) {UF_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); UF_DEBUGBREAK;}
#else
    #define UF_ASSERT(x, ...)
    #define UF_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
#define EXPAND(x) x
#define STRINGIFY(x) #x

#define UF_BIND_EVENT_FN(fn) \
    [this](auto&&... args) -> decltype(auto) { \
        return this->fn(std::forward<decltype(args)>(args)...); \
    }

namespace UniFox {
    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename... Args>
    Scope<T> MakeScope(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;
    
    template<typename T, typename... Args>
    Ref<T> MakeRef(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}