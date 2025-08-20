#include "common.hpp"
#include "agent.hpp"
#include "vector2d.hpp"

#include <random>

Agent::Agent(Vector2d position) {
    this->position = position;
}

Agent::Agent(Vector2d position, Vector2d speedPerSecond) {
    this->position = position;
    this->speedPerSecond = speedPerSecond;
}

Vector2d Agent::getPosition() {
    return this->position;
}

Vector2d Agent::getSpeedPerSeconds() {
    return this->speedPerSecond;
}

void Agent::step(double timeInSeconds, Vector2d bounds) {
    double xspeed = this->speedPerSecond.getX();
    double yspeed = this->speedPerSecond.getY();

    double speed = sqrt(xspeed * xspeed + yspeed * yspeed);
    double angle = atan2(yspeed, xspeed);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> rnAngle(-0.05 * MATH_PI, 0.05 * MATH_PI);

    angle += rnAngle(mt);

    xspeed = cos(angle) * speed;
    yspeed = sin(angle) * speed;

    double x2 = this->position.getX() + xspeed * timeInSeconds;
    double y2 = this->position.getY() + yspeed * timeInSeconds;

    if (x2 < 0)
    {
        xspeed *= -1.0;
        x2 = 1.0;
    }
    if (y2 < 0)
    {
        yspeed *= -1.0;
        y2 = 1.0;
    }
    if (x2 >= bounds.getX())
    {
        xspeed *= -1.0;
        x2 = bounds.getX() - 1.0;
    }
    if (y2 >= bounds.getY())
    {
        yspeed *= -1.0;
        y2 = bounds.getY() - 1.0;
    }

    this->speedPerSecond.setX(xspeed);
    this->speedPerSecond.setY(yspeed);

    this->position.setX(x2);
    this->position.setY(y2);
}