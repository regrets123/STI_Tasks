#include "../Sensors/Sensor.h"
#include <random>

Sensor::Sensor(SensorType type, const std::string& name, float minRange, float maxRange)
    : type(type), name(name), minRange(minRange), maxRange(maxRange)
{
}

float Sensor::read() const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution dis(minRange, maxRange);
    return dis(gen);
}

SensorType Sensor::getType() const {
    return type;
}
