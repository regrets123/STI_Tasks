#pragma once

#include <atomic>
#include <memory>
#include <vector>
#include <string>
#include <thread>

#include "Measurement.h"
#include "Sensors/HumiditySensor.h"

class Storage {
public:
    Storage(std::vector<Measurement>* data,
        std::vector<std::unique_ptr<Sensor>>* sensors,
        std::vector<std::shared_ptr<Threshold>>* thresholds,
        std::vector<std::pair<time_t,std::shared_ptr<Threshold>>>* triggeredAlarms)
    : measurementData(data),
      sensors(sensors),
      activeThresholds(thresholds),
      triggeredAlarms(triggeredAlarms) {
    }

    ~Storage() {
        stopPeriodicReading();
    }

    void startPeriodicReading(std::chrono::milliseconds interval);
    void stopPeriodicReading();
    static Statistics calculateStatistics (const std::vector<Measurement>* dataToProcess);
    [[nodiscard]] std::vector<Measurement> GetMeasurementByType(SensorType type) const;
    bool loadFromFile(const std::string& filename);
    std::string trim(const std::string &str);

    std::vector<Measurement> addMeasurements() const;
    [[nodiscard]] bool saveToFile(const std::string& filename) const;
    [[nodiscard]] const std::vector<Measurement>& getAllMeasurements() const;
    [[nodiscard]] std::vector<std::shared_ptr<Threshold>> getActiveThresholds() const;
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] size_t measurementSize() const;
    [[nodiscard]] size_t numberOfSensors() const;

    void addTriggeredAlarm(const std::pair<time_t, std::shared_ptr<Threshold>>& pair) const;
    std::vector<std::pair<time_t, std::shared_ptr<Threshold>>> getTriggeredAlarms() const;

private:
    std::atomic<bool> running{false};
    std::thread measurementThread;
    std::vector<Measurement>* measurementData;
    std::vector<std::unique_ptr<Sensor>>* sensors;
    std::vector<std::shared_ptr<Threshold>>* activeThresholds;
    std::vector<std::pair<time_t, std::shared_ptr<Threshold>>>* triggeredAlarms;
};
