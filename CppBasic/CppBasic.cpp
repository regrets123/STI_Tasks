#include "UserInterface.h"
#include "Storage.h"
#include <vector>
#include <memory>
#include "Utils.h"
#include "Sensors/VelocitySensor.h"
#include "Sensors/HumiditySensor.h"
#include "Sensors/TemperatureSensor.h"


void InitiateSensors(std::vector<std::unique_ptr<Sensor>>* sensors,std::vector<std::shared_ptr<Threshold>>* thresholds, Storage* storage) {
    for (int i = 0; i < 12; i++) {
        if (i < 4) {
            auto alarm = std::make_shared<Threshold>(static_cast<float>(Utils::generateRandom(30.f,55.f)),false);
            thresholds->push_back(alarm);
            sensors->emplace_back(std::make_unique<TemperatureSensor>("Thermostat" + std::to_string(i), -25.f, 60.f, alarm.get(), storage));
        }
        else if (i < 8) {
            auto alarm = std::make_shared<Threshold>(static_cast<float>(Utils::generateRandom(10.f, 75.f)), false);
            thresholds->push_back(alarm);
            sensors->emplace_back(std::make_unique<HumiditySensor>("MoistSensor" + std::to_string(i-4), 1.f, 99.f, alarm.get(), storage));
        }
        else {
            auto alarm = std::make_shared<Threshold>(static_cast<float>(Utils::generateRandom(10000.f,50000.f)),true);
            thresholds->push_back(alarm);
            sensors->emplace_back(std::make_unique<VelocitySensor>(Point3D{Utils::generateRandom(1,-1),
                Utils::generateRandom(1,-1),Utils::generateRandom(1,-1)}
                ,Point3D(),0.5f,5.f, "Accelerometer" + std::to_string(i-8), alarm.get(), storage));
        }
    }
}

int main() {

    std::vector<Measurement> data;
    std::vector<std::unique_ptr<Sensor>> sensors;
    std::vector<std::shared_ptr<Threshold>> thresholds;
    std::vector<std::shared_ptr<Threshold>> triggeredAlarms;
    Storage storage(&data, &sensors, &thresholds, &triggeredAlarms);

    InitiateSensors(&sensors,&thresholds,&storage);
    const UserInterface ui(&storage);
    ui.run();
    return 0;
}

