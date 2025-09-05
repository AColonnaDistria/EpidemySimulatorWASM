#include "common.hpp"
#include "epidemy_statistics.hpp"
#include "agent.hpp"

EpidemyStatistics::EpidemyStatistics() {
    this->clear();
}

EpidemyStatistics::EpidemyStatistics(int healthy, int infected, int immune, int dead) {
    this->setHealthyNumberOfAgents(healthy);
    this->setInfectedNumberOfAgents(infected);
    this->setImmuneNumberOfAgents(immune);
    this->setDeadNumberOfAgents(dead);
}

void EpidemyStatistics::setHealthyNumberOfAgents(int healthy_numberOfAgents) {
    this->healthy_numberOfAgents = healthy_numberOfAgents;
}
void EpidemyStatistics::setInfectedNumberOfAgents(int infected_numberOfAgents) {
    this->infected_numberOfAgents = infected_numberOfAgents;
}
void EpidemyStatistics::setImmuneNumberOfAgents(int immune_numberOfAgents) {
    this->immune_numberOfAgents = immune_numberOfAgents;
}
void EpidemyStatistics::setDeadNumberOfAgents(int dead_numberOfAgents) {
    this->dead_numberOfAgents = dead_numberOfAgents;
}

void EpidemyStatistics::addHealthyNumberOfAgents(int delta_healthy_numberOfAgents) {
    this->healthy_numberOfAgents += delta_healthy_numberOfAgents;
}
void EpidemyStatistics::addInfectedNumberOfAgents(int delta_infected_numberOfAgents) {
    this->infected_numberOfAgents += delta_infected_numberOfAgents;
}
void EpidemyStatistics::addImmuneNumberOfAgents(int delta_immune_numberOfAgents) {
    this->immune_numberOfAgents += delta_immune_numberOfAgents;
}
void EpidemyStatistics::addDeadNumberOfAgents(int delta_dead_numberOfAgents) {
    this->dead_numberOfAgents += delta_dead_numberOfAgents;
}

int EpidemyStatistics::getHealthyNumberOfAgents() {
    return this->healthy_numberOfAgents;
}

int EpidemyStatistics::getInfectedNumberOfAgents() {
    return this->infected_numberOfAgents;
}

int EpidemyStatistics::getImmuneNumberOfAgents() {
    return this->immune_numberOfAgents;
}

int EpidemyStatistics::getDeadNumberOfAgents() {
    return this->dead_numberOfAgents;
}

void EpidemyStatistics::clear() {
    this->setHealthyNumberOfAgents(0);
    this->setInfectedNumberOfAgents(0);
    this->setImmuneNumberOfAgents(0);
    this->setDeadNumberOfAgents(0);
}

void EpidemyStatistics::count(Agent& agent) {
    switch (agent.getState()) {
        case AgentState::AGENT_HEALTHY:
            this->addHealthyNumberOfAgents(+1);
            break;
        case AgentState::AGENT_INFECTED:
            this->addInfectedNumberOfAgents(+1);
            break;
        case AgentState::AGENT_IMMUNE:
            this->addImmuneNumberOfAgents(+1);
            break;
        case AgentState::AGENT_DEAD:
            this->addDeadNumberOfAgents(+1);
            break;
    }
}