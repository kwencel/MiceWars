#include "NotificationBox.h"
#include "Timer.h"

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

NotificationBox::NotificationBox(int* msg, float timer, int x, int y, int width, int height)
        : Object(x, y, width, height), timer(timer) {
    time_created = Timer::Instance()->getTime();
    //std::chrono::time_point<std::chrono::system_clock, std::chrono::system_clock::duration<float>> duration_time;
    //std::chrono::system_clock::duration duration_time (std::chrono::duration<float>(timer));
    //int timer_int = dynamic_cast<int>(timer*5000);
    std::chrono::milliseconds duration_time(static_cast<int>(timer*5000));
    time_to_destroy = time_created + duration_time;
    cout << "NotificationBox created!" << endl;
}

NotificationBox::NotificationBox(std::string msg, float timer, int x, int y, int width, int height)
        : Object(x, y, width, height), timer(timer), text(msg) {
    time_created = Timer::Instance()->getTime();
    std::chrono::milliseconds duration_time(static_cast<int>(timer*5000));
    time_to_destroy = time_created + duration_time;
    cout << "NotificationBox created!" << endl;
}
