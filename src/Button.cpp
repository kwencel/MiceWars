#include <iosfwd>
#include "Object.h"
#include "Button.h"

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
