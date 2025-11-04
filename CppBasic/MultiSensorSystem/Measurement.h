//
// Created by hula_ on 2025-10-31.
//

#ifndef STI_TASKS_MEASUREMENTS_H
#define STI_TASKS_MEASUREMENTS_H
#include <string>
#include  "MultiSensorSystem/Sensor.h"

struct Statistics {
    uint8_t size;
    float average;
    float minValue;
    float maxValue;
    float stdDev;

    Statistics(uint8_t size, float average, float minValue,
              float maxValue, float stdDev)
       : size(size), average(average), minValue(minValue),
         maxValue(maxValue), stdDev(stdDev) {}
};

struct Measurement {
    SensorType type;
    float value;
    std::string name;
    time_t  time;
    Measurement(SensorType type, float value, const std::string& name, time_t time)
           : type(type), value(value), name(name), time(time) {}
};


#endif //STI_TASKS_MEASUREMENTS_H