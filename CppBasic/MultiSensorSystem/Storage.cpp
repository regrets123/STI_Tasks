#include "Storage.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <iostream>
#include <cmath>
#include <map>

#include "Utils.h"

void Storage::addMeasurement(const Measurement& m) {
    data.push_back(m);
}

void Storage::analyseData() {
    std::cout << "\n========================================\n";
    std::cout << "       STATISTICAL ANALYSIS\n";
    std::cout << "========================================\n";

    if (data.empty()) {
        std::cout << "No data available for analysis!\n";
        return;
    }

    // Group measurements by sensor type
    std::map<SensorType, std::vector<float>> groupedData;

    for (const auto& measurement : data) {
        if (measurement.type != SensorType::none) {
            groupedData[measurement.type].push_back(measurement.value);
        }
    }

    // Analyze each sensor type
    for (const auto& [sensorType, values] : groupedData) {
        std::cout << "\n" << Utils::sensorTypeToString(sensorType) << " ("
                  << Utils::getUnitString(sensorType) << ")\n";
        std::cout << std::string(40, '-') << "\n";

        size_t count = values.size();
        float mean = Utils::calculateMean(values);
        float stdDev = Utils::calculateStdDev(values, mean);
        float minVal = Utils::findMin(values);
        float maxVal = Utils::findMax(values);

        // Print results with nice formatting
        std::cout << std::left << std::setw(25) << "Number of measurements:"
                  << count << "\n";

        std::cout << std::left << std::setw(25) << "Mean:"
                  << std::fixed << std::setprecision(2) << mean
                  << " " << Utils::getUnitString(sensorType) << "\n";

        std::cout << std::left << std::setw(25) << "Standard deviation:"
                  << std::fixed << std::setprecision(2) << stdDev
                  << " " << Utils::getUnitString(sensorType) << "\n";

        std::cout << std::left << std::setw(25) << "Minimum value:"
                  << std::fixed << std::setprecision(2) << minVal
                  << " " << Utils::getUnitString(sensorType) << "\n";

        std::cout << std::left << std::setw(25) << "Maximum value:"
                  << std::fixed << std::setprecision(2) << maxVal
                  << " " << Utils::getUnitString(sensorType) << "\n";
    }

    std::cout << "\n========================================\n";
    std::cout << "Total measurements: " << data.size() << "\n";
    std::cout << "========================================\n";
}

void Storage::printAll() {
    std::cout << "\n========================================\n";
    std::cout << "       ALL MEASUREMENTS\n";
    std::cout << "========================================\n";

    if (data.empty()) {
        std::cout << "No measurements available!\n";
        return;
    }

    std::cout << std::left
              << std::setw(20) << "Date/Time"
              << std::setw(18) << "Sensor"
              << std::setw(12) << "Value"
              << std::setw(8) << "Unit" << "\n";
    std::cout << std::string(58, '-') << "\n";

    for (const auto& m : data) {
        char timeBuffer[20];
        struct tm* timeInfo = localtime(&m.time);
        strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M", timeInfo);

        std::cout << std::left
                  << std::setw(20) << timeBuffer
                  << std::setw(18) << m.name
                  << std::setw(12) << std::fixed << std::setprecision(1) << m.value
                  << std::setw(8) << Utils::getUnitString(m.type) << "\n";
    }

    std::cout << "\nTotal: " << data.size() << " measurements\n";
    std::cout << "========================================\n";
}

bool Storage::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    for (const auto& m : data) {
        char timeBuffer[20];
        struct tm* timeInfo = localtime(&m.time);
        strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M", timeInfo);

        file << timeBuffer << ", "
             << m.name << ", "
             << std::fixed << std::setprecision(1) << m.value << ", "
             << Utils::getUnitString(m.type) << "\n";
    }

    file.close();
    return true;
}

bool Storage::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    int loadedCount = 0;
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string dateStr, sensorName, valueStr, unit;

        // Parse: 2025-10-28 09:15, Temperature, 22.5, °C
        if (std::getline(ss, dateStr, ',') &&
            std::getline(ss, sensorName, ',') &&
            std::getline(ss, valueStr, ',') &&
            std::getline(ss, unit, ',')) {

            // Trim whitespace
            sensorName.erase(0, sensorName.find_first_not_of(" \t"));
            sensorName.erase(sensorName.find_last_not_of(" \t") + 1);
            valueStr.erase(0, valueStr.find_first_not_of(" \t"));
            valueStr.erase(valueStr.find_last_not_of(" \t") + 1);

            try {
                float value = std::stof(valueStr);

                // Determine sensor type from name
                SensorType type = SensorType::none;
                if (sensorName == "Temperature") {
                    type = SensorType::celsius;
                } else if (sensorName == "Humidity") {
                    type = SensorType::humidity;
                }

                if (type != SensorType::none) {
                    Measurement m;
                    m.type = type;
                    m.value = value;
                    m.name = sensorName;
                    m.time = time(nullptr);

                    data.push_back(m);
                    loadedCount++;
                }
            } catch (...) {
                // Skip invalid lines
            }
        }
    }

    file.close();
    return loadedCount > 0;
}

const std::vector<Measurement>& Storage::getAllMeasurements() const {
    return data;
}

bool Storage::isEmpty() const {
    return data.empty();
}

size_t Storage::size() const {
    return data.size();
}