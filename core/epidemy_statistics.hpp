#ifndef EPIDEMY_STATISTICS
#define EPIDEMY_STATISTICS

#include "common.hpp"
#include "agent.hpp"

class EpidemyStatistics {
    int healthy_numberOfAgents;
    int infected_numberOfAgents;
    int immune_numberOfAgents;
    int dead_numberOfAgents;

public:
    EpidemyStatistics();
    EpidemyStatistics(int healthy, int infected, int immune, int dead);

    void setHealthyNumberOfAgents(int healthy_numberOfAgents);
    void setInfectedNumberOfAgents(int infected_numberOfAgents);
    void setImmuneNumberOfAgents(int immune_numberOfAgents);
    void setDeadNumberOfAgents(int dead_numberOfAgents);

    int getHealthyNumberOfAgents();
    int getInfectedNumberOfAgents();
    int getImmuneNumberOfAgents();
    int getDeadNumberOfAgents();

    void addHealthyNumberOfAgents(int delta_healthy_numberOfAgents);
    void addInfectedNumberOfAgents(int delta_infected_numberOfAgents);
    void addImmuneNumberOfAgents(int delta_immune_numberOfAgents);
    void addDeadNumberOfAgents(int delta_dead_numberOfAgents);

    void clear();
    void count(Agent& agent);
};

#endif