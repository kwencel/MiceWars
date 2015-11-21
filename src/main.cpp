#include "Game.h"
#include "Timer.h"
#include "ConfigFile.h"

int main(int argc, char** argv) {

    ConfigFile::Instance()->loadConfig(CONFIG_FILE_PATH);
    Engine::Instance()->getReady();
    Game::Instance()->generateTerrain();
    Game::Instance()->createPlayer("Daktyl", true, 4, 0);
    Game::Instance()->createPlayer("Aleker", true, 4, 0);
//    Game::Instance()->createPlayer("Lazarz", false, 4, 0);
    Game::Instance()->placeMice();
    Game::Instance()->changePlayer();
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
}