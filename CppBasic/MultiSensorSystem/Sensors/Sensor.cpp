#include "Sensors/Sensor.h"
#include <random>

Sensor::Sensor(SensorType type, const std::string& name, float minRange, float maxRange)
    : type(type), name(name), minRange(minRange), maxRange(maxRange)
{
}

SensorType Sensor::getType() const {
    return type;
}

Point3D Sensor::getMoreData() const {
    return {0,0,0};
}

double Sensor::generateRandom() const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(minRange, maxRange);
    return dis(gen);
}
