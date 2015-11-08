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
        default:break;
    }
}
