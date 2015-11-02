#include "Object.h"
#include "Engine.h"

void Object::display(){
    SDL_Rect rectangle;
    rectangle.x = pos_x; rectangle.y = pos_y;
    rectangle.w = obj_width; rectangle.h = obj_height;
    SDL_RenderCopy(Engine::Instance()->renderer, texture, NULL, &rectangle);
}

void Object::destroy() {

}
