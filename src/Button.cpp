#include <iosfwd>
#include "Object.h"
#include "Button.h"
#include "Game.h"

Button::~Button() {
    cout << "Button destroyed!" << endl;
}

void Button::save(std::ofstream& file) {
    Object::save(file);
    file.write((char*) &state, sizeof(state));
}

void Button::load(std::ifstream& file) {
    Object::load(file);
    file.read((char*) &state, sizeof(state));
}

void Button::click() {
    //state = !state;
    if (this == Game::Instance()->buttons_vector[B_RESUME_GAME] and this->state) {
        Game::Instance()->pause();
    }
    else if (this == Game::Instance()->buttons_vector[B_SAVE_GAME] and this->state) {
        Game::Instance()->saveGame(SAVED_GAME);
        Game::Instance()->menu_needs_redraw = true;
        // TODO display "Game is saved"
    }
    else if (this == Game::Instance()->buttons_vector[B_LOAD_GAME] and this->state) {
        Game::Instance()->loadGame(SAVED_GAME);
        if (not Game::Instance()->world_map.empty()) {
            Game::Instance()->pause();
        }
    }
    else if (this == Game::Instance()->buttons_vector[B_QUIT_GAME]) {
        Game::Instance()->quit = true;
    }
    else if (this == Game::Instance()->buttons_vector[B_NEW_GAME] and !Game::Instance()->new_game) {
        Game::Instance()->new_game = true;
        Game::Instance()->buttons_vector[P_DAKTYL]->state = true;
        Game::Instance()->buttons_vector[P_MIKI]->state = true;
        Game::Instance()->menu_active_players = 2;
        Game::Instance()->menu_needs_redraw = true;
    }
    else if (this == Game::Instance()->buttons_vector[B_START] and this->state) {
        Game::Instance()->world_map.clear();
        if (!Game::Instance()->player_vector.empty()) {
            while (!Game::Instance()->player_vector.empty()) {
                delete Game::Instance()->player_vector[0];
            }
        }
        Game::Instance()->current_player = nullptr;
        Game::Instance()->current_player_vecpos = 0;
        Game::Instance()->players_count = 0;
        // Reading and generating
        Game::Instance()->generateTerrain();
        for (int i = 0; i <= 3; i++) {
            if (Game::Instance()->buttons_vector[i + P_DAKTYL]->state) {
                std::stringstream name;
                bool human;
                int mouse_amount;
                switch (i + P_DAKTYL) {
                    case P_DAKTYL: {
                        name << GREEN_MOUSE;
                        break;
                    }
                    case P_MIKI: {
                        name << PINK_MOUSE;
                        break;
                    }
                    case P_LAZARZ: {
                        name << BLUE_MOUSE;
                        break;
                    }
                    case P_ZIOMEK: {
                        name << RED_MOUSE;
                        break;
                    }
                    default: {
                        name << "";
                        break;
                    }
                }
                human = Game::Instance()->buttons_vector[i + B_AI_HUMAN_D]->state;
                mouse_amount = Game::Instance()->buttons_vector[i + B_NUM_D]->amount;
                Game::Instance()->createPlayer(name.str(), human, mouse_amount, 0);
            }
        }
        Game::Instance()->players_count = Game::Instance()->player_vector.size();
        Game::Instance()->placeMice();
        Game::Instance()->changePlayer();
        Game::Instance()->background_needs_redraw = true;
        Game::Instance()->pause();
        // load new_game
    }
    else if ((this == Game::Instance()->buttons_vector[B_AI_HUMAN_D]
              or this == Game::Instance()->buttons_vector[B_AI_HUMAN_M]
              or this == Game::Instance()->buttons_vector[B_AI_HUMAN_L]
              or this == Game::Instance()->buttons_vector[B_AI_HUMAN_Z]) and Game::Instance()->new_game) {
        this->state = !this->state;
        Game::Instance()->menu_needs_redraw = true;
    }
    else if ((this == Game::Instance()->buttons_vector[B_NUM_D]
              or this == Game::Instance()->buttons_vector[B_NUM_M]
              or this == Game::Instance()->buttons_vector[B_NUM_L]
              or this == Game::Instance()->buttons_vector[B_NUM_Z]) and Game::Instance()->new_game) {
        if (this->amount == 7) {
            this->amount = 1;
        } else {
            this->amount++;
        }
        Game::Instance()->menu_needs_redraw = true;
    }
    else if ((this == Game::Instance()->buttons_vector[P_DAKTYL]
              or this == Game::Instance()->buttons_vector[P_MIKI]
              or this == Game::Instance()->buttons_vector[P_LAZARZ]
              or this == Game::Instance()->buttons_vector[P_ZIOMEK]) and Game::Instance()->new_game) {
        this->state = !this->state;
        if (this->state) {
            Game::Instance()->menu_active_players++;
        }
        else {
            Game::Instance()->menu_active_players--;
        }
        Game::Instance()->menu_needs_redraw = true;
    }
}
