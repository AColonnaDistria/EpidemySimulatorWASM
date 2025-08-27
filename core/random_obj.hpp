#ifndef RANDOM_SIM_HPP
#define RANDOM_SIM_HPP

#include "common.hpp"
#include <random>

namespace RandomObj {
    void initializeRandom();
    void initializeRandom(double deviation, double minSpeedPerSeconds, double maxSpeedPerSeconds, double boxSize_width, double boxSize_height);
    
    double getRandomAngleDeviation();
    double random();

    double getRandomAngle();
    double getRandomSpeed();
    double getRandomPositionX();
    double getRandomPositionY();
}
#endif