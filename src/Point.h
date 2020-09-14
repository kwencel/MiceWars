#ifndef MICEWARS_POINT_H
#define MICEWARS_POINT_H


#include <utility>
#include <SDL_rect.h>
#include <vector>
#include <ostream>

struct Point {
    int x;
    int y;

    Point(std::pair<int, int> pair) : x(pair.first), y(pair.second) { }

    Point(SDL_Point point) : x(point.x), y(point.y) { }

    Point(int x, int y) : x(x), y(y) {}

    operator std::pair<int, int>() const {
        return std::make_pair(x, y);
    }

    bool operator==(const Point& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator!=(const Point& rhs) const {
        return !(rhs == *this);
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << "x: " << point.x << " y: " << point.y;
        return os;
    }
};
#endif //MICEWARS_POINT_H
