#ifndef EPIDEMY_HPP
#define EPIDEMY_HPP

#include "common.hpp"
#include "agent.hpp"
#include "virus_characteristics.hpp"

#include <vector>

class EpidemySimulator {
    std::vector<Agent> agents;
    double boxSize_width;
    double boxSize_height;
    VirusCharacteristics virusCharacteristics;

    double timeTriggerContaminationStep;
public:
    EpidemySimulator(double boxSize_width, double boxSize_height, VirusCharacteristics virus);
    void addRandomAgents(int numberOfAgents, double maxSpeedPerSeconds, int numberOfInfectedAgents = 0, int numberOfImmuneAgents = 0);
    void step(double timeInSeconds);

    Agent getAgent(int index);
    int getNumberOfAgents();

    std::vector<Agent>& getAgents();

    VirusCharacteristics getVirusCharacteristics();
};

#endif