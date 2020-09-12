#ifndef MICEWARS_POINT_H
#define MICEWARS_POINT_H


#include <utility>

struct Point {
    int x;
    int y;

    Point(std::pair<int, int> pair) : x(pair.first), y(pair.second) { }

    Point(int x, int y) : x(x), y(y) { }

    operator std::pair<int, int>() const {
        return std::make_pair(x, y);
    }
};


#endif //MICEWARS_POINT_H
