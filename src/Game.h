#ifndef MICEWARS_GAME_H
#define MICEWARS_GAME_H

#include <vector>
#include <queue>
#include <deque>
#include <string>
#include <random>
#include <climits>
#include <fstream>
#include <iterator>
#include <SDL2/SDL.h>
#include <bits/stl_queue.h>
#include "Player.h"
#include "NotificationBox.h"
#include "Button.h"

class Game {
private:
    static Game* m_pInstance;
    std::random_device rd;
    std::mt19937 mt;
    bool state = not gameplay;
    bool fullscreen = 0;

    bool checkCollision(int x, int y);

    std::pair<int, int> findNextPoint(int x, int y, int max_height, int distance, int river_height);

    void connectPoints(std::vector<std::pair<int, int>> points_vector, int river_height);

    int getRandomIntBetween(int min, int max);

    void drawBackground();

    Game() {
        mt.seed(rd());
        cout << "Game created!" << endl;
    };

public:
    int players_count = 0;
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    std::vector<std::vector<char>> world_map;
    std::vector<Player*> player_vector;
    std::vector<Button*> buttons_vector;
    std::vector<std::string> buttons_images;
    std::deque<NotificationBox*> notification_queue;
    short menu_active_players = 0;
    bool menu_needs_redraw = false;
    bool background_needs_redraw = true;
    bool new_game = false;
    int current_player_vecpos = 0;
    bool quit = false;
    Player* current_player = nullptr;

    void createPlayer(std::string name, bool is_human, int mouse_amount, int colour);

    void changePlayer();

    void generateTerrain();

    void createHoles(int x0, int y0, int radius, std::vector<Mouse*>* affectedMice = nullptr);

    void placeMice();

    void saveGame(std::string file_name);

    void loadGame(std::string file_name);

    void returnToMenu(std::string winning_string = "");

    void exit();

    void redraw();

    void displayMenu();

    void redrawMenu();

    void searchForButton(std::pair<int, int> pair);

    void createButtonsImagesVector();

    void pause();

    bool getState() { return state; };

    bool doesCollide(Object* object, int x_offset = 0, int y_offset = 0);

    bool doesCollideWithPoint(Object* object, int coll_x, int coll_y, int x_offset = 0, int y_offset = 0);

    void applyGravity();

    void applyMovement();

    void createNotification(std::string message, float timer = -1.0, SDL_Color colour = {255, 255, 255}, int x = -1,
                            int y = -1, int width = -1, int height = -1);

    NotificationBox* createNotification(std::string message, int* number_ptr, float timer = -1.0, int x = -1,
                                        int y = -1, int width = -1, int height = -1, bool push_to_vector = true);

    bool isInsideWindowBorders(Object* object, int x_offset = 0, int y_offset = 0);

    void readKeyboardState();

    void displayBackground();

    void capFPS();

    void removePersistentNotifications();

    bool checkMiceCollisionBool(int coll_x, int coll_y, int x_offset = 0, int y_offset = 0);

    void checkMiceCollisionRef(int coll_x, int coll_y, std::vector<Mouse*>* affectedMice, int x_offset = 0,
                               int y_offset = 0);

    void checkWinLoseConditions();

    void controlMenu();

    bool doesObjectsOverlap(Object* object1, Object* object2);

    std::vector<Mouse*> checkMiceCollisionRect(Object* object);

    static Game* Instance();
};


#endif //MICEWARS_GAME_H
