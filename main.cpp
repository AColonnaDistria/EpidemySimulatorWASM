#include "common.hpp"
#include "epidemy.hpp"

int main(int argc, char** argv) {
    EpidemySimulator epidemySimulator(Vector2d(100.0, 100.0));

    epidemySimulator.addRandomAgents(100, 5.0);
}