#include "../Sensors/TemperatureSensor.h"
#include <chrono>
#include "Storage.h"
#include "Threshold.h"
#include "Utils.h"

double TemperatureSensor::read() const {
    double currentValue = Utils::generateRandom(minRange, maxRange);
    if (alarm->isThresholdTriggered(currentValue)) {
        auto now = std::chrono::system_clock::now();
        time_t timestamp = std::chrono::system_clock::to_time_t(now);
        storage->addTriggeredAlarm(std::make_pair(timestamp, alarm));
    }
    return currentValue;
}
