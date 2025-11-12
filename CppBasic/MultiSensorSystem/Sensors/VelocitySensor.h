#pragma once

#include "Sensor.h"


class VelocitySensor final : public Sensor{
public:
    VelocitySensor(SensorType type, const std::string &name, float minRange, float maxRange)
        : Sensor(type, name, minRange, maxRange) {
    }
    float read() const override;
};
