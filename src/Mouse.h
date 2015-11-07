#ifndef MICEWARS_MOUSE_H
#define MICEWARS_MOUSE_H

#include "Weapon.h"
#include "NotificationBox.h"

class Mouse: public Object {
public:
    int hp = 100;
    short wants_to_move_direction = 0;
    int movepoints = 0;
    bool can_move = false;
    Weapon* last_weapon = nullptr;
    NotificationBox* notification_hp = nullptr;

    Mouse(int x, int y, int width, int height)
            : Object(x, y, width, height) { cout << "Mouse created!" << endl; }
    void move();
    void jump();
    void ready();
    void changeWeapon();
    void destroy() override;
    bool overcomeHill(int direction);
};


#endif //MICEWARS_MOUSE_H
