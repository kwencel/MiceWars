#ifndef MICEWARS_GAME_H
#define MICEWARS_GAME_H

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include "Player.h"
#include "NotificationBox.h"

using namespace std;

class Game {
private:
    float time;
    bool state;

public:
    vector<vector<int>> world_map;
    vector<Player*> player_vector;
    vector<NotificationBox*> notification_vector;
    int players_count;

    Game() { cout << "Game created!" << endl; };
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

};


#endif //MICEWARS_GAME_H
