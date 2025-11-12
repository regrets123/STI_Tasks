#pragma once

#include "Sensor.h"

class TemperatureSensor final : public Sensor {
public:
    TemperatureSensor(SensorType type, const std::string &name, float minRange, float maxRange)
        : Sensor(type, name, minRange, maxRange) {
    }
    double read() const override;
};
