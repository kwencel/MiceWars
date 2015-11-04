#ifndef MICEWARS_TIMER_H
#define MICEWARS_TIMER_H

#include <chrono>
using namespace std::chrono;

// Based on: http://headerphile.com/sdl2/sdl2-part-9-no-more-delays/
class Timer {
private:
    // For delta time calculation, updated every frame
    // We use high_resolution_clock
    // because we want the highest possible accuracy
    time_point< high_resolution_clock > time_prev;
    double current_delta;
    Timer() { };
    Timer(Timer const&) { };
    Timer& operator=(Timer const&) { };
    static Timer* m_pInstance;

public:
    // Returns time since last time this function was called
    // in seconds with nanosecond precision
    double getNewDelta();
    double getDelta();
    void start() { time_prev = high_resolution_clock::now(); }
//    void restart();
    static Timer* Instance();

};


#endif //MICEWARS_TIMER_H
