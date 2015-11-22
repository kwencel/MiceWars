#include <algorithm>
#include <assert.h>
#include <iostream>
#include <fstream>
#include "Game.h"
#include "Timer.h"
#include "RangedWeapon.h"
#include "AI.h"

Game* Game::m_pInstance = nullptr;

Game* Game::Instance() {
    if (m_pInstance == nullptr) {
        m_pInstance = new Game;
    }
    return m_pInstance;
}

void Game::readKeyboardState() {
    if (current_player != nullptr) {
        if (current_player->is_human) {
            current_player->handleKeys(keystates);
        }
        else {
            current_player->handleKeys(SDLK_KP_ENTER);
        }
    }
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                quit = true;
                break;
            }
            case SDL_KEYDOWN: {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    pause();
                }
                else if (event.key.keysym.sym == SDLK_q) {
                    quit = true;
                }
                else if (current_player != nullptr and current_player->is_human and
                        (event.key.keysym.sym != SDLK_LEFT or event.key.keysym.sym != SDLK_RIGHT or
                         event.key.keysym.sym != SDLK_UP or event.key.keysym.sym != SDLK_DOWN or
                         event.key.keysym.sym != SDLK_SPACE)) {
                    current_player->handleKeys(event.key.keysym.sym);
                }
                break;
            }
            case SDL_MOUSEMOTION: {
                Engine::Instance()->readCursorPosition();
                break;
            }
            default:break;
        }
    }
}

void Game::saveGame(std::string fileName) {
    std::ofstream save_game_file;
    save_game_file.open(fileName, std::ios::out | std::ios::trunc | std::ios::binary); // output operations, replace content, in binary mode
    if (save_game_file.is_open()) {
        save_game_file.write((char*)&current_player_vecpos, sizeof(int));
        save_game_file.write((char*)&win_width, sizeof(int));
        save_game_file.write((char*)&win_height, sizeof(int));
        save_game_file.write((char*)&background_need_redraw, sizeof(bool));
        for (auto column: world_map) {
            for (auto pixel: column) {
                save_game_file.write(&pixel, sizeof(char));
            }
        }
        // PLAYERS AND MICE
        int players;
        players = int(player_vector.size());
        save_game_file.write((char*)&players, sizeof(int));
        if (players_count > 0) {
            for (int i=0; i < players_count; i++) {
                player_vector[i]->save(save_game_file);
            }
        }

        cout << "File is saved!\n";
        save_game_file.close();
    }
    else cout << "Unable to open file\n";
}

void Game::loadGame(std::string fileName) {
    while (not player_vector.empty()) {
        delete player_vector[0];
    }
    player_vector.clear();
    world_map.clear();

    std::ifstream read_game_file;
    read_game_file.open(fileName, std::ios::in | std::ios::binary); // output operations, replace content, in binary mode
    if (read_game_file.is_open()) {
        read_game_file.read((char*)&current_player_vecpos, sizeof(int));
        read_game_file.read((char*)&win_width, sizeof(int));
        read_game_file.read((char*)&win_height, sizeof(int));
        read_game_file.read((char*)&background_need_redraw, sizeof(bool));
        for (int i = 0; i <= win_width; i++) {
            std::vector<char> pixel_vector;
            for (int j = 0; j < win_height; j++) {
                char pixel;
                read_game_file.read(&pixel, sizeof(char));
                pixel_vector.push_back(pixel);
            }
            world_map.push_back(pixel_vector);
        }
        // PLAYERS AND MICE
        read_game_file.read((char*)&players_count, sizeof(int));
        if (players_count != 0) {
            for (int i = 0; i < players_count; i++) {
                Player* player = new Player();
                (*player).load(read_game_file);
                player_vector.push_back(player);
            }
        }

        // ADDITIONAL
        for (int player_id = 0; player_id < players_count; ++player_id) { // For each player
            for (int i = 0; i < player_vector[player_id]->mice_amount; ++i) {    // Place their mice
                std::stringstream mouse_img;
                mouse_img << MOUSE_IMG << player_id + 1 << MOUSE_IMG_EXTENSION;
                player_vector[player_id]->mice_vector[i]->texture = Engine::Instance()->makeTexture(mouse_img.str().c_str());
                player_vector[player_id]->mice_vector[i]->changeWeapon(shotgun);
                player_vector[player_id]->mice_vector[i]->notification_hp = createNotification("",
                            &player_vector[player_id]->mice_vector[i]->hp,
                            -1, player_vector[player_id]->mice_vector[i]->pos_x,
                            player_vector[player_id]->mice_vector[i]->pos_y - NOTIFICATION_HP_OFFSET,
                            NOTIFICATION_HP_WIDTH, NOTIFICATION_HP_HEIGHT, false);
            }
        }
        drawBackground();
        cout << "File is loaded";
        read_game_file.close();
        this->current_player = player_vector[current_player_vecpos];
    }
    else cout << "Unable to open file\n";

}

