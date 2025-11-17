#pragma once

#include "Sensor.h"

class TemperatureSensor final : public Sensor {
public:
    TemperatureSensor(const std::string &name, float minRange, float maxRange, Threshold threshold)
        : Sensor(celsius, name, minRange, maxRange,threshold) {
    }
    [[nodiscard]] double read() const override;
private:
    Point3D lastPosition;
};
