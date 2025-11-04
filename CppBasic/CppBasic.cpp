#include "UserInterface.h"
#include "Storage.h"
#include <vector>
#include <memory>

void InitiateSensors(std::vector<std::shared_ptr<Sensor>>* sensors) {
    for (int i = 0; i < 4; i++) {
        if (i < 2) {
            auto newSensor = std::make_shared<Sensor>(celsius, "Thermostat" + std::to_string(i), -25.f, 60.f);
            sensors->push_back(newSensor);
        }
        else {
            auto newSensor = std::make_shared<Sensor>(humidity, "MoistSensor" + std::to_string(i-2), 0.1f, 0.95f);
            sensors->push_back(newSensor);
        }
    }
}

int main() {

    std::vector<Measurement> data;
    std::vector<std::shared_ptr<Sensor>> sensors;
    Storage storage = Storage(&data, &sensors);
    InitiateSensors(&sensors);
    const UserInterface ui(&storage);
    ui.run();
    return 0;
}

