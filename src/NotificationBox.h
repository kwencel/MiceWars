#ifndef MICEWARS_NOTIFICATIONBOX_H
#define MICEWARS_NOTIFICATIONBOX_H

#include <string>
#include "Object.h"
#include <iostream>

class NotificationBox: public Object {
public:
    std::string text;
    float timer;

    NotificationBox(int x, int y, int width, int height, std::string text, float timer)
            : Object(x, y, width, height), text(text), timer(timer) { cout << "NotificationBox created!" << endl; }
    NotificationBox(std::string text, float timer) {} // TODO

    void display() override;
};


#endif //MICEWARS_NOTIFICATIONBOX_H
