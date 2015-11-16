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
    NotificationBox* notification_hp = nullptr;

    Mouse(int x, int y, int width, int height, std::string img_path)
            : Object(x, y, width, height, img_path) { cout << "Mouse created!" << endl; }
    ~Mouse();
    void move();
    void jump();
    void changeWeapon(short index);
    bool overcomeHill(int direction);
    void display();
    void save(std::ofstream& file) override;
    void load(std::ifstream& file) override;
};


#endif //MICEWARS_MOUSE_H
