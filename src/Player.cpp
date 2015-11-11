#include "Player.h"

void Player::makeTurn() {
    if (current_mouse == nullptr) {
        current_mouse = mice_vector[0];
        current_mouse_vecpos = 0;
    }
    else {
        if (current_mouse_vecpos == mice_vector.size()) {
            current_mouse_vecpos = 0;   // Reset the counter if the end of vector was reached
        }
        else {
            ++current_mouse_vecpos;
        }
        current_mouse = mice_vector[current_mouse_vecpos];
    }
    current_mouse->can_move = true;
    current_mouse->movepoints = MOUSE_MOVEPOINTS;
}

std::string Player::getName() {
    return name;
}

int Player::getColour() {
    return colour;
}

void Player::handle_keys(SDL_Keycode keycode) {
    switch (keycode) {
        case SDLK_LEFT:
            if (current_mouse->can_move) {
                current_mouse->wants_to_move_direction = -1;
            }
            break;
        case SDLK_RIGHT:
            if (current_mouse->can_move) {
                current_mouse->wants_to_move_direction = 1;
            }
            break;
        case SDLK_UP:
            if (current_mouse->can_move) {
                current_mouse->weapon->wants_to_move_crosshair = -1;
            }
            break;
        case SDLK_DOWN:
            if (current_mouse->can_move) {
                current_mouse->weapon->wants_to_move_crosshair = 1;
            }
            break;
        case SDLK_1:
            current_mouse->changeWeapon(shotgun);
            break;
        case SDLK_2:
            current_mouse->changeWeapon(bazooka);
            break;
        case SDLK_3:
            current_mouse->changeWeapon(grenade);
            break;
        case SDLK_4:
            current_mouse->changeWeapon(cheesebomb);
            break;
        case SDLK_5:
            current_mouse->changeWeapon(mousetrap);
            break;
        default:break;
    }
}
