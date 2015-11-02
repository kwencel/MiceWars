#ifndef MICEWARS_MOUSE_H
#define MICEWARS_MOUSE_H

#include "Weapon.h"
#include "NotificationBox.h"

using namespace std;

class Mouse: public Object {
public:
    int hp = 100;
    bool can_move = false;
    int movepoints = 0;
    Weapon* last_weapon = nullptr;
    NotificationBox* notification_hp = nullptr;
    bool facing_direction;

    Mouse(int x, int y, int width, int height)
            : Object(x, y, width, height) { cout << "Mouse created!" << endl; }
    void move(bool facing_direction);
    void jump();
    void ready();
    void changeWeapon();
    void destroy() override;

};


#endif //MICEWARS_MOUSE_H
