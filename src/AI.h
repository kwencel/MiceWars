#ifndef MICEWARS_AI_H
#define MICEWARS_AI_H

#include <string>
#include "Player.h"

struct EnemyTarget {
    Mouse* pointer = nullptr;
    int distance = 0;
    bool direction = false; // left = false, right = true
    bool vulnerable = false;
    int hp = 0;

    void clear();
};

class AI : public Player {
private:
    std::vector<EnemyTarget> enemies_vector;
    EnemyTarget enemy_mouse;
    int stuck_count = 0;
    int stuck_times = 0;
    bool has_shot = false;
    int ideal_crosshair_x = -1;
    int ideal_crosshair_y = -1;
    float a_coefficient = -1;
    float b_coefficient = -1;
    short override_movement = stay;
    short motion_inverter = stay;
    SDL_Point last_pos = {-1, -1};

    void chooseTarget();

    void moveToPosition();

    bool simulateBulletMovement(Object* target);

    void gotStuckWorkaround();

    void chooseWeapon();

    void aim(Object* target, bool simulate);

    void fire();

    void handleKeys(SDL_Keycode keycode) override;

    int calculateDistanceBetweenObjects(Object* base_obj, Object* distant_obj);

public:
    AI(std::string name, bool is_human, int mouse_amount, int colour)
            : Player(name, is_human, mouse_amount, colour) { /* cout << "AI created!" << endl; */ }

    ~AI();

    void makeTurn() override;
};


#endif //MICEWARS_AI_H
