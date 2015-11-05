#include "Mouse.h"
#include "Timer.h"

void Mouse::move() {
    if (wants_to_move == left) {
        if (facing_direction == right) {
            flipTexture();
        }
        //if (not Game::Instance()->doesCollide(this)) {
            pos_x -= 100 * Timer::Instance()->getDelta();
        //}
    }
    else if (wants_to_move == right) {
        if (facing_direction == left) {
            flipTexture();
        }
        //if (not Game::Instance()->doesCollide(this)) {
            pos_x += 100 * Timer::Instance()->getDelta();
        //}
    }
    wants_to_move = -1;
}

void Mouse::ready() {

}

void Mouse::changeWeapon() {

}

void Mouse::destroy() {
    Object::destroy();
}

void Mouse::jump() {

}

void Mouse::flipTexture() {

}
