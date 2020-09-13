#ifndef MICEWARS_MATH2D_H
#define MICEWARS_MATH2D_H

#include <iostream>
#include "../Point.h"
#include "../Vector.h"
#include "../global_vars.h"

class Math2D {
public:

    static float compute_acute_angle(Point p1, Point p2) {
        Point right_p2 = p1.x < p2.x ? p2 : Point(p2.x + 2 * (p1.x - p2.x), p2.y);
        Vector v_direction = Vector(p1, right_p2);
        Vector v_parallel = Vector(right_p2.x - p1.x, 0);
        float angle = std::atan2(v_parallel.determinant(v_direction), v_parallel.dot_product(v_direction));
        float degrees = angle * 180 / PI;
        std::cout << "angle = " << angle << ", degrees = " << degrees << "\n";
        return angle;
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

    Math2D() = delete;
};

#endif //MICEWARS_MATH2D_H
