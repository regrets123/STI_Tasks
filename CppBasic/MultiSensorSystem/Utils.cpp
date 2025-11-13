#include "Utils.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <sstream>
#include "Sensors/Sensor.h"


int Utils:: getValidInput(int min, int max) {
    std::string input;
    int choice;

    while (true) {
        std::getline(std::cin, input);
        if (input.empty()) {
            std::cout << "No input detected! Please enter a number between "
                      << min << " and " << max << ": ";
            continue;
        }
        try {
            size_t pos;
            choice = std::stoi(input, &pos);
            if (pos != input.length()) {
                std::cout << "Invalid format! Please enter only a number: ";
                continue;
            }
            if (choice < min || choice > max) {
                std::cout << "Input out of range! Please enter a number between "
                          << min << " and " << max << ": ";
                continue;
            }
            return choice;

        } catch (const std::invalid_argument&) {
            std::cout << "Invalid input! Please enter a valid number: ";
        } catch (const std::out_of_range&) {
            std::cout << "Number too large! Please enter a number between "
                      << min << " and " << max << ": ";
        }
    }
}

std::string Utils::sensorTypeToString(int type)  {
    switch (type) {
        case static_cast<int>(celsius): {
            return "Temperature";
        }
        case static_cast<int>(humidity): {
            return "Humidity";
        }
        case static_cast<int>(velocity): {
            return "Velocity";
        }
        default:
            return "Unknown";
    }
}

int Utils::stringToSensorType(const std::string& typeStr) {
    if (typeStr == "Temperature") {
        return celsius;
    }
    if (typeStr == "Humidity") {
        return humidity;
    }
    if (typeStr == "Velocity")
        return velocity;
    return none;
}

std::string Utils::getUnitString(int type) {
    switch (type) {
        case static_cast<int>(celsius): {
            return "Celsius";
        }
        case static_cast<int>(humidity): {
            return "%";
        }
        case static_cast<int>(velocity): {
             return "V";
        }
        default: {
            return "Error";
        }
    }
}

void Utils::clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

float Utils::calculateMean(const std::vector<float>& values) {
    if (values.empty()) return 0.0f;

    float sum = 0.0f;
    for (float value : values) {
        sum += value;
    }
    return sum / values.size();
}

float Utils::calculateStdDev(const std::vector<float>& values, float mean) {
    if (values.size() <= 1) return 0.0f;

    float sumSquaredDiff = 0.0f;
    for (float value : values) {
        float diff = value - mean;
        sumSquaredDiff += diff * diff;
    }

    // Sample standard deviation (n-1)
    return std::sqrt(sumSquaredDiff / (values.size() - 1));
}