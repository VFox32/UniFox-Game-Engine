#pragma once

#include <chrono>
#include <format>

namespace UniFox {
    class Clock;
    class Time;
    class TimePoint;
    class Duration;

    class Duration {
    public:
        Duration() : m_ns(std::chrono::nanoseconds(0)) {}
        Duration(const int& seconds) : m_ns(std::chrono::seconds(seconds)) {}

        Duration(const std::chrono::nanoseconds ns)  : m_ns(ns) {}
        Duration(const std::chrono::microseconds us) : m_ns(std::chrono::nanoseconds(us)) {}
        Duration(const std::chrono::milliseconds ms) : m_ns(std::chrono::nanoseconds(ms)) {}
        Duration(const std::chrono::seconds s)       : m_ns(std::chrono::nanoseconds(s )) {}
        Duration(const std::chrono::minutes m)       : m_ns(std::chrono::nanoseconds(m )) {}
        Duration(const std::chrono::hours h)         : m_ns(std::chrono::nanoseconds(h )) {}
        //Duration(const std::chrono::days d)          : m_ns(std::chrono::duration_cast<std::chrono::nanoseconds>(d )) {}
        //Duration(const std::chrono::weeks w)         : m_ns(std::chrono::duration_cast<std::chrono::nanoseconds>(w )) {}

        Duration(const std::chrono::duration<double, std::nano>          duration) : m_ns(std::chrono::duration_cast<std::chrono::nanoseconds>(duration)) {}
        Duration(const std::chrono::duration<double, std::micro>         duration) : m_ns(std::chrono::duration_cast<std::chrono::nanoseconds>(duration)) {}
        Duration(const std::chrono::duration<double, std::milli>         duration) : m_ns(std::chrono::duration_cast<std::chrono::nanoseconds>(duration)) {}
        Duration(const std::chrono::duration<double>                     duration) : m_ns(std::chrono::duration_cast<std::chrono::nanoseconds>(duration)) {}
        Duration(const std::chrono::duration<double, std::ratio<60>>     duration) : m_ns(std::chrono::duration_cast<std::chrono::nanoseconds>(duration)) {}
        Duration(const std::chrono::duration<double, std::ratio<3600>>   duration) : m_ns(std::chrono::duration_cast<std::chrono::nanoseconds>(duration)) {}
        Duration(const std::chrono::duration<double, std::ratio<86400>>  duration) : m_ns(std::chrono::duration_cast<std::chrono::nanoseconds>(duration)) {}
        Duration(const std::chrono::duration<double, std::ratio<604800>> duration) : m_ns(std::chrono::duration_cast<std::chrono::nanoseconds>(duration)) {}

        double ns() const {return m_ns.count();}
        double us() const {return std::chrono::duration<double, std::micro>        (m_ns).count();}
        double ms() const {return std::chrono::duration<double, std::milli>        (m_ns).count();}
        double s () const {return std::chrono::duration<double>                    (m_ns).count();}
        double m () const {return std::chrono::duration<double, std::ratio<60>>    (m_ns).count();}
        double h () const {return std::chrono::duration<double, std::ratio<3600>>  (m_ns).count();}
        double d () const {return std::chrono::duration<double, std::ratio<86400>> (m_ns).count();}
        double w () const {return std::chrono::duration<double, std::ratio<604800>>(m_ns).count();}

        double Nanoseconds () const {return ns();}
        double Microseconds() const {return us();}
        double Milliseconds() const {return ms();}
        double Seconds     () const {return s ();}
        double Minutes     () const {return m ();}
        double Hours       () const {return h ();}
        double Days        () const {return d ();}
        double Weeks       () const {return w ();}

        template<typename T>
        void ns(const T ns) {m_ns = std::chrono::nanoseconds (ns);}
        template<typename T>
        void us(const T us) {m_ns = std::chrono::microseconds(us);}
        template<typename T>
        void ms(const T ms) {m_ns = std::chrono::milliseconds(ms);}
        template<typename T>
        void s (const T s ) {m_ns = std::chrono::seconds     (s );}
        template<typename T>
        void m (const T m ) {m_ns = std::chrono::minutes     (m );}
        template<typename T>
        void h (const T h ) {m_ns = std::chrono::hours       (h );}
        template<typename T>
        void d (const T d ) {m_ns = std::chrono::duration<double, std::ratio<86400>>(d);}
        template<typename T>
        void w (const T w ) {m_ns = std::chrono::duration<double, std::ratio<604800>>(w);}

