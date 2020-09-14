#ifndef MICEWARS_PARABOLICTRAJECTORY_H
#define MICEWARS_PARABOLICTRAJECTORY_H

#include "Trajectory.h"
#include "../global_vars.h"
#include "../Vector.h"
#include "../math/Math2D.h"

#include <cmath>

class ParabolicTrajectory : public Trajectory {
public:
    ParabolicTrajectory(Point p1, Point p2) : ParabolicTrajectory(p1, p2, 9.81f, 15.f, 10) { }
    ParabolicTrajectory(Point p1, Point p2, float gravity, float initial_speed, float pixel_to_meter_proportion) :
        angle(Math2D::compute_acute_angle(p1, p2)), elapsedTime(0.0f), initial_position(p1),
        gravity(gravity), initial_speed(initial_speed), pixel_to_meter_proportion(pixel_to_meter_proportion) {
        x_direction = setupXDirection(p1, p2);
        angle = -angle;
        vx0 = initial_speed * cos(angle);
        vy0 = initial_speed * sin(angle);
        std::cout << "------------------------------------------------\n";
        std::cout << "START(x, y) -> " << initial_position.x << "\t" << initial_position.y << "\n";
        std::cout << "START(radians, degrees) -> " << angle << "\t (" << angle * 180 / PI << ")\n";
        std::cout << "START(vx0, vy0) -> " << vx0 << "\t" << vy0 << "\n";
        std::cout << "START(INITIAL_SPEED) -> " << initial_speed << "\n";
        std::cout << "START(GRAVITY) -> " << gravity << "\n";
        std::cout << "------------------------------------------------\n";

    }

private:
    /*
     * gravity (m/s^2)
     * Greater gravity, go down faster
     * For now let's not change that so the gravity can behave like in real world
     */
    float gravity;
    /*
     * initial_speed (m/s)
     * Greater speed, further flies
     */
    float initial_speed;
    /*
     * pixel_to_meter_proportion (pixels / m)
     * it tells us how many pixels is one meter
     * greater proportion, faster bullet
     * so you can manipulate with initial_speed and pixel_to_meter_proportion to control power and speed.
     * Remember that when you increase pixel_to_meter_proportion it will fly faster but as a result also further.
     * If you want to change only speed than increase pixel_to_meter_proportion and decrease initial_speed
     */
    int pixel_to_meter_proportion;

    short x_direction;
    double vx0;
    double vy0;
    float angle;
    float elapsedTime;
    Point initial_position;

    Point moveByTime(float deltaTime) override {
        elapsedTime += deltaTime;
//        cout << "elapsedTime: " << elapsedTime << "\n";

        double mov_x = pixel_to_meter_proportion * vx0 * elapsedTime * x_direction;
        double x_after_move = initial_position.x + mov_x;

        double vy = vy0 - gravity * elapsedTime;
//        cout << "vx = vx0 : " << vx0 << ", vy : " << vy << endl;
        double mov_y = pixel_to_meter_proportion * (vy0 * elapsedTime - gravity * elapsedTime * elapsedTime / 2);
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

