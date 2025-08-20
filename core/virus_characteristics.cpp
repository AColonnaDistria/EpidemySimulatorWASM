#include "common.hpp"
#include "virus_characteristics.hpp"

VirusCharacteristics::VirusCharacteristics() {
    this->p_contamination = 0.0;
}

VirusCharacteristics::VirusCharacteristics(double p_contamination) {
    this->p_contamination = p_contamination;
}

double VirusCharacteristics::get_p_contamination() {
    return this->p_contamination;
}