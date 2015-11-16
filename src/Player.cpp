#include "Player.h"

void Player::makeTurn() {
    if (current_mouse == nullptr) {
        current_mouse = mice_vector[0];
        current_mouse_vecpos = 0;
    }
    else {
        current_mouse->weapon->angle = 0;
        if (current_mouse_vecpos >= mice_vector.size() - 1) {
            if (mice_vector.size() == 0) {

            }
            current_mouse_vecpos = 0;   // Reset the counter if the end of vector was reached
            current_mouse = mice_vector[0];
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

void Player::handle_keys(const Uint8* keystates) {
    if (keystates[SDL_SCANCODE_LEFT]) {
        if (current_mouse->can_move) {
            current_mouse->wants_to_move_direction = -1;
        }
    }
    else if (keystates[SDL_SCANCODE_RIGHT]) {
        if (current_mouse->can_move) {
            current_mouse->wants_to_move_direction = 1;
        }
    }
    if (keystates[SDL_SCANCODE_UP]) {
        if (not current_mouse->can_move) {
            current_mouse->weapon->wants_to_move_crosshair = -1;
        }
    }
    else if (keystates[SDL_SCANCODE_DOWN]) {
        if (not current_mouse->can_move) {
            current_mouse->weapon->wants_to_move_crosshair = 1;
        }
    }
//    if (keystates[SDL_SCANCODE_SPACE]) {
//        if (current_mouse->can_move) {
//            current_mouse->can_move = false;
//            current_mouse->movepoints = 0;
//            current_mouse->space_key_released = false;
//        }
//        else if (current_mouse->space_key_released) {
//            current_mouse->weapon->shoot();
//        }
//    }
}
void Player::handle_keys(SDL_Keycode keycode) {
    switch (keycode) {
        case SDLK_SPACE:
            if (current_mouse->can_move) {
                current_mouse->can_move = false;
                current_mouse->movepoints = 0;
            }
            else {
                current_mouse->weapon->shoot();
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

void Player::save(std::ofstream &file) {
    file.write((char*)&this->name, sizeof(name));
    file.write((char*)&this->colour, sizeof(int));
    file.write((char*)&this->current_mouse_vecpos, sizeof(int));
    file.write((char*)&this->mice_amount, sizeof(int));
    file.write((char*)&this->is_human, sizeof(bool));
}

void Player::load(std::ifstream &file) {
    file.read((char*)&this->name, sizeof(name));
    file.read((char*)&this->colour, sizeof(int));
    file.read((char*)&this->current_mouse_vecpos, sizeof(int));
    file.read((char*)&this->mice_amount, sizeof(int));
    file.read((char*)&this->is_human, sizeof(bool));
}
