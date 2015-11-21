#include "Game.h"
#include "Timer.h"

int main(int argc, char** argv) {

    // TODO getReady- bad win_width
    Engine::Instance()->getReady(Game::Instance()->getWindowWidth(), Game::Instance()->getWindowHeigth());
    Timer::Instance()->setFPS(60);
    Timer::Instance()->getNewDelta();
//    Game::Instance()->generateTerrain();
//    Game::Instance()->createPlayer(GREEN_MOUSE, true, 2, 0);
//    Game::Instance()->createPlayer(PINK_MOUSE, true, 2, 0);
//    Game::Instance()->createPlayer(BLUE_MOUSE, true, 2, 0);
//    Game::Instance()->players_count = Game::Instance()->player_vector.size();
//    Game::Instance()->placeMice();
//    Game::Instance()->changePlayer();


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