#ifndef MICEWARS_PARABOLICTRAJECTORY_H
#define MICEWARS_PARABOLICTRAJECTORY_H

#include "Trajectory.h"
#include "../global_vars.h"
#include "../Vector.h"
#include "../math/Math2D.h"

#include <cmath>

class ParabolicTrajectory : public Trajectory {
public:
    ParabolicTrajectory(Point p1, Point p2) : angle(Math2D::compute_acute_angle(p1, p2)), elapsedTime(0.0f), initial_position(p1) {
        x_direction = setupXDirection(p1, p2);
        angle = -angle;
        vx0 = INITIAL_SPEED * cos(angle);
        vy0 = INITIAL_SPEED * sin(angle);
        std::cout << "------------------------------------------------\n";
        std::cout << "START(x, y) -> " << initial_position.x << "\t" << initial_position.y << "\n";
        std::cout << "START(radians, degrees) -> " << angle << "\t (" << angle * 180 / PI << ")\n";
        std::cout << "START(vx0, vy0) -> " << vx0 << "\t" << vy0 << "\n";
        std::cout << "START(INITIAL_SPEED) -> " << INITIAL_SPEED << "\n";
        std::cout << "START(GRAVITY) -> " << GRAVITY << "\n";
        std::cout << "------------------------------------------------\n";

    }

private:
    /*
     * GRAVITY (m/s^2)
     * Greater gravity, go down faster
     * For now let's not change that so the gravity can behave like in real world
     */
    constexpr static const float GRAVITY = 9.81f;
    /*
     * INITIAL SPEED (m/s)
     * Greater speed, further flies
     */
    constexpr static const float INITIAL_SPEED = 15.f;
    /*
     * PIXEL_TO_METER_PROPORTION (pixels / m)
     * it tells us how many pixels is one meter
     * greater proportion, faster bullet
     * so you can manipulate with INITIAL_SPEED and PIXEL_TO_METER_PROPORTION to control power and speed.
     * Remember that when you increase PIXEL_TO_METER_PROPORTION it will fly faster but as a result also further.
     * If you want to change only speed than increase PIXEL_TO_METER_PROPORTION and decrease INITIAL_SPEED
     */
    constexpr static const int PIXEL_TO_METER_PROPORTION = 10;

    short x_direction;
    double vx0;
    double vy0;
    float angle;
    float elapsedTime;
    Point initial_position;

    Point moveByTime(float deltaTime) override {
        elapsedTime += deltaTime;
//        cout << "elapsedTime: " << elapsedTime << "\n";

        double mov_x = PIXEL_TO_METER_PROPORTION * vx0 * elapsedTime * x_direction;
        double x_after_move = initial_position.x + mov_x;

        double vy = vy0 - GRAVITY * elapsedTime;
//        cout << "vx = vx0 : " << vx0 << ", vy : " << vy << endl;
        double mov_y = PIXEL_TO_METER_PROPORTION * (vy0 * elapsedTime - GRAVITY * elapsedTime * elapsedTime / 2);
//        cout << "x move (distance) : " << mov_x << ", y move (height) : " << mov_y << endl;
        double y_after_move = initial_position.y - mov_y;

//        std::cout << "new position: " << x_after_move << "\t" << y_after_move << endl;
        return Point(x_after_move, y_after_move);
    }

    short setupXDirection(Point p1, Point p2) {
        if (p1.x < p2.x) return 1;
        else return -1;
    }
};

#endif //MICEWARS_PARABOLICTRAJECTORY_H

