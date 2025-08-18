#include "common.hpp"
#include "agent.hpp"

Agent::Agent(Vector2d position) {
    this->position = position;
}

Agent::Agent(Vector2d position, Vector2d speedPerSecond) {
    this->position = position;
    this->speedPerSecond = speedPerSecond;
}