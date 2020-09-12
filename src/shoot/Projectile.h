#ifndef MICEWARS_PROJECTILE_H
#define MICEWARS_PROJECTILE_H


#include <utility>
#include <memory>

#include "../Object.h"
#include "Trajectory.h"
#include "ParabolicTrajectory.h"

class Projectile : public Object {
public:
    Projectile(int x, int y, int width, int height, std::unique_ptr<Trajectory> trajectory, std::string img_path = "")
    : Object(x, y, width, height, img_path), trajectory(std::move(trajectory)) { }

    Projectile(Point center, int width, int height, std::unique_ptr<Trajectory> trajectory, std::string img_path = "")
            : Object(center, width, height, img_path), trajectory(std::move(trajectory)) { }

    Point move(float deltaTime) {
        return trajectory->moveByTime(deltaTime);
    }
private:
    std::unique_ptr<Trajectory> trajectory;
};


#endif //MICEWARS_PROJECTILE_H
