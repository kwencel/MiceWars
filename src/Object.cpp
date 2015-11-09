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
