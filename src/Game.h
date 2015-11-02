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

    pair<int,int> findNext(int x, int y, int max_height, int distance, int river_height);

public:
    vector<vector<char>> world_map;
    vector<Player*> player_vector;
    vector<NotificationBox*> notification_vector;
    int players_count;
    int win_width = 400;
    int win_height = 200;

    Game() { mt.seed(rd()); cout << "Game created!" << endl; };
    void readConfigFile();
    void saveGame(string file_name);
    void loadGame(string file_name);
    void returnToMenu();
    void exit();
    void redraw();
    void generateTerrain();
    void placeMice();
    void createPlayer(string name, bool is_human, int mouse_amount, int colour);
    void gameplay();
    void pause();
    float getTime()         { return time; };
    int getWindowWidth()    { return win_width; };
    int getWindowHeigth()   { return win_height; };
    int getRandomIntBetween(int min, int max);
};


#endif //MICEWARS_GAME_H
