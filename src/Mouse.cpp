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
//                    space_key_released = true;
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
    if (weapon != nullptr) {
        weapon->destroy();
    }
    switch (index) {
        case shotgun: {
            RangedWeapon* shotgun = new RangedWeapon(pos_x + WEAPON_X_OFFSET, pos_y + WEAPON_Y_OFFSET, WEAPON_WIDTH,
                                                    WEAPON_HEIGHT, SHOTGUN_IMG);
            shotgun->damage = SHOTGUN_DAMAGE;
            shotgun->dmg_range = SHOTGUN_RANGE;
            shotgun->gravity = false;
            shotgun->weight = 0;
            weapon = shotgun;
            break;
        }
        case bazooka: {
            RangedWeapon* tmp_weapon = new RangedWeapon(pos_x + WEAPON_X_OFFSET, pos_y + WEAPON_Y_OFFSET, WEAPON_WIDTH,
                                                        WEAPON_HEIGHT, BAZOOKA_IMG);
            tmp_weapon->damage = BAZOOKA_DAMAGE;
            tmp_weapon->dmg_range = BAZOOKA_RANGE;
            tmp_weapon->gravity = true;
            tmp_weapon->weight = BAZOOKA_WEIGHT;
            weapon = tmp_weapon;
            break;

        }
        case grenade: {
            ThrownWeapon* tmp_weapon = new ThrownWeapon(pos_x + WEAPON_X_OFFSET, pos_y + WEAPON_Y_OFFSET, WEAPON_WIDTH,
                                                        WEAPON_HEIGHT, GRENADE_IMG);
            tmp_weapon->damage = GRENADE_DAMAGE;
            tmp_weapon->dmg_range = GRENADE_RANGE;
            tmp_weapon->gravity = true;
            tmp_weapon->weight = GRENADE_WEIGHT;
            tmp_weapon->timer = GRENADE_TIMER;
            weapon = tmp_weapon;
            break;

        }
        case cheesebomb: {
            ThrownWeapon* tmp_weapon = new ThrownWeapon(pos_x + WEAPON_X_OFFSET, pos_y + WEAPON_Y_OFFSET, WEAPON_WIDTH,
                                                        WEAPON_HEIGHT, CHEESE_IMG);
            tmp_weapon->damage = CHEESE_DAMAGE;
            tmp_weapon->dmg_range = CHEESE_RANGE;
            tmp_weapon->gravity = true;
            tmp_weapon->weight = CHEESE_WEIGHT;
            tmp_weapon->timer = CHEESE_TIMER;
            weapon = tmp_weapon;
            break;

        }
        case mousetrap: {
            PlacedWeapon* tmp_weapon = new PlacedWeapon(pos_x + WEAPON_X_OFFSET, pos_y + WEAPON_Y_OFFSET, WEAPON_WIDTH,
                                                        WEAPON_HEIGHT, MOUSE_TRAP_IMG);
            tmp_weapon->damage = MOUSE_TRAP_DAMAGE;
            tmp_weapon->dmg_range = MOUSE_TRAP_RANGE;
            tmp_weapon->trig_range = MOUSE_TRAP_TRIG_RANGE;
            weapon = tmp_weapon;
            break;
        }
        default:break;
    }
}

void Mouse::destroy() {
    Object::destroy();
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

//void Mouse::markPositionOnMap() {
//
//}

void Mouse::jump() {

}
