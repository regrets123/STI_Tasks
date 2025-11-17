#include "UserInterface.h"
#include "Storage.h"
#include <vector>
#include <memory>
#include "Utils.h"
#include "Sensors/VelocitySensor.h"
#include "Sensors/HumiditySensor.h"
#include "Sensors/TemperatureSensor.h"


void InitiateSensors(std::vector<std::unique_ptr<Sensor>>* sensors) {
    for (int i = 0; i < 12; i++) {
        if (i < 4) {
            Threshold alarm = Threshold(static_cast<float>(Utils::generateRandom(30.f,55.f)),false);
            sensors->emplace_back(std::make_unique<TemperatureSensor>("Thermostat" + std::to_string(i), -25.f, 60.f, alarm));
        }
        else if (i < 8) {
            Threshold alarm = Threshold(static_cast<float>(Utils::generateRandom(10.f,75.f)),false);
            sensors->emplace_back(std::make_unique<HumiditySensor>("MoistSensor" + std::to_string(i-4), 1.f, 99.f, alarm));
        }
        else {
            Threshold alarm = Threshold(static_cast<float>(Utils::generateRandom(10000.f,50000.f)),true);
            sensors->emplace_back(std::make_unique<VelocitySensor>(Point3D{Utils::generateRandom(1,-1),
                Utils::generateRandom(1,-1),Utils::generateRandom(1,-1)}
                ,Point3D(),0.5f,5.f, "Accelerometer" + std::to_string(i-8), alarm));
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

