#include "NotificationBox.h"

void NotificationBox::display() {
    Object::display();
}

void NotificationBox::refresh() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), colour);
    texture = SDL_CreateTextureFromSurface(Engine::Instance()->renderer, surface);
    SDL_FreeSurface(surface);
}