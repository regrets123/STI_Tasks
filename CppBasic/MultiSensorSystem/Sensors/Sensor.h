#pragma once

#include <string>

enum SensorType { none, celsius, humidity, velocity, maxNum};

class Sensor {
public:
     virtual ~Sensor() = default;

     Sensor(SensorType type, const std::string& name, float minRange, float maxRange);
     [[nodiscard]] virtual float read() const; //compiler yells if the return variable isn't used.
     [[nodiscard]] virtual std::string getName() { return name;}
     [[nodiscard]] virtual SensorType getType() const;
private:
     std::string name;
     SensorType type = none;
     float minRange = -1000;
     float maxRange = 1000;
};
