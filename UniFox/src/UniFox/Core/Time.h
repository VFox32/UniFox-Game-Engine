#pragma once

#include "UniFox/Util/StreamWriter.h"
#include "UniFox/Util/StreamReader.h"

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

        static void Serialize(StreamWriter* serializer, const Duration& instance) {
            uint64_t ns = instance.ns();
            serializer->WriteRaw(ns);
        }
        static void DeSerialize(StreamReader* deserializer, Duration& instance) {
            deserializer->ReadRaw(instance.m_ns);
        }

        template<typename Rep, typename Period>
        Duration(const std::chrono::duration<Rep, Period>& d)
            : m_ns(std::chrono::duration_cast<std::chrono::nanoseconds>(d)) {}

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
        template<typename Rep, typename Period>
        operator std::chrono::duration<Rep, Period> () const
            {return std::chrono::duration_cast<std::chrono::duration<Rep, Period>> (m_ns);}

        operator double() const {return s();}

        Duration operator+(const Duration& other) const {return Duration(m_ns + other.m_ns);}
        Duration operator-(const Duration& other) const {return Duration(m_ns - other.m_ns);}
        Duration operator*(const double& other)   const {return Duration(m_ns * other);}
        Duration operator/(const double& other)   const {return Duration(m_ns / other);}
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
        friend class TimePoint;
    private:
        std::chrono::nanoseconds m_ns;
    };
    
    class TimePoint {
    public:
        TimePoint() : m_tp(std::chrono::steady_clock::now()) {}
        TimePoint(std::chrono::time_point<std::chrono::steady_clock> timepoint) : m_tp(timepoint) {}
        TimePoint(std::chrono::time_point<std::chrono::system_clock> timepoint);

        static void Serialize(StreamWriter* serializer, const TimePoint& instance) {
            serializer->WriteRaw(instance.Nanoseconds());
        }
        static void DeSerialize(StreamReader* deserializer, TimePoint& instance);

        TimePoint(int year, unsigned month, unsigned day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0, int nanosecond = 0);

        std::string ToString(const std::string& format = "%d/%m/%Y %H:%M:%S") const;

        int Second    () const {return int(     hms().seconds().count());}
        int Minute    () const {return int(     hms().minutes().count());}
        int Hour      () const {return int(     hms().hours  ().count());}
        unsigned Day  () const {return unsigned(ymd().day  ());}
        unsigned Month() const {return unsigned(ymd().month());}
        int Year      () const {return int(     ymd().year ());}

        int64_t Nanoseconds () const;
        int64_t Microseconds() const;
        int64_t Milliseconds() const;
        int64_t Seconds     () const;
        int64_t Minutes     () const;
        int64_t Hours       () const;
        int64_t Days        () const;
        int64_t Weeks       () const;
    public:
        operator std::chrono::steady_clock::time_point();
        operator std::chrono::system_clock::time_point();
        operator std::chrono::tai_clock::time_point();

        operator std::string() {return ToString();}
        inline std::string format_as(const TimePoint& tp) {return tp.ToString();}
        friend std::ostream& operator<<(std::ostream& os, const TimePoint& tp) {return os << tp.ToString();}

        TimePoint operator+(const Duration& duration) const {return TimePoint(m_tp + duration.m_ns);}
        TimePoint operator-(const Duration& duration) const {return TimePoint(m_tp - duration.m_ns);}
        TimePoint& operator+=(const Duration& duration) {m_tp += duration.m_ns; return *this;}
        TimePoint& operator-=(const Duration& duration) {m_tp -= duration.m_ns; return *this;}

        Duration operator-(const TimePoint& other) const { return Duration(m_tp - other.m_tp); }

        bool operator==(const TimePoint& other) const {return m_tp == other.m_tp;}
        bool operator!=(const TimePoint& other) const {return m_tp != other.m_tp;}
        bool operator> (const TimePoint& other) const {return m_tp >  other.m_tp;}
        bool operator< (const TimePoint& other) const {return m_tp <  other.m_tp;}
        bool operator>=(const TimePoint& other) const {return m_tp >= other.m_tp;}
        bool operator<=(const TimePoint& other) const {return m_tp <= other.m_tp;}
    private:
        std::chrono::steady_clock::time_point m_tp;

        std::chrono::year_month_day ymd() const;
        std::chrono::hh_mm_ss<std::chrono::seconds> hms() const;
    };

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

    class Clock {
    public:
        static TimePoint Now() {return (TimePoint)std::chrono::steady_clock::now();}
        static TimePoint StartTime() {return (TimePoint)GLOBAL_TIME_ANCHOR.m_steady;}
        static Duration RunTime() {return (Duration)(Now()-StartTime());}
    private:
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
        static Steady::time_point ToSteady(System::time_point tp) {
            return GLOBAL_TIME_ANCHOR.m_steady + (ToTai(tp) - GLOBAL_TIME_ANCHOR.m_tai);
        }
        static Steady::time_point ToSteady(Tai::time_point tp) {
            return GLOBAL_TIME_ANCHOR.m_steady + (tp - GLOBAL_TIME_ANCHOR.m_tai);
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