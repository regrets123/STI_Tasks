//
// Created by hula_ on 2025-10-31.
//

#ifndef STI_TASKS_MEASUREMENTS_H
#define STI_TASKS_MEASUREMENTS_H
#include <string>
#include  "MultiSensorSystem/Sensor.h"


struct Measurement {
    SensorType type;
    float value;
    std::string name;
    time_t  time;

};


#endif //STI_TASKS_MEASUREMENTS_H