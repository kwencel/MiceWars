#ifndef MICEWARS_NOTIFICATIONBOX_H
#define MICEWARS_NOTIFICATIONBOX_H

#include <iostream>
#include <sstream>
#include <SDL_ttf.h>
#include "Object.h"
#include "Engine.h"

class NotificationBox: public Object {
public:
    std::string text;
    float timer;
    TTF_Font* font = TTF_OpenFont("font/OpenSans-Bold.ttf", NOTIFICATIONBOX_FONTSIZE);;
    SDL_Color colour = {255, 255, 255};  // White colour

    NotificationBox(int x, int y, int width, int height, float timer)
            : Object(x, y, width, height), timer(timer) { cout << "NotificationBox created!" << endl;}
    NotificationBox(std::string text, float timer) {} // TODO

    void display() override;
    void refresh();
};


#endif //MICEWARS_NOTIFICATIONBOX_H
