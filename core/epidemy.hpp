#ifndef EPIDEMY_HPP
#define EPIDEMY_HPP

#include "common.hpp"
#include "agent.hpp"
#include "vector2d.hpp"
#include "virus_characteristics.hpp"

#include <vector>

class EpidemySimulator {
    std::vector<Agent> agents;
    Vector2d boxSize;
    VirusCharacteristics virusCharacteristics;

    double timeTriggerContaminationStep;
public:
    EpidemySimulator(Vector2d boxSize, VirusCharacteristics virus);
    void addRandomAgents(int numberOfAgents, double maxSpeedPerSeconds, int numberOfInfectedAgents = 0, int numberOfImmuneAgents = 0);
    void step(double timeInSeconds);

    Agent getAgent(int index);
    int getNumberOfAgents();

    VirusCharacteristics getVirusCharacteristics();
};

#endif