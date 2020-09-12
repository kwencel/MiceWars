#ifndef MICEWARS_TRAJECTORY_H
#define MICEWARS_TRAJECTORY_H

#include <vector>
#include "../Point.h"

class Trajectory {
public:
//    virtual std::vector<Point> getTrajectory(Point p1, Point p2) = 0;

    virtual Point moveByTime(float deltaTime) = 0;
};

#endif //MICEWARS_TRAJECTORY_H
