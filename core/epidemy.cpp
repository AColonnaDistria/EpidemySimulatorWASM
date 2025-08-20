#include <random>

#include "epidemy.hpp"
#include "agent.hpp"
#include "vector2d.hpp"
#include "virus_characteristics.hpp"

#include "common.hpp"

#define P_CONTAMINATION 0.1
#define CONTAMINATION_RADIUS 10.0
#define TIME_CONTAMINATION_TRIGGER 0.1

EpidemySimulator::EpidemySimulator(Vector2d boxSize) {
    this->timeTriggerContaminationStep = 0.0;
    this->boxSize = boxSize;

    this->virusCharacteristics = VirusCharacteristics(P_CONTAMINATION);
}

void EpidemySimulator::addRandomAgents(int numberOfAgents, double maxSpeedPerSeconds, int numberOfInfectedAgents, int numberOfImmuneAgents) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> rnAngle(-MATH_PI, MATH_PI);
    std::uniform_real_distribution<double> rnSpeed(maxSpeedPerSeconds * 0.75, maxSpeedPerSeconds);

    std::uniform_real_distribution<double> rnPositionX(0.0, boxSize.getX());
    std::uniform_real_distribution<double> rnPositionY(0.0, boxSize.getY());
    
    for (int i = 0; i < numberOfAgents; ++i) {
        double angle = rnAngle(mt);
        double speed = rnSpeed(mt);

        double x = rnPositionX(mt);
        double y = rnPositionY(mt);

        Vector2d position(x, y);
        Vector2d speedVectorPerSeconds(cos(angle) * speed, sin(angle) * speed);

        AgentState state = AgentState::AGENT_HEALTHY;

        if (i <= numberOfInfectedAgents)
            state = AgentState::AGENT_INFECTED;
        else if (i <= numberOfInfectedAgents + numberOfImmuneAgents)
            state = AgentState::AGENT_IMMUNE;

        this->agents.push_back(Agent(position, speedVectorPerSeconds, state));
    }
}

Agent EpidemySimulator::getAgent(int index) {
    #ifdef CHECK_BOUNDS
        if (index < 0 && index >= this->agents.size()) {
            std::cerr << "Agent index out of bounds: index=" << index << std::endl;
            exit(EXIT_FAILURE);
        }
    #endif

    return this->agents[index];
}

int EpidemySimulator::getNumberOfAgents() {
    return this->agents.size();
}

void EpidemySimulator::step(double timeInSeconds) {
    this->timeTriggerContaminationStep += timeInSeconds;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> rnd(0.0, 1.0);

    if (this->timeTriggerContaminationStep >= TIME_CONTAMINATION_TRIGGER) {
        int n = (int) (this->timeTriggerContaminationStep / TIME_CONTAMINATION_TRIGGER);
        this->timeTriggerContaminationStep -= n * TIME_CONTAMINATION_TRIGGER;

        for (int k = 0; k < n; ++k) {
            // compute infections: naive implementation
            for (int i = 0; i < agents.size(); ++i) {
                for (int j = 0; j < agents.size(); ++j) {
                    // A -> B
                    if (i != j) {
                        // if A is infected and B is healthy then there is a p_contamination probability that a contamination happens
                        if (agents[i].getState() == AgentState::AGENT_INFECTED 
                        && agents[j].getState() == AgentState::AGENT_HEALTHY 
                        && (Vector2d::distance(agents[i].getPosition(), agents[j].getPosition()) <= CONTAMINATION_RADIUS)
                        && rnd(mt) <= this->virusCharacteristics.get_p_contamination()) {
                            agents[j].infected();
                        }
                    }
                }
            }
        }
    }
    // advance and apply infections
    for (auto& agent: agents) {
        agent.step(timeInSeconds, this->boxSize);
    }
}