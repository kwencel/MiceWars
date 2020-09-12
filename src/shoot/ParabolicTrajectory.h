#ifndef MICEWARS_PARABOLICTRAJECTORY_H
#define MICEWARS_PARABOLICTRAJECTORY_H

#include "Trajectory.h"
#include "../global_vars.h"
#include "../Vector.h"

#include <cmath>

class ParabolicTrajectory : public Trajectory {
private:
    constexpr static const float GRAVITY = 10.f;
    constexpr static const float VELOCITY = 20.f;

    Vector v0;
    float alfa;

    ParabolicTrajectory(Point pos_1, Point pos_2) : v0(Vector(pos_1, pos_2)), alfa(this->computeAngle(pos_1, pos_2)) {
    }

    float computeAngle(Point pos_1, Point pos_2) {
        float angle = atan2(pos_1.y - pos_2.y, pos_1.x - pos_2.x);
        float degrees = angle * 180 / PI;
        return degrees;
    }

    Vector compute_vx_t() {
        float cos_alfa = cos(alfa);
        new Vector(v0.v_x * cos_alfa, v0.v_y * cos_alfa);
    }

    Vector compute_vy_t() {
        
    }


};

#endif //MICEWARS_PARABOLICTRAJECTORY_H

