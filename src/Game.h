#ifndef MICEWARS_GAME_H
#define MICEWARS_GAME_H

#include <vector>
#include <queue>
#include <deque>
#include <string>
#include <random>
#include <climits>
#include <SDL2/SDL.h>
#include <bits/stl_queue.h>
#include "Player.h"
#include "NotificationBox.h"

class Game {
private:
    std::random_device rd;
    std::mt19937 mt;
    bool state = gameplay;
    bool fullscreen = 0;
    int current_player_vecpos = 0;
    std::pair<int,int> findNext(int x, int y, int max_height, int distance, int river_height);
    bool checkCollision(int x, int y);
    void connectPoints(std::vector<std::pair<int, int>> points_vector, int river_height);
    void displayArrayOfValues();

    static Game* m_pInstance;
    Game() { mt.seed(rd()); cout << "Game created!" << endl; };

public:
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    std::vector<std::vector<char>> world_map;
    std::vector<Player*> player_vector;
    std::deque<NotificationBox*> notification_queue;
    int players_count = 3;
    int win_width = 800;
    int win_height = 600;
    bool quit = false;
    bool background_need_redraw = true;
    Player* current_player = nullptr;

    void createHoles(int x0, int y0, int radius, std::vector<Mouse*> *affectedMice = nullptr);
    void readConfigFile();
    void saveGame(std::string file_name);
    void loadGame(std::string file_name);
    void returnToMenu();
    void exit();
    void redraw();
    void generateTerrain();
    void placeMice();
    void createPlayer(std::string name, bool is_human, int mouse_amount, int colour);
    void changePlayer();
    void pause();
    int getWindowWidth()    { return win_width; };
    int getWindowHeigth()   { return win_height; };
    bool getState()         { return state; };
    int getRandomIntBetween(int min, int max);
    void drawBackground();
    bool doesCollide(Object* object, int x_offset = 0, int y_offset = 0);
    bool doesCollideWithPoint(Object *object, int coll_x, int coll_y, int x_offset = 0, int y_offset = 0);
    void applyGravity();
    static Game* Instance();
    void applyMovement();
    void createNotification(std::string message, float timer = -1.0, int x = -1, int y = -1, int width = -1, int height = -1);
    NotificationBox* createNotification(std::string message, int* number_ptr, float timer = -1.0, int x = -1,
                                        int y = -1, int width = -1, int height = -1, bool push_to_vector = true);
    bool isInsideWindowBorders(Object* object, int x_offset = 0, int y_offset = 0);
    void readKeyboardState();
    void displayBackground();
    void capFPS();
    void removePersistentNotifications();
    bool checkMiceCollisionBool(int coll_x, int coll_y, int x_offset = 0, int y_offset = 0);
    std::vector<Mouse *> checkMiceCollision(int coll_x, int coll_y, int x_offset = 0, int y_offset = 0);
    void checkMiceCollisionRef(int coll_x, int coll_y, std::vector<Mouse*> *affectedMice, int x_offset = 0, int y_offset = 0);
    void checkWinLoseConditions();
    void controlMenu();
    void displayMenu();
};


#endif //MICEWARS_GAME_H
