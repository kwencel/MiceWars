#include <iostream>
#include "Game.h"
#include "Engine.h"

using namespace std;

int main(int argc, char **argv) {

    Game Game;
    Engine::Instance()->getReady(Game.getWindowWidth(), Game.getWindowHeigth());
    Game.generateTerrain();
    Game.createPlayer("Joe", true, 3, 0);
    Game.placeMice();


    while (true) {
        Game.redraw();
    }

}