#include "Timer.h"

double Timer::getDelta() {
    // 1. Get current time as a std::chrono::time_point
    auto timeCurrent = high_resolution_clock::now();

    // 2. Get the time difference as seconds
    // ...represented as a double
    duration< double > delta( timeCurrent - time_prev );

    // 3. Reset the timePrev to the current point in time
    time_prev = high_resolution_clock::now();

    // 4. Returns the number of ticks in delta
    return delta.count();
}