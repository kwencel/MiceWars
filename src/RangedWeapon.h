#ifndef MICEWARS_RANGEDWEAPON_H
#define MICEWARS_RANGEDWEAPON_H

#include "Weapon.h"

class RangedWeapon: Weapon {
public:
    bool gravity;
    int weight;
    Object* bullet;
    Object* crosshair;

    RangedWeapon(int x, int y, int width, int height )
            : Weapon(x, y, width, height) { cout << "RangedWeapon created!" << endl; }
    virtual void shoot();
    void moveCrosshair(bool direction);
};


#endif //MICEWARS_RANGEDWEAPON_H
