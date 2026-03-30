#include "ufpch.h"
#include "UniFox/Core/Time.h"

namespace UniFox {
    TimePoint::TimePoint(std::chrono::time_point<std::chrono::system_clock> timepoint) : m_tp(Clock::ToSteady(timepoint)) {}
    TimePoint::TimePoint(int year, unsigned month, unsigned day, int hour, int minute, int second, int millisecond, int microsecond, int nanosecond) {
        /*auto sys = std::chrono::sys_days {std::chrono::year{year} / std::chrono::month{month} / std::chrono::day{day}}
            + std::chrono::hours{hour}
            + std::chrono::minutes{minute}
            + std::chrono::seconds{second}
            + std::chrono::milliseconds{millisecond}
            + std::chrono::microseconds{microsecond}
            + std::chrono::nanoseconds{nanosecond};

        m_tp = Clock::ToSteady(sys);*/
        auto local = std::chrono::local_days {std::chrono::year{year} / std::chrono::month{month} / std::chrono::day{day}}
            + std::chrono::hours{hour}
            + std::chrono::minutes{minute}
            + std::chrono::seconds{second}
            + std::chrono::milliseconds{millisecond}
            + std::chrono::microseconds{microsecond}
            + std::chrono::nanoseconds{nanosecond};

        std::chrono::zoned_time zt{std::chrono::current_zone(), local};

        m_tp = Clock::ToSteady(zt.get_sys_time());
    }

    void TimePoint::DeSerialize(StreamReader* deserializer, TimePoint& instance) {
        uint64_t ns;
        deserializer->ReadRaw(ns);
        auto tai = std::chrono::tai_clock::time_point{
            std::chrono::nanoseconds(ns)
        };
        instance.m_tp = Clock::ToSteady(tai);
    }

    std::string TimePoint::ToString(const std::string& format) const {
        std::chrono::zoned_time zt{std::chrono::current_zone(), Clock::ToSystem(m_tp)};
        //auto local = zt.get_local_time();
        auto local = std::chrono::current_zone()->to_local(Clock::ToSystem(m_tp));
        return std::vformat("{:" + format + "}", std::make_format_args(local));
    }
    
    std::chrono::year_month_day TimePoint::ymd() const {
        auto sys = Clock::ToSystem(*this);
        auto days = std::chrono::floor<std::chrono::days>(sys);
        return std::chrono::year_month_day{days};
    }
    std::chrono::hh_mm_ss<std::chrono::seconds> TimePoint::hms() const {
        auto sys = Clock::ToSystem(*this);
        auto days = std::chrono::floor<std::chrono::days>(sys);
        auto tod = std::chrono::floor<std::chrono::seconds>(sys - days);
        return std::chrono::hh_mm_ss<std::chrono::seconds>{tod};
    }

    TimePoint::operator std::chrono::steady_clock::time_point() {return m_tp;}
    TimePoint::operator std::chrono::system_clock::time_point() {return Clock::ToSystem(*this);}
    TimePoint::operator std::chrono::tai_clock::time_point() {return Clock::ToTai(*this);}
    
    int64_t TimePoint::Nanoseconds() const {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::ToTai(*this).time_since_epoch()).count();
    }
    int64_t TimePoint::Microseconds() const {
        return std::chrono::duration_cast<std::chrono::microseconds>(Clock::ToTai(*this).time_since_epoch()).count();
    }
    int64_t TimePoint::Milliseconds() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(Clock::ToTai(*this).time_since_epoch()).count();
    }
    int64_t TimePoint::Seconds() const {
        return std::chrono::duration_cast<std::chrono::seconds>(Clock::ToTai(*this).time_since_epoch()).count();
    }
    int64_t TimePoint::Minutes() const {
        return std::chrono::duration_cast<std::chrono::minutes>(Clock::ToTai(*this).time_since_epoch()).count();
    }
    int64_t TimePoint::Hours() const {
        return std::chrono::duration_cast<std::chrono::hours>(Clock::ToTai(*this).time_since_epoch()).count();
    }
    int64_t TimePoint::Days() const {
        return std::chrono::duration_cast<std::chrono::days>(Clock::ToTai(*this).time_since_epoch()).count();
    }
    int64_t TimePoint::Weeks() const {
        return std::chrono::duration_cast<std::chrono::weeks>(Clock::ToTai(*this).time_since_epoch()).count();
    }
}