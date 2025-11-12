#include "../Sensors/HumiditySensor.h"

double HumiditySensor::read() const {
    return generateRandom();
}
