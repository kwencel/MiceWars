#include "RangedWeapon.h"
#include "Game.h"

std::vector<std::pair<int,int>> markSemicircleLeft() {
    std::vector<std::pair<int,int>> semicircle_vector;
    std::pair<int,int> pair;
    int x0 = Game::Instance()->current_player->current_mouse->center.x;
    int y0 = Game::Instance()->current_player->current_mouse->center.y;
    int x = RADIUS_CROSSHAIR;
    int y = 0;
    int decisionOver2 = 1 - x;   // Decision criterion divided by 2 evaluated at x=radius, y=0

    // drawing circle
    while (y <= x) {
        if ((-y + x0) >= 0 && (-y + x0) <= Game::Instance()->win_width && (x + y0) >= 0 && (x + y0) <= Game::Instance()->win_height){
            pair.first = -y + x0;               // Octant 3/2
            pair.second = x + y0;
            cout << pair.first << " " << pair.second << endl;
            semicircle_vector.push_back(pair);
        }
        if ((-x + x0) >= 0 && (-x + x0) <= Game::Instance()->win_width && (y + y0) >= 0 && (y + y0) <= Game::Instance()->win_height) {
            pair.first = -x + x0;               // Octant 4/1
            pair.second = y + y0;
            cout << pair.first << " " << pair.second << endl;
            semicircle_vector.push_back(pair);
        }
        if ((-x + x0) >= 0 && (-x + x0) <= Game::Instance()->win_width && (-y + y0) >= 0 && (-y + y0) <= Game::Instance()->win_height) {
            pair.first = -x + x0;               // Octant 5/8
            pair.second = -y + y0;
            cout << pair.first << " " << pair.second << endl;
            semicircle_vector.push_back(pair);
        }
        if ((-y + x0) >= 0 && (-y + x0) <= Game::Instance()->win_width && (-x + y0) >= 0 && (-x + y0) <= Game::Instance()->win_height) {
            pair.first = -y + x0;               // Octant 6/7
            pair.second = -x + y0;
            cout << pair.first << " " << pair.second << endl;
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
    return semicircle_vector;
}

std::vector<std::pair<int,int>> markSemicircleRight() {
    std::vector<std::pair<int,int>> semicircle_vector;
    std::pair<int,int> pair;
    int x0 = Game::Instance()->current_player->current_mouse->center.x;
    int y0 = Game::Instance()->current_player->current_mouse->center.y;
    int x = RADIUS_CROSSHAIR;
    int y = 0;
    int decisionOver2 = 1 - x;   // Decision criterion divided by 2 evaluated at x=radius, y=0

    // drawing circle
    while (y <= x) {
        if ((y + x0) >= 0 && (y + x0) <= Game::Instance()->win_width && (x + y0) >= 0 && (x + y0) <= Game::Instance()->win_height){
            pair.first = y + x0;               // Octant 3/2
            pair.second = x + y0;
            cout << pair.first << " " << pair.second << endl;
            semicircle_vector.push_back(pair);
        }
        if ((x + x0) >= 0 && (x + x0) <= Game::Instance()->win_width && (y + y0) >= 0 && (y + y0) <= Game::Instance()->win_height) {
            pair.first = x + x0;               // Octant 4/1
            pair.second = y + y0;
            cout << pair.first << " " << pair.second << endl;
            semicircle_vector.push_back(pair);
        }
        if ((x + x0) >= 0 && (x + x0) <= Game::Instance()->win_width && (-y + y0) >= 0 && (-y + y0) <= Game::Instance()->win_height) {
            pair.first = x + x0;               // Octant 5/8
            pair.second = -y + y0;
            cout << pair.first << " " << pair.second << endl;
            semicircle_vector.push_back(pair);
        }
        if ((y + x0) >= 0 && (y + x0) <= Game::Instance()->win_width && (-x + y0) >= 0 && (-x + y0) <= Game::Instance()->win_height) {
            pair.first = y + x0;               // Octant 6/7
            pair.second = -x + y0;
            cout << pair.first << " " << pair.second << endl;
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
    return semicircle_vector;
}

void RangedWeapon::moveCrosshair() {
    std::vector<std::pair<int,int>> semicircle_vector;
    crosshair = new Object();
    int x_mouse = Game::Instance()->current_player->current_mouse->center.x;
    int y_mouse = Game::Instance()->current_player->current_mouse->center.y;
    crosshair->pos_x = x_mouse;
    crosshair->pos_y = y_mouse - RADIUS_CROSSHAIR;

//    while (event.key.keysym.sym != SDLK_q) {    // while not ready to shoot
//        if (event.key.keysym.sym == SDLK_DOWN) {
//            if (Game::Instance()->current_player->current_mouse->wants_to_move_direction == -1) {    // if left
//                semicircle_vector = markSemicircleLeft();  // nadpisze?
//            }
//            else { // right
//                semicircle_vector = markSemicircleRight();
//            }
//        }
//        else if (event.key.keysym.sym == SDLK_UP) {
//
//        }
//
//    }
}

void RangedWeapon::prepare() {
    moveCrosshair();
}

void RangedWeapon::shoot() {

}
