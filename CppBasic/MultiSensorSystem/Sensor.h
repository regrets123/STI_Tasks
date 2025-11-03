#include <string>

#ifndef STI_TASKS_SENSOR_H
#define STI_TASKS_SENSOR_H

enum SensorType { none, celsius, humidity, maxNum};

class Sensor
{
public:
     float read();
     SensorType getType();
private:
     std::string name;
     SensorType type = none;
     float minRange = -1000;
     float maxRange = 1000;
};


#endif //STI_TASKS_SENSOR_H