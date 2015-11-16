#include "Game.h"
#include "Timer.h"

int main(int argc, char** argv) {

    Engine::Instance()->getReady(Game::Instance()->getWindowWidth(), Game::Instance()->getWindowHeigth());
    Timer::Instance()->setFPS(60);
    Game::Instance()->generateTerrain();
    Game::Instance()->createPlayer("Daktyl", true, 2, 0);
    Game::Instance()->createPlayer("Aleker", true, 2, 0);
    Game::Instance()->createPlayer("Lazarz", true, 2, 0);
    Game::Instance()->placeMice();
    Game::Instance()->changePlayer();
    Timer::Instance()->getNewDelta();

    // LOADING PLAYER
    std::ifstream read_game_file;
    read_game_file.open("Saved_player.txt", std::ios::in | std::ios::trunc | std::ios::binary);
    Game::Instance()->player_vector[1]->load(read_game_file);
    read_game_file.close();

    while (not Game::Instance()->quit) {
        if (Game::Instance()->getState() == gameplay) {
            Game::Instance()->readKeyboardState();
        }
        else {
            Game::Instance()->controlMenu();
        }
        Game::Instance()->applyMovement();
        Game::Instance()->applyGravity();
        Game::Instance()->redraw();
        Game::Instance()->capFPS();
        Engine::Instance()->setWindowTitle();
        Timer::Instance()->getNewDelta();
    }
    Game::Instance()->exit();

    // SAVING PLAYER
//    std::ofstream save_game_file;
//    save_game_file.open("Saved_player.txt", std::ios::out | std::ios::trunc | std::ios::binary);
//    Game::Instance()->player_vector[0]->save(save_game_file);
//    save_game_file.close();

}