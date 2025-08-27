#ifndef VIRUS_CHARACTERISTICS_HPP
#define VIRUS_CHARACTERISTICS_HPP

class VirusCharacteristics {
    double p_contamination;
    double radius_contamination;

    double p_heal;
    double p_death;
    double p_immune;
public:
    VirusCharacteristics();
    VirusCharacteristics(double p_contamination, double radius_contamination, double p_heal, double p_death, double p_immune);

    double get_p_contamination();
    double get_p_heal();
    double get_p_death();
    double get_p_immune();

    double get_p_contamination(int n);
    double get_p_heal(int n);
    double get_p_death(int n);
    double get_p_immune(int n);

    double get_radius_contamination();
};

#endif