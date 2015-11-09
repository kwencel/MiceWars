#include "NotificationBox.h"
#include "Timer.h"

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
    cout << "NotificationBox created!" << endl;
}

NotificationBox::NotificationBox(std::string message, float timer, int x, int y, int width, int height)
        : Object(x, y, width, height), timer(timer), text(message) {
    cout << "NotificationBox created!" << endl;
}

void NotificationBox::destroy() {
    TTF_CloseFont(font);
    Object::destroy();
}
