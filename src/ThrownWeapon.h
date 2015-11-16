#ifndef MICEWARS_THROWNWEAPON_H
#define MICEWARS_THROWNWEAPON_H

#include "RangedWeapon.h"

class ThrownWeapon: public RangedWeapon {
public:
    float timer;

    ThrownWeapon(int x, int y, int width, int height, std::string img_path)
            : RangedWeapon(x, y, width, height, img_path) { cout << "ThrownWeapon created!" << endl; }
    ~ThrownWeapon() { cout << "ThrownWeapon destroyed!" << endl; }
    void prepare() override;
    void shoot() override;
    void save(std::ofstream& file) override;
    void load(std::ifstream& file) override;
};


#endif //MICEWARS_THROWNWEAPON_H