void Game::returnToMenu() {
    removePersistentNotifications();
    while (not player_vector.empty()) {
        delete player_vector[0];
    }
    world_map.clear();
    notification_queue.clear();
    current_player_vecpos = 0;
    current_player = nullptr;
    background_need_redraw = true;
    state = menu;
}

void Game::exit() {
    Engine::Instance()->destroy();
}

void Game::drawBackground() {
    if (Engine::Instance()->background_texture != nullptr) {
        SDL_DestroyTexture(Engine::Instance()->background_texture);
    }
    SDL_LockSurface(Engine::Instance()->background);
    for (int x = 0; x < Engine::Instance()->getWindowWidth(); ++x) {
        for (int y = 0; y < Engine::Instance()->getWindowHeight(); ++y) {
            switch(world_map[x][y]) {
                case 0:
                    Engine::Instance()->colorPixel(Engine::Instance()->background, x, y, BLACK);
                    break;
                case 1:
                    Engine::Instance()->colorPixel(Engine::Instance()->background, x, y, YELLOW);
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
}


void Game::displayBackground() {
    SDL_RenderCopy(Engine::Instance()->renderer, Engine::Instance()->background_texture, NULL, NULL);
}

void Game::redraw() {
    if (state == gameplay) {
        // Draw background
        if (background_need_redraw) {
            drawBackground();
            background_need_redraw = false;
        }
        displayBackground();
        for (auto player : player_vector) {
            for (auto mouse : player->mice_vector) {
                mouse->display();
            }
        }
    }
    else {
        displayMenu();
    }
    // Draw notifications
    if (not notification_queue.empty() and not (Game::Instance()->getState() == menu and not player_vector.empty())) {
        // If notification queue is not empty and pause is not active (main menu after match is OK)
        auto time_now = Timer::Instance()->getTime();
        if (notification_queue.front()->is_being_displayed == false) {
            notification_queue.front()->time_created = time_now;
            notification_queue.front()->is_being_displayed = true;
        }
        auto time_notification_created = notification_queue.front()->time_created;
        float time_difference = std::chrono::duration_cast<std::chrono::milliseconds>(time_now - time_notification_created).count() / 1000.0;
        if ((notification_queue.front()->timer != -1) and (time_difference > notification_queue.front()->timer)) {
            delete notification_queue.front();
            notification_queue.pop_front();
        }
        else {
            notification_queue.front()->display();
        }
    }
    // Show it on screen
    SDL_RenderPresent(Engine::Instance()->renderer);
}

void Game::displayArrayOfValues() {
    // displaying content of vector
    cout << endl << "CONTENT OF VECTOR" << endl;
    for (int j = Engine::Instance()->getWindowWidth(); j >= 0; j-- ) {
        for (int i = 0; i < Engine::Instance()->getWindowHeight(); i++ ) {
            cout << world_map[j][i] + '0' - 48;
        }
        cout << endl;
    }
}

std::pair<int,int> Game::findNext(int x, int y, int max_height, int distance, int river_height) {
    int win_width = Engine::Instance()->getWindowWidth();
    int win_height = Engine::Instance()->getWindowHeight();
    std::pair<int,int> point_coordinates;
    int x_2, y_2;

    // SEARCHING FOR X
    if ((win_width - x) < distance) {  // setting x_2 as last
        x_2 = win_width;
    }
    else x_2 = x + distance;

    // SEARCHING FOR Y
    if ((y - max_height) > distance) {                          // if not too high
        if ((win_height - river_height - y) < 3*distance) {    // too low
            y_2 = getRandomIntBetween(y - 3*distance, win_height - river_height);
        }
        else
            y_2 = getRandomIntBetween(y - 3*distance, y + 3*distance);
    }
    else
        y_2 = getRandomIntBetween(max_height, y + 3*distance);

    // ADDING COORDINATES TO VECTOR
    point_coordinates.first = x_2;
    point_coordinates.second = y_2;

    return point_coordinates;
}

void Game::connectPoints(std::vector<std::pair<int, int>> points_vector, int river_height) {
    int win_width = Engine::Instance()->getWindowWidth();
    int win_height = Engine::Instance()->getWindowHeight();
    // CONNECTING POINTS
    std::vector<std::pair<int,int>>::iterator current;
    int x1, y1, x2, y2, a, b;
    current = points_vector.begin();            // iterator at the beginning

    while (*current != points_vector.back()) {
        x1 = current->first;
        y1 = current->second;
        current++;
        x2 = current->first;
        y2 = current->second;
        a = (y1-y2)/(x1-x2);
        b = y1 - (a * x1);

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
}

void Game::createHoles(int x0, int y0, int radius, std::vector<Mouse*> *affectedMice) {
    int win_width = Engine::Instance()->getWindowWidth();
    int win_height = Engine::Instance()->getWindowHeight();
    for (int i = radius; i >= 1; i--) {
        int x = i;
        int y = 0;
        int decisionOver2 = 1 - x;   // Decision criterion divided by 2 evaluated at x=radius, y=0
        // drawing and colouring circle
        while (y <= x) {
            for (int l = x + x0; l >= x0; l--){
                if ( l >= 0 && l <= win_width && (y + y0) >= 0 && (y + y0) <= win_height) {
                    if (affectedMice != nullptr)
                        checkMiceCollisionRef(l, y + y0, affectedMice);
                    if (y + y0 >= (win_height - win_height / RIVER_DIVIDER))
                        world_map[l][y + y0] = 2;
                    else world_map[l][y + y0] = 0;   // Octant 1
                }
                if ( l >= 0 && l <= win_width && (-y + y0) >= 0 && (-y + y0) <= win_height) {
                    if (affectedMice != nullptr)
                        checkMiceCollisionRef(l, -y + y0, affectedMice);
                    if (-y + y0 >= (win_height - win_height / RIVER_DIVIDER))
                        world_map[l][-y + y0] = 2;  // Octant 8
                    else world_map[l][-y + y0] = 0;
                }
            }
            for (int l = x + y0; l >= y0; l--){
                if ( (y + x0) >= 0 && (y + x0) <= win_width && l >= 0 && l <= win_height) {
                    if (affectedMice != nullptr)
                        checkMiceCollisionRef(y + x0, l, affectedMice);
                    if (l >= (win_height - win_height / RIVER_DIVIDER))
                        world_map[y + x0][l] = 2;   // Octant 2
                    else world_map[y + x0][l] = 0;
                }
                if ( (-y + x0) >= 0 && (-y + x0) <= win_width && l >= 0 && l <= win_height) {
                    if (affectedMice != nullptr)
                        checkMiceCollisionRef(-y + x0, l, affectedMice);
                    if (l >= (win_height - win_height / RIVER_DIVIDER))
                        world_map[-y + x0][l] = 2;  // Octant 3
                    else world_map[-y + x0][l] = 0;
                }
            }
            for (int l = -x + x0; l <= x0; l++){
                if ( l >= 0 && l <= win_width && (y + y0) >= 0 && (y + y0) <= win_height) {
                    if (affectedMice != nullptr)
                        checkMiceCollisionRef(l, y + y0, affectedMice);
                    if (y + y0 >= (win_height - win_height / RIVER_DIVIDER))
                        world_map[l][y + y0] = 2;   //Octant 4
                    else world_map[l][y + y0] = 0;
                }
                if ( l >= 0 && l <= win_width && (-y + y0) >= 0 && (-y + y0) <= win_height) {
                    if (affectedMice != nullptr)
                        checkMiceCollisionRef(l, -y + y0, affectedMice);
                    if (-y + y0 >= (win_height - win_height / RIVER_DIVIDER))
                        world_map[l][-y + y0] = 2;  //Octant 5
                    else world_map[l][-y + y0] = 0;
                }
            }
            for (int l = -x + y0; l <= y0; l++){
                if ( (-y + x0) >= 0 && (-y + x0) <= win_width && l >= 0 && l <= win_height) {
                    if (affectedMice != nullptr)
                        checkMiceCollisionRef(-y + x0, l, affectedMice);
                    if (l >= (win_height - win_height / RIVER_DIVIDER))
                        world_map[-y + x0][l] = 2;  //Octant 6
                    else world_map[-y + x0][l] = 0;
                }
                if ( (y + x0) >= 0 && (y + x0) <= win_width && l >= 0 && l <= win_height) {
                    if (affectedMice != nullptr)
                        checkMiceCollisionRef(y + x0, l, affectedMice);
                    if (l >= (win_height - win_height / RIVER_DIVIDER))
                        world_map[y + x0][l] = 2;   //Octant 7
                    else world_map[y + x0][l] = 0;
                }
            }
            y++;
            if (decisionOver2 <= 0) {
                decisionOver2 += 2 * y + 1;   // Change in decision criterion for y -> y+1
            }
            else {
                x--;
                decisionOver2 += 2 * (y - x) + 1;   // Change for y -> y+1, x -> x-1
            }
        }
    }
}

void Game::generateTerrain() {
    int win_width = Engine::Instance()->getWindowWidth();
    int win_height = Engine::Instance()->getWindowHeight();
    world_map.resize(win_width + 1);
    std::vector<std::pair<int, int>> points_vector;
    std::pair<int, int> point_coordinates;            // respectively x and y
    int river_height = win_height/RIVER_DIVIDER;
    int distance = win_width / (win_width/15); // distance between points
    int max_height = 2 * win_height / 5;
    int cur_x = 0;
    int cur_y = max_height + distance;

    // CREATING POINTS
    // adding first const. point to vector
    point_coordinates.first = cur_x;
    point_coordinates.second = cur_y;
    //cout << "x = " << point_coordinates.first << ", y = " << point_coordinates.second << endl;
    points_vector.push_back(point_coordinates);

    // creating and adding the rest of points
    while (cur_x != (win_width)) {
        point_coordinates = findNext(cur_x, cur_y, max_height, distance, river_height);
        //cout << "x = " << point_coordinates.first << ", y = " << point_coordinates.second << endl;
        cur_x = point_coordinates.first;
        cur_y = point_coordinates.second;
        points_vector.push_back(point_coordinates);
    }

    // CONNECTING POINTS
    connectPoints(points_vector, river_height);

    // ADDING CHEESE HOLES EFFECT
    for ( int i = 1; i <= AMOUNT_OF_CHEESE_HOLES/6; i++){
        createHoles(getRandomIntBetween(0,win_width/3),
                    getRandomIntBetween(win_height/3, 2*win_height/3),
                    getRandomIntBetween (win_height/40,win_height/10));
        createHoles(getRandomIntBetween(0,win_width/3),
                    getRandomIntBetween(2*win_height/3, win_height - river_height - 50),
                    getRandomIntBetween (win_height/40,win_height/10));
    }
    for ( int i = 1; i <= AMOUNT_OF_CHEESE_HOLES/6; i++){
        createHoles(getRandomIntBetween(win_width/3,2*win_width/3),
                    getRandomIntBetween(win_height/3, 2*win_height/3),
                    getRandomIntBetween (win_height/40,win_height/10));
        createHoles(getRandomIntBetween(win_width/3,2*win_width/3),
                    getRandomIntBetween(2*win_height/3, win_height - river_height - 50),
                    getRandomIntBetween (win_height/40,win_height/10));
    }
    for ( int i = 1; i <= AMOUNT_OF_CHEESE_HOLES/6; i++){
        createHoles(getRandomIntBetween(2*win_width/3,win_width),
                    getRandomIntBetween(win_height/3, 2*win_height/3),
                    getRandomIntBetween (win_height/40,win_height/10));
        createHoles(getRandomIntBetween(2*win_width/3,win_width),
                    getRandomIntBetween(2*win_height/3, win_height - river_height - 50),
                    getRandomIntBetween (win_height/40,win_height/10));
    }
}

inline bool Game::checkCollision(int x, int y) {
    return (world_map[x][y] == 1);
}

bool Game::doesCollide(Object* object, int x_offset, int y_offset) {
    int x = object->pos_x + x_offset;
    int y = object->pos_y + y_offset;
    // Upper object rectangle edge check
    for (; x <= object->pos_x + x_offset + object->obj_width; ++x)
        if (checkCollision(x,y)) { return true; }
    // Right object rectangle edge check
    for (--x; y <= object->pos_y + y_offset + object->obj_height; ++y)
        if (checkCollision(x,y)) { return true; }
    // Lower object rectangle edge check
    for (--y; x >= object->pos_x + x_offset; --x)
        if (checkCollision(x,y)) { return true; }
    // Left object rectangle edge check
    for (++x; y >= object->pos_y + y_offset; --y)
        if (checkCollision(x,y)) { return true; }
    return false;
}

bool Game::doesCollideWithPoint(Object* object, int coll_x, int coll_y, int x_offset, int y_offset) {
    int x = object->pos_x + x_offset;
    int y = object->pos_y + y_offset;
    // Upper object rectangle edge check
    for (; x <= object->pos_x + x_offset + object->obj_width; ++x)
        if (x == coll_x and y == coll_y) { return true; }
    // Right object rectangle edge check
    for (--x; y <= object->pos_y + y_offset + object->obj_height; ++y)
        if (x == coll_x and y == coll_y) { return true; }
    // Lower object rectangle edge check
    for (--y; x >= object->pos_x + x_offset; --x)
        if (x == coll_x and y == coll_y) { return true; }
    // Left object rectangle edge check
    for (++x; y >= object->pos_y + y_offset; --y)
        if (x == coll_x and y == coll_y) { return true; }
    return false;
}

std::vector<Mouse*> Game::checkMiceCollisionRect(Object* object) {
    std::vector<Mouse*> affectedMice;
    for (auto player : player_vector) {
        for (auto mouse: player->mice_vector) {
            if (doesObjectsOverlap(mouse, object)) {
                affectedMice.push_back(mouse);
            }
        }
    }
    return affectedMice;
}

bool Game::checkMiceCollisionBool(int coll_x, int coll_y, int x_offset, int y_offset) {
    for (auto player : player_vector) {
        for (auto mouse: player->mice_vector) {
            if (mouse != current_player->current_mouse and doesCollideWithPoint(mouse, coll_x, coll_y, x_offset, y_offset)) {
                return true;
            }
        }
    }
    return false;
}

void Game::checkMiceCollisionRef(int coll_x, int coll_y, std::vector<Mouse *> *affectedMice, int x_offset, int y_offset) {
    for (auto player : player_vector) {
        for (auto mouse: player->mice_vector) {
            if (std::find (affectedMice->begin(), affectedMice->end(), mouse) != affectedMice->end()) {
                continue;
            }
            if (doesCollideWithPoint(mouse, coll_x, coll_y, x_offset, y_offset)) {
                affectedMice->push_back(mouse);
            }
        }
    }
}

void Game::applyGravity() {
    std::vector<Mouse*> affected_mice;
    for (auto player : player_vector) {
        for (auto mouse: player->mice_vector) {
            int steps = static_cast<int>(GRAVITY_MUL * Timer::Instance()->getDelta());
            if (steps == 0) {
                steps = 1;
            }
            for (int pixel = 0; pixel < steps; ++pixel) {
                if (not doesCollide(mouse, 0, 1)) {
                    mouse->pos_y++;
                    if (not isInsideWindowBorders(mouse, 0, 1)) {
                        affected_mice.push_back(mouse);
                        break;
                    }
                }
                else {
                    break;
                }
            }
            if (RangedWeapon* ranged_weapon = dynamic_cast<RangedWeapon*>(mouse->weapon)) {
                if (ranged_weapon->gravity and ranged_weapon->bullet != nullptr) {
                    double a_decrement = pow(ranged_weapon->in_air_counter, 1/8.0)/ranged_weapon->weight;
                    cout << ranged_weapon->in_air_counter << ", " << a_decrement << endl;
                    ranged_weapon->a_coefficient += a_decrement;
                }
            }
        }
    }
    // Delete mice that got killed by the water
    if (not affected_mice.empty()) {
        while (not affected_mice.empty()) {
            delete affected_mice[0];
            affected_mice.erase(affected_mice.begin());
        }
        Game::Instance()->checkWinLoseConditions();
    }
}

void Game::placeMice() {
    for (int player_id = 0; player_id < players_count; ++player_id) { // For each player
        for (int i = 0; i < player_vector[player_id]->mice_amount; ++i) {    // Place their mice
            if (player_vector[player_id]->name == GREEN_MOUSE)
                player_vector[player_id]->colour = GREEN_COLOUR;
            else if (player_vector[player_id]->name == PINK_MOUSE)
                player_vector[player_id]->colour = PINK_COLOUR;
            else if (player_vector[player_id]->name == BLUE_MOUSE)
                player_vector[player_id]->colour = BLUE_COLOUR;
            else if (player_vector[player_id]->name == RED_MOUSE)
                player_vector[player_id]->colour = RED_COLOUR;
            std::stringstream mouse_img;
            mouse_img << MOUSE_IMG << player_vector[player_id]->colour << MOUSE_IMG_EXTENSION;
            Mouse* mouse = new Mouse(getRandomIntBetween(0, Engine::Instance()->getWindowWidth() - MICE_WIDTH),
                                     getRandomIntBetween(0, Engine::Instance()->getWindowHeight()/3), MICE_WIDTH, MICE_HEIGHT, mouse_img.str());
            mouse->changeWeapon(shotgun);
            mouse->notification_hp = createNotification("",
                                                        &mouse->hp,
                                                        -1,
                                                        mouse->pos_x,
                                                        mouse->pos_y - NOTIFICATION_HP_OFFSET,
                                                        NOTIFICATION_HP_WIDTH,
                                                        NOTIFICATION_HP_HEIGHT,
                                                        false);
            player_vector[player_id]->mice_vector.push_back(mouse);
        }
    }
}

void Game::createPlayer(std::string name, bool is_human, int mice_amount, int colour) {
    if (is_human) {
        Player* player = new Player(name, is_human, mice_amount, colour);
        player->player_vecpos = player_vector.size();
        player_vector.push_back(player);
    }
    else {
        AI* player = new AI(name, is_human, mice_amount, colour);
        player->player_vecpos = player_vector.size();
        player_vector.push_back(player);
    }
}

void Game::changePlayer() {
    removePersistentNotifications();
    if (current_player == nullptr) {
        current_player = player_vector[0];
        current_player_vecpos = 0;
    }
    else {
        if (current_player_vecpos < player_vector.size() - 1) {
            current_player = player_vector[++current_player_vecpos];
        }
        else {
            current_player = player_vector[0];
            current_player_vecpos = 0;
        }
    }
    current_player->makeTurn();
    createNotification(current_player->getName(), 1);
    createNotification("Movepoints remaining: ", &Game::Instance()->current_player->current_mouse->movepoints, -1.0);
}

void Game::pause() {
    state = !state;
    if (state != gameplay) {
        menu_need_redraw = true;
    }
    else {
        new_game = false;
    }
}

int Game::getRandomIntBetween(int min, int max) {
    std::uniform_int_distribution<int> distribution(min, nextafter(max, INT_MAX));
    return distribution(mt);
}

void Game::applyMovement() {
    if (current_player == nullptr) {
        return;
    }
    if (current_player->current_mouse->can_move) {
        current_player->current_mouse->move();
    }
    else {
        current_player->current_mouse->weapon->prepare();
        if (dynamic_cast<RangedWeapon*>(current_player->current_mouse->weapon)->bullet != nullptr) {
            dynamic_cast<RangedWeapon*>(current_player->current_mouse->weapon)->moveBullet();
        }
    }
}

bool Game::isInsideWindowBorders(Object* object, int x_offset, int y_offset) {
    return ((object->pos_x + x_offset >= 0) and (object->pos_x + x_offset + object->obj_width <= Engine::Instance()->getWindowWidth()) and
            (object->pos_y + y_offset >= 0) and (object->pos_y + y_offset + object->obj_height <= Engine::Instance()->getWindowHeight()));
}

void Game::createNotification(std::string message, float timer, int x, int y, int width, int height) {
    int win_width = Engine::Instance()->getWindowWidth();
    int win_height = Engine::Instance()->getWindowHeight();
    int message_length = message.length();
    if (x == -1) { x = (win_width / 2) - message_length * 5; };
    if (y == -1) { y = win_height / 16; };
    if (width == -1) { width = (message_length * 10); }
    if (height == -1) { height = NOTIFICATIONBOX_FONTSIZE; };
    NotificationBox* message_box = new NotificationBox(message, timer, x, y, width, height);
    message_box->refresh();
    notification_queue.push_back(message_box);
}

NotificationBox* Game::createNotification(std::string message, int* number_ptr, float timer, int x, int y, int width, int height, bool push_to_queue) {
    int win_width = Engine::Instance()->getWindowWidth();
    int win_height = Engine::Instance()->getWindowHeight();
    int message_length = message.length() + 1;
    if (x == -1) { x = (win_width / 2) - message_length * 5; };
    if (y == -1) { y = win_height / 16; };
    if (width == -1) { width = (message_length * 10); }
    if (height == -1) { height = NOTIFICATIONBOX_FONTSIZE; };
    NotificationBox* message_box = new NotificationBox(message, timer, x, y, width, height);
    message_box->number_ptr = number_ptr;
    message_box->refresh();
    if (push_to_queue) {
        notification_queue.push_back(message_box);
    }
    else {
        return message_box;
    }
    return nullptr;
}

void Game::removePersistentNotifications() {
    for (int i = 0; i < notification_queue.size(); ++i) {
        if (notification_queue[i]->timer == -1.0) {
            delete notification_queue[i];
            notification_queue.erase(notification_queue.begin() + i);
        }
    }
}

void Game::capFPS() {
    if (Timer::Instance()->getTimeFromLastDelta() + 0.010 < Timer::Instance()->getTargetFrametime()) {
        SDL_Delay((Timer::Instance()->getTargetFrametime() - Timer::Instance()->getTimeFromLastDelta())*975);
    }
}

void Game::checkWinLoseConditions() {
    // Remove players with no mice remaining from player_vector
    std::vector<Player*> players_to_delete;
    for (auto player : player_vector) {
        if (player->mice_vector.empty()) {
            std::stringstream ss;
            ss << "Player " << player->getName() << " has lost!";
            createNotification(ss.str(), 3);
            players_to_delete.push_back(player);
        }
    }
    if (not players_to_delete.empty()) {
        for (auto player : players_to_delete) {
            delete player;
        }
    }
    if (player_vector.size() == 1) {
        std::stringstream ss;
        ss << "Player " << player_vector[0]->getName() << " has won!";
        cout << "[INFO] Player " << player_vector[0]->getName() << " has won!!!" << endl;
        createNotification(ss.str(), 1);
        returnToMenu();
    }
    else if (player_vector.empty()) {
        returnToMenu();
    }
    else {
        changePlayer();
    }
}

bool Game::doesObjectsOverlap(Object* object1, Object* object2) {
    return (object1->pos_x < object2->pos_x + object2->obj_width && object1->pos_x + object1->obj_width > object2->pos_x &&
            object1->pos_y < object2->pos_y + object2->obj_height && object1->pos_y + object1->obj_height > object2->pos_y);
}

void Game::searchForButton(std::pair<int,int> pair) {
    Engine::Instance()->readCursorPosition();
    Object* point_where_mouse = new Object(pair.first, pair.second, 1, 1);
    for (auto button: buttons_vector) {
        if (Game::Instance()->doesObjectsOverlap(button, point_where_mouse)) {
            if (button == buttons_vector[B_NEW_GAME] and new_game) {
                continue;
            }
            else {
                //cout << "Button click\n";
                button->click();
                break;
            }
        }
    }
}

void Game::controlMenu() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                quit = true;
                break;
            }
            case SDL_KEYDOWN: {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    pause();
                }
                else if (event.key.keysym.sym == SDLK_q) {
                    quit = true;
                }
            }
            case SDL_MOUSEMOTION: {
                Engine::Instance()->readCursorPosition();
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    searchForButton(Engine::Instance()->getCursorPosition());
                }
            }
            default:break;
        }
    }
}
void Game::creatingButtonsImagesVector() {
    buttons_images.push_back("img/b_ResumeGame.png");
    buttons_images.push_back("img/b_SaveGame.png");
    buttons_images.push_back("img/b_LoadGame.png");
    buttons_images.push_back("img/b_Quit.png");
    buttons_images.push_back("img/b_NewGame.png");
    buttons_images.push_back("img/b_Start.png");
    buttons_images.push_back("img/b_Human1.png");
    buttons_images.push_back("img/b_Human1.png");
    buttons_images.push_back("img/b_Human1.png");
    buttons_images.push_back("img/b_Human1.png");
    buttons_images.push_back("img/1.png");
    buttons_images.push_back("img/1.png");
    buttons_images.push_back("img/1.png");
    buttons_images.push_back("img/1.png");
    buttons_images.push_back("img/p_daktyl.png");
    buttons_images.push_back("img/p_miki.png");
    buttons_images.push_back("img/p_lazarz.png");
    buttons_images.push_back("img/p_ziomek.png");

    // alternative
    buttons_images.push_back("img/b_ResumeGame2.png");
    buttons_images.push_back("img/b_SaveGame2.png");
    buttons_images.push_back("img/b_LoadGame2.png");
    buttons_images.push_back("img/b_Quit2.png");
    buttons_images.push_back("img/b_NewGame2.png");
    buttons_images.push_back("img/b_Start2.png");
    buttons_images.push_back("img/b_AI1.png");
    buttons_images.push_back("img/b_AI1.png");
    buttons_images.push_back("img/b_AI1.png");
    buttons_images.push_back("img/b_AI1.png");
    buttons_images.push_back("");
    buttons_images.push_back("");
    buttons_images.push_back("");
    buttons_images.push_back("");
    buttons_images.push_back("img/p_daktyl2.png");
    buttons_images.push_back("img/p_miki2.png");
    buttons_images.push_back("img/p_lazarz2.png");
    buttons_images.push_back("img/p_ziomek2.png");
    buttons_images.push_back("img/1.png"); // nr.36
    buttons_images.push_back("img/2.png");
    buttons_images.push_back("img/3.png");
    buttons_images.push_back("img/4.png");
    buttons_images.push_back("img/5.png");
    buttons_images.push_back("img/6.png");
    buttons_images.push_back("img/7.png");


}

