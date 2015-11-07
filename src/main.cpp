#include <iostream>
#include <sstream>
#include "Game.h"
#include "Engine.h"
#include "Timer.h"

void setWindowTitle() {
    std::stringstream window_title;
    std::pair <int,int> cursor_pos = Engine::Instance()->getCursorPosition();
    window_title << "Frametime: " << Timer::Instance()->getDelta() << " Cursor " << cursor_pos.first << " " << cursor_pos.second;
    window_title.str().c_str();
    SDL_SetWindowTitle(Engine::Instance()->window, window_title.str().c_str());
}

int main(int argc, char **argv) {

    Engine::Instance()->getReady(Game::Instance()->getWindowWidth(), Game::Instance()->getWindowHeigth());
    Game::Instance()->generateTerrain();
    Game::Instance()->createPlayer("Joe", true, 1, 0);
    Game::Instance()->placeMice();
    Timer::Instance()->setFPS(60);

    std::pair<int, int> last_mouse_pos;
    while (!Game::Instance()->quit) {

        Game::Instance()->updateGameState();

        if ((Game::Instance()->player_vector[0]->mice_vector[0]->pos_x != last_mouse_pos.first) or
            (Game::Instance()->player_vector[0]->mice_vector[0]->pos_y != last_mouse_pos.second)) {
            cout << "Mouse coordinates: " << Game::Instance()->player_vector[0]->mice_vector[0]->pos_x << " " <<
            Game::Instance()->player_vector[0]->mice_vector[0]->pos_y << endl;
            cout << "Collision at current position: " <<
            Game::Instance()->doesCollide(Game::Instance()->player_vector[0]->mice_vector[0]) << endl;
            last_mouse_pos = {Game::Instance()->player_vector[0]->mice_vector[0]->pos_x,
                              Game::Instance()->player_vector[0]->mice_vector[0]->pos_y};
        }
        Timer::Instance()->getNewDelta();
        setWindowTitle();
        Game::Instance()->applyMovement();
        Game::Instance()->applyGravity();
        Game::Instance()->redraw();
    }
}