#ifndef MICEWARS_OBJECT_H
#define MICEWARS_OBJECT_H

#include <vector>
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include "global_vars.h"
using std::cout;
using std::endl;

class Object {
private:
    SDL_Rect rectangle;

public:
    int pos_x;
    int pos_y;
    int obj_width;
    int obj_height;
    SDL_Texture* texture = nullptr;

    bool flip = false;
    double angle = 0;

    Object() { /* cout << "Created temp object!" << endl; */ };
    Object(int x, int y, int width, int height, std::string img_path = "");
    virtual ~Object();
    SDL_Point getCenter();
    virtual void display();
    virtual void save(std::ofstream& file);
    virtual void load(std::ifstream& file);
};


#endif //MICEWARS_OBJECT_H
