#include <assert.h>
#include "Mouse.h"
#include "Timer.h"
#include "Game.h"
#include "RangedWeapon.h"
#include "ThrownWeapon.h"
#include "PlacedWeapon.h"

bool Mouse::overcomeHill(int direction) {
    int hill_pixels_used = 0;
    while (Game::Instance()->doesCollide(this, direction) and (hill_pixels_used < HILL_OVERCOME_PIXELS)) {
        pos_y--;                                    // Try to overcome the sharp hill
        ++hill_pixels_used;
    }
    if (hill_pixels_used == HILL_OVERCOME_PIXELS) { // If number of tries (pixels) exceeded
        pos_y += HILL_OVERCOME_PIXELS;              // Revert to the previous position
        return false;                               // Return mouse's failure to overcome the hill
    }
    pos_x += direction;
    if (--movepoints == 0) {
        can_move = false;
        return false;
    }
    return true;                                    // Return success
}

void Mouse::move() {
    if (wants_to_move_direction == stay) {
        return;
    }
    else if (wants_to_move_direction == left) {
        flip = false;
        weapon->flip = false;
    }
    else {
        flip = true;
        weapon->flip = true;
    }

    int steps = static_cast<int>(MICE_SPEED_MUL * Timer::Instance()->getDelta());
    if (steps == 0) {
        steps = 1;
    }
    for (int pixel = 0; pixel < steps; ++pixel) {
        if (Game::Instance()->isInsideWindowBorders(this, wants_to_move_direction)) {
            if (Game::Instance()->doesCollide(this, wants_to_move_direction)) { // checking collision in advance (prior to actually moving an object
                if (not overcomeHill(wants_to_move_direction)) {                // if collision is detected, try to overcome it (if it's not too high)
                    break;                                                      // if mouse didn't manage to overcome the hill, stop the further movement
                }
            }
            else {
                pos_x += wants_to_move_direction;
                if (--movepoints == 0) {
                    can_move = false;
                    break;
                }
            }
        }
        else {
            break;
        }
    }
    wants_to_move_direction = stay;
}

void Mouse::changeWeapon(short index) {
    weapon_index = index;
    delete weapon;
    weapon = nullptr;
    switch (index) {
        case shotgun: {
            RangedWeapon* shotgun = new RangedWeapon(pos_x + WEAPON_X_OFFSET, pos_y + WEAPON_Y_OFFSET, WEAPON_WIDTH,
                                                    WEAPON_HEIGHT, SHOTGUN_IMG);
            shotgun->damage = SHOTGUN_DAMAGE;
            shotgun->dmg_range = SHOTGUN_RANGE;
            shotgun->gravity = false;
            shotgun->weight = 0;
            shotgun->flip = this->flip;
            weapon = shotgun;
            break;
        }
        case bazooka: {
            RangedWeapon* bazooka = new RangedWeapon(pos_x + WEAPON_X_OFFSET, pos_y + WEAPON_Y_OFFSET, WEAPON_WIDTH,
                                                        WEAPON_HEIGHT, BAZOOKA_IMG);
            bazooka->damage = BAZOOKA_DAMAGE;
            bazooka->dmg_range = BAZOOKA_RANGE;
            bazooka->gravity = true;
            bazooka->weight = BAZOOKA_WEIGHT;
            bazooka->flip = this->flip;
            weapon = bazooka;
            break;

        }
        case grenade: {
            ThrownWeapon* grenade = new ThrownWeapon(pos_x + WEAPON_X_OFFSET, pos_y + WEAPON_Y_OFFSET, WEAPON_WIDTH,
                                                        WEAPON_HEIGHT, GRENADE_IMG);
            grenade->damage = GRENADE_DAMAGE;
            grenade->dmg_range = GRENADE_RANGE;
            grenade->gravity = true;
            grenade->weight = GRENADE_WEIGHT;
            grenade->timer = GRENADE_TIMER;
            grenade->flip = this->flip;
            weapon = grenade;
            break;

        }
        case cheesebomb: {
            ThrownWeapon* cheesebomb = new ThrownWeapon(pos_x + WEAPON_X_OFFSET, pos_y + WEAPON_Y_OFFSET, WEAPON_WIDTH,
                                                        WEAPON_HEIGHT, CHEESE_IMG);
            cheesebomb->damage = CHEESE_DAMAGE;
            cheesebomb->dmg_range = CHEESE_RANGE;
            cheesebomb->gravity = true;
            cheesebomb->weight = CHEESE_WEIGHT;
            cheesebomb->timer = CHEESE_TIMER;
            cheesebomb->flip = this->flip;
            weapon = cheesebomb;
            break;

        }
        case mousetrap: {
            PlacedWeapon* mousetrap = new PlacedWeapon(pos_x + WEAPON_X_OFFSET, pos_y + WEAPON_Y_OFFSET, WEAPON_WIDTH,
                                                        WEAPON_HEIGHT, MOUSE_TRAP_IMG);
            mousetrap->damage = MOUSE_TRAP_DAMAGE;
            mousetrap->dmg_range = MOUSE_TRAP_RANGE;
            mousetrap->trig_range = MOUSE_TRAP_TRIG_RANGE;
            mousetrap->flip = this->flip;

            weapon = mousetrap;
            break;
        }
        default:break;
    }
}

void Mouse::display() {
    Object::display();
    if (notification_hp != nullptr) {
        notification_hp->pos_x = pos_x;
        notification_hp->pos_y = pos_y - NOTIFICATION_HP_OFFSET;
        notification_hp->display();
    }
    if (weapon != nullptr) {
        weapon->pos_x = pos_x + WEAPON_X_OFFSET;
        weapon->pos_y = pos_y + WEAPON_Y_OFFSET;
        weapon->display();
    }
}

void Mouse::jump() {

}

Mouse::~Mouse() {
    bool found_itself = false;
    // Remove itself from the mice_vector
    for (int player_id = 0; player_id < Game::Instance()->player_vector.size(); ++player_id) {
        for (int mouse_id = 0; mouse_id < Game::Instance()->player_vector[player_id]->mice_vector.size(); ++mouse_id) {
            if (Game::Instance()->player_vector[player_id]->mice_vector[mouse_id] == this) {
                found_itself = true;
                Game::Instance()->player_vector[player_id]->mice_vector[mouse_id] = nullptr;
                Game::Instance()->player_vector[player_id]->mice_vector.erase(Game::Instance()->player_vector[player_id]->mice_vector.begin() + mouse_id);
                Game::Instance()->player_vector[player_id]->mice_vector.shrink_to_fit();
                break;
            }
        }
    }
    assert(found_itself);
    delete weapon;
    weapon = nullptr;
    delete notification_hp;
    notification_hp = nullptr;
    cout << "Mouse destroyed!" << endl;
}
