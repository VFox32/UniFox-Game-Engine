#pragma once

#include "UniFox/Core/Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace UniFox {
    class UF_API Log {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {return s_CoreLogger;};
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() {return s_ClientLogger;};

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

#define UF_CORE_TRACE(...)   ::UniFox::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define UF_CORE_INFO(...)    ::UniFox::Log::GetCoreLogger()->info(__VA_ARGS__)
#define UF_CORE_WARN(...)    ::UniFox::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define UF_CORE_ERROR(...)   ::UniFox::Log::GetCoreLogger()->error(__VA_ARGS__)
#define UF_CORE_FATAL(...)   ::UniFox::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define UF_TRACE(...) ::UniFox::Log::GetClientLogger()->trace(__VA_ARGS__)
#define UF_INFO(...)  ::UniFox::Log::GetClientLogger()->info(__VA_ARGS__)
#define UF_WARN(...)  ::UniFox::Log::GetClientLogger()->warn(__VA_ARGS__)
#define UF_ERROR(...) ::UniFox::Log::GetClientLogger()->error(__VA_ARGS__)
#define UF_FATAL(...) ::UniFox::Log::GetClientLogger()->fatal(__VA_ARGS__)