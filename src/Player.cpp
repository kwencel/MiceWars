#include "Player.h"
#include "Game.h"

void Player::makeTurn() {
    if (current_mouse == nullptr) {
        current_mouse = mice_vector[0];
        current_mouse_vecpos = 0;
    }
    else {
        if (current_mouse_vecpos >= static_cast<int>(mice_vector.size()) - 1) {
            if (mice_vector.size() == 0) {
                return;
            }
            current_mouse_vecpos = 0;   // Reset the counter if the end of vector was reached
            current_mouse = mice_vector[0];
        }
        else {
            ++current_mouse_vecpos;
        }
        current_mouse = mice_vector[current_mouse_vecpos];
    }
    end_turn = false;
    current_mouse->can_move = true;
    current_mouse->movepoints = MOUSE_MOVEPOINTS;
    current_mouse->weapon->angle = 0;
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
            current_mouse->weapon->flip = false;
        }
        else {
            current_mouse->flip = false;
        }
    }
    else if (keystates[SDL_SCANCODE_RIGHT]) {
        if (current_mouse->can_move) {
            current_mouse->wants_to_move_direction = 1;
            current_mouse->weapon->flip = true;
        }
        else {
            current_mouse->flip = true;
        }
    }
    if (keystates[SDL_SCANCODE_UP]) {
        if (not current_mouse->can_move and not end_turn) {
            current_mouse->weapon->wants_to_move_crosshair = -1;
        }
    }
    else if (keystates[SDL_SCANCODE_DOWN]) {
        if (not current_mouse->can_move and not end_turn) {
            current_mouse->weapon->wants_to_move_crosshair = 1;
        }
    }
}

void Player::handle_keys(SDL_Keycode keycode) {
    switch (keycode) {
        case SDLK_SPACE:
            if (current_mouse->can_move) {
                current_mouse->can_move = false;
                current_mouse->movepoints = 0;
            }
            else {
                if (not end_turn) {
                    current_mouse->weapon->shoot();
                }
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

Player::~Player() {
    // Remove all mice remaining (shouldn't be necessary, just in case)
    while (not mice_vector.empty()) {
        delete mice_vector[0];
    }
    // Remove itself from player_vector
    for (int i = 0; i < Game::Instance()->player_vector.size(); ++i) {
        if (Game::Instance()->player_vector[i] == this) {
            Game::Instance()->player_vector.erase(Game::Instance()->player_vector.begin() + i);
            Game::Instance()->player_vector.shrink_to_fit();
        }
    }
    // Check if other player has a matching vecpos
    for (int i = 0; i < Game::Instance()->player_vector.size(); ++i) {
        Game::Instance()->player_vector[i]->player_vecpos = i;
    }
    Game::Instance()->players_count--;
    cout << "Player destroyed!" << endl;
}
