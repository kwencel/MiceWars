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
    AI(int colour, int mouse_amount, bool is_human, string name)
            : Player(colour, mouse_amount, is_human, name) { cout << "AI created!" << endl; }
    void makeTurn() override;
};


#endif //MICEWARS_AI_H
