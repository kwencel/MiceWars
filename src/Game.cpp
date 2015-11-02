#include "Game.h"
#include "Engine.h"
#include "global_vars.h"

void Game::saveGame(string fileName) {

}

void Game::loadGame(string fileName) {

}

void Game::returnToMenu() {

}

void Game::exit() {

}

void Game::redraw() {
    Engine::Instance()->clearRenderer();
    for (auto player : player_vector) {
        for (auto mouse : player->mice_vector) {
            mouse->display();
        }
    }
    SDL_RenderPresent(Engine::Instance()->renderer);
}

vector<int> Game::findNext(int x, int y, int max_height, int distance) {
    vector<int> point_coordinates;
    int x_2, y_2;

    // SEARCHING FOR X
    if ((win_width - x) < distance) {                                   // setting x_2 as last
        x_2 = win_width;
    }
    else x_2 = getRandomIntBetween(x, x + distance);

    // SEARCHING FOR Y
    if ((y - max_height) > distance) {                                  // if not too high
        if ((win_height - distance - y) < distance) {                   // too low
            y_2 = getRandomIntBetween(y - distance, win_height - distance);
        }
        else y_2 = getRandomIntBetween(y - distance, y + distance);           // if not too low
    }
    else y_2 = getRandomIntBetween(max_height, y + distance);                 // if too high

    // ADDING COORDINATES TO VECTOR
    point_coordinates.push_back(x_2);
    point_coordinates.push_back(y_2);

    return point_coordinates;
}

void Game::generateTerrain() {
    vector<vector<int>> points_vector;
    vector<int> point_coordinates;      // respectively x and y
    int distance = win_width / 10;        // distance between points
    int max_height = win_height / 2;
    int cur_x = 0;
    int cur_y = max_height + distance;

    // ADDING FIRS CONST. POINT TO VECTOR
    point_coordinates.push_back(cur_x);
    point_coordinates.push_back(cur_y);
    cout << "x = " << point_coordinates.front() << ", y = " << point_coordinates.back() << endl;
    points_vector.push_back(point_coordinates);
    point_coordinates.clear();

    while (cur_x != win_width) {    // aby nie poza ekran
        point_coordinates = findNext(cur_x, cur_y, max_height, distance);
        cout << "x = " << point_coordinates.front() << ", y = " << point_coordinates.back() << endl;
        cur_x = point_coordinates.front();
        cur_y = point_coordinates.back();
        points_vector.push_back(point_coordinates);
        point_coordinates.clear();
    }
}

void Game::placeMice() {
    for (auto player : player_vector) { // For each player
        for (int i = 0; i < player->mouse_amount; ++i) {    // Place their mice
            Mouse *mouse = new Mouse(getRandomIntBetween(0, win_width), getRandomIntBetween(0, win_height), 50, 50);
            mouse->texture = Engine::Instance()->makeTexture(mouse1_img);
            player->mice_vector.push_back(mouse);
        }
    }
}

void Game::createPlayer(string name, bool is_human, int mouse_amount, int colour) {
    Player* player = new Player(name, is_human, mouse_amount, colour);
    player_vector.push_back(player);
}

void Game::gameplay() {


}

void Game::pause() {

}

int Game::getRandomIntBetween(int min, int max) {
    uniform_int_distribution<int> distribution(min, nextafter(max, INT_MAX));
    return distribution(mt);
}

//TODO
void Game::readConfigFile() {

}
