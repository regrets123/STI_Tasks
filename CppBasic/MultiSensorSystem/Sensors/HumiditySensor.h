#pragma once
#include "Sensor.h"

class HumiditySensor : public Sensor {
public:
    HumiditySensor(const std::string &name, float minRange, float maxRange, const std::shared_ptr<Threshold> &threshold, Storage* storage)
        : Sensor(humidity, name, minRange, maxRange, threshold, storage) {
    }
    [[nodiscard]] double read() const override;
};
