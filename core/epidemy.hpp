#ifndef EPIDEMY_HPP
#define EPIDEMY_HPP

#include "common.hpp"
#include "agent.hpp"
#include "grid.hpp"
#include "virus_characteristics.hpp"

#include <vector>
#include <random>

class EpidemySimulator {
    std::vector<Agent> agents;
    Grid grid;

    double boxSize_width;
    double boxSize_height;
    VirusCharacteristics virusCharacteristics;

    double timeTriggerContaminationStep;
private:
    void checkGrid(int agentIndex1, int n, std::mt19937 &mt, std::uniform_real_distribution<double> &rnd);
    void tryInfect(Agent& agent1, Agent& agent2, int n, std::mt19937 &mt, std::uniform_real_distribution<double> &rnd);
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