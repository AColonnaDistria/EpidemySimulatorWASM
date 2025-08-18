#include "common.hpp"
#include "vector2d.hpp"

Vector2d::Vector2d() {
    this->x = 0.0;
    this->y = 0.0;
}

Vector2d::Vector2d(double x, double y) {
    this->setX(x);
    this->setY(y);
}

// x
double Vector2d::getX() {
    return this->x;
}

void Vector2d::setX(double x) {
    this->x = x;
}

// y
double Vector2d::getY() {
    return this->y;
}

void Vector2d::setY(double y) {
    this->y = y;
}

Vector2d Vector2d::operator +(Vector2d& right) {
    return Vector2d(this->x + right.x, this->y + right.y);
}

Vector2d Vector2d::operator -(Vector2d& right) {
    return Vector2d(this->x - right.x, this->y - right.y);
}