#include <iosfwd>
#include "Object.h"
#include "Button.h"
#include "Game.h"

Button::~Button() {
    cout << "Button destroyed!" << endl;
}
void Button::save(std::ofstream &file) {
    Object::save(file);
    file.write((char*)&state, sizeof(state));
}

void Button::load(std::ifstream &file) {
    Object::load(file);
    file.read((char*)&state, sizeof(state));
}

void Button::click() {
    state = !state;
    if (this == Game::Instance()->buttons_vector[0]) {
        
    }
}
