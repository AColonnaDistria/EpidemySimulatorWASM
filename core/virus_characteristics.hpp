#ifndef VIRUS_CHARACTERISTICS_HPP
#define VIRUS_CHARACTERISTICS_HPP

class VirusCharacteristics {
    double p_contamination;
    double radius_contamination;
public:
    VirusCharacteristics();
    VirusCharacteristics(double p_contamination, double radius_contamination);

    double get_p_contamination();
    double get_radius_contamination();
};

#endif