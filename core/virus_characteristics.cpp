#include "common.hpp"
#include "virus_characteristics.hpp"

VirusCharacteristics::VirusCharacteristics() {
    this->p_contamination = 0.0;
    this->radius_contamination = 0.0;
}

VirusCharacteristics::VirusCharacteristics(double p_contamination, double radius_contamination, double p_heal, double p_death, double p_immune) {
    this->p_contamination = p_contamination;
    this->radius_contamination = radius_contamination;
    this->p_heal = p_heal;
    this->p_death = p_death;
    this->p_immune = p_immune;
}

double VirusCharacteristics::get_radius_contamination() {
    return this->radius_contamination;
}

double VirusCharacteristics::get_p_contamination() {
    return this->p_contamination;
}

double VirusCharacteristics::get_p_death() {
    return this->p_death;
}

double VirusCharacteristics::get_p_immune() {
    return this->p_immune;
}

double VirusCharacteristics::get_p_heal() {
    return this->p_heal;
}

double VirusCharacteristics::get_p_contamination(int n) {
    return 1.0 - pow(1.0 - this->p_contamination, n);
}

double VirusCharacteristics::get_p_death(int n) {
    return 1.0 - pow(1.0 - this->p_death, n);
}

double VirusCharacteristics::get_p_immune(int n) {
    return 1.0 - pow(1.0 - this->p_immune, n);
}

double VirusCharacteristics::get_p_heal(int n) {
    return 1.0 - pow(1.0 - this->p_heal, n);
}
