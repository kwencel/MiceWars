#include <iostream>
#include "Game.h"
#include "Engine.h"
#include "Timer.h"

using namespace std;

int main(int argc, char **argv) {

    Game Game;
    Engine::Instance()->getReady(Game.getWindowWidth(), Game.getWindowHeigth());
    Game.generateTerrain();
    Game.createPlayer("Joe", true, 3, 0);
    Game.placeMice();
    Timer Timer;
    Timer.start();

    bool quit = false;
    while (!quit) {
        SDL_Event event;
        if ( SDL_PollEvent(&event) ) {
            if (event.type == SDL_QUIT)
                quit = true;
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                quit = true;
        }
        cout << "Frametime: " << Timer.getDelta() << endl;
        Game.redraw();
    }
}