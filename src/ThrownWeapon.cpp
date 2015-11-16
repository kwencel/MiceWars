#include "ThrownWeapon.h"

void ThrownWeapon::shoot() {
  RangedWeapon::prepare();
}

void ThrownWeapon::prepare() {
  RangedWeapon::prepare();
}

void ThrownWeapon::save(std::ofstream &file) {
  RangedWeapon::save(file);
  file.write((char*)&timer, sizeof(timer));

}

void ThrownWeapon::load(std::ifstream &file) {
  RangedWeapon::load(file);
  file.read((char*)&timer, sizeof(timer));
}
