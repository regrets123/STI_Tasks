#include "../Sensors/VelocitySensor.h"

VelocitySensor::VelocitySensor(const Point3D& dir, const Point3D& startPos, 
                               float minSpeed, float maxSpeed, const std::string& name)
    : Sensor(velocity, name, minSpeed, maxSpeed),
      direction(dir.normalized()),
      startPosition(startPos),
      currentSpeed(0.0),
      distanceTraveled(0, 0, 0),
      creationTime(std::chrono::steady_clock::now()),
      lastUpdate(creationTime){
    currentSpeed = generateRandom();
}

double VelocitySensor::read() const {
    updateDistance();
    currentSpeed = generateRandom();
    return currentSpeed;
}

Point3D VelocitySensor::getMoreData() const {
    updateDistance();
    return distanceTraveled;
}

void VelocitySensor::updateDistance() const {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate);
    double deltaTime = elapsed.count() / 1000.0;
    
    if (deltaTime > 0) {
        Point3D deltaDistance = direction * (currentSpeed * deltaTime);
        distanceTraveled = distanceTraveled + deltaDistance;
        lastUpdate = now;
    }
}