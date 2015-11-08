#include <iostream>
#include "Game.h"
#include "Timer.h"

void printDebugInfo(std::pair<int, int> &last_mouse_pos) {
    if ((Game::Instance()->player_vector[0]->mice_vector[0]->pos_x != last_mouse_pos.first) or
        (Game::Instance()->player_vector[0]->mice_vector[0]->pos_y != last_mouse_pos.second)) {
        cout << "Mouse coordinates: " << Game::Instance()->player_vector[0]->mice_vector[0]->pos_x << " " <<
        Game::Instance()->player_vector[0]->mice_vector[0]->pos_y << endl;
        cout << "Collision at current position: " <<
        Game::Instance()->doesCollide(Game::Instance()->player_vector[0]->mice_vector[0]) << endl;
        last_mouse_pos = {Game::Instance()->player_vector[0]->mice_vector[0]->pos_x,
                          Game::Instance()->player_vector[0]->mice_vector[0]->pos_y};
    }
}

int main(int argc, char **argv) {
    std::pair<int, int> last_mouse_pos;

    Engine::Instance()->getReady(Game::Instance()->getWindowWidth(), Game::Instance()->getWindowHeigth());
    Timer::Instance()->setFPS(60);
    Game::Instance()->generateTerrain();
    Game::Instance()->createPlayer("Daktyl", true, 1, 0);
    Game::Instance()->createPlayer("Aleker", true, 1, 0);
    Game::Instance()->placeMice();
    Game::Instance()->player_vector[0]->makeTurn();

    //TODO ADD 60FPS cap, if deltatime is lower than for 60fps, switch to auto.

    while (!Game::Instance()->quit) {
        Game::Instance()->gameplay();
        Game::Instance()->updateGameState();
        //printDebugInfo(last_mouse_pos);

        Timer::Instance()->getNewDelta();
        Engine::Instance()->setWindowTitle();
        Game::Instance()->applyMovement();
        Game::Instance()->applyGravity();
        Game::Instance()->redraw();
    }
}