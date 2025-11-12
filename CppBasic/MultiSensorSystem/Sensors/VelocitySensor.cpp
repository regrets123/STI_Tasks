
#include "../Sensors/VelocitySensor.h"

double VelocitySensor::read() const {
    return velocity.length();
}

Point3D VelocitySensor::getDirection() const {
   return velocity;
}
