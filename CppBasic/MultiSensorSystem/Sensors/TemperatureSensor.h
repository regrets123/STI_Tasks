#pragma once

#include "Sensor.h"

class TemperatureSensor final : public Sensor {
public:
    TemperatureSensor(SensorType type, const std::string &name, float minRange, float maxRange)
        : Sensor(type, name, minRange, maxRange) {
    }
    float read() const override;
};
