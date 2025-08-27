#include "common.hpp"
#include "random_obj.hpp"

namespace RandomObj {
    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_real_distribution<double> rnAngleDeviation; // (-0.05 * MATH_PI, 0.05 * MATH_PI);
    std::uniform_real_distribution<double> rnd;

    std::uniform_real_distribution<double> rnAngle; // (-MATH_PI, MATH_PI);
    std::uniform_real_distribution<double> rnSpeed; // (maxSpeedPerSeconds * 0.75, maxSpeedPerSeconds);

    std::uniform_real_distribution<double> rnPositionX; //(0.0, this->boxSize_width);
    std::uniform_real_distribution<double> rnPositionY; //(0.0, this->boxSize_height);
    
    void initializeRandom() {
        // default
        initializeRandom(-0.05, 1.0, 1.0, 500.0, 500.0);
    }

    void initializeRandom(double deviation, double minSpeedPerSeconds, double maxSpeedPerSeconds, double boxSize_width, double boxSize_height) {
        rnd = std::uniform_real_distribution<double>(0.0, 1.0);
        rnAngle = std::uniform_real_distribution<double>(-MATH_PI, MATH_PI);

        rnAngleDeviation = std::uniform_real_distribution<double>(-deviation * MATH_PI, +deviation * MATH_PI);
        rnSpeed = std::uniform_real_distribution<double>(minSpeedPerSeconds, maxSpeedPerSeconds);
        rnPositionX = std::uniform_real_distribution<double>(0.0, boxSize_width);
        rnPositionY = std::uniform_real_distribution<double>(0.0, boxSize_height);
    }

    double getRandomAngleDeviation() { return rnAngleDeviation(RandomObj::mt); }
    double random() { return rnd(RandomObj::mt); }

    double getRandomAngle() { return rnAngle(RandomObj::mt); }
    double getRandomSpeed() { return rnSpeed(RandomObj::mt); }

    double getRandomPositionX() { return rnPositionX(RandomObj::mt); }
    double getRandomPositionY() { return rnPositionY(RandomObj::mt); }
};
