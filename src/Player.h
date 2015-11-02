#ifndef MICEWARS_PLAYER_H
#define MICEWARS_PLAYER_H

#include <vector>
#include <string>
#include "Mouse.h"

using namespace std;

class Player {
private:
    string name;
    int colour;
    int last_mouse;
    vector<int> weapon_amount;

public:
    vector<Mouse*> mice_vector;
    int mouse_amount;
    bool is_human;

    Player(string name, bool is_human, int mouse_amount, int colour)
            : name(name), is_human(is_human), mouse_amount(mouse_amount), colour(colour) { cout << "Player created!" << endl; };
    virtual void makeTurn();
    string getName();
    int getColour();

};


#endif //MICEWARS_PLAYER_H
