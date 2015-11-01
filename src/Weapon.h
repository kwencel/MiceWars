#ifndef MICEWARS_WEAPON_H
#define MICEWARS_WEAPON_H

#include "Object.h"

using namespace std;

class Weapon: public Object {
public:
    int damage;
    int dmg_range;

    Weapon(int x, int y, int width, int height)
            : Object(x, y, width, height) { cout << "Weapon created!" << endl; }
    virtual void shoot() = 0;
};


#endif //MICEWARS_WEAPON_H
