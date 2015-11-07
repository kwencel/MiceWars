#ifndef MICEWARS_GAME_H
#define MICEWARS_GAME_H

#include <vector>
#include <string>
#include <random>
#include <climits>
#include <SDL2/SDL.h>
#include "Player.h"
#include "NotificationBox.h"

class Game {
private:
    std::random_device rd;
    std::mt19937 mt;
    float time;
    bool state;
    bool fullscreen;
    std::pair<int,int> findNext(int x, int y, int max_height, int distance, int river_height);
    bool checkCollision(int x, int y);
    void connectingPoints(std::vector<std::pair<int,int>> points_vector, int river_height);
    void displayArrayOfValues();
    void createHoles(int x0, int y0, int radius);
    static Game* m_pInstance;
    Game() { mt.seed(rd()); cout << "Game created!" << endl; };

public:
    std::vector<std::vector<char>> world_map;
    std::vector<Player*> player_vector;
    std::vector<NotificationBox*> notification_vector;
    int players_count = 1;
    int win_width = 800;
    int win_height = 600;
    bool quit = false;

    void readConfigFile();
    void saveGame(std::string file_name);
    void loadGame(std::string file_name);
    void returnToMenu();
    void exit();
    void redraw();
    void generateTerrain();
    void placeMice();
    void createPlayer(std::string name, bool is_human, int mouse_amount, int colour);
    void gameplay();
    void pause();
    float getTime()         { return time; };
    int getWindowWidth()    { return win_width; };
    int getWindowHeigth()   { return win_height; };
    int getRandomIntBetween(int min, int max);
    void drawBackground();
    bool doesCollide(Object* object, int x_offset = 0, int y_offset = 0);
    void applyGravity();
    static Game* Instance();

    void applyMovement();

    bool isInsideWindowBorders(Object* object, int x_offset = 0, int y_offset = 0);

    void updateGameState();
};


#endif //MICEWARS_GAME_H
