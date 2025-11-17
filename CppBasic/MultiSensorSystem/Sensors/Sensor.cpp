#include "Sensors/Sensor.h"

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

