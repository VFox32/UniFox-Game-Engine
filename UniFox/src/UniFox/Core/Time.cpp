#include "ufpch.h"
#include "UniFox/Core/Time.h"

namespace UniFox {
    std::string TimePoint::ToString(const std::string& format) const {
        std::chrono::zoned_time local_tp{std::chrono::current_zone(), Clock::ToSystem(m_tp)};
        return std::vformat("{:" + format + "}", std::make_format_args(local_tp));
    }
}