#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include "common.hpp"

class Vector2d {
    double x;
    double y;

public:
    Vector2d();
    Vector2d(double x, double y);
    // x
    double getX();
    void setX(double x);

    // y
    double getY();
    void setY(double y);

    Vector2d operator +(Vector2d& right);
    Vector2d operator -(Vector2d& right);
};

#endif