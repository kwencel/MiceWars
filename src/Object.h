#ifndef MICEWARS_OBJECT_H
#define MICEWARS_OBJECT_H

#include <vector>
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

class Object {
protected:
//    vector<SDL_Surface*> bitmap_vector;
//    int current_bitmap;

public:
    int pos_x;
    int pos_y;
    int obj_width;
    int obj_height;
    SDL_Texture* texture;

    Object() { cout << "Created temp object!" << endl; };
    Object(int x, int y, int width, int height)
            : pos_x(x), pos_y(y), obj_height(height), obj_width(width) { cout << "Object created!" << endl; }
    virtual void display();
    virtual void destroy();
};


#endif //MICEWARS_OBJECT_H
