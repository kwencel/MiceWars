#ifndef MICEWARS_NOTIFICATIONBOX_H
#define MICEWARS_NOTIFICATIONBOX_H

#include <string>
#include "Object.h"
#include <iostream>

using namespace std;

class NotificationBox: public Object {
public:
    string text;
    float timer;

    NotificationBox(int x, int y, int width, int height, string text, float timer)
            : Object(x, y, width, height), text(text), timer(timer) { cout << "NotificationBox created!" << endl; }
    NotificationBox(string text, float timer) {} // TODO

    void display() override;
};


#endif //MICEWARS_NOTIFICATIONBOX_H
