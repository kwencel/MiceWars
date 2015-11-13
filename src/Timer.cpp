#include "Timer.h"

Timer* Timer::m_pInstance = nullptr;

Timer* Timer::Instance() {
    if (m_pInstance == nullptr) {
        m_pInstance = new Timer;
    }
    return m_pInstance;
}

double Timer::getNewDelta() {
    //if (FPS != -1) { return current_delta; }
    // 1. Get current time as a std::chrono::time_point
    auto timeCurrent = std::chrono::high_resolution_clock::now();

    // 2. Get the time difference as seconds
    // ...represented as a double
    std::chrono::duration<double> delta( timeCurrent - time_prev );

    // 3. Reset the timePrev to the current point in time
    time_prev = std::chrono::high_resolution_clock::now();

    // 4. Saves current delta to current_delta
    current_delta = delta.count();

    // 5. Returns the number of ticks in delta
    return current_delta;
}

double Timer::getDelta() {
    return current_delta;
}

void Timer::setFPS(float FPS) {
    this->FPS = FPS;
    this->current_delta = 1.0/FPS;
    this->target_frametime = 1.0/FPS;
}

float Timer::getFPS() {
    return FPS;
}

double Timer::getTargetFrametime() {
    return target_frametime;
}

double Timer::getTimeFromLastDelta() {
    std::chrono::duration<double> time_from_last_delta (getTime() - time_prev);
    return time_from_last_delta.count();
}
