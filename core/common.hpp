#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <cmath>

#define CHECK_BOUNDS

#define MATH_PI 3.14159265358979323846

inline double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

#endif
