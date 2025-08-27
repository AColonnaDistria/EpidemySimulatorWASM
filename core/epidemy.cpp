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

    this->grid = Grid(virus.get_radius_contamination(), boxSize_width, boxSize_height);
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
        int agentIndex = this->agents.size() - 1;
        this->grid.storeAgent(agentIndex, this->agents);
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

void EpidemySimulator::tryInfect(Agent& agent1, Agent& agent2, int n, std::mt19937 &mt, std::uniform_real_distribution<double> &rnd) {
    if (rnd(mt) > this->virusCharacteristics.get_p_contamination(n)) return; // clause 4
    if (agent2.getNextState() != AgentState::AGENT_HEALTHY) return; // clause 2.5
    if (agent2.getState() != AgentState::AGENT_HEALTHY) return; // clause 2
    if (distance(agent1.getPositionX(), agent1.getPositionY(), 
                 agent2.getPositionX(), agent2.getPositionY())
        > this->virusCharacteristics.get_radius_contamination()) return;

    // then agent2 gets infected
    agent2.infected();
}

void EpidemySimulator::checkGrid(int agentIndex1, int n, std::mt19937 &mt, std::uniform_real_distribution<double> &rnd) {
    auto& agent1 = this->agents[agentIndex1];
    
    int gridIndex = this->grid.getGridCaseIndex(agent1.getPositionX(), agent1.getPositionY());
    
    int i = this->grid.getGridCaseI(agent1.getPositionX());
    int j = this->grid.getGridCaseJ(agent1.getPositionY());

    // check neighbors
    for (int gi = -1; gi <= 1; ++gi) {
        for (int gj = -1; gj <= 1; ++gj) {
            // check bounds
            int ni = i+gi;
            int nj = j+gj;

            if (ni < 0 || ni >= this->grid.getGridWidth()
            ||  nj < 0 || nj >= this->grid.getGridHeight()) {
                continue;
            }
        
            for (int agentIndex2: this->grid.getCaseAgentsIndexes(ni, nj)) {
                // doesn't try to autoinfect
                if (agentIndex1 == agentIndex2) {
                    continue;
                }
                auto& agent2 = this->agents[agentIndex2];
                tryInfect(agent1, agent2, n, mt, rnd);
            }
        }
    }
    //resolveHealth(agent1, mt, rnd);
}

void EpidemySimulator::step(double timeInSeconds) {
    this->timeTriggerContaminationStep += timeInSeconds;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> rnd(0.0, 1.0);

    std::vector<int> agentAddToGrid;

    if (this->timeTriggerContaminationStep >= TIME_CONTAMINATION_TRIGGER) {
        int n = (int) (this->timeTriggerContaminationStep / TIME_CONTAMINATION_TRIGGER);
        this->timeTriggerContaminationStep -= n * TIME_CONTAMINATION_TRIGGER;

        // compute infections: grid
        for (int agentIndex1 = 0; agentIndex1 < this->getNumberOfAgents(); ++agentIndex1) {
            auto& agent1 = this->agents[agentIndex1];

            if (agent1.getState() == AgentState::AGENT_INFECTED) {
            // check agents inside the grid
                checkGrid(agentIndex1, n, mt, rnd);
            }

            if (agent1.getState() == AgentState::AGENT_INFECTED) {
                double r = rnd(mt);
                // heal/immune/death

                // compute probabilities according to n

                if (r <= this->virusCharacteristics.get_p_heal(n)) {
                    // heals
                    agent1.heal(false);
                    agentAddToGrid.push_back(agentIndex1);
                }
                else if (r <= this->virusCharacteristics.get_p_immune(n) + this->virusCharacteristics.get_p_heal(n)) {
                    // gets immunized
                    agent1.heal(true);
                }
                else if (r <= this->virusCharacteristics.get_p_death(n) + this->virusCharacteristics.get_p_immune(n) + this->virusCharacteristics.get_p_heal(n)) {
                    // dies
                    agent1.die();
                }
            }
        }
    }
    // advance and apply infections
    for (auto& agent: this->agents) {
        agent.step(timeInSeconds, this->boxSize_width, this->boxSize_height);
    }

    // update grids
    for (int i = 0; i < this->grid.getGridWidth(); ++i) {
        for (int j = 0; j < this->grid.getGridHeight(); ++j) {
            int oldGridIndex = this->grid.getGridCaseIndexFromIJ(i, j);

            for (int agentIndex: this->grid.getCaseAgentsIndexes(i, j)) {
                auto& agent = this->agents[agentIndex];
                this->grid.updateAgent(agentIndex, this->agents, oldGridIndex);
            }
        }
    }

    for (int agentIndex: agentAddToGrid) {
        auto& agent = this->agents[agentIndex];
        int gridIndex = this->grid.getGridCaseIndex(agent.getPositionX(), agent.getPositionY());

        this->grid.updateAgent(agentIndex, this->agents, gridIndex);
    }
}