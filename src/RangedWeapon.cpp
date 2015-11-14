#include <algorithm>
#include "RangedWeapon.h"
#include "Game.h"
#include "Timer.h"

bool compareXIncreasing(const std::pair<int, int> &a, const std::pair<int, int> &b) {
    return a.first < b.first;
}

bool compareXDecreasing(const std::pair<int, int> &a, const std::pair<int, int> &b) {
    return a.first > b.first;
}

bool compareY (const std::pair<int,int>& a, const std::pair<int,int>& b) {
    return a.second < b.second;
}

bool equalX (const std::pair<int,int>& a, const std::pair<int,int>& b) {
    return (a.first == b.first);
}

bool equalY (const std::pair<int,int>& a, const std::pair<int,int>& b) {
    return (a.second == b.second);
}

void RangedWeapon::sortVector() {
    // SORTING VECTOR BY "Y":
    sort(semicircle_vector.begin(), semicircle_vector.end(), compareY);
    // REMOVING EXACTLY THE SAME POINTS FROM VECTOR:
    semicircle_vector.erase(std::unique(semicircle_vector.begin(), semicircle_vector.end()), semicircle_vector.end());
    std::vector<std::pair<int,int>>::iterator it_startY = semicircle_vector.begin();        // start iterator
    std::vector<std::pair<int,int>>::iterator it_endY;                                      // end iterator
    std::vector<std::pair<int,int>>::iterator it_currentY;                                  // current iterator

    for (it_currentY = semicircle_vector.begin() + 1; it_currentY <= semicircle_vector.end() + 1; ++it_currentY) {
        if (it_currentY->second != it_startY->second) {
            it_endY = it_currentY;
            // LEFT
            if (Game::Instance()->current_player->current_mouse->flip == 0) {
                if (it_startY->second < Game::Instance()->current_player->current_mouse->center.y) // over the center of mouse
                    sort(it_startY, it_endY, compareXDecreasing);
                else    // under the center of mouse
                    sort(it_startY, it_endY, compareXIncreasing);
            } // RIGHT
            else {
                if (it_startY->second < Game::Instance()->current_player->current_mouse->center.y) // over the center of mouse
                    sort(it_startY, it_endY, compareXIncreasing);
                else    // under the center of mouse
                    sort(it_startY, it_endY, compareXDecreasing);
            }
            it_startY = it_currentY;
        }
    }
}

void RangedWeapon::markSemicircle() {
    semicircle_vector.clear();
    std::pair<int,int> pair;
    int x0 = Game::Instance()->current_player->current_mouse->pos_x;
    int y0 = Game::Instance()->current_player->current_mouse->pos_y;
    int x = RADIUS_CROSSHAIR;
    int y = 0;
    int decisionOver2 = 1 - x;   // Decision criterion divided by 2 evaluated at x=radius, y=0

    // DECIDE IF LEFT OR RIGHT SIDE DRAWING
    int coefficient;
    if (Game::Instance()->current_player->current_mouse->flip == 0) // left
        coefficient = -1;
    else
        coefficient = 1;

    // DRAW SEMICIRCLE
    while (y <= x) {
        if ((coefficient*y + x0) >= 0 && (coefficient*y + x0) <= Game::Instance()->win_width && (x + y0) >= 0
                && (x + y0) <= Game::Instance()->win_height){
            pair.first = coefficient*y + x0;               // Octant 3/2
            pair.second = x + y0;
            semicircle_vector.push_back(pair);
        }
        if ((coefficient*x + x0) >= 0 && (coefficient*x + x0) <= Game::Instance()->win_width && (y + y0) >= 0
                && (y + y0) <= Game::Instance()->win_height) {
            pair.first = coefficient*x + x0;               // Octant 4/1
            pair.second = y + y0;
            semicircle_vector.push_back(pair);
        }
        if ((coefficient*x + x0) >= 0 && (coefficient*x + x0) <= Game::Instance()->win_width && (-y + y0) >= 0
                && (-y + y0) <= Game::Instance()->win_height) {
            pair.first = coefficient*x + x0;               // Octant 5/8
            pair.second = -y + y0;
            semicircle_vector.push_back(pair);
        }
        if ((coefficient*y + x0) >= 0 && (coefficient*y + x0) <= Game::Instance()->win_width && (-x + y0) >= 0
                && (-x + y0) <= Game::Instance()->win_height) {
            pair.first = coefficient*y + x0;               // Octant 6/7
            pair.second = -x + y0;
            semicircle_vector.push_back(pair);
        }
        y++;
        if (decisionOver2 <= 0) {
            decisionOver2 += 2 * y + 1;   // Change in decision criterion for y -> y+1
        }
        else {
            x--;
            decisionOver2 += 2 * (y - x) + 1;   // Change for y -> y+1, x -> x-1
        }
    }
    sortVector();
    // DISPLAY THE CONTENT OF VECTOR:
//    for (auto gucio: semicircle_vector){
//        cout << "x " << gucio.first << " ";
//        cout << "y " << gucio.second << endl;
//    }
}

