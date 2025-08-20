#include "common.hpp"
#include "virus_characteristics.hpp"

VirusCharacteristics::VirusCharacteristics() {
    this->p_contamination = 0.0;
    this->radius_contamination = 0.0;
}

VirusCharacteristics::VirusCharacteristics(double p_contamination, double radius_contamination) {
    this->p_contamination = p_contamination;
    this->radius_contamination = radius_contamination;
}

double VirusCharacteristics::get_p_contamination() {
    return this->p_contamination;
}

double VirusCharacteristics::get_radius_contamination() {
    return this->radius_contamination;
}