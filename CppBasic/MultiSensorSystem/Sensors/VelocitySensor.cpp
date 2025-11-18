#include "../Sensors/VelocitySensor.h"

#include "Utils.h"

VelocitySensor::VelocitySensor(const Point3D& dir, const Point3D& startPos, 
                               float minSpeed, float maxSpeed, const std::string& name, const std::shared_ptr<Threshold> &threshold, Storage* storage)
    : Sensor(velocity, name, minSpeed, maxSpeed, threshold, storage),
      direction(dir.normalized()),
      startPosition(startPos),
      currentSpeed(0.0),
      currentPosition(0, 0, 0),
      creationTime(std::chrono::steady_clock::now()),
      lastUpdate(creationTime){
    currentSpeed = Utils::generateRandom(minSpeed, maxSpeed);
}

double VelocitySensor::read() const {
    updateDistance();
    return (currentPosition - startPosition).length();;
}

Point3D VelocitySensor::getMoreData() const {
    return currentPosition;
}

void VelocitySensor::updateDistance() const {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate);
    double deltaTime = elapsed.count() / 1000.0;
    
    if (deltaTime > 0) {
        Point3D deltaDistance = direction * (currentSpeed * deltaTime);
        currentPosition = currentPosition + deltaDistance;
        lastUpdate = now;
    }
}