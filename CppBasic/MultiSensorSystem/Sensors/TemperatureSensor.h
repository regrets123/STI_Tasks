#pragma once
#include "Sensor.h"

class TemperatureSensor final : public Sensor {
public:
    TemperatureSensor(const std::string &name, float minRange, float maxRange, const std::shared_ptr<Threshold> &threshold, Storage* storage)
        : Sensor(celsius, name, minRange, maxRange,threshold, storage) {
    }
    [[nodiscard]] double read() const override;
private:
    Point3D lastPosition;
};
