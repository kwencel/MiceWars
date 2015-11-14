#ifndef MICEWARS_OBJECT_H
#define MICEWARS_OBJECT_H

#include <vector>
#include <SDL2/SDL.h>
#include <iostream>
#include "global_vars.h"
using std::cout;
using std::endl;

class Object {
protected:
//    vector<SDL_Surface*> bitmap_vector;
//    int current_bitmap;

public:
    int pos_x;
    int pos_y;
    int obj_width;
    int obj_height;
    SDL_Texture* texture = nullptr;
    SDL_Rect rectangle;
    SDL_Point center;
    bool flip = false;
    double angle = 0;

    Object() { cout << "Created temp object!" << endl; };
    Object(int x, int y, int width, int height, std::string img_path = "");
    void updateCenter();
    
    virtual void display();
    virtual void destroy();
};


#endif //MICEWARS_OBJECT_H
