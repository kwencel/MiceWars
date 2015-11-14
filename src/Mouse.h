#ifndef MICEWARS_MOUSE_H
#define MICEWARS_MOUSE_H

#include "Weapon.h"
#include "NotificationBox.h"

class Mouse: public Object {
public:
    int hp = 100;
    short wants_to_move_direction = 0;
    int movepoints = MOUSE_MOVEPOINTS;
    bool can_move = false;
    Weapon* weapon = nullptr;
    int weapon_index = 0;
    bool space_key_released = false;
    NotificationBox* notification_hp = nullptr;

    Mouse(int x, int y, int width, int height, std::string img_path)
            : Object(x, y, width, height, img_path) { cout << "Mouse created!" << endl; }
    void move();
    void jump();
    //void ready();
    void changeWeapon(short index);
    void destroy() override;
    bool overcomeHill(int direction);
    void display();
};


#endif //MICEWARS_MOUSE_H