        template<typename T>
        void Nanoseconds (const T ns) {Duration::ns(ns);}
        template<typename T>
        void Microseconds(const T us) {Duration::us(us);}
        template<typename T>
        void Milliseconds(const T ms) {Duration::ms(ms);}
        template<typename T>
        void Seconds     (const T s ) {Duration::s (s );}
        template<typename T>
        void Minutes     (const T m ) {Duration::m (m );}
        template<typename T>
        void Hours       (const T h ) {Duration::h (h );}
        template<typename T>
        void Days        (const T d ) {Duration::d (d );}
        template<typename T>
        void Weeks       (const T w ) {Duration::w (w );}
    public:
        operator std::chrono::nanoseconds () const {return m_ns;}
        operator std::chrono::microseconds() const {return std::chrono::duration_cast<std::chrono::microseconds>(m_ns);}
        operator std::chrono::milliseconds() const {return std::chrono::duration_cast<std::chrono::milliseconds>(m_ns);}
        operator std::chrono::seconds     () const {return std::chrono::duration_cast<std::chrono::seconds>     (m_ns);}
        operator std::chrono::minutes     () const {return std::chrono::duration_cast<std::chrono::minutes>     (m_ns);}
        operator std::chrono::hours       () const {return std::chrono::duration_cast<std::chrono::hours>       (m_ns);}
        //operator std::chrono::days        () const {return std::chrono::duration_cast<std::chrono::days>        (m_ns);}
        //operator std::chrono::weeks       () const {return std::chrono::duration_cast<std::chrono::weeks>       (m_ns);}

        operator std::chrono::duration<double, std::nano>          () const {return std::chrono::duration<double, std::nano>          (m_ns);}
        operator std::chrono::duration<double, std::micro>         () const {return std::chrono::duration<double, std::micro>         (m_ns);}
        operator std::chrono::duration<double, std::milli>         () const {return std::chrono::duration<double, std::milli>         (m_ns);}
        operator std::chrono::duration<double>                     () const {return std::chrono::duration<double>                     (m_ns);}
        operator std::chrono::duration<double, std::ratio<60>>     () const {return std::chrono::duration<double, std::ratio<60>>     (m_ns);}
        operator std::chrono::duration<double, std::ratio<3600>>   () const {return std::chrono::duration<double, std::ratio<3600>>   (m_ns);}
        operator std::chrono::duration<double, std::ratio<86400>>  () const {return std::chrono::duration<double, std::ratio<86400>>  (m_ns);}
        operator std::chrono::duration<double, std::ratio<604800>> () const {return std::chrono::duration<double, std::ratio<604800>> (m_ns);}

        operator double() const {return s();}

        Duration operator+(const Duration& other) const {return Duration(m_ns + other.m_ns);}
        Duration operator-(const Duration& other) const {return Duration(m_ns - other.m_ns);}
        //Duration operator*(const double& other)   const { return Duration(m_ns * other); }
        //Duration operator/(const double& other)   const { return Duration(m_ns / other); }
        Duration operator*(const int& other)      const {return Duration(m_ns * other);}
        Duration operator/(const int& other)      const {return Duration(m_ns / other);}

        Duration& operator= (const Duration& other) {m_ns =  other.m_ns; return *this;}
        Duration& operator+=(const Duration& other) {m_ns += other.m_ns; return *this;}
        Duration& operator-=(const Duration& other) {m_ns -= other.m_ns; return *this;}
        Duration& operator*=(const double& other)   {m_ns /= other;      return *this;}
        Duration& operator/=(const double& other)   {m_ns *= other;      return *this;}
        Duration& operator*=(const int& other)      {m_ns /= other;      return *this;}
        Duration& operator/=(const int& other)      {m_ns *= other;      return *this;}

        bool operator==(const Duration& other) const {return m_ns == other.m_ns;}
        bool operator!=(const Duration& other) const {return m_ns != other.m_ns;}
        bool operator> (const Duration& other) const {return m_ns >  other.m_ns;}
        bool operator< (const Duration& other) const {return m_ns <  other.m_ns;}
        bool operator>=(const Duration& other) const {return m_ns >= other.m_ns;}
        bool operator<=(const Duration& other) const {return m_ns <= other.m_ns;}
    private:
        std::chrono::nanoseconds m_ns;
    };
    
    class TimePoint {
    public:
        TimePoint() : m_tp(std::chrono::steady_clock::now()) {}
        TimePoint(std::chrono::time_point<std::chrono::steady_clock> timepoint) : m_tp(timepoint) {}

        std::string ToString(const std::string& format = "%d/%m/%Y %H:%M:%S") const;
    public:
        operator std::chrono::time_point<std::chrono::steady_clock>() {return m_tp;}

        inline std::string format_as(const TimePoint& tp) {return tp.ToString();}
        operator std::string() {return ToString();}
        friend std::ostream& operator<<(std::ostream& os, const TimePoint& tp) {return os << tp.ToString();}

