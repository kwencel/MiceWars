#ifndef MICEWARS_TRAJECTORY_H
#define MICEWARS_TRAJECTORY_H

#include <vector>
#include "../Point.h"

class Trajectory {
public:
    virtual Point moveByTime(float deltaTime) = 0;
};

#endif //MICEWARS_TRAJECTORY_H
