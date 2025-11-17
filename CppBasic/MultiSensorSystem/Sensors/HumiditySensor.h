#pragma once
#include "Sensor.h"

class HumiditySensor : public Sensor {
public:
    HumiditySensor(const std::string &name, float minRange, float maxRange)
        : Sensor(humidity, name, minRange, maxRange) {
    }
    [[nodiscard]] double read() const override;
};
