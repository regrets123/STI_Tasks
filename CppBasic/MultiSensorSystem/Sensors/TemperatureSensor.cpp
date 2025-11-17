#include "../Sensors/TemperatureSensor.h"
#include "Utils.h"

double TemperatureSensor::read() const {
    return Utils::generateRandom(minRange, maxRange);
}
