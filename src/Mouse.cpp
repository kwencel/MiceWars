#include "Mouse.h"
#include "Timer.h"
#include "Game.h"

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
        flip = 0;
    }
    else {
        flip = 1;
    }

    int steps = (int) (MICE_SPEED_MUL * Timer::Instance()->getDelta());
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
    wants_to_move_direction = 0;
}

void Mouse::ready() {

}

void Mouse::changeWeapon() {

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
}

void Mouse::jump() {

}