        TimePoint operator+(const Duration& duration) const {return TimePoint(m_tp + (std::chrono::nanoseconds)duration);}
        TimePoint operator-(const Duration& duration) const {return TimePoint(m_tp - (std::chrono::nanoseconds)duration);}
        TimePoint& operator+=(const Duration& duration) {m_tp += (std::chrono::nanoseconds)duration; return *this;}
        TimePoint& operator-=(const Duration& duration) {m_tp -= (std::chrono::nanoseconds)duration; return *this;}

        Duration operator-(const TimePoint& other) const { return Duration(m_tp - other.m_tp); }

        bool operator==(const TimePoint& other) const {return m_tp == other.m_tp;}
        bool operator!=(const TimePoint& other) const {return m_tp != other.m_tp;}
        bool operator> (const TimePoint& other) const {return m_tp >  other.m_tp;}
        bool operator< (const TimePoint& other) const {return m_tp <  other.m_tp;}
        bool operator>=(const TimePoint& other) const {return m_tp >= other.m_tp;}
        bool operator<=(const TimePoint& other) const {return m_tp <= other.m_tp;}
    private:
        std::chrono::steady_clock::time_point m_tp;
    };

    class Time {
    public:
        static TimePoint Now() {return (TimePoint)std::chrono::steady_clock::now();}

        template<typename T>
        static Duration Nanoseconds (const T ns) {return Duration(std::chrono::nanoseconds                         (ns));}
        template<typename T>
        static Duration Microseconds(const T us) {return Duration(std::chrono::microseconds                        (us));}
        template<typename T>
        static Duration Milliseconds(const T ms) {return Duration(std::chrono::milliseconds                        (ms));}
        template<typename T>
        static Duration Seconds     (const T s ) {return Duration(std::chrono::seconds                             (s ));}
        template<typename T>
        static Duration Minutes     (const T m ) {return Duration(std::chrono::minutes                             (m ));}
        template<typename T>
        static Duration Hours       (const T h ) {return Duration(std::chrono::hours                               (h ));}
        template<typename T>
        static Duration Days        (const T d ) {return Duration(std::chrono::duration<double, std::ratio<86400>> (d ));}
        template<typename T>
        static Duration Weeks       (const T w ) {return Duration(std::chrono::duration<double, std::ratio<604800>>(w ));}

        static Duration Nanoseconds () {return Nanoseconds (1);}
        static Duration Microseconds() {return Microseconds(1);}
        static Duration Milliseconds() {return Milliseconds(1);}
        static Duration Seconds     () {return Seconds     (1);}
        static Duration Minutes     () {return Minutes     (1);}
        static Duration Hours       () {return Hours       (1);}
        static Duration Days        () {return Days        (1);}
        static Duration Weeks       () {return Weeks       (1);}
    };

    class Clock {
    public:
        friend class Time;
        friend class TimePoint;
        friend class Duration;
    private:
        using Steady = std::chrono::steady_clock;
        using System = std::chrono::system_clock;
        using Tai = std::chrono::tai_clock;
    private:
        static Steady::time_point ToSteady(TimePoint tp) {
            return (Steady::time_point)tp;
        }

        static Tai::time_point ToTai(TimePoint tp) {
            Steady::duration delta = (Steady::time_point)tp - GLOBAL_TIME_ANCHOR.m_steady;
            return GLOBAL_TIME_ANCHOR.m_tai + delta;
        }
        static Tai::time_point ToTai(Steady::time_point tp) {
            Steady::duration delta = tp - GLOBAL_TIME_ANCHOR.m_steady;
            return GLOBAL_TIME_ANCHOR.m_tai + delta;
        }
        static Tai::time_point ToTai(System::time_point tp) {
            return std::chrono::clock_cast<Tai>(tp);
        }

        static System::time_point ToSystem(TimePoint tp) {
            return std::chrono::clock_cast<System>(ToTai(tp));
        }
    private:
        struct TimeAnchor {
            static TimeAnchor Create() {
                return {
                    Tai::now(),
                    Steady::now()
                };
            }
            Tai::time_point m_tai;
            Steady::time_point m_steady;
        };
        inline static const TimeAnchor GLOBAL_TIME_ANCHOR = TimeAnchor::Create();
    };

    //inline Duration operator"" _ns(long double ns) { return Clock::Nanoseconds(ns); }
    //inline Duration operator"" _us(long double us) { return Clock::Microseconds(us); }
    //inline Duration operator"" _ms(long double ms) { return Clock::Milliseconds(ms); }
    //inline Duration operator"" _s (long double s)  { return Clock::Seconds(s); }
    //inline Duration operator"" _m (long double m)  { return Clock::Minutes(m); }
    //inline Duration operator"" _h (long double h)  { return Clock::Hours(h); }
}