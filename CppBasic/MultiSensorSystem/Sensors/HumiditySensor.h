#pragma once
#include "Sensor.h"

class HumiditySensor : public Sensor {
public:
    HumiditySensor(SensorType type, const std::string &name, float minRange, float maxRange)
        : Sensor(type, name, minRange, maxRange) {
    }
    [[nodiscard]] double read() const override;
};
