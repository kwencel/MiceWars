#ifndef MICEWARS_PLAYER_H
#define MICEWARS_PLAYER_H

#include <vector>
#include <string>
#include "Mouse.h"

class Player {
private:
    std::string name;
    int colour;
    //Mouse* current_mouse = nullptr;
    int current_mouse_vecpos = 0;
    std::vector<int> weapon_amount;

public:
    std::vector<Mouse*> mice_vector;
    int mice_amount;
    bool is_human;
    Mouse* current_mouse = nullptr;

    Player(std::string name, bool is_human, int mouse_amount, int colour)
            : name(name), is_human(is_human), mice_amount(mouse_amount), colour(colour) { cout << "Player created!" << endl; };
    virtual void makeTurn();    // Selects the current mouse to make turn, control is provided by readKeyboardState() in Game class
    void handle_keys(const Uint8* keystates);
    void handle_keys(SDL_Keycode keycode);
    std::string getName();
    int getColour();
    void save(std::ofstream& file);
    void load(std::ifstream& file);

};


#endif //MICEWARS_PLAYER_H
