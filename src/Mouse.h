#ifndef MICEWARS_MOUSE_H
#define MICEWARS_MOUSE_H

#include "Weapon.h"
#include "NotificationBox.h"

class Mouse: public Object {
public:
    int hp = 100;
    bool can_move = false;
    short wants_to_move = -1;
    int movepoints = 0;
    Weapon* last_weapon = nullptr;
    NotificationBox* notification_hp = nullptr;
    bool facing_direction;

    Mouse(int x, int y, int width, int height)
            : Object(x, y, width, height) { cout << "Mouse created!" << endl; }
    void move();
    void jump();
    void ready();
    void changeWeapon();
    void destroy() override;

    void flipTexture();

    void overcomeHill(bool direction);
};


#endif //MICEWARS_MOUSE_H