void Game::redrawMenu() {
    SDL_SetRenderDrawColor(Engine::Instance()->renderer, 255, 255, 51, 255 );
    Engine::Instance()->clearRenderer();
    // CREATING NOTIFICATIONS
    Object* n_menu = new Object(20, 25, 206, 100, "img/n_menu.png");
    n_menu->display();
    Object* n_option = new Object(397, 25, 206, 100, "img/n_option.png");
    n_option->display();
    if (buttons_vector.empty()) {   // every button's state is true
        // CREATING VECTOR OF PATHS TO IMAGES AND THEIR ALTERNATIVES
        creatingButtonsImagesVector();
        // CREATING BUTTONS
        Button* b_resume_game = new Button(25, 150, 150, 70, "img/b_ResumeGame.png");
        buttons_vector.push_back(b_resume_game);
        Button* b_save_game = new Button(25, 245, 150, 70, "img/b_SaveGame.png");
        buttons_vector.push_back(b_save_game);
        Button* b_load_game = new Button(25, 340, 150, 70, "img/b_LoadGame.png");
        buttons_vector.push_back(b_load_game);
        Button* b_quit_game = new Button(25, 480, 150, 70, "img/b_Quit.png");
        buttons_vector.push_back(b_quit_game);
        Button* b_new_game = new Button(425, 150, 150, 70, "img/b_NewGame.png");
        buttons_vector.push_back(b_new_game);
        Button* b_start = new Button(425, 150, 150, 70, "img/b_Start.png");
        buttons_vector.push_back(b_start);
        // CREATING PLAYERS' BUTTONS
        Button* b_ai_d = new Button(300, 330, 100, 46, "img/b_Human1.png");
        buttons_vector.push_back(b_ai_d);
        Button* b_ai_m = new Button(570, 330, 100, 46, "img/b_Human1.png");
        buttons_vector.push_back(b_ai_m);
        Button* b_ai_l = new Button(300, 480, 100, 46, "img/b_Human1.png");
        buttons_vector.push_back(b_ai_l);
        Button* b_ai_z = new Button(570, 480, 100, 46, "img/b_Human1.png");
        buttons_vector.push_back(b_ai_z);
        //
        Button* b_num_d = new Button(340, 270, 60, 60, "img/1.png");
        buttons_vector.push_back(b_num_d);
        Button* b_num_m = new Button(610, 270, 60, 60, "img/1.png");
        buttons_vector.push_back(b_num_m);
        Button* b_num_l = new Button(340, 420, 60, 60, "img/1.png");
        buttons_vector.push_back(b_num_l);
        Button* b_num_z = new Button(610, 420, 60, 60, "img/1.png");
        buttons_vector.push_back(b_num_z);
        // CREATING BUTTONS OF PLAYERS
        Button* p_daktyl = new Button(230, 245, 270, 150, "img/p_daktyl.png");
        buttons_vector.push_back(p_daktyl);
        Button* p_miki = new Button(500, 245, 270, 150, "img/p_miki.png");
        buttons_vector.push_back(p_miki);
        Button* p_lazarz = new Button(230, 395, 270, 150, "img/p_lazarz.png");
        buttons_vector.push_back(p_lazarz);
        Button* p_ziomek = new Button(500, 395, 270, 150, "img/p_ziomek.png");
        buttons_vector.push_back(p_ziomek);

    }
        // AT THE BEGINNING OF GAME
    if (world_map.empty() and !new_game) {
        buttons_vector[B_RESUME_GAME]->state = false;
        buttons_vector[B_SAVE_GAME]->state = false;
        buttons_vector[B_START]->state = false;
        buttons_vector[P_DAKTYL]->state = false;
        buttons_vector[P_MIKI]->state = false;
        buttons_vector[P_LAZARZ]->state = false;
        buttons_vector[P_ZIOMEK]->state = false;
    }
        // IN PAUSE STATE BUT NO NEW GAME
    else if (!world_map.empty() and !new_game) {
        buttons_vector[B_RESUME_GAME]->state = true;
        buttons_vector[B_SAVE_GAME]->state = true;
        buttons_vector[B_START]->state = false;
        buttons_vector[P_DAKTYL]->state = false;
        buttons_vector[P_MIKI]->state = false;
        buttons_vector[P_LAZARZ]->state = false;
        buttons_vector[P_ZIOMEK]->state = false;
    }
        // NEW GAME
    if (new_game) {
        if (menu_active_players >= 2) {
            buttons_vector[B_START]->state = true;
        }
        else {
            buttons_vector[B_START]->state = false;
        }
    }
    // CHANGING IMAGE BASING ON THE STATE OF BUTTON AND DISPLAYING
    // first players
    for (int i = P_DAKTYL; i <= P_ZIOMEK; i++ ) {
        if (!buttons_vector[i]->state) {
            buttons_vector[i]->texture = Engine::Instance()->makeTexture(buttons_images[i + ALL_IN_B_VECTOR].c_str());
        }
        else {
            buttons_vector[i]->texture = Engine::Instance()->makeTexture(buttons_images[i].c_str());
        }
        buttons_vector[i]->display();
    }
    for (int i = 0; i <= B_AI_HUMAN_Z; i++) {
        if (!buttons_vector[i]->state) {
            buttons_vector[i]->texture = Engine::Instance()->makeTexture(buttons_images[i + ALL_IN_B_VECTOR].c_str());
        }
        else {
            buttons_vector[i]->texture = Engine::Instance()->makeTexture(buttons_images[i].c_str());
        }
        if ((!new_game and i != B_START) or (new_game and i != B_NEW_GAME)) {
            buttons_vector[i]->display();
        }
    }
    for (int i = B_NUM_D; i <= B_NUM_Z; i++) {
        buttons_vector[i]->texture = Engine::Instance()->makeTexture(buttons_images[buttons_vector[i]->amount + 35].c_str());
        buttons_vector[i]->display();
    }
    delete n_menu;
    delete n_option;
}

void Game::displayMenu() {
    if (menu_need_redraw) {
        redrawMenu();
        menu_need_redraw = false;
    }
}