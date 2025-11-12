#pragma once

#include "Sensor.h"
#include "Measurement.h"

class VelocitySensor final : public Sensor{
public:
    VelocitySensor(SensorType type, const std::string &name, float minRange, float maxRange)
        : Sensor(type, name, minRange, maxRange), velocity() {
    }
    double read() const override;
    Point3D getDirection() const;
private:
    Point3D velocity;
};
