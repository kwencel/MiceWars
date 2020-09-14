#include "ThrownWeapon.h"
#include "Game.h"

void ThrownWeapon::shoot() {
    if (crosshair == nullptr) {
        return;
    }
    wants_to_move_crosshair = stay;
    // CREATING BULLET
    if (bullet == nullptr) {
        if (flip) {
            bullet = new Projectile(pos_x + 2 * obj_width, getCenter().y, bullet_width, bullet_height, crosshair->getCenter(), bullet_img);
        }
        else {
            bullet = new Projectile(pos_x - obj_width, getCenter().y, bullet_width, bullet_height, crosshair->getCenter(), bullet_img);
        }
        bullet->flip = this->flip;
        bullet->angle = this->angle;
    }



//    // CALCULATING TRAJECTORY
//    float x1, y1, x2, y2;
//    x1 = (this->bullet->pos_x);
//    y1 = (this->bullet->pos_y);
//    x2 = (crosshair->getCenter().x);
//    y2 = (crosshair->getCenter().y);
//
//    a_coefficient = (y1 - y2) / (x1 - x2);
//    if (not flip and a_coefficient > 1.0) {
//        if ((a_coefficient = 1.0 / a_coefficient) > 0.5) {
//            a_coefficient = 0.5;
//        }
//    }
//    b_coefficient = y1 - (a_coefficient * x1);
    Game::Instance()->current_player->end_turn = true;
}

void ThrownWeapon::prepare() {
    RangedWeapon::prepare();
}

void ThrownWeapon::save(std::ofstream& file) {
    RangedWeapon::save(file);
    file.write((char*) &timer, sizeof(timer));

}

void ThrownWeapon::load(std::ifstream& file) {
    RangedWeapon::load(file);
    file.read((char*) &timer, sizeof(timer));
}
