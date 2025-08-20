#ifndef AGENT_HPP
#define AGENT_HPP

#include "common.hpp"
#include "vector2d.hpp"

enum class AgentState {
    AGENT_HEALTHY,
    AGENT_INFECTED,
    AGENT_IMMUNE,
    AGENT_DEAD
};

class Agent {
    Vector2d position;
    Vector2d speedPerSecond;

    AgentState state;
    AgentState stateBuffer;
public:
    Agent(Vector2d position);
    Agent(Vector2d position, Vector2d speedPerSecond);

    Agent(Vector2d position, AgentState state);
    Agent(Vector2d position, Vector2d speedPerSecond, AgentState state);

    Vector2d getPosition();
    Vector2d getSpeedPerSeconds();

    AgentState getState();

    void step(double time, Vector2d bounds);

    void infected();
    void immune();
    void die();
    void heal(bool immunity);
};

#endif