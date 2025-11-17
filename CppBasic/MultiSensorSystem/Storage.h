#pragma once

#include <memory>
#include <vector>
#include <string>
#include "Measurement.h"

class Storage {
public:
    Storage(std::vector<Measurement> *data, std::vector<std::unique_ptr<Sensor>> *sensors)
        : measurementData(data),
          sensors(sensors) {
    }
    static Statistics calculateStatistics (const std::vector<Measurement>* dataToProcess);

    std::vector<Measurement> GetMeasurementByType(SensorType type);
    [[nodiscard]] std::vector<Measurement> addMeasurements() const;

    bool loadFromFile(const std::string& filename);

    std::string trim(const std::string &str);

    [[nodiscard]] bool saveToFile(const std::string& filename) const;

    [[nodiscard]] const std::vector<Measurement>& getAllMeasurements() const;
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] size_t measurementSize() const;
    [[nodiscard]] size_t numberOfSensors() const;

private:
    std::vector<Measurement>* measurementData;
    std::vector<std::unique_ptr<Sensor>>* sensors;
    std::vector<Threshold> activeThresholds;
    std::vector<Threshold> triggeredAlarms;
};
