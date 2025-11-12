#pragma once

#include "UserInterface.h"
#include "Storage.h"
#include <vector>
#include <memory>
#include "Sensors/HumiditySensor.h"
#include "Sensors/TemperatureSensor.h"


void InitiateSensors(std::vector<std::unique_ptr<Sensor>>* sensors) {
    for (int i = 0; i < 4; i++) {
        if (i < 2) {
            sensors->emplace_back(std::make_unique<TemperatureSensor>(celsius, "Thermostat" + std::to_string(i), -25.f, 60.f));
        }
        else {
            sensors->emplace_back(std::make_unique<HumiditySensor>(humidity, "MoistSensor" + std::to_string(i-2), 1.f, 99.f));
        }
    }
}

int main() {

    std::vector<Measurement> data;
    std::vector<std::unique_ptr<Sensor>> sensors;
    Storage storage = Storage(&data, &sensors);
    InitiateSensors(&sensors);
    const UserInterface ui(&storage);
    ui.run();
    return 0;
}

