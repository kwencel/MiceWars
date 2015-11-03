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

void Game::drawBackground() {
    if (Engine::Instance()->background_texture != nullptr) {
        SDL_DestroyTexture(Engine::Instance()->background_texture);
    }
    SDL_LockSurface(Engine::Instance()->background);
    for (int x = 0; x < win_width; ++x) {
        for (int y = 0; y < win_height; ++y) {
            switch(world_map[x][y]) {
                case 1:
                    Engine::Instance()->colorPixel(Engine::Instance()->background, x, y, GREEN);
                    break;
                case 2:
                    Engine::Instance()->colorPixel(Engine::Instance()->background, x, y, BLUE);
                    break;
                default:break;
            }
        }
    }
    SDL_UnlockSurface(Engine::Instance()->background);
    Engine::Instance()->background_texture = SDL_CreateTextureFromSurface(Engine::Instance()->renderer, Engine::Instance()->background);
    SDL_RenderCopy(Engine::Instance()->renderer, Engine::Instance()->background_texture, NULL, NULL);
}

void Game::redraw() {
    Engine::Instance()->clearRenderer();
    drawBackground();
    for (auto player : player_vector) {
        for (auto mouse : player->mice_vector) {
            mouse->display();
        }
    }
    SDL_RenderPresent(Engine::Instance()->renderer);
}

pair<int,int> Game::findNext(int x, int y, int max_height, int distance, int river_height) {
    pair<int,int> point_coordinates;
    int x_2, y_2;

    // SEARCHING FOR X
    if ((win_width - x) < distance) {  // setting x_2 as last
        x_2 = win_width;
    }
    else x_2 = getRandomIntBetween(x + 1, x + distance);

    // SEARCHING FOR Y
    if ((y - max_height) > distance) { // if not too high
        if ((win_height - river_height - y) < distance) {   // too low
            y_2 = getRandomIntBetween(y - distance, win_height - river_height);
        }
        else y_2 = getRandomIntBetween(y - distance, y + distance); // if not too low
    }
    else y_2 = getRandomIntBetween(max_height, y + distance);  // if too high

    // ADDING COORDINATES TO VECTOR
    point_coordinates.first = x_2;
    point_coordinates.second = y_2;

    return point_coordinates;
}

void Game::generateTerrain() {
    world_map.resize(win_width + 1);
    vector<pair<int,int>> points_vector;
    pair<int,int> point_coordinates;            // respectively x and y
    int distance;                               // distance between points
    int river_height;
    if (win_width < 50){
        distance = win_width / 10;
        river_height = distance;
    } else {
        distance = win_width / 50;
        river_height = 3* distance;
    }
    int max_height = win_height / 2;
    int cur_x = 0;
    int cur_y = max_height + distance;

    // CREATING POINTS
    // adding first const. point to vector
    point_coordinates.first =cur_x;
    point_coordinates.second =cur_y;
    cout << "x = " << point_coordinates.first << ", y = " << point_coordinates.second << endl;
    points_vector.push_back(point_coordinates);

    // creating and adding the rest of points
    while (cur_x != (win_width)) {
        point_coordinates = findNext(cur_x, cur_y, max_height, distance, river_height);
        cout << "x = " << point_coordinates.first << ", y = " << point_coordinates.second << endl;
        cur_x = point_coordinates.first;
        cur_y = point_coordinates.second;
        points_vector.push_back(point_coordinates);
    }

    // CONNECTING POINTS
    vector<pair<int,int>>::iterator current;
    int x1,y1,x2,y2,a, b;
    current = points_vector.begin();            // iterator at the beginning

    while (*current != points_vector.back()) {
        x1 = current->first;
        y1 = current->second;
        current++;
        x2 = current->first;
        y2 = current->second;
        a = (y2-y1)/(x2-x1);
        b = y1 - (a*x1);

        // columns for points between P1 and P2
        for (int x = x1; x < x2; x++) {
            int y = a*x + b;
            if (x == x1) {      // for the first point P1
                y = y1;
            }
            for (int i = 0; i <= win_height; i++) {
                if (i < y) {
                    world_map[x].push_back(0);
                }
                else if (i < win_height - river_height) {
                    world_map[x].push_back(1);
                }
                else if (i < win_height) {
                    world_map[x].push_back(2);
                }
            }
        }
    }
    // column for last point
    cout << endl;
    for (int i = 0; i <= win_height; i++) {
        if (i < y2) {
            world_map[x2].push_back(0);
        }
        else if (i < win_height - river_height) {
            world_map[x2].push_back(1);
        }
        else if (i < win_height) {
            world_map[x2].push_back(2);
        }
    }
    // displaying content of vector
//    cout << endl << "CONTENT OF VECTOR" << endl;
//    for (int j = win_width; j >= 0; j-- ) {
//        for (int i = 0; i < win_height; i++ ) {
//            cout << world_map[j][i] + '0' - 48;
//        }
//        cout << endl;
//    }
}
inline bool Game::checkCollision(int x, int y) {
    return (world_map[x][y] > 0);
}

bool Game::doesCollide(Object* object) {
    int x = object->pos_x;
    int y = object->pos_y;
    // Upper object rectangle edge check
    for (; x <= object->pos_x + object->obj_width; ++x)
        if (checkCollision(x,y)) { return true; }
    // Right object rectangle edge check
    for (--x; y <= object->pos_y + object->obj_height; ++y)
        if (checkCollision(x,y)) { return true; }
    // Lower object rectangle edge check
    for (--y; x >= object->pos_x; --x)
        if (checkCollision(x,y)) { return true; }
    // Left object rectangle edge chceck
    for (++x; y >= object->pos_x; --y)
        if (checkCollision(x,y)) { return true; }
    return false;
}

void Game::applyGravity() {
    for (auto player : player_vector) {
        for (auto mouse: player->mice_vector) {
            if (not doesCollide(mouse)) {
                mouse->pos_y++;
            }
        }
    }
}

void Game::placeMice() {
    for (auto player : player_vector) { // For each player
        for (int i = 0; i < player->mouse_amount; ++i) {    // Place their mice
            //Mouse *mouse = new Mouse(getRandomIntBetween(0, win_width - MICE_WIDTH), getRandomIntBetween(0, win_height/3), 25, 25);
            Mouse *mouse = new Mouse(getRandomIntBetween(0, win_width - MICE_WIDTH), getRandomIntBetween(0, win_height/3), MICE_WIDTH, MICE_HEIGHT);
            mouse->texture = Engine::Instance()->makeTexture(MOUSE1_IMG);
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
