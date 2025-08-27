#ifndef AGENT_HPP
#define AGENT_HPP

#include "common.hpp"

enum AgentState {
    AGENT_HEALTHY = 0,
    AGENT_INFECTED = 1,
    AGENT_IMMUNE = 2,
    AGENT_DEAD = 3
};

// Flat Agent
class Agent {
    double x;
    double y;

    double vx;
    double vy;

    double state;
    double stateBuffer;
public:
    Agent(double x, double y);
    Agent(double x, double y, double vx, double vy);

    Agent(double x, double y, AgentState state);
    Agent(double x, double y, double vx, double vy, AgentState state);

    double getPositionX();
    double getPositionY();

    double getSpeedX();
    double getSpeedY();

    AgentState getState();
    AgentState getNextState();

    void step(double time, double bounds_width, double bounds_height);

    void infected();
    void immune();
    void die();
    void heal(bool immunity);
};

#endif