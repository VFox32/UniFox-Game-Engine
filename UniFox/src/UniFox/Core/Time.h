#pragma once

#include <chrono>

namespace UniFox {
    class Duration {
    public:
        Duration() : m_ns(std::chrono::nanoseconds(0)) {}
        Duration(const int& seconds) : m_ns(std::chrono::seconds(seconds)) {}

        Duration(const std::chrono::nanoseconds ns)  : m_ns(ns) {}
        Duration(const std::chrono::microseconds us) : m_ns(std::chrono::duration_cast<std::chrono::nanoseconds>(us)) {}
        Duration(const std::chrono::milliseconds ms) : m_ns(std::chrono::duration_cast<std::chrono::nanoseconds>(ms)) {}
        Duration(const std::chrono::seconds s)       : m_ns(std::chrono::duration_cast<std::chrono::nanoseconds>(s )) {}
        Duration(const std::chrono::minutes m)       : m_ns(std::chrono::duration_cast<std::chrono::nanoseconds>(m )) {}
        Duration(const std::chrono::hours h)         : m_ns(std::chrono::duration_cast<std::chrono::nanoseconds>(h )) {}
        Duration(const std::chrono::days d)          : m_ns(std::chrono::duration_cast<std::chrono::nanoseconds>(d )) {}
        Duration(const std::chrono::weeks w)         : m_ns(std::chrono::duration_cast<std::chrono::nanoseconds>(w )) {}

        double ns() const {return m_ns.count();}
        double us() const {return std::chrono::duration_cast<std::chrono::duration<double, std::micro>>        (m_ns).count();}
        double ms() const {return std::chrono::duration_cast<std::chrono::duration<double, std::milli>>        (m_ns).count();}
        double s () const {return std::chrono::duration_cast<std::chrono::duration<double>>                    (m_ns).count();}
        double m () const {return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<60>>>    (m_ns).count();}
        double h () const {return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<3600>>>  (m_ns).count();}
        double d () const {return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<86400>>> (m_ns).count();}
        double w () const {return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<604800>>>(m_ns).count();}

        double Nanoseconds () const {return ns();}
        double Microseconds() const {return us();}
        double Milliseconds() const {return ms();}
        double Seconds     () const {return s ();}
        double Minutes     () const {return m ();}
        double Hours       () const {return h ();}
        double Days        () const {return d ();}
        double Weeks       () const {return w ();}

        void ns(const int ns) {m_ns = std::chrono::nanoseconds (ns);}
        void us(const int us) {m_ns = std::chrono::microseconds(us);}
        void ms(const int ms) {m_ns = std::chrono::milliseconds(ms);}
        void s (const int s ) {m_ns = std::chrono::seconds     (s );}
        void m (const int m ) {m_ns = std::chrono::minutes     (m );}
        void h (const int h ) {m_ns = std::chrono::hours       (h );}
        void d (const int d ) {m_ns = std::chrono::days        (d );}
        void w (const int w ) {m_ns = std::chrono::weeks       (w );}

        void Nanoseconds (const int ns) {Duration::ns(ns);}
        void Microseconds(const int us) {Duration::us(us);}
        void Milliseconds(const int ms) {Duration::ms(ms);}
        void Seconds     (const int s ) {Duration::s (s );}
        void Minutes     (const int m ) {Duration::m (m );}
        void Hours       (const int h ) {Duration::h (h );}
        void Days        (const int d ) {Duration::d (d );}
        void Weeks       (const int w ) {Duration::w (w );}
    public:
        operator std::chrono::nanoseconds () const {return m_ns;}
        operator std::chrono::microseconds() const {return std::chrono::duration_cast<std::chrono::microseconds>(m_ns);}
        operator std::chrono::milliseconds() const {return std::chrono::duration_cast<std::chrono::milliseconds>(m_ns);}
        operator std::chrono::seconds     () const {return std::chrono::duration_cast<std::chrono::seconds>     (m_ns);}
        operator std::chrono::minutes     () const {return std::chrono::duration_cast<std::chrono::minutes>     (m_ns);}
        operator std::chrono::hours       () const {return std::chrono::duration_cast<std::chrono::hours>       (m_ns);}
        operator std::chrono::days        () const {return std::chrono::duration_cast<std::chrono::days>        (m_ns);}
        operator std::chrono::weeks       () const {return std::chrono::duration_cast<std::chrono::weeks>       (m_ns);}

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
        TimePoint() : m_tp(std::chrono::high_resolution_clock::now()) {}
        TimePoint(std::chrono::time_point<std::chrono::high_resolution_clock> timepoint) : m_tp(timepoint) {}
    public:
        operator std::chrono::time_point<std::chrono::high_resolution_clock>() {return m_tp;}

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
        std::chrono::time_point<std::chrono::high_resolution_clock> m_tp;
    };

    class Clock {
    public:
        static TimePoint Now() {return std::chrono::high_resolution_clock::now();}

        static Duration Nanoseconds (const double ns) {return Duration(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double, std::nano>         (ns)));}
        static Duration Microseconds(const double us) {return Duration(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double, std::micro>        (us)));}
        static Duration Milliseconds(const double ms) {return Duration(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double, std::milli>        (ms)));}
        static Duration Seconds     (const double s ) {return Duration(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>                    (s )));}
        static Duration Minutes     (const double m ) {return Duration(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double, std::ratio<60>>    (m )));}
        static Duration Hours       (const double h ) {return Duration(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double, std::ratio<3600>>  (h )));}
        static Duration Days        (const double d ) {return Duration(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double, std::ratio<86400>> (d )));}
        static Duration Weeks       (const double w ) {return Duration(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double, std::ratio<604800>>(w )));}
    };

    //inline Duration operator"" _ns(long double ns) { return Clock::Nanoseconds(ns); }
    //inline Duration operator"" _us(long double us) { return Clock::Microseconds(us); }
    //inline Duration operator"" _ms(long double ms) { return Clock::Milliseconds(ms); }
    //inline Duration operator"" _s (long double s)  { return Clock::Seconds(s); }
    //inline Duration operator"" _m (long double m)  { return Clock::Minutes(m); }
    //inline Duration operator"" _h (long double h)  { return Clock::Hours(h); }
}