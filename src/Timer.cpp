#include "Timer.h"

Timer* Timer::m_pInstance = nullptr;

Timer* Timer::Instance() {
    if (!m_pInstance) {
        m_pInstance = new Timer;
    } // Only allow one instance at time
}


double Timer::getNewDelta() {
    // 1. Get current time as a std::chrono::time_point
    auto timeCurrent = high_resolution_clock::now();

    // 2. Get the time difference as seconds
    // ...represented as a double
    duration< double > delta( timeCurrent - time_prev );

    // 3. Reset the timePrev to the current point in time
    time_prev = high_resolution_clock::now();

    // 4. Saves current delta to current_delta
    current_delta = delta.count();

    // 5. Returns the number of ticks in delta
    return current_delta;
}

double Timer::getDelta() {
    return current_delta;
}