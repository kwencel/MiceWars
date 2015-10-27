#ifndef MICEWARS_THROWNWEAPON_H
#define MICEWARS_THROWNWEAPON_H

#include "RangedWeapon.h"

using namespace std;

class ThrownWeapon: RangedWeapon {
public:
    float timer;

    ThrownWeapon(int x, int y, int width, int height)
            : RangedWeapon(x, y, width, height) { cout << "ThrownWeapon created!" << endl; }
    void shoot() override;
};


#endif //MICEWARS_THROWNWEAPON_H
