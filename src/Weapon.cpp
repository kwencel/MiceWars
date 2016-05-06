#include <iosfwd>
#include "Object.h"
#include "Weapon.h"

void Weapon::save(std::ofstream& file) {
    Object::save(file);
    file.write((char*) &damage, sizeof(damage));
    file.write((char*) &dmg_range, sizeof(dmg_range));
    file.write((char*) &wants_to_move_crosshair, sizeof(wants_to_move_crosshair));
}

void Weapon::load(std::ifstream& file) {
    Object::load(file);
    file.read((char*) &damage, sizeof(damage));
    file.read((char*) &dmg_range, sizeof(dmg_range));
    file.read((char*) &wants_to_move_crosshair, sizeof(wants_to_move_crosshair));
}
