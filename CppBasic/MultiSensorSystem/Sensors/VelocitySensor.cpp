#include "../Sensors/VelocitySensor.h"

#include "Storage.h"
#include "Threshold.h"
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
    double currentValue = (currentPosition - startPosition).length();
    if (alarm->isThresholdTriggered(currentValue)) {
        auto now = std::chrono::system_clock::now();
        time_t timestamp = std::chrono::system_clock::to_time_t(now);
        storage->addTriggeredAlarm(std::make_pair(timestamp, alarm));
    }
    return currentValue;
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