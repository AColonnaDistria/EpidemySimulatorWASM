#include <emscripten/emscripten.h>

#include "epidemy.hpp"
#include "vector2d.hpp"

static EpidemySimulator* simulator = nullptr;

extern "C" {
    EMSCRIPTEN_KEEPALIVE void create_simulator(double width, double height, double p_contamination, double radius_contamination, double p_heal, double p_death, double p_immune) {
        simulator = new EpidemySimulator(Vector2d(width, height), VirusCharacteristics(p_contamination, radius_contamination, p_heal, p_death, p_immune));
    }

    EMSCRIPTEN_KEEPALIVE void add_random_agents(int numberOfAgents, double maxSpeedPerSeconds, int numberOfInfected, int numberOfImmune) {
        simulator->addRandomAgents(numberOfAgents, maxSpeedPerSeconds, numberOfInfected, numberOfImmune);
    }

    EMSCRIPTEN_KEEPALIVE int getNumberOfAgents() {
        return simulator->getNumberOfAgents();
    }

    EMSCRIPTEN_KEEPALIVE double getAgentX(int index) {
        return simulator->getAgent(index).getPosition().getX();
    }

    EMSCRIPTEN_KEEPALIVE double getAgentY(int index) {
        return simulator->getAgent(index).getPosition().getY();
    }

    EMSCRIPTEN_KEEPALIVE double getAgentSpeedX(int index) {
        return simulator->getAgent(index).getSpeedPerSeconds().getX();
    }

    EMSCRIPTEN_KEEPALIVE double getAgentSpeedY(int index) {
        return simulator->getAgent(index).getSpeedPerSeconds().getY();
    }

    EMSCRIPTEN_KEEPALIVE int getAgentState(int index) {
        return (int)simulator->getAgent(index).getState();
    }

    EMSCRIPTEN_KEEPALIVE void step(double timeInSeconds) {
        return simulator->step(timeInSeconds);
    }
}