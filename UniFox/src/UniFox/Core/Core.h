#pragma once

#include <memory>
#include "UniFox/Core/Log.h"

#ifdef UF_DEBUG
    #define UF_ENABLE_ASSERTS
#endif

#ifdef UF_ENABLE_ASSERTS
    #define UF_ASSERT(x, ...) if(!(x)) {UF_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}
    #define UF_CORE_ASSERT(x, ...) if(!(x)) {UF_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}
#else
    #define UF_ASSERT(x, ...)
    #define UF_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
#define EXPAND(x) x
#define STRINGIFY(x) #x

#define UF_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

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