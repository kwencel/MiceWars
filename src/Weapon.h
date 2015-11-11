#ifndef MICEWARS_WEAPON_H
#define MICEWARS_WEAPON_H

#include "Object.h"

class Weapon: public Object {
public:
    int damage;
    int dmg_range;
    short wants_to_move_crosshair = 0;

    Weapon(int x, int y, int width, int height, std::string img_path)
            : Object(x, y, width, height, img_path) { cout << "Weapon created!" << endl; }
    virtual void prepare() = 0;
    virtual void shoot() = 0;
};


#endif //MICEWARS_WEAPON_H
