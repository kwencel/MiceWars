#ifndef MICEWARS_BUTTON_H
#define MICEWARS_BUTTON_H

#include "Object.h"

class Button: public Object {
public:
    bool state;

    Button(int x, int y, int width, int height)
            : Object(x, y, width, height) { cout << "Button created!" << endl; }
    ~Button();
    Button(bool state = false) : state(state)  { }
    void click() { state = !state; };
    void save(std::ofstream& file) override;
    void load(std::ifstream& file) override;

};


#endif //MICEWARS_BUTTON_H
