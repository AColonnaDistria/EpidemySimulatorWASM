#include "common.hpp"
#include "agent.hpp"

#include <random>

Agent::Agent(double x, double y) {
    this->x = x;
    this->y = y;

    this->vx = 0.0;
    this->vy = 0.0;
}

Agent::Agent(double x, double y, double vx, double vy) {
    this->x = x;
    this->y = y;

    this->vx = vx;
    this->vy = vy;
}

Agent::Agent(double x, double y, AgentState state) {
    this->x = x;
    this->y = y;

    this->vx = 0.0;
    this->vy = 0.0;

    this->state = (AgentState) state;
    this->stateBuffer = this->state;
}

Agent::Agent(double x, double y, double vx, double vy, AgentState state) {
    this->x = x;
    this->y = y;

    this->vx = vx;
    this->vy = vy;

    this->state = (AgentState) state;
    this->stateBuffer = this->state;
}

double Agent::getPositionX() {
    return this->x;
}

double Agent::getPositionY() {
    return this->y;
}

double Agent::getSpeedX() {
    return this->vx;
}

double Agent::getSpeedY() {
    return this->vy;
}

void Agent::step(double timeInSeconds, double bounds_x, double bounds_y) {
    this->state = this->stateBuffer;

    // move
    double xspeed = this->vx;
    double yspeed = this->vy;

    double speed = sqrt(xspeed * xspeed + yspeed * yspeed);
    double angle = atan2(yspeed, xspeed);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> rnAngle(-0.05 * MATH_PI, 0.05 * MATH_PI);

    angle += rnAngle(mt);

    xspeed = cos(angle) * speed;
    yspeed = sin(angle) * speed;

    double x2 = this->x + xspeed * timeInSeconds;
    double y2 = this->y + yspeed * timeInSeconds;

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
    if (x2 >= bounds_x)
    {
        xspeed *= -1.0;
        x2 = bounds_x - 1.0;
    }
    if (y2 >= bounds_y)
    {
        yspeed *= -1.0;
        y2 = bounds_y - 1.0;
    }

    this->vx = xspeed;
    this->vy = yspeed;

    this->x = x2;
    this->y = y2;
}

AgentState Agent::getState() {
    return (AgentState) this->state;
}

void Agent::infected() {
    this->stateBuffer = (int) AgentState::AGENT_INFECTED;
}

void Agent::heal(bool immunity) {
    this->stateBuffer = (int) (immunity ? AgentState::AGENT_IMMUNE : AgentState::AGENT_HEALTHY);
}

void Agent::die() {
    this->stateBuffer = (int) AgentState::AGENT_DEAD;
}
