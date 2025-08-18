#ifndef EPIDEMY_HPP
#define EPIDEMY_HPP

#include "common.hpp"
#include "agent.hpp"
#include "vector2d.hpp"

#include <vector>

class EpidemySimulator {
    std::vector<Agent> agents;
    Vector2d boxSize;
private:
    void setupRandomGenerator();
    
public:
    EpidemySimulator(Vector2d boxSize);
    void addRandomAgents(int numberOfAgents, double maxSpeedPerSeconds);

    Agent getAgent(int index);
    int getNumberOfAgents();
};

#endif