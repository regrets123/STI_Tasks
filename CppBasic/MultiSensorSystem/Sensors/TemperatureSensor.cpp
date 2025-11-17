#include "../Sensors/TemperatureSensor.h"
#include "Utils.h"

double TemperatureSensor::read() const {
    double currentValue =  Utils::generateRandom(minRange, maxRange);
    if (alarm.IsThresholdTriggered(currentValue)) {

    }
    return currentValue;
}
