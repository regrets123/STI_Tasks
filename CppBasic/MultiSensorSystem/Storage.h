#ifndef STI_TASKS_STORAGE_H
#define STI_TASKS_STORAGE_H
#include <vector>
#include <string>
#include "Measurement.h"

class Storage {
public:
    void addMeasurement(const Measurement&);
    void analyseData();  // Analyzes data per sensor type
    void printAll();

    // File operations
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

    // Get all measurements (const reference for safety)
    const std::vector<Measurement>& getAllMeasurements() const;

    // Check if storage is empty
    bool isEmpty() const;

    // Get count
    size_t size() const;

private:
    std::vector<Measurement> data;
};

#endif //STI_TASKS_STORAGE_H