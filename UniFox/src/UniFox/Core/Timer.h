#pragma once

#include "Time.h"

#include <future>
#include <thread>
#include <functional>

namespace UniFox {
    /*class Timer {
    public:
        Timer() {}

        Timer(Duration duration, std::function<void()> callback) {
            m_Callback = callback;
            Start(duration, callback);
        };

        ~Timer() {}

        void Start() { m_Start = Clock::Now(); }
        Duration Stop() { m_Stop = Clock::Now(); return Duration(); }

        std::future<void> Start(Duration duration, std::function<void()> callback) {
            m_Duration = duration;
            m_Callback = callback;
            Start();
            return std::async(std::launch::async, [duration, callback]() {
                std::this_thread::sleep_for((std::chrono::nanoseconds)duration);
                callback();
            });
        }
        bool Finished() const {
            return (Clock::Now() - m_Start > m_Duration);
        }

        Duration Duration() const {
            using namespace std::chrono;
            return m_Stop - m_Start;
        }

        UniFox::Duration Elapsed() const {
            using namespace std::chrono;
            return Clock::Now() - m_Start;
        }

        UniFox::Duration Remainder() const {
            using namespace std::chrono;
            return m_Duration - (Clock::Now() - m_Start);
        }

    private:
        TimePoint m_Start, m_Stop;
        UniFox::Duration m_Duration;
        std::function<void()> m_Callback;
    };*/
}