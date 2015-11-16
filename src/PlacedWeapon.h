#ifndef MICEWARS_PLACED_WEAPON_H
#define MICEWARS_PLACED_WEAPON_H

#include "Weapon.h"

class PlacedWeapon : public Weapon {
public:
    int trig_range;

    PlacedWeapon(int x, int y, int width, int height, std::string img_path)
            : Weapon(x, y, width, height, img_path), trig_range(trig_range) { cout << "PlacedWeapon created!" << endl; }
    ~PlacedWeapon() { cout << "PlacedWeapon destroyed!" << endl; }
    void prepare() override;
    void shoot() override;
    void explode();
    void save(std::ofstream& file) override;
    void load(std::ifstream& file) override;
};


#endif //MICEWARS_PLACED_WEAPON_H
