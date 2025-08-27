#include <random>

#include "epidemy.hpp"
#include "agent.hpp"
#include "virus_characteristics.hpp"

#include "common.hpp"

//#define P_CONTAMINATION 0.25
//#define CONTAMINATION_RADIUS 30.0
#define TIME_CONTAMINATION_TRIGGER 0.1

EpidemySimulator::EpidemySimulator(double boxSize_width, double boxSize_height, VirusCharacteristics virus) {
    this->timeTriggerContaminationStep = 0.0;
    this->boxSize_width = boxSize_width;
    this->boxSize_height = boxSize_height;

    this->virusCharacteristics = virus;
}

void EpidemySimulator::addRandomAgents(int numberOfAgents, double maxSpeedPerSeconds, int numberOfInfectedAgents, int numberOfImmuneAgents) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> rnAngle(-MATH_PI, MATH_PI);
    std::uniform_real_distribution<double> rnSpeed(maxSpeedPerSeconds * 0.75, maxSpeedPerSeconds);

    std::uniform_real_distribution<double> rnPositionX(0.0, this->boxSize_width);
    std::uniform_real_distribution<double> rnPositionY(0.0, this->boxSize_height);
    
    for (int i = 0; i < numberOfAgents; ++i) {
        double angle = rnAngle(mt);
        double speed = rnSpeed(mt);

        double x = rnPositionX(mt);
        double y = rnPositionY(mt);

        double vx = cos(angle) * speed;
        double vy = sin(angle) * speed;

        AgentState state = AgentState::AGENT_HEALTHY;

        if (i <= numberOfInfectedAgents)
            state = AgentState::AGENT_INFECTED;
        else if (i <= numberOfInfectedAgents + numberOfImmuneAgents)
            state = AgentState::AGENT_IMMUNE;

        this->agents.push_back(Agent(x, y, vx, vy, state));
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

std::vector<Agent>& EpidemySimulator::getAgents() {
    return this->agents;
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
                        && (distance(agents[i].getPositionX(), agents[i].getPositionY(), agents[j].getPositionX(), agents[j].getPositionY()) <= this->virusCharacteristics.get_radius_contamination())
                        && rnd(mt) <= this->virusCharacteristics.get_p_contamination()) {
                            agents[j].infected();
                        }
                    }
                }

                if (agents[i].getState() == AgentState::AGENT_INFECTED) {
                    double r = rnd(mt);
                    // heal/immune/death

                    if (r <= this->virusCharacteristics.get_p_heal()) {
                        // heals
                        agents[i].heal(false);
                    }
                    else if (r <= this->virusCharacteristics.get_p_immune() + this->virusCharacteristics.get_p_heal()) {
                        // gets immunized
                        agents[i].heal(true);
                    }
                    else if (r <= this->virusCharacteristics.get_p_death() + this->virusCharacteristics.get_p_immune() + this->virusCharacteristics.get_p_heal()) {
                        // dies
                        agents[i].die();
                    }
                }
            }
        }
    }
    // advance and apply infections
    for (auto& agent: agents) {
        agent.step(timeInSeconds, this->boxSize_width, this->boxSize_height);
    }
}