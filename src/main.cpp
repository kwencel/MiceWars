#include "Game.h"
#include "Timer.h"
#include "ConfigFile.h"

int main(int argc, char** argv) {
    ConfigFile::Instance()->loadConfig(CONFIG_FILE_PATH);
    Engine::Instance()->getReady();
    Timer::Instance()->getNewDelta();
    Game::Instance()->menu_needs_redraw = true;

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