#ifndef MICEWARS_POINT_H
#define MICEWARS_POINT_H


#include <utility>
#include <SDL_rect.h>
#include <vector>

struct Point {
    int x;
    int y;

    Point(std::pair<int, int> pair) : x(pair.first), y(pair.second) { }

    Point(SDL_Point point) : x(point.x), y(point.y) { }

    Point(int x, int y) : x(x), y(y) {}

    operator std::pair<int, int>() const {
        return std::make_pair(x, y);
    }

    static std::vector<Point> pointsBetween(Point p1, Point p2) {
        std::vector<Point> pixels;
        //calculating range for line between start and end point
        int dx = p2.x - p1.x;
        int dy = p2.y - p1.y;

        int x = p1.x;
        int y = p2.y;

        //this is the case when slope(m) < 1
        if (abs(dx) > abs(dy)) {
            pixels.emplace_back(x, y);    //this putpixel is for very first pixel of the line
            int pk = (2 * abs(dy)) - abs(dx);

            for (int i = 0; i < abs(dx); i++) {
                x = x + 1;
                if (pk < 0)
                    pk = pk + (2 * abs(dy));
                else {
                    y = y + 1;
                    pk = pk + (2 * abs(dy)) - (2 * abs(dx));
                }
                pixels.emplace_back(x, y);
            }
        } else {
            //this is the case when slope is greater than or equal to 1  i.e: m>=1
            pixels.emplace_back(x, y);    //this putpixel is for very first pixel of the line
            int pk = (2 * abs(dx)) - abs(dy);

            for (int i = 0; i < abs(dy); i++) {
                y = y + 1;
                if (pk < 0)
                    pk = pk + (2 * abs(dx));
                else {
                    x = x + 1;
                    pk = pk + (2 * abs(dx)) - (2 * abs(dy));
                }

                pixels.emplace_back(x, y);    // display pixel at coordinate (x, y)
            }
        }
        return pixels;
    }
};
#endif //MICEWARS_POINT_H
