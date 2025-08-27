#ifndef GRID_HPP
#define GRID_HPP

#include "common.hpp"
#include "agent.hpp"
#include <vector>

class Grid {
    std::vector<std::vector<int>> grid_cells; // stores indices of agents in order to reduce contamination check time, naive is O(n^2)

    double contaminationRadius;
    double caseSize_wh;

    double boxSize_width;
    double boxSize_height;

    int grid_width;
    int grid_height;
public:
    Grid();
    Grid(double contaminationRadius, double boxSize_width, double boxSize_height);

    int getGridCaseIndex(double x, double y);
    int getGridCaseIndexFromIJ(int i, int j);

    void storeAgent(int agentIndex, std::vector<Agent>& agents);

    void updateAgent(int agentIndex, std::vector<Agent>& agents, int previousGridIndex);

    int getGridWidth();
    int getGridHeight();

    double getCaseSize();

    std::vector<int>& getCaseAgentsIndexes(int i, int j);
};

#endif