#ifndef MICEWARS_NOTIFICATIONBOX_H
#define MICEWARS_NOTIFICATIONBOX_H

#include <iostream>
#include <sstream>
#include <SDL_ttf.h>
#include <chrono>
#include "Object.h"
#include "Engine.h"

class NotificationBox: public Object {
public:
    std::string text = "";
    int* number_ptr = nullptr;
    int number;
    float timer;
    bool is_being_displayed = false;
    TTF_Font* font = TTF_OpenFont("font/OpenSans-Bold.ttf", NOTIFICATIONBOX_FONTSIZE);
    SDL_Color colour = {255, 255, 255};  // White colour
    std::chrono::time_point<std::chrono::high_resolution_clock> time_created;

    NotificationBox(int& msg, float timer, int x, int y, int width, int height);
    NotificationBox(std::string msg, float timer, int x, int y, int width, int height);

    void display() override;
    void destroy() override;
    void refresh();
    void save(std::ofstream& file) override;
    void load(std::ifstream& file) override;
};


#endif //MICEWARS_NOTIFICATIONBOX_H
