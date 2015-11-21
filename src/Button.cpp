#include <iosfwd>
#include "Object.h"
#include "Button.h"
#include "Game.h"

Button::~Button() {
    cout << "Button destroyed!" << endl;
}
void Button::save(std::ofstream &file) {
    Object::save(file);
    file.write((char*)&state, sizeof(state));
}

void Button::load(std::ifstream &file) {
    Object::load(file);
    file.read((char*)&state, sizeof(state));
}

void Button::click() {
    //state = !state;
    if (this == Game::Instance()->buttons_vector[B_RESUME_GAME]) {
        Game::Instance()->pause();
    }
    else if (this == Game::Instance()->buttons_vector[B_SAVE_GAME] and this->state) {
        Game::Instance()->saveGame(SAVED_GAME);
        Game::Instance()->menu_need_redraw = true;
        // TODO display "Game is saved"
    }
    else if (this == Game::Instance()->buttons_vector[B_LOAD_GAME] and this->state) {
        Game::Instance()->loadGame(SAVED_GAME);
        Game::Instance()->pause();
    }
    else if (this == Game::Instance()->buttons_vector[B_QUIT_GAME]) {
        Game::Instance()->quit = true;
    }
    else if (this == Game::Instance()->buttons_vector[B_NEW_GAME]) {
        Game::Instance()->new_game = true;
        Game::Instance()->buttons_vector[P_DAKTYL]->state = true;
        Game::Instance()->buttons_vector[P_MIKI]->state = true;
        Game::Instance()->menu_active_players = 2;
        Game::Instance()->menu_need_redraw = true;
    }
    else if (this == Game::Instance()->buttons_vector[B_START] and this->state) {
        // load new_game
    }
    else if ((this == Game::Instance()->buttons_vector[B_AI_HUMAN_D]
              or this == Game::Instance()->buttons_vector[B_AI_HUMAN_M]
              or this == Game::Instance()->buttons_vector[B_AI_HUMAN_L]
              or this == Game::Instance()->buttons_vector[B_AI_HUMAN_Z]) and Game::Instance()->new_game) {
        this->state = !this->state;
        // TODO change in player if AI or HUMAN
        Game::Instance()->menu_need_redraw = true;
    }
    else if ((this == Game::Instance()->buttons_vector[P_DAKTYL]
              or this == Game::Instance()->buttons_vector[P_MIKI]
              or this == Game::Instance()->buttons_vector[P_LAZARZ]
              or this == Game::Instance()->buttons_vector[P_ZIOMEK]) and Game::Instance()->new_game) {
        this->state = !this->state;
        if (this->state) {
            // TODO adding player to vector?
            Game::Instance()->menu_active_players++;
        }
        else {
            // TODO deleting player from vector
            Game::Instance()->menu_active_players--;
        }
        Game::Instance()->menu_need_redraw = true;
    }
}
