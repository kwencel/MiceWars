#include "Object.h"
#include "Engine.h"

void Object::display() {
    rectangle.x = pos_x; rectangle.y = pos_y;
    rectangle.w = obj_width; rectangle.h = obj_height;
    if (flip) {
        SDL_RenderCopyEx(Engine::Instance()->renderer, texture, NULL, &rectangle, angle, &center, SDL_FLIP_HORIZONTAL);
    }
    else {
        SDL_RenderCopyEx(Engine::Instance()->renderer, texture, NULL, &rectangle, angle, &center, SDL_FLIP_NONE);
    }
}

void Object::destroy() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

Object::Object(int x, int y, int width, int height, std::string img_path) {
    pos_x = x;
    pos_y = y;
    obj_width = width;
    obj_height = height;
    if (img_path != "") {
        texture = Engine::Instance()->makeTexture(img_path.c_str());
    }
    cout << "Object created!" << endl;
    center.x = obj_width / 2;
    center.y = obj_height / 2;
}