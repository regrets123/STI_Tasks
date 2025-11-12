#pragma once

#include <memory>
#include <vector>
#include <string>
#include "Measurement.h"

class Storage {
public:
    Storage(std::vector<Measurement> *data, std::vector<std::shared_ptr<Sensor>> *sensors)
        : measurementData(data),
          sensors(sensors) {
    }
    static Statistics calculateStatistics (const std::vector<Measurement>* dataToProcess);

    std::vector<Measurement> addMeasurements();
    std::vector<Measurement> GetMeasuermentByType(SensorType type);
    void analyseData() const;
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;

    [[nodiscard]] const std::vector<Measurement>& getAllMeasurements() const;
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] size_t measurementSize() const;
    [[nodiscard]] size_t numberOfSensors() const;

private:
    std::vector<Measurement>* measurementData;
    std::vector<std::shared_ptr<Sensor>>* sensors;
};
