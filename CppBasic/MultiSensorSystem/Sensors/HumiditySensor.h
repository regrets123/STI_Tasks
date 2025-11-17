#pragma once
#include "Sensor.h"

class HumiditySensor : public Sensor {
public:
    HumiditySensor(const std::string &name, float minRange, float maxRange, Threshold threshold)
        : Sensor(humidity, name, minRange, maxRange, threshold) {
    }
    [[nodiscard]] double read() const override;
};
