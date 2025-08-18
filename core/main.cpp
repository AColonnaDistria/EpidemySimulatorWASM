#include "common.hpp"
#include "epidemy.hpp"
#include "vector2d.hpp"

int main(int argc, char** argv) {
    EpidemySimulator epidemySimulator(Vector2d(100.0, 100.0));

    epidemySimulator.addRandomAgents(100, 5.0);

    for (int index = 0; index < epidemySimulator.getNumberOfAgents(); ++index) {
        Vector2d position = epidemySimulator.getAgent(index).getPosition();
        Vector2d speedPerSeconds = epidemySimulator.getAgent(index).getSpeedPerSeconds();

        printf("position:(%f,%f) speed:(%f,%f)\n", position.getX(), position.getY(), speedPerSeconds.getX(), speedPerSeconds.getY());
    }
}