#include "common.hpp"
#include "agent.hpp"
#include "vector2d.hpp"

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

void Agent::step(double timeInSeconds) {
    this->position.setX(this->position.getX() + this->getSpeedPerSeconds().getX() * timeInSeconds);
    this->position.setY(this->position.getY() + this->getSpeedPerSeconds().getY() * timeInSeconds);
}