#ifndef MICEWARS_OBJECT_H
#define MICEWARS_OBJECT_H

#include <vector>
#include <SDL2/SDL.h>
#include <iostream>
#include "global_vars.h"
using std::cout;
using std::endl;

class Object {
private:
    double angle = 0;

protected:
//    vector<SDL_Surface*> bitmap_vector;
//    int current_bitmap;
    bool flip = false;

public:
    int pos_x;
    int pos_y;
    int obj_width;
    int obj_height;
    SDL_Texture* texture;
    SDL_Rect rectangle;
    SDL_Point center;

    Object() { cout << "Created temp object!" << endl; };
    Object(int x, int y, int width, int height)
            : pos_x(x), pos_y(y), obj_height(height), obj_width(width) { center.x = obj_width/2;
                                                                         center.y = obj_height/2;
                                                                         cout << "Object created!" << endl; }
    virtual void display();
    virtual void destroy();
};


#endif //MICEWARS_OBJECT_H
