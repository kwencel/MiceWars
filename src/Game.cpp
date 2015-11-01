#include "Game.h"

void Game::saveGame(string fileName) {

}

void Game::loadGame(string fileName) {

}

void Game::returnToMenu() {

}

void Game::exit() {

}

void Game::redraw() {

}

void Game::generateTerrain() {

}

void Game::placeMice() {

}

void Game::gameplay() {

}

void Game::pause() {

}

float Game::getTime() {
    return time;
}

int Game::getRandomIntBetween(int min, int max) {
    //mt19937 mt(rd());
    uniform_int_distribution<int> distribution(min, nextafter(max, INT_MAX));
    return distribution(mt);
}
