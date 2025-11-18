#pragma once
#include <string>
#include <utility>
#include "Sensor.h"

class Threshold {

public:
    Threshold(SensorType type, std::string name, double threshold, bool is_below)
        : type(type), sensorName(std::move(name)),
          threshold(threshold),
          isBelow(is_below), savedValue(0) {
    }

    void ToggleAlarm(bool isOn);
    [[nodiscard]] std::string getSensorName() const{ return sensorName;};
    [[nodiscard]] bool IsAlarmActive() const { return isActive;};
    [[nodiscard]] bool isThresholdTriggered(double value);
    [[nodiscard]] double getThreshold() const { return threshold;};
    [[nodiscard]] double getLastValue() const { return savedValue;};
    [[nodiscard]] bool isBelowThreshold() const { return isBelow;};
    [[nodiscard]] SensorType getType() const { return type;};

private:
    SensorType type;
    std::string sensorName;
    double threshold;
    double savedValue;
    bool isBelow;
    bool isActive = false;
};
