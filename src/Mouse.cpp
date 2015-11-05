#include "Mouse.h"
#include "Timer.h"
#include "global_vars.h"
#include "Game.h"

void Mouse::overcomeHill(bool direction) {
    int hill_pixels_used = 0;
    for (int pixel = 0; pixel < steps; ++pixel) {
        while (Game::Instance()->doesCollide(this) and (hill_pixels_used < HILL_OVERCOME_PIXELS)) {
            pos_y--;                    // Try to overcome the sharp hill
            ++hill_pixels_used;
        }
        if (hill_pixels_used == HILL_OVERCOME_PIXELS) { //  Number of tries (pixels) exceeded
            pos_y += HILL_OVERCOME_PIXELS;              // Revert to the previous position
            break;
        }
        pos_x--;
    }
}

void Mouse::move() {
    int steps = (int) (MICE_SPEED_MUL * Timer::Instance()->getDelta());
    if (wants_to_move == left) {
        if (facing_direction == right) {
            flipTexture();
        }
    }
    else if (wants_to_move == right) {
        if (facing_direction == left) {
            flipTexture();
        }
    }
    else {
        wants_to_move = 0;
        return;
    }

        int hill_pixels_used = 0;
        for (int pixel = 0; pixel < steps; ++pixel) {
            if (Game::Instance()->isInsideWindowBorders(this->pos_x + wants_to_move, this->pos_y))   // wants_to_move is negative for left movement
            if (Game::Instance()->doesCollide(this)) {                                               // and positive for right movement

            }

        }
    }
    else if (wants_to_move == right) {
        if (facing_direction == left) {
            flipTexture();
        }
    }
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
