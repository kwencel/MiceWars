#ifndef MICEWARS_AI_H
#define MICEWARS_AI_H

#include <string>
#include "Player.h"
#include "Mouse.h"

using namespace std;

class AI: public Player {
private:
    Mouse* enemy_target;

    void chooseTarget();
    void moveToPosition();
    void chooseWeapon();
    void aim();
    void fire();

public:
    AI(string name, bool is_human, int mouse_amount, int colour)
            : Player(name, is_human, mouse_amount, colour) { cout << "AI created!" << endl; }
    void makeTurn() override;
};


#endif //MICEWARS_AI_H
