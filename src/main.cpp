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

int main(int argc, char** argv) {

    Engine::Instance()->getReady(Game::Instance()->getWindowWidth(), Game::Instance()->getWindowHeigth());
    Timer::Instance()->setFPS(60);
    Game::Instance()->generateTerrain();
    Game::Instance()->createPlayer("Daktyl", true, 2, 0);
    Game::Instance()->createPlayer("Aleker", true, 2, 0);
    Game::Instance()->placeMice();
//    Game::Instance()->player_vector[0]->makeTurn();
    Game::Instance()->changePlayer();
    Timer::Instance()->getNewDelta();

    // LOADING PLAYER
    std::ifstream read_game_file;
    read_game_file.open("Saved_player.txt", std::ios::in | std::ios::trunc | std::ios::binary);
    Game::Instance()->player_vector[1]->load(read_game_file);
    read_game_file.close();

    while (not Game::Instance()->quit) {
        Game::Instance()->readKeyboardState();
        Game::Instance()->applyMovement();
        Game::Instance()->applyGravity();
        Game::Instance()->redraw();
        Game::Instance()->capFPS();
        Engine::Instance()->setWindowTitle();
        Timer::Instance()->getNewDelta();
    }

    // SAVING PLAYER
//    std::ofstream save_game_file;
//    save_game_file.open("Saved_player.txt", std::ios::out | std::ios::trunc | std::ios::binary);
//    Game::Instance()->player_vector[0]->save(save_game_file);
//    save_game_file.close();

}