#pragma once

#include "UniFox/Core/Core.h"
#include "UniFox/Core/Time.h"

namespace UniFox {
    class Stopwatch {
    public:
        Stopwatch() {Start();}
        ~Stopwatch() {}

        void Start() {
            elapsed = Duration(0);
            running = true;
            m_Last = Time::Now();
        }

        Duration Stop() {
            elapsed += Time::Now() - m_Last;
            return elapsed;
        }

        void Pause() {
            if(!running) return;
            elapsed += Time::Now() - m_Last;
            running = false;
        }

        void Resume() {
            if(running) return;
            running = true;
            m_Last = Time::Now();
        }

        Duration Elapsed() {
            if(!running) return elapsed;
            return elapsed + (Time::Now() - m_Last);
        }

        bool Running() {
            return running;
        }
    public:
        operator Duration() const {return Duration(elapsed.s());}
    private:
        TimePoint m_Last;
        Duration elapsed;
        bool running = false;
    };
}