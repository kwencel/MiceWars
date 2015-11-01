#ifndef MICEWARS_GAME_H
#define MICEWARS_GAME_H

#include <vector>
#include <string>
#include <random>
#include <climits>
#include <SDL2/SDL.h>
#include "Player.h"
#include "NotificationBox.h"

using namespace std;

class Game {
private:
    random_device rd;
    mt19937 mt;
    float time;
    bool state;
    bool fullscreen;

    vector<int> findNext(int x, int y, int max_height, int distance);

public:
    vector<vector<char>> world_map;
    vector<Player*> player_vector;
    vector<NotificationBox*> notification_vector;
    int players_count;
    int win_width = 800;
    int win_height = 600;

    Game() { mt.seed(rd()); cout << "Game created!" << endl; };
    void saveGame(string file_name);
    void loadGame(string file_name);
    void returnToMenu();
    void exit();
    void redraw();
    void generateTerrain();
    void placeMice();
    void gameplay();
    void pause();
    float getTime();
    int getRandomIntBetween(int min, int max);

};


#endif //MICEWARS_GAME_H
