#ifndef STI_TASKS_STORAGE_H
#define STI_TASKS_STORAGE_H
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

    std::vector<Measurement> addMeasurements();
    void analyseData() const;
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

    static Statistics calculateStatistics (const std::vector<Measurement>* dataToProcess);
    // Get all measurements (const reference for safety)
    const std::vector<Measurement>& getAllMeasurements() const;
    std::vector<Measurement> GetMeasuermentByType(SensorType type);

    // Check if storage is empty
    bool isEmpty() const;

    // Get count
    size_t measurementSize() const;
    size_t numberOfSensors() const;

private:
    std::vector<Measurement>* measurementData;
    std::vector<std::shared_ptr<Sensor>>* sensors;
};

#endif //STI_TASKS_STORAGE_H