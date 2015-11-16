#include "PlacedWeapon.h"

void PlacedWeapon::prepare() {

}

void PlacedWeapon::explode() {

}

void PlacedWeapon::shoot() {

}

void PlacedWeapon::save(std::ofstream &file) {
    Weapon::save(file);
    file.write((char*)&trig_range, sizeof(trig_range));
}

void PlacedWeapon::load(std::ifstream &file) {
    Weapon::load(file);
    file.read((char*)&trig_range, sizeof(trig_range));
}
