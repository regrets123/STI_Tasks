#pragma once

#include "Sensor.h"

class TemperatureSensor final : public Sensor {
public:
    TemperatureSensor(const std::string &name, float minRange, float maxRange)
        : Sensor(celsius, name, minRange, maxRange) {
    }
    double read() const override;
private:
    Point3D lastPosition;
};
