#include "grid.hpp"
#include <algorithm>

Grid::Grid() {}

Grid::Grid(double contaminationRadius, double boxSize_width, double boxSize_height) {
    this->boxSize_width = boxSize_width;
    this->boxSize_height = boxSize_height;

    this->contaminationRadius = contaminationRadius;
    this->caseSize_wh = contaminationRadius / SQRT_2;

    this->grid_width = this->boxSize_width / caseSize_wh;
    this->grid_height = this->boxSize_height / caseSize_wh;

    this->grid_cells = std::vector<std::vector<int>>();
    this->grid_cells.clear();
    for (int i = 0; i < grid_width * grid_height; ++i)
        this->grid_cells.push_back(std::vector<int>());
}

int Grid::getGridCaseIndex(double x, double y) {
    int i = std::min(this->grid_width  - 1, std::max(0, int(x / this->caseSize_wh)));
    int j = std::min(this->grid_height - 1, std::max(0, int(y / this->caseSize_wh)));

    return this->getGridCaseIndexFromIJ(i, j);
}

int Grid::getGridCaseIndexFromIJ(int i, int j) {
    return j * this->grid_width + i;
}

void Grid::storeAgent(int agentIndex, std::vector<Agent>& agents) {
    Agent& agent = agents[agentIndex];

    int grid_index = this->getGridCaseIndex(agent.getPositionX(), agent.getPositionY());
    printf("%d", grid_index);

    this->grid_cells[grid_index].push_back(agentIndex);
}

void Grid::updateAgent(int agentIndex, std::vector<Agent>& agents, int previousGridIndex) {
    Agent& agent = agents[agentIndex];

    int grid_index = this->getGridCaseIndex(agent.getPositionX(), agent.getPositionY());
    
    if (grid_index != previousGridIndex) {
        auto& oldCell = this->grid_cells[previousGridIndex];
        auto& newCell = this->grid_cells[grid_index];

        auto position = std::find(oldCell.begin(), oldCell.end(), agentIndex);
        if (position != oldCell.end()) // if found
            oldCell.erase(position);

        newCell.push_back(agentIndex);
    }
}

int Grid::getGridWidth() {
    return this->grid_width;
}
int Grid::getGridHeight() {
    return this->grid_height;
}

double Grid::getCaseSize() {
    return this->caseSize_wh;
}

std::vector<int>& Grid::getCaseAgentsIndexes(int i, int j){
    return this->grid_cells[this->getGridCaseIndexFromIJ(i, j)];
}