void RangedWeapon::moveCrosshair() {
    if (wants_to_move_crosshair == stay) {
        return;
    }

    int steps = static_cast<int>(CROSSHAIR_SPEED_MUL * Timer::Instance()->getDelta());
    if (steps == 0) {
        steps = 1;
    }
    for (int pixel = 0; pixel < steps; ++pixel) {
        if (Game::Instance()->isInsideWindowBorders(this, wants_to_move_crosshair)) {
            if (wants_to_move_crosshair == up && it != semicircle_vector.begin()) {
                --it;
                crosshair->pos_x = it->first;
                crosshair->pos_y = it->second;
                if (Game::Instance()->current_player->current_mouse->flip) {
                    --angle;
                }
                else {
                    ++angle;
                }
            }
            else if (wants_to_move_crosshair == down and it != semicircle_vector.end() - 1) {
                ++it;
                crosshair->pos_x = it->first;
                crosshair->pos_y = it->second;
                if (Game::Instance()->current_player->current_mouse->flip) {
                    ++angle;
                }
                else {
                    --angle;
                }
            }
        }
    }
    wants_to_move_crosshair = stay;
}

void RangedWeapon::prepare() {
    if (crosshair == nullptr) {
        createCrosshair();
    }
    moveCrosshair();
}

void RangedWeapon::shoot() {
    wants_to_move_crosshair = stay;
    // CREATING BULLET
    if (bullet == nullptr){
        bullet = new Object(this->center.x,this->center.y,BULLET_WIDTH,BULLET_HEIGHT,BULLET_IMG);
        bullet->flip = this->flip;
        bullet->angle = this->angle;
    }
    // CALCULATING TRAJECTORY
    float x1, y1, x2, y2;
    x1 = (this->bullet->pos_x);
    y1 = (this->bullet->pos_y);
    x2 = (crosshair->center.x);
    y2 = (crosshair->center.y);

    a_coefficient = (y1-y2)/(x1-x2);
    b_coefficient = y1 - (a_coefficient * x1);
    std::cout << "SHOOOOOOOOOOOOOOOOT!!!" << endl;
}

void RangedWeapon::createCrosshair() {
    if (crosshair == nullptr) {
        int mouse_x = Game::Instance()->current_player->current_mouse->pos_x;
        int mouse_y = Game::Instance()->current_player->current_mouse->pos_y;
        if (Game::Instance()->current_player->current_mouse->flip) {
            crosshair = new Object(mouse_x + RADIUS_CROSSHAIR, mouse_y, CROSSHAIR_WIDTH, CROSSHAIR_WIDTH, CROSSHAIR_IMG);
        }
        else {
            crosshair = new Object(mouse_x - RADIUS_CROSSHAIR, mouse_y, CROSSHAIR_WIDTH, CROSSHAIR_WIDTH, CROSSHAIR_IMG);
        }
        markSemicircle();
        it = (semicircle_vector.begin() + semicircle_vector.size()/2);
    }
}

void RangedWeapon::display() {
    Object::display();
    if (crosshair != nullptr) {
        crosshair->display();
    }
    if (bullet != nullptr) {
        bullet->display();
    }
}

void RangedWeapon::moveBullet() {
    //bullet->center.y = (a_coefficient * bullet->center.x) + b_coefficient;
    int steps = static_cast<int>(BULLET_SPEED_MUL * Timer::Instance()->getDelta());
    if (steps == 0) {
        steps = 1;
    }
    for (int pixel = 0; pixel < steps; ++pixel) {
        int offset_x = -1, offset_y = -1;
        if (flip) {
            offset_x = 1;
        }
        if (a_coefficient) {
            offset_y = 1;
        }
        if (Game::Instance()->isInsideWindowBorders(bullet)) {
            if (Game::Instance()->doesCollide(bullet, offset_x, offset_y)) { // checking collision
                Game::Instance()->createHoles(bullet->center.x, bullet->center.y, SHOTGUN_RANGE);
                Game::Instance()->background_need_redraw = true;
                // czyszczenie?
                bullet->destroy();
                bullet = nullptr;
                crosshair->destroy();
                crosshair = nullptr;
                Game::Instance()->changePlayer();
                break;
            }
            else {
                if (bullet->flip == 0) {
                    bullet->pos_x -= 1;
                }
                else {
                    bullet->pos_x += 1;
                }
                bullet->pos_y = int(ceil((a_coefficient * bullet->pos_x) + b_coefficient));
            }
        }
        else {   // outside the windowBorders
            bullet->destroy();
            bullet = nullptr;
            crosshair->destroy();
            crosshair = nullptr;
            Game::Instance()->changePlayer();
            break;
        }
    }
    wants_to_move_crosshair = stay;
}
