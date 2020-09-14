#ifndef MICEWARS_PARABOLICTRAJECTORY_H
#define MICEWARS_PARABOLICTRAJECTORY_H

#include "Trajectory.h"
#include "../global_vars.h"
#include "../Vector.h"
#include "../math/Math2D.h"

#include <cmath>

class ParabolicTrajectory : public Trajectory {
public:
    ParabolicTrajectory(Point p1, Point p2) : angle(Math2D::compute_acute_angle(p1, p2)), elapsedTime(0.0f), position(p1) { }
        vx0 = INITIAL_SPEED * cos(TEST_ANGLE);
        vy0 = INITIAL_SPEED * sin(TEST_ANGLE);
        cout << "------------------------------------------------\n";
        cout << position.x << "\t" << position.y << endl;
        // calculate range of trajectory
//        double range = (pow(INITIAL_SPEED,2)*sin((2*TEST_ANGLE_IN_RADIANS*M_PI)/180.00))/GRAVITY;
//        cout << "x range: " << range << endl;
    }

private:
    constexpr static const float GRAVITY = 9.81f;      // (m/s^2)
    constexpr static const float INITIAL_SPEED = 50.f; // (m/s)
    constexpr static const float TEST_ANGLE = 60 * M_PI / 180.0;


//    Vector v0;
//    double dt = 0.1;
    double vx0;
    double vy0;
    float angle;
    float elapsedTime;
    Point position;

    Point moveByTime(float deltaTime) override {
        double deltaTime2 = 0.1f;
        elapsedTime += deltaTime2;
        cout << "elapsedTime: " << elapsedTime << "\n";
        cout << "******** vx0 " << vx0 << " vy0 " << vy0 - GRAVITY * elapsedTime << endl;
        angle = TEST_ANGLE;

//        int x_offset = INITIAL_SPEED * std::cos(angle) * elapsedTime;
//        int y_offset = INITIAL_SPEED * std::sin(angle) * elapsedTime - 0.5 * GRAVITY * std::pow(elapsedTime, 2);
//        std::cout << "x_offset = " << x_offset << ", y_offset = " << y_offset << "\n";
//        return Point(position.x + x_offset, position.y - y_offset);

//        double vx1 = vx0 - (pow(vx0, 2) * (deltaTime2 / 2) );
//        double vx2 = vx0 - (pow(vx1, 2) * deltaTime2 );
//        double x = vx1 * deltaTime2 + position.x;
        double mov_x = vx0 * elapsedTime;
        double x_after_move = position.x + mov_x;

//        double vy1 = vy0 - (GRAVITY + vy0 * fabs(vy0) ) * (deltaTime2 / 2) ;
//        double vy2 = vy0 - (GRAVITY + vy1 * fabs(vy1) ) * deltaTime2;
//        double y = position.y - vy1*deltaTime2;
        double vy = vy0 - GRAVITY * elapsedTime;
        cout << "******** vx = vx0 : " << vx0 << ", vy : " << vy << endl;
        double mov_y = vy0 * elapsedTime - GRAVITY * elapsedTime * elapsedTime / 2;
        cout << "******************** x = distance : " << mov_x << ", height : " << mov_y << endl;
        double y_after_move = mov_y + position.y - 2 * mov_y;

//        position.x = x;
//        position.y = y;
//        vx0 = vx2;
//        vy0 = vy2;

        cout << x_after_move << "\t" << y_after_move << endl;
//        cout << "(delta_x) " << vx1*deltaTime2 << "\t" << "(delta_y) "<< -vy1*deltaTime2 << endl;
        return Point(x_after_move, y_after_move);
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

