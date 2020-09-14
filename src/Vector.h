#ifndef MICEWARS_VECTOR_H
#define MICEWARS_VECTOR_H


#include <utility>
#include <ostream>
#include "Point.h"

struct Vector {
    int v_x;
    int v_y;

    Vector(int v_x, int v_y) : v_x(v_x), v_y(v_y) { }

    Vector(Point pos_1, Point pos_2) : v_x(pos_2.x - pos_1.x), v_y(pos_2.y - pos_1.y) { }

    int dot_product(const Vector& rhs) {
        return v_x * rhs.v_x + v_y * rhs.v_y;
    }

    int determinant(Vector rhs) {
        return v_x * rhs.v_y - v_y * rhs.v_x;
    }

    Vector operator+(const Vector& rhs) const {
        return Vector(v_x + rhs.v_x, v_y + rhs.v_y);
    }

    Vector operator-(const Vector& rhs) const {
        return Vector(v_x - rhs.v_x, v_y - rhs.v_y);
    }

    Vector operator*(const int scalar) {
        return Vector(v_x * scalar, v_y * scalar);
    }

    Vector& operator+=(const Vector& rhs) {
        v_x += rhs.v_x;
        v_y += rhs.v_y;
        return *this;
    }

    Vector& operator-=(const Vector& rhs) {
        v_x += rhs.v_x;
        v_y += rhs.v_y;
        return *this;
    }

    Vector& operator*=(const int scalar) {
        v_x *= scalar;
        v_y *= scalar;
        return *this;
    }

    bool operator==(const Vector& rhs) const {
        return v_x == rhs.v_x && v_y == rhs.v_y;
    }

    bool operator!=(const Vector& rhs) const {
        return !(rhs == *this);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector& vector) {
        os << "v_x: " << vector.v_x << " v_y: " << vector.v_y;
        return os;
    }
};


#endif //MICEWARS_VECTOR_H
