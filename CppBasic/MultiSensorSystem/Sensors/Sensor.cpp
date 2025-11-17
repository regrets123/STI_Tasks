#include <utility>
#include "Sensors/Sensor.h"

Sensor::Sensor(SensorType type, std::string  name, float minRange, float maxRange, Threshold threshold)
    : alarm(threshold), name(std::move(name)), type(type), minRange(minRange), maxRange(maxRange) {

}

SensorType Sensor::getType() const {
    return type;
}

Point3D Sensor::getMoreData() const {
    return {0,0,0};
}

