#pragma once

#include <ctime>
#include <string>
#include <Sensors/Sensor.h>


struct Statistics {
    int size;
    float average;
    float minValue;
    float maxValue;
    float stdDev;

    Statistics(int size, float average, float minValue,
              float maxValue, float stdDev)
       : size(size), average(average), minValue(minValue),
         maxValue(maxValue), stdDev(stdDev) {}
};

struct Measurement {
    SensorType type{};
    float value;
    std::string name;
    time_t  time;
    Measurement(SensorType type, float value, const std::string& name, time_t time)
           : type(type), value(value), name(name), time(time) {}
};

