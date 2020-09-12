#ifndef MICEWARS_PARABOLICTRAJECTORY_H
#define MICEWARS_PARABOLICTRAJECTORY_H

#include "Trajectory.h"
#include "../global_vars.h"
#include "../Vector.h"

#include <cmath>

class ParabolicTrajectory : public Trajectory {
public:
    ParabolicTrajectory(Point p1, Point p2) : angle(computeAngle(p1, p2)), elapsedTime(0.0f), position(p1) { }

private:
    constexpr static const float GRAVITY = 10.f;      // g
    constexpr static const float INITIAL_SPEED = 5.f; // U


//    Vector v0;
    float angle;
    float elapsedTime;
    Point position;

    Point moveByTime(float deltaTime) override {
        elapsedTime += deltaTime;
        int x_offset = INITIAL_SPEED * std::cos(angle) * elapsedTime;
        int y_offset = INITIAL_SPEED * std::sin(angle) * elapsedTime - 0.5 * GRAVITY * std::pow(elapsedTime, 2);
        position.x += x_offset;
        position.y += y_offset;
        std::cout << "x_offset = " << x_offset << ", y_offset = " << y_offset << "\n";
        return position;
    }

    static float computeAngle(Point p1, Point p2) {
        Point vector_distance = Point( p2.x - p1.x, p2.y - p1.y);
        Point vector_floor = Point( p2.x - p1.x, 0);
        float angle = std::atan2(vector_floor.y - vector_distance.y, vector_floor.x - vector_distance.x);
        float degrees = angle * 180 / PI;
        std::cout << "angle = " << angle << ", degrees = " << degrees << "\n";
        return angle;
    }

//    std::vector<Point> getTrajectory(Point pos_1, Point pos_2) override {
//
//    }
//

//
//    Vector compute_movement_x() {
//        float cos_alfa = cos(angle);
//        new Vector(v0.v_x * cos_alfa, v0.v_y * cos_alfa);
//    }
//
//    Vector compute_vy_t() {
//
//    }
};

#endif //MICEWARS_PARABOLICTRAJECTORY_H

