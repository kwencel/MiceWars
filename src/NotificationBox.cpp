#include "NotificationBox.h"

void NotificationBox::display() {
    if (number_ptr != nullptr) {
        if ((*number_ptr) != (number)) {
            number = *number_ptr;
            refresh();
        }
    }
    Object::display();
}

void NotificationBox::refresh() {
    SDL_Surface* surface = nullptr;
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
    if (number_ptr != nullptr) {    // If the NotificationBox has a number to display
        std::stringstream ss;
        ss << text << number;
        surface = TTF_RenderText_Blended(font, ss.str().c_str(), colour);
    }
    else {
        surface = TTF_RenderText_Blended(font, text.c_str(), colour);
    }
    texture = SDL_CreateTextureFromSurface(Engine::Instance()->renderer, surface);
    SDL_FreeSurface(surface);
}

NotificationBox::NotificationBox(int& message, float timer, int x, int y, int width, int height)
        : Object(x, y, width, height), timer(timer) {
    //cout << "NotificationBox created!" << endl;
}

NotificationBox::NotificationBox(std::string message, float timer, int x, int y, int width, int height)
        : Object(x, y, width, height), timer(timer), text(message) {
    //cout << "NotificationBox created!" << endl;
}

NotificationBox::~NotificationBox() {
    number_ptr = nullptr;
    TTF_CloseFont(font);
    //cout << "NotificationBox destroyed!" << endl;
}

void NotificationBox::save(std::ofstream &file) {
    Object::save(file);
    file.write((char*)&text, sizeof(text));
    file.write((char*)&number, sizeof(number));
    file.write((char*)&timer, sizeof(timer));
    file.write((char*)&is_being_displayed, sizeof(is_being_displayed));
}

void NotificationBox::load(std::ifstream &file) {
    Object::load(file);
    file.read((char*)&text, sizeof(text));
    file.read((char*)&number, sizeof(number));
    file.read((char*)&timer, sizeof(timer));
    file.read((char*)&is_being_displayed, sizeof(is_being_displayed));
}
