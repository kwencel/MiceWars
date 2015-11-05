#ifndef MICEWARS_TIMER_H
#define MICEWARS_TIMER_H

#include <chrono>

// Based on: http://headerphile.com/sdl2/sdl2-part-9-no-more-delays/
class Timer {
private:
    // For delta time calculation, updated every frame
    // We use high_resolution_clock
    // because we want the highest possible accuracy
    std::chrono::time_point< std::chrono::high_resolution_clock > time_prev;
    float FPS = -1.0;
    double current_delta;
    static Timer* m_pInstance;
    Timer() { };

public:
    // Returns time since last time this function was called
    // in seconds with nanosecond precision
    double getNewDelta();
    double getDelta();
    void start() { time_prev = std::chrono::high_resolution_clock::now(); }
//    void restart();
    void setFPS(float FPS);
    static Timer* Instance();
};


#endif //MICEWARS_TIMER_H
