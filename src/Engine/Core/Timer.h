#pragma once
#include <chrono>

namespace ENGINE {
    class Timer {
        public:
            Timer() { this->Reset(); }

            void Reset() {
                this->m_Start = std::chrono::high_resolution_clock::now();
            }

            float Elapsed() {
                return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - this->m_Start).count() * 0.001f * 0.001f * 0.001f;
            }

            float ElapsedMillis() {
                return this->Elapsed() * 1000.0f;
            }

        private:
            std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
    };
}