#include "ThrownWeapon.h"
#include "Game.h"

void ThrownWeapon::shoot() {
    wants_to_move_crosshair = stay;
    // CREATING BULLET
    if (bullet == nullptr) {
        if (flip) {
            bullet = new Object(pos_x + 2 * obj_width, getCenter().y, bullet_width, bullet_height, bullet_img);
        }
        else {
            bullet = new Object(pos_x - obj_width, getCenter().y, bullet_width, bullet_height, bullet_img);
        }
        bullet->flip = this->flip;
        bullet->angle = this->angle;
    }
    // CALCULATING TRAJECTORY
    float x1, y1, x2, y2;
    x1 = (this->bullet->pos_x);
    y1 = (this->bullet->pos_y);
    x2 = (crosshair->getCenter().x);
    y2 = (crosshair->getCenter().y);

    a_coefficient = (y1 - y2) / (x1 - x2);
    b_coefficient = y1 - (a_coefficient * x1);
    std::cout << "SHOOOOOOOOOOOOOOOOT!!!" << endl;
    Game::Instance()->current_player->end_turn = true;
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
