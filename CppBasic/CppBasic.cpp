#include "UserInterface.h"
#include "Storage.h"
#include <vector>
#include <memory>
#include "Utils.h"
#include "Sensors/VelocitySensor.h"
#include "Sensors/HumiditySensor.h"
#include "Sensors/TemperatureSensor.h"
#include "Sensors/Sensor.h"
#include "Sensors/Threshold.h"

void InitiateSensors(std::vector<std::unique_ptr<Sensor>>* sensors,std::vector<std::shared_ptr<Threshold>>* thresholds, Storage* storage) {
    for (int i = 0; i < 12; i++) {
        if (i < 4) {
            std::string sensorName = "Thermostat " + std::to_string(i);
            auto alarm = std::make_shared<Threshold>(celsius, sensorName, static_cast<float>(Utils::generateRandom(30.f,55.f)),false);
            alarm->ToggleAlarm(i % 2 == 0);
            if (alarm->IsAlarmActive()) {
                thresholds->push_back(alarm);
            }
            sensors->emplace_back(std::make_unique<TemperatureSensor>(sensorName, -25.f, 60.f, alarm, storage));
        }
        else if (i < 8) {
            std::string sensorName = "MoistSensor " + std::to_string(i-4);
            auto alarm = std::make_shared<Threshold>(humidity, sensorName, static_cast<float>(Utils::generateRandom(10.f, 75.f)), false);
            alarm->ToggleAlarm(i % 2 == 0);
            if (alarm->IsAlarmActive()) {
                thresholds->push_back(alarm);
            }
            sensors->emplace_back(std::make_unique<HumiditySensor>(sensorName, 1.f, 99.f, alarm, storage));
        }
        else {
            std::string sensorName = "Accelerometer " + std::to_string(i-8);
            auto alarm = std::make_shared<Threshold>(velocity ,sensorName, static_cast<float>(Utils::generateRandom(10000.f,50000.f)),true);
            alarm->ToggleAlarm(i % 2 == 0);
            if (alarm->IsAlarmActive()) {
                thresholds->push_back(alarm);
            }
            sensors->emplace_back(std::make_unique<VelocitySensor>(Point3D{Utils::generateRandom(1,-1),
                Utils::generateRandom(1,-1),Utils::generateRandom(1,-1)}
                ,Point3D(),0.5f,5.f, sensorName, alarm, storage));
        }
    }
}

int main() {
    std::vector<Measurement> data;
    std::vector<std::unique_ptr<Sensor>> sensors;
    std::vector<std::shared_ptr<Threshold>> thresholds;
    std::vector<std::pair<time_t,std::shared_ptr<Threshold>>> triggeredAlarms;
    Storage storage(&data, &sensors, &thresholds, &triggeredAlarms);

    InitiateSensors(&sensors,&thresholds,&storage);
    storage.startPeriodicReading(std::chrono::seconds(5));
    const UserInterface ui(&storage);
    ui.run();
    storage.stopPeriodicReading();
    return 0;
}

