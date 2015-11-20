#include <algorithm>
#include "AI.h"
#include "Game.h"
#include "RangedWeapon.h"

bool compareHPIncreasing(const EnemyTarget &a, const EnemyTarget &b) {
    return a.hp < b.hp;
}

bool compareDistanceIncreasing(const EnemyTarget &a, const EnemyTarget &b) {
    return a.distance < b.distance;
}

void AI::makeTurn() {
    Player::makeTurn();
    has_shot = false;
    ideal_crosshair_center_x = -1;
    ideal_crosshair_center_x = -1;
    a_coefficient = -1;
    a_coefficient = -1;
    stuck_count = 0;
    override_movement = stay;
    motion_inverter = stay;
    last_pos = {-1, -1};
    chooseTarget();
    chooseWeapon();
}

bool AI::simulateBulletMovement(Object* target) {
    Object *test_bullet = new Object(current_mouse->weapon->getCenter().x, current_mouse->weapon->getCenter().y,
                                     BULLET_WIDTH, BULLET_HEIGHT);
    aim(target, true);
//    int offset_x = 0;
//    int offset_y = 0;
    int offset_x = -1;
    int offset_y = -1;
    if (current_mouse->weapon->flip) {
        offset_x = 1;
    }
    if (a_coefficient) {
        offset_y = 1;
    }
    std::vector<Mouse *> affectedMice;
    while (Game::Instance()->isInsideWindowBorders(test_bullet, offset_x, offset_y)) {
        if (Game::Instance()->doesCollide(test_bullet, offset_x, offset_y)) {
            delete test_bullet;
            return false;
        }
        // Save the mouse that was hit by test bullet to the vector
//        affectedMice.clear();
//        affectedMice = Game::Instance()->checkMiceCollision(test_bullet->getCenter().x, test_bullet->getCenter().y, offset_x, offset_y);
//        if (not affectedMice.empty()) {
//            // For each mouse that got hurt by the test bullet
//            for (auto affected : affectedMice) {
//                // Check if it's one of the enemy mice
//                for (int i = 0; i < enemies_vector.size(); ++i) {
//                    // If it's one of the enemies, return true
//                    if (affected != enemies_vector[i].pointer) {
//                        delete test_bullet;
//                        return true;
//                    }
//                }
//            }
//            // If it's your own mouse, stop and move until you find a clear position to shoot
//            delete test_bullet;
//            return false;
//        }

        Mouse *affected = Game::Instance()->checkMouseCollision(test_bullet->pos_x, test_bullet->pos_y,
                                                                offset_x, offset_y);
        if (affected != nullptr) {
            for (int i = 0; i < enemies_vector.size(); ++i) {
                // If it's one of the enemies, return true
                if (affected == enemies_vector[i].pointer) {
                    delete test_bullet;
                    return true;
                }
//                else {
//                    return false;
//                }
            }
            // If it's your own mouse, stop and move until you find a clear position to shoot
//            delete test_bullet;
//            return false;
        }



//            // The hit mouse was found in the enemies vector (enemy mouse got hit - very good!)
//            if (std::find (enemies_vector.begin(), enemies_vector.end(), mouse) != enemies_vector.end()) {
//                delete test_bullet;
//                return true;
//            }
//            else {  // The hit mouse is not an enemy so you've hit your ally. Return false.
//                delete test_bullet;
//                return false;
//            }
//        if (std::find (affectedMice.begin(), affectedMice.end(), enemy_mouse.pointer) != affectedMice.end()) {
//            delete test_bullet;
//            return true;
//        }
        if (current_mouse->weapon->flip == 0) {
            test_bullet->pos_x -= 1;
        }
        else {
            test_bullet->pos_x += 1;
        }
        test_bullet->pos_y = static_cast<int>(ceil((a_coefficient * test_bullet->pos_x) + b_coefficient));
    }
    delete test_bullet;
    return false;
}

