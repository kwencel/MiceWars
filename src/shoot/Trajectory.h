#ifndef MICEWARS_TRAJECTORY_H
#define MICEWARS_TRAJECTORY_H

#include <vector>
#include "../Point.h"

class Trajectory {
public:
    virtual std::vector<Point> getTrajectory(Point pos_1, Point pos_2) = 0;
};

#endif //MICEWARS_TRAJECTORY_H
