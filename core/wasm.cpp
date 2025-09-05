#include <emscripten/emscripten.h>

#include "epidemy.hpp"
#include "random_obj.hpp"

static EpidemySimulator* simulator = nullptr;

extern "C" {
    EMSCRIPTEN_KEEPALIVE void create_simulator(double width, double height, double p_contamination, double radius_contamination, double p_heal, double p_death, double p_immune) {
        RandomObj::initializeRandom(-0.05, 0.0, 0.0, width, height);
        
        simulator = new EpidemySimulator(width, height, VirusCharacteristics(p_contamination, radius_contamination, p_heal, p_death, p_immune));
    }

    EMSCRIPTEN_KEEPALIVE void add_random_agents(int numberOfAgents, double maxSpeedPerSeconds, int numberOfInfected, int numberOfImmune) {
        simulator->addRandomAgents(numberOfAgents, maxSpeedPerSeconds, numberOfInfected, numberOfImmune);
    }

    EMSCRIPTEN_KEEPALIVE void set_virus_characteristics(
        double P_CONTAMINATION, 
        double CONTAMINATION_RADIUS,
        double P_HEAL,
        double P_DEATH,
        double P_IMMUNE) {
        
        simulator->getVirusCharacteristics().set_p_contamination(P_CONTAMINATION);
        simulator->getVirusCharacteristics().set_radius_contamination(CONTAMINATION_RADIUS);
        simulator->getVirusCharacteristics().set_p_heal(P_HEAL);
        simulator->getVirusCharacteristics().set_p_death(P_DEATH);
        simulator->getVirusCharacteristics().set_p_immune(P_IMMUNE);
    }

    EMSCRIPTEN_KEEPALIVE Agent* get_agents_raw() {
        return simulator->getAgents().data();
    }

    EMSCRIPTEN_KEEPALIVE int getNumberOfAgents() {
        return simulator->getNumberOfAgents();
    }

    EMSCRIPTEN_KEEPALIVE EpidemyStatistics* getStatsPtr() {
        return simulator->getEpidemyStatisticsPtr();
    }

    EMSCRIPTEN_KEEPALIVE double getAgentX(int index) {
        return simulator->getAgent(index).getPositionX();
    }

    EMSCRIPTEN_KEEPALIVE double getAgentY(int index) {
        return simulator->getAgent(index).getPositionY();
    }

    EMSCRIPTEN_KEEPALIVE double getAgentSpeedX(int index) {
        return simulator->getAgent(index).getSpeedX();
    }

    EMSCRIPTEN_KEEPALIVE double getAgentSpeedY(int index) {
        return simulator->getAgent(index).getSpeedY();
    }

    EMSCRIPTEN_KEEPALIVE int getAgentState(int index) {
        return (int)simulator->getAgent(index).getState();
    }

    EMSCRIPTEN_KEEPALIVE void step(double timeInSeconds) {
        return simulator->step(timeInSeconds);
    }
}