void AI::chooseTarget() {
    enemies_vector.clear();
    enemy_mouse.clear();
    for (auto enemy_player : Game::Instance()->player_vector) {
        if (enemy_player == this) {
            continue;
        }
        // Make a vector with all enemy mice
        for (auto enemy : enemy_player->mice_vector) {
            EnemyTarget enemy_target;
            enemy_target.pointer = enemy;
            enemy_target.distance = calculateDistanceBetweenObjects(current_mouse, enemy);
            enemy_target.direction = (enemy->getCenter().x >= current_mouse->getCenter().x);
            enemy_target.vulnerable = simulateBulletMovement(enemy);
            enemy_target.hp = enemy->hp;
            enemies_vector.push_back(enemy_target);
        }
    }
    // Choose the mouse to attack
    std::vector<EnemyTarget> vulnerable_enemies;
    for (auto enemy : enemies_vector) {
        if (enemy.vulnerable) {
            vulnerable_enemies.push_back(enemy);
        }
    }
    // If there is one, choose it as a target
    if (vulnerable_enemies.size() == 1) {
        enemy_mouse = vulnerable_enemies[0];
    }
    // If there are many, choose the weakest one
    else if (vulnerable_enemies.size() > 1) {
        sort(vulnerable_enemies.begin(), vulnerable_enemies.end(), compareHPIncreasing);
        enemy_mouse = vulnerable_enemies[0];
    }
    // There are no vulnerable mice. Choose the closest one
    else {
        sort(enemies_vector.begin(), enemies_vector.end(), compareDistanceIncreasing);
        enemy_mouse = enemies_vector[0];
    }
}

void AI::got_stuck_workaround() {
    Mouse* old_enemy = enemy_mouse.pointer;
    chooseTarget();
    // If finding another, better target succeeded
    if (enemy_mouse.pointer != old_enemy) {
        // Let the AI control the move
        override_movement = stay;
    }
}

void AI::moveToPosition() {
    if (override_movement != stay) {
        got_stuck_workaround();
    }
    if (current_mouse->can_move) {
        // If mouse has a clear shot, don't move and shoot.
        if (enemy_mouse.vulnerable or simulateBulletMovement(enemy_mouse.pointer)) {
            current_mouse->can_move = false;
        }
        else {
            if (stuck_count > AI_STUCK_COUNT) {
                ++stuck_times;
                if (stuck_times >= AI_MAX_STUCK_TIMES) {
                    current_mouse->can_move = false;
                }
                override_movement = motion_inverter * (-1);
                stuck_count = 0;
                got_stuck_workaround();
                return;
            }
            if (override_movement != stay) {
                motion_inverter = override_movement;
            }
            else if (enemy_mouse.distance < current_mouse->weapon->dmg_range - AI_SAFETY_RADIUS) {
                motion_inverter = -1;
            }
            else if (enemy_mouse.distance > current_mouse->weapon->dmg_range + AI_SAFETY_RADIUS) {
                motion_inverter = 1;
            }
            else {
                if (simulateBulletMovement(enemy_mouse.pointer)) {
                    current_mouse->can_move = false;
                }
                else {
                    motion_inverter = 1;
                }
            }
            if (enemy_mouse.direction == false) {   // Enemy mouse is on the left side of AI's player
                current_mouse->wants_to_move_direction = motion_inverter * left;
            }
            else {                                  // Enemy mouse is on the right side of AI's player
                current_mouse->wants_to_move_direction = motion_inverter * right;
            }
            if (last_pos.x == current_mouse->pos_x and last_pos.y == current_mouse->pos_y) {
                ++stuck_count;
            }
            else {
                last_pos = {current_mouse->pos_x, current_mouse->pos_y};
            }
        }
    }
}

void AI::chooseWeapon() {
    current_mouse->changeWeapon(shotgun);
}

