#include <random>
#include <cmath>

#include "epidemy.hpp"
#include "agent.hpp"
#include "vector2d.hpp"

#include "common.hpp"

EpidemySimulator::EpidemySimulator(Vector2d boxSize) {
    this->boxSize = boxSize;
}

void EpidemySimulator::addRandomAgents(int numberOfAgents, double maxSpeedPerSeconds) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> rnAngle(-MATH_PI, MATH_PI);
    std::uniform_real_distribution<double> rnSpeed(0.0, maxSpeedPerSeconds);

    std::uniform_real_distribution<double> rnPositionX(0.0, boxSize.getX());
    std::uniform_real_distribution<double> rnPositionY(0.0, boxSize.getY());
    
    for (int i = 0; i < numberOfAgents; ++i) {
        double angle = rnAngle(mt);
        double speed = rnSpeed(mt);

        double x = rnPositionX(mt);
        double y = rnPositionY(mt);

        Vector2d position(x, y);
        Vector2d speedVectorPerSeconds(cos(angle) * speed, sin(angle) * speed);

        this->agents.push_back(Agent(position, speedVectorPerSeconds));
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
    for (auto& agent: agents) {
        agent.step(timeInSeconds);
    }
}