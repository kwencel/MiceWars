#ifndef MICEWARS_PLACED_WEAPON_H
#define MICEWARS_PLACED_WEAPON_H

#include "Weapon.h"

using namespace std;

class PlacedWeapon : Weapon {
public:
    int trig_range;

    PlacedWeapon(int x, int y, int width, int height, int trig_range)
            : Weapon(x, y, width, height), trig_range(trig_range) { cout << "PlacedWeapon created!" << endl; }
    void shoot() override;
    void explode();
};


#endif //MICEWARS_PLACED_WEAPON_H
