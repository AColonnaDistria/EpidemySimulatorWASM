#ifndef AGENT_HPP
#define AGENT_HPP

#include "common.hpp"
#include "vector2d.hpp"

class Agent {
    Vector2d position;
    Vector2d speedPerSecond;

public:
    Agent(Vector2d position);
    Agent(Vector2d position, Vector2d speedPerSecond);

    Vector2d getPosition();
    Vector2d getSpeedPerSeconds();
};

#endif