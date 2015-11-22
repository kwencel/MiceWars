#include "Game.h"
#include "Timer.h"

int main(int argc, char** argv) {

    Engine::Instance()->getReady(Game::Instance()->getWindowWidth(), Game::Instance()->getWindowHeigth());
    Timer::Instance()->setFPS(60);
    Timer::Instance()->getNewDelta();
    Game::Instance()->menu_need_redraw = true;

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