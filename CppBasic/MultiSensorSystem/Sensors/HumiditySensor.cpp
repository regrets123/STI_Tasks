#include "../Sensors/HumiditySensor.h"
#include "Utils.h"

double HumiditySensor::read() const {
    return Utils::generateRandom(minRange, maxRange);
}