void AI::aim(Object* target, bool simulate) {
    if (enemy_mouse.direction == right) {
        current_mouse->flip = true;
    }
    else {
        current_mouse->flip = false;
    }
    RangedWeapon *ranged_weapon_ptr = dynamic_cast<RangedWeapon *>(current_mouse->weapon);
    RangedWeapon TestWeapon(current_mouse->pos_x + WEAPON_X_OFFSET, current_mouse->pos_y + WEAPON_Y_OFFSET,
                            WEAPON_WIDTH,
                            WEAPON_HEIGHT, SHOTGUN_IMG);
    TestWeapon.flip = current_mouse->flip;
    // CALCULATING TRAJECTORY
    float x1, y1, x2, y2;
    x1 = float(current_mouse->weapon->getCenter().x);
    y1 = float(current_mouse->weapon->getCenter().y);
    x2 = float(target->getCenter().x);
    y2 = float(target->getCenter().y);
//    if (current_mouse->flip) {
//        x1 = float(current_mouse->weapon->pos_x + current_mouse->weapon->obj_width);
//        y1 = float(current_mouse->weapon->pos_y + current_mouse->weapon->obj_height);
//        x2 = float(target->getCenter().x);
//        y2 = float(target->getCenter().y);
//    }
//    else {
//        x1 = float(current_mouse->weapon->pos_x);
//        y1 = float(current_mouse->weapon->pos_y + current_mouse->weapon->obj_height);
//        x2 = float(target->getCenter().x);
//        y2 = float(target->getCenter().y);
//    }
    a_coefficient = (y1 - y2) / (x1 - x2);
    b_coefficient = y1 - (a_coefficient * x1);
    // CROSSHAIR COORDINATES
    TestWeapon.createCrosshair();
    for (auto point : TestWeapon.semicircle_vector) {
        int curr_y = static_cast<int>(a_coefficient * (point.first) + b_coefficient);
        if ((curr_y > point.second - CROSSHAIR_SIM_TOLERANCE) and (curr_y < point.second + CROSSHAIR_SIM_TOLERANCE)) {
            ideal_crosshair_center_x = point.first;
            ideal_crosshair_center_y = point.second;
            break;
        }
    }
    if (not simulate) {
        // Gradually move the crosshair to the desired position
        if (enemy_mouse.pointer->pos_y < current_mouse->pos_y) {  // Enemy is higher than you
            current_mouse->weapon->wants_to_move_crosshair = up;
        }
        else if (enemy_mouse.pointer->pos_y > current_mouse->pos_y) {  // Enemy is higher than you
            current_mouse->weapon->wants_to_move_crosshair = down;
        }

        int old_crosshair_x = -1;
        int old_crosshair_y = -1;
        if (ranged_weapon_ptr->crosshair != nullptr) {
            old_crosshair_x = ranged_weapon_ptr->crosshair->pos_x;
            old_crosshair_y = ranged_weapon_ptr->crosshair->pos_y;
        }

        current_mouse->weapon->prepare();
        if (old_crosshair_x == ranged_weapon_ptr->crosshair->pos_x and old_crosshair_y == ranged_weapon_ptr->crosshair->pos_y) {
            ++stuck_count;
        }

        if ((ranged_weapon_ptr->it == ranged_weapon_ptr->semicircle_vector.begin()) or (ranged_weapon_ptr->it == ranged_weapon_ptr->semicircle_vector.end() - 1)) {
            fire();
            return;
        }
        else if (ranged_weapon_ptr->crosshair->pos_x == ideal_crosshair_center_x and
                ranged_weapon_ptr->crosshair->pos_y == ideal_crosshair_center_y) {
            fire();
            return;
        }
        else if (stuck_count >= AI_STUCK_COUNT) {
            fire();
            return;
        }
    }
}

void AI::fire() {
    current_mouse->weapon->shoot();
    has_shot = true;
}

AI::~AI() {
    cout << "AI destroyed!" << endl;
}

void AI::handle_keys(SDL_Keycode keycode) {
    // Do not allow any actions while in air
    if (not Game::Instance()->doesCollide(current_mouse, 0, 1)) {
        return;
    }
    if (current_mouse->can_move) {
        moveToPosition();
        return;
    }
    if (not has_shot) {
        aim(enemy_mouse.pointer, false);
    }
}

int AI::calculateDistanceBetweenObjects(Object* base_obj, Object* distant_obj) {
    int dist_x = abs(distant_obj->getCenter().x - base_obj->getCenter().x);
    int dist_y = abs(distant_obj->getCenter().y - base_obj->getCenter().y);
    int distance = static_cast<int>(sqrt( (dist_x * dist_x) + (dist_y * dist_y)) );
    return distance;
}

void EnemyTarget::clear() {
    pointer = nullptr;
    distance = 0;
    direction = false;
}
