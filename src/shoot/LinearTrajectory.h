#ifndef MICEWARS_LINEARTRAJECTORY_H
#define MICEWARS_LINEARTRAJECTORY_H

#include "ParabolicTrajectory.h"
#include "../Point.h"

#include <cmath>

class LinearTrajectory : public ParabolicTrajectory {
public:
    LinearTrajectory(Point p1, Point p2) : ParabolicTrajectory(p1, p2, 0.0f, 15.f, 10) { }
};

#endif //MICEWARS_LINEARTRAJECTORY_H

