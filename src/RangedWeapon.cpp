#include "RangedWeapon.h"

bool changeFlag(bool flag){
    if (flag == true) return false;
    else return true;
}

void RangedWeapon::moveCrosshair(bool direction) {
    std::pair coordinates;
    SDL_Event event;
    crosshair = new Object();
    int x_mouse = Game::Instance()->currentPlayer->currentMouse.center.x;
    int y_mouse = Game::Instance()->currentPlayer->currentMouse.center.y;
    bool flag = true; // true if up to mouse position

    crosshair->pos_x = x_mouse;
    crosshair->pos_y = y_mouse - RADIUS_CROSSHAIR;
    while (event.key.keysym.sym != SDLK_q) {
        if (currentMouse.wants_to_move_direction == -1) {    // if left

        }
        else { // right

        }

    }
}

void RangedWeapon::shoot() {
    int x1, y1; // mouse coordinates
    int x2, y2; // crosshair coordinates


}