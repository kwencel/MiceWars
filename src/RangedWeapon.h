#ifndef MICEWARS_RANGEDWEAPON_H
#define MICEWARS_RANGEDWEAPON_H

#include "Weapon.h"

class RangedWeapon: public Weapon {
public:
    bool gravity;
    int weight;
    Object* bullet;
    Object* crosshair;

    RangedWeapon(int x, int y, int width, int height, std::string img_path )
            : Weapon(x, y, width, height, img_path) { cout << "RangedWeapon created!" << endl; }
    virtual void prepare();
    virtual void shoot();
    void moveCrosshair();
};


#endif //MICEWARS_RANGEDWEAPON_H
