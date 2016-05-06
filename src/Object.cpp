#include "Object.h"
#include "Engine.h"

void Object::display() {
    rectangle.x = pos_x;
    rectangle.y = pos_y;
    rectangle.w = obj_width;
    rectangle.h = obj_height;
    if (flip) {
        SDL_RenderCopyEx(Engine::Instance()->renderer, texture, NULL, &rectangle, angle, NULL, SDL_FLIP_HORIZONTAL);
    }
    else {
        SDL_RenderCopyEx(Engine::Instance()->renderer, texture, NULL, &rectangle, angle, NULL, SDL_FLIP_NONE);
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
    //cout << "Object created!" << endl;
}

Object::~Object() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
    //cout << "Object destroyed!" << endl;
}

SDL_Point Object::getCenter() {
    SDL_Point center;
    center.x = pos_x + obj_width / 2;
    center.y = pos_y + obj_height / 2;
    return center;
}


void Object::save(std::ofstream& file) {
    file.write((char*) &pos_x, sizeof(int));
    file.write((char*) &pos_y, sizeof(int));
    file.write((char*) &obj_width, sizeof(int));
    file.write((char*) &obj_height, sizeof(int));
//    file.write((char*)&texture, sizeof(SDL_Texture*));
    file.write((char*) &rectangle, sizeof(SDL_Rect));
    file.write((char*) &flip, sizeof(bool));
    file.write((char*) &angle, sizeof(double));
}

void Object::load(std::ifstream& file) {
    file.read((char*) &pos_x, sizeof(int));
    file.read((char*) &pos_y, sizeof(int));
    file.read((char*) &obj_width, sizeof(int));
    file.read((char*) &obj_height, sizeof(int));
//    file.read((char*)&texture, sizeof(SDL_Texture*));
    file.read((char*) &rectangle, sizeof(SDL_Rect));
    file.read((char*) &flip, sizeof(bool));
    file.read((char*) &angle, sizeof(double));
}
