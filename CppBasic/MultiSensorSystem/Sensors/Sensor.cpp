#include <utility>
#include "Sensors/Sensor.h"
#include "Storage.h"

Sensor::Sensor(SensorType type, std::string  name, float minRange, float maxRange, Threshold* threshold, Storage* storage)
    : alarm(threshold), name(std::move(name)), type(type), minRange(minRange), maxRange(maxRange), storage(storage) {

}

SensorType Sensor::getType() const {
    return type;
}

Point3D Sensor::getMoreData() const {
    return {0,0,0};
}

