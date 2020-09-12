#ifndef MICEWARS_VECTOR_H
#define MICEWARS_VECTOR_H


#include <utility>
#include "Point.h"

struct Vector {
    int v_x;
    int v_y;

    Vector(int v_x, int v_y) : v_x(v_x), v_y(v_y) { }

    Vector(Point pos_1, Point pos_2) : v_x(pos_2.x - pos_1.x), v_y(pos_2.y - pos_1.y) { }

};


#endif //MICEWARS_VECTOR_H
