#pragma once

#include <chrono>

namespace UniFox {
    class Duration {
    public:
        Duration() : m_ns(std::chrono::nanoseconds(0)) {}

        Duration(const std::chrono::nanoseconds ns) : m_ns(ns) {}
        Duration(const std::chrono::microseconds us) : m_ns(std::chrono::duration_cast<std::chrono::nanoseconds>(us)) {}
        Duration(const std::chrono::milliseconds ms) : m_ns(std::chrono::duration_cast<std::chrono::nanoseconds>(ms)) {}
        Duration(const std::chrono::seconds s) : m_ns(std::chrono::duration_cast<std::chrono::nanoseconds>(s)) {}
        Duration(const std::chrono::minutes m) : m_ns(std::chrono::duration_cast<std::chrono::nanoseconds>(m)) {}
        Duration(const std::chrono::hours h) : m_ns(std::chrono::duration_cast<std::chrono::nanoseconds>(h)) {}

        double ns() const { return m_ns.count(); }
        double us() const { return std::chrono::duration_cast<std::chrono::duration<double, std::micro>>(m_ns).count(); }
        double ms() const { return std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(m_ns).count(); }
        double s() const { return std::chrono::duration_cast<std::chrono::duration<double>>(m_ns).count(); }
        double m() const { return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<60>>>(m_ns).count(); }
        double h() const { return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<3600>>>(m_ns).count(); }

        operator std::chrono::nanoseconds() const { return m_ns; }
        operator std::chrono::microseconds() const { return std::chrono::duration_cast<std::chrono::microseconds>(m_ns); }
        operator std::chrono::milliseconds() const { return std::chrono::duration_cast<std::chrono::milliseconds>(m_ns); }
        operator std::chrono::seconds() const { return std::chrono::duration_cast<std::chrono::seconds>(m_ns); }
        operator std::chrono::minutes() const { return std::chrono::duration_cast<std::chrono::minutes>(m_ns); }
        operator std::chrono::hours() const { return std::chrono::duration_cast<std::chrono::hours>(m_ns); }

        operator double() const {return s();}

        Duration operator+(const Duration& other) const { return Duration(m_ns + other.m_ns); }
        Duration operator-(const Duration& other) const { return Duration(m_ns - other.m_ns); }
        Duration operator*(const int& other) const { return Duration(m_ns * other); }
        Duration operator/(const int& other) const { return Duration(m_ns / other); }

        Duration& operator=(const Duration& other) { m_ns = other.m_ns; return *this; }
        Duration& operator+=(const Duration& other) { m_ns += other.m_ns; return *this; }
        Duration& operator-=(const Duration& other) { m_ns -= other.m_ns; return *this; }
        Duration& operator*=(const int& other) { m_ns /= other; return *this; }
        Duration& operator/=(const int& other) { m_ns *= other; return *this; }

        bool operator>(const Duration& other) const { return m_ns > other.m_ns; }
        bool operator<(const Duration& other) const { return m_ns < other.m_ns; }
        bool operator>=(const Duration& other) const { return m_ns >= other.m_ns; }
        bool operator<=(const Duration& other) const { return m_ns <= other.m_ns; }
    private:
        std::chrono::nanoseconds m_ns;
    };
    
    class TimePoint {
    public:
        TimePoint() : m_tp(std::chrono::high_resolution_clock::now()) {}
        TimePoint(std::chrono::time_point<std::chrono::high_resolution_clock> timepoint) : m_tp(timepoint) {}

        operator std::chrono::time_point<std::chrono::high_resolution_clock>() { return m_tp; }

        TimePoint operator+(const Duration& duration) const { return TimePoint(m_tp + (std::chrono::nanoseconds)duration); }
        TimePoint operator-(const Duration& duration) const { return TimePoint(m_tp - (std::chrono::nanoseconds)duration); }
        TimePoint& operator+=(const Duration& duration) { m_tp += (std::chrono::nanoseconds)duration; return *this;}
        TimePoint& operator-=(const Duration& duration) { m_tp -= (std::chrono::nanoseconds)duration; return *this;}

        Duration operator-(const TimePoint& other) const { return Duration(m_tp - other.m_tp); }

        bool operator>(const TimePoint& other) const { return m_tp > other.m_tp; }
        bool operator<(const TimePoint& other) const { return m_tp < other.m_tp; }
        bool operator>=(const TimePoint& other) const { return m_tp >= other.m_tp; }
        bool operator<=(const TimePoint& other) const { return m_tp <= other.m_tp; }
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_tp;
    };

    class Clock {
    public:
        static TimePoint Now() {return std::chrono::high_resolution_clock::now();}

        static Duration Nanoseconds(const double ns) { return Duration(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double, std::nano>(ns))); }
        static Duration Microseconds(const double us) { return Duration(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double, std::micro>(us))); }
        static Duration Milliseconds(const double ms) { return Duration(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double, std::milli>(ms))); }
        static Duration Seconds(const double s) { return Duration(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(s))); }
        static Duration Minutes(const double m) { return Duration(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double, std::ratio<60>>(m))); }
        static Duration Hours(const double h) { return Duration(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double, std::ratio<3600>>(h))); }
    };

    //inline Duration operator"" _ns(long double ns) { return Clock::Nanoseconds(ns); }
    //inline Duration operator"" _us(long double us) { return Clock::Microseconds(us); }
    //inline Duration operator"" _ms(long double ms) { return Clock::Milliseconds(ms); }
    //inline Duration operator"" _s (long double s)  { return Clock::Seconds(s); }
    //inline Duration operator"" _m (long double m)  { return Clock::Minutes(m); }
    //inline Duration operator"" _h (long double h)  { return Clock::Hours(h); }
}