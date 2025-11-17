#pragma once

#include <string>
#include "Point3D.h"

enum SensorType { none, celsius, humidity, velocity, maxNum};

class Sensor {
public:
     virtual ~Sensor() = default;

     Sensor(SensorType type, const std::string& name, float minRange, float maxRange);
     [[nodiscard]] virtual double read() const = 0;
     [[nodiscard]] virtual std::string getName() { return name;}
     [[nodiscard]] virtual SensorType getType() const;
     [[nodiscard]] virtual Point3D getMoreData() const;
protected:
     std::string name;
     SensorType type = none;
     float minRange = -1000;
     float maxRange = 1000;
};
