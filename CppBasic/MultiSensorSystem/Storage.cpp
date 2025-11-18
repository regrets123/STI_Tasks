#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <fstream>
#include <cmath>
#include "Utils.h"
#include "Storage.h"

std::vector<Measurement> Storage::addMeasurements() const {
    std::vector<Measurement> measurements;
    for (const auto& sensor: *sensors) {
        Measurement newReading (sensor->getType()
            ,sensor->read()
            ,sensor->getName()
            , std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
        if (sensor->getType() == velocity) {
            newReading.position = sensor->getMoreData();

        }
        measurementData->push_back(newReading);
        measurements.push_back(newReading);
    }
    return measurements;
}

bool Storage::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        return false;
    }
    file << "Time,Type,Value, MoreData,Name\n";
    for (const auto& measurement : *measurementData) {
        char timeBuffer[20];
        std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M",
                      std::localtime(&measurement.time));

        file << timeBuffer << ","
             << Utils::sensorTypeToString(measurement.type) << ","
             << measurement.value << ","
             << measurement.position.toString() << ","
             << measurement.name << "\n";
    }
    file.close();
    return true;
}

bool Storage::loadFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    int loadedCount = 0;
    std::string line;
    if (std::getline(file, line)) {
        if (line != "Time,Type,Value, MoreData,Unit,Name") {
            file.seekg(0); // Reset to beginning
        }
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string dateStr, typeStr, valueStr, MoreData, name;

        if (std::getline(ss, dateStr, ',') &&
            std::getline(ss, typeStr, ',') &&
            std::getline(ss, valueStr, ',') &&
            std::getline(ss, MoreData,',') &&
            std::getline(ss, name, ',')) {
            dateStr = trim(dateStr);
            typeStr = trim(typeStr);
            valueStr = trim(valueStr);
            MoreData = trim(valueStr);
            name = trim(name);

            try {
                float value = std::stof(valueStr);
                std::tm tm = {};
                int year, month, day, hour, minute;

                if (sscanf(dateStr.c_str(), "%d-%d-%d %d:%d",
                           &year, &month, &day, &hour, &minute) == 5) {
                    tm.tm_year = year - 1900;
                    tm.tm_mon = month - 1;
                    tm.tm_mday = day;
                    tm.tm_hour = hour;
                    tm.tm_min = minute;
                    tm.tm_sec = 0;
                    tm.tm_isdst = -1;
                    time_t timestamp = std::mktime(&tm);

                    auto type = static_cast<SensorType>(Utils::stringToSensorType(typeStr));
                    Measurement m = Measurement(type, value, name, timestamp);
                    if (m.type == velocity) {
                        m.position = Point3D::fromString(MoreData);
                    }
                    measurementData->push_back(m);
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

std::string Storage::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

Statistics Storage::calculateStatistics(const std::vector<Measurement> *dataToProcess) {
    if (dataToProcess == nullptr || dataToProcess->empty()) {
        return {0, 0.0f, 0.0f, 0.0f, 0.0f};
    }

    int size = static_cast<int>(dataToProcess->size());
    float sum = 0.0f;
    float minValue = dataToProcess->at(0).value;
    float maxValue = dataToProcess->at(0).value;

    for (const auto& measurement : *dataToProcess) {
        float val = measurement.value;
        sum += val;

        if (val < minValue) {
            minValue = val;
        }
        if (val > maxValue) {
            maxValue = val;
        }
    }
    float average = sum / size;
    float varianceSum = 0.0f;
    for (const auto& measurement : *dataToProcess) {
        float diff = measurement.value - average;
        varianceSum += diff * diff;
    }

    float variance = varianceSum / size;
    float stdDev = std::sqrt(variance);

    return {size, average, minValue, maxValue, stdDev};
}

const std::vector<Measurement>& Storage::getAllMeasurements() const {
    return *measurementData;
}

std::vector<std::shared_ptr<Threshold>> Storage::getActiveThresholds() const {
    return *activeThresholds;
}

std::vector<Measurement> Storage::GetMeasurementByType(SensorType type) const {
    std::vector<Measurement> filteredMeasurements;
    filteredMeasurements.clear();
    for (const auto& measurement : *measurementData) {
       if (measurement.type == type) {
           filteredMeasurements.push_back(measurement);
       }
    }
    return filteredMeasurements;
}

bool Storage::isEmpty() const {
    return measurementData->empty();
}

size_t Storage::measurementSize() const {
    return measurementData->size();
}

size_t Storage::numberOfSensors() const {
    return sensors->size();
}

void Storage::addTriggeredAlarm(const std::pair<time_t, std::shared_ptr<Threshold>>& pair) const {
    if (pair.second == nullptr) return;
    triggeredAlarms->push_back(pair);
}

std::vector<std::pair<time_t, std::shared_ptr<Threshold>>> Storage::getTriggeredAlarms() const {
    return *triggeredAlarms;
}
