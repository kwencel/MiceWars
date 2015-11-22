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

void Player::handleKeys(const Uint8 *keystates) {
    if (keystates[SDL_SCANCODE_LEFT] and not end_turn) {
        if (current_mouse->can_move) {
            current_mouse->wants_to_move_direction = -1;
            current_mouse->weapon->flip = false;
        }
        else {
            current_mouse->flip = false;
        }
    }
    else if (keystates[SDL_SCANCODE_RIGHT] and not end_turn) {
        if (current_mouse->can_move) {
            current_mouse->wants_to_move_direction = 1;
            current_mouse->weapon->flip = true;
        }
        else {
            current_mouse->flip = true;
        }
    }
    if (keystates[SDL_SCANCODE_UP] and not end_turn) {
        if (not current_mouse->can_move) {
            current_mouse->weapon->wants_to_move_crosshair = -1;
        }
    }
    else if (keystates[SDL_SCANCODE_DOWN] and not end_turn) {
        if (not current_mouse->can_move) {
            current_mouse->weapon->wants_to_move_crosshair = 1;
        }
    }
}

void Player::handleKeys(SDL_Keycode keycode) {
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
            if (not end_turn) {
                current_mouse->changeWeapon(shotgun);
            }
            break;
        case SDLK_2:
            if (not end_turn) {
                current_mouse->changeWeapon(bazooka);
            }
            break;
        case SDLK_3:
            if (not end_turn) {
                current_mouse->changeWeapon(grenade);
            }
            break;
        case SDLK_4:
            if (not end_turn) {
                current_mouse->changeWeapon(cheesebomb);
            }
            break;
//        case SDLK_5:
//            if (not end_turn) {
//                current_mouse->changeWeapon(mousetrap);
//            }
//            break;
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
    //cout << "Player destroyed!" << endl;
}

void Player::save(std::ofstream &file) {
    file.write((char*)&colour, sizeof(int));
    file.write((char*)&current_mouse_vecpos, sizeof(int));
    file.write((char*)&mice_amount, sizeof(int));
    unsigned long weapon_amount_size = weapon_amount.size();
    file.write((char*)&weapon_amount_size, sizeof (unsigned long));
    if (weapon_amount_size > 0) {
        for (auto weapon : weapon_amount) {
            file.write((char *) &weapon, sizeof(int));
        }
    }
    if (mice_amount != 0) {
        for (int i=0; i < mice_amount; i++) {
            mice_vector[i]->save(file);
        }
    }
    file.write((char*)&player_vecpos, sizeof(int));
    file.write((char*)&is_human, sizeof(bool));
    file.write((char*)&end_turn, sizeof(bool));
}

void Player::load(std::ifstream &file) {
    weapon_amount.clear();
    file.read((char*)&colour, sizeof(int));
    // SETTING NAME
    if (colour == 1) name = GREEN_MOUSE;
    else if (colour == 2) name = PINK_MOUSE;
    else if (colour == 3) name = BLUE_MOUSE;
    else if (colour == 4) name = RED_MOUSE;
    //
    file.read((char*)&current_mouse_vecpos, sizeof(int));
    file.read((char*)&mice_amount, sizeof(int));
    unsigned long weapon_amount_size;
    file.read((char*)&weapon_amount_size, sizeof(unsigned long));
    if (weapon_amount_size > 0) {
        for (int i = 0; i < int(weapon_amount_size); i++) {
            int number;
            file.read((char*)&number, sizeof(int));
            weapon_amount.push_back(number);
        }
    }
    if (mice_amount != 0) {
        for (int i=0; i< mice_amount; i++) {
            Mouse* mouse = new Mouse();
            (*mouse).load(file);
            mice_vector.push_back(mouse);
        }
    }
    file.read((char*)&player_vecpos, sizeof(int));
    file.read((char*)&is_human, sizeof(bool));
    current_mouse = mice_vector[current_mouse_vecpos];
    file.read((char*)&end_turn, sizeof(bool));
}

