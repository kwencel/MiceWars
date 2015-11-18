#include "Game.h"
#include "Timer.h"

int main(int argc, char** argv) {

    Engine::Instance()->getReady(Game::Instance()->getWindowWidth(), Game::Instance()->getWindowHeigth());
    Timer::Instance()->setFPS(60);
    Game::Instance()->generateTerrain();
    Game::Instance()->createPlayer("Daktyl", true, 2, 0);
    Game::Instance()->createPlayer("Aleker", true, 2, 0);
    Game::Instance()->createPlayer("Lazarz", true, 2, 0);
    Game::Instance()->players_count = Game::Instance()->player_vector.size();
    Game::Instance()->placeMice();
    Game::Instance()->changePlayer();

    //Game::Instance()->loadGame("load_game.dat");

    Timer::Instance()->getNewDelta();

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

    // SAVING GAME
    Game::Instance()->saveGame("load_game.dat");

}