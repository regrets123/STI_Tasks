#include <string>

#ifndef STI_TASKS_SENSOR_H
#define STI_TASKS_SENSOR_H

enum SensorType { none, celsius, humidity, maxNum};

class Sensor
{
public:
     Sensor(SensorType type, const std::string& name, float minRange, float maxRange);
     [[nodiscard]] float read() const; //compiler yells if the return variable isn't used.
     [[nodiscard]] std::string getName() { return name;}
     [[nodiscard]] SensorType getType() const;
private:
     std::string name;
     SensorType type = none;
     float minRange = -1000;
     float maxRange = 1000;
};


#endif //STI_TASKS_SENSOR_H