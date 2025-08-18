#include <emscripten/emscripten.h>

#include "epidemy.hpp"
#include "vector2d.hpp"

static EpidemySimulator* simulator = nullptr;

extern "C" {
    EMSCRIPTEN_KEEPALIVE void create_simulator(double width, double height) {
        simulator = new EpidemySimulator(Vector2d(width, height));
    }

    EMSCRIPTEN_KEEPALIVE void add_random_agents(int numberOfAgents, double maxSpeedPerSeconds) {
        simulator->addRandomAgents(numberOfAgents, maxSpeedPerSeconds);
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
}