#include <iostream>
#include <sstream>
#include "Game.h"
#include "Engine.h"
#include "Timer.h"

void setWindowTitleDT() {
    std::stringstream title_frametime;
    title_frametime << "Frametime: " << Timer::Instance()->getDelta();
    title_frametime.str().c_str();
    SDL_SetWindowTitle(Engine::Instance()->window, title_frametime.str().c_str());
    //cout << "Frametime: " << Timer.getDelta() << endl;
}

int main(int argc, char **argv) {
    
    Engine::Instance()->getReady(Game::Instance()->getWindowWidth(), Game::Instance()->getWindowHeigth());
    Game::Instance()->generateTerrain();
    Game::Instance()->createPlayer("Joe", true, 1, 0);
    Game::Instance()->placeMice();
    Timer::Instance()->setFPS(60);

    bool quit = false;
    while (!quit) {
        SDL_Event event;
        if ( SDL_PollEvent(&event) ) {
            if (event.type == SDL_QUIT)
                quit = true;
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                }
                else if (event.key.keysym.sym == SDLK_LEFT) {
                    Game::Instance()->player_vector[0]->mice_vector[0]->wants_to_move = 0;
                }
                else if (event.key.keysym.sym == SDLK_RIGHT) {
                    Game::Instance()->player_vector[0]->mice_vector[0]->wants_to_move = 1;
                }
            }
        }
        Timer::Instance()->getNewDelta();
        setWindowTitleDT();
        Game::Instance()->applyMovement();
        Game::Instance()->applyGravity();
        Game::Instance()->redraw();
    }
}