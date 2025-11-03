#include "UserInterface.h"
#include "Storage.h"
#include "Measurement.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <ctime>

#include "Utils.h"

UserInterface::UserInterface(std::vector<std::shared_ptr<Sensor>>& sensors,
                             Storage& storage)
    : sensors(sensors), storage(storage) {}

void UserInterface::run() {
    bool running = true;
    
    while (running) {
        displayMenu();
        int choice = getMenuChoice();
        
        switch (choice) {
            case 1:
                readNewMeasurements();
                break;
            case 2:
                showStatisticsPerSensor();
                break;
            case 3:
                showAllMeasurements();
                break;
            case 4:
                saveMeasurementsToFile();
                break;
            case 5:
                loadMeasurementsFromFile();
                break;
            case 6:
                std::cout << "\nExiting program...\n";
                running = false;
                break;
            default:
                std::cout << "\nInvalid choice! Please try again.\n";
        }
        
        if (running) {
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
        }
    }
}

void UserInterface::displayMenu() {
    std::cout << "\n========================================\n";
    std::cout << "       SENSOR MANAGEMENT SYSTEM\n";
    std::cout << "========================================\n";
    std::cout << "1. Read new measurements from all sensors\n";
    std::cout << "2. Show statistics per sensor\n";
    std::cout << "3. Show all measurements\n";
    std::cout << "4. Save all measurements to file\n";
    std::cout << "5. Load measurements from file\n";
    std::cout << "6. Exit program\n";
    std::cout << "========================================\n";
    std::cout << "Choose an option (1-6): ";
}

int UserInterface::getMenuChoice() {
    return Utils::getValidInput(1, 6);
}

void UserInterface::readNewMeasurements() {
    std::cout << "\nReading new measurements\n";
    
    if (sensors.empty()) {
        std::cout << "No sensors available!\n";
        return;
    }
    
    time_t currentTime = time(nullptr);
    
    for (const auto& sensor : sensors) {
        float value = sensor->read();
        SensorType type = sensor->getType();
        
        Measurement m;
        m.type = type;
        m.value = value;
        m.name = Utils::sensorTypeToString(type);
        m.time = currentTime;
        
        storage.addMeasurement(m);
        
        std::cout << "  " << m.name << ": " << value << " " 
                  << Utils::getUnitString(type) << "\n";
    }
    
    std::cout << "\nTotal " << sensors.size() << " measurements read.\n";
}

void UserInterface::showStatisticsPerSensor() {
    std::cout << "\nStatistics per sensor\n";
    
    if (storage.isEmpty()) {
        std::cout << "No measurements available!\n";
        return;
    }
    
    const auto& measurements = storage.getAllMeasurements();
    
    // Group measurements by sensor type
    for (int sensorType = 1; sensorType < static_cast<int>(SensorType::maxNum); ++sensorType) {
        std::vector<float> values;
        
        for (const auto& m : measurements) {
            if (static_cast<int>(m.type) == sensorType) {
                values.push_back(m.value);
            }
        }
        
        if (!values.empty()) {
            float sum = 0;
            float minVal = values[0];
            float maxVal = values[0];
            
            for (float val : values) {
                sum += val;
                if (val < minVal) minVal = val;
                if (val > maxVal) maxVal = val;
            }
            
            float average = sum / values.size();
            
            std::cout << "\n" << Utils::sensorTypeToString(sensorType) << ":\n";
            std::cout << "  Number of measurements: " << values.size() << "\n";
            std::cout << "  Average: " << std::fixed << std::setprecision(2) 
                      << average << " " << Utils::getUnitString(sensorType) << "\n";
            std::cout << "  Minimum: " << minVal << " " 
                      << Utils::getUnitString(sensorType) << "\n";
            std::cout << "  Maximum: " << maxVal << " " 
                      << Utils::getUnitString(sensorType) << "\n";
        }
    }
}

void UserInterface::showAllMeasurements() {
    std::cout << "\nAll measurements\n";
    
    if (storage.isEmpty()) {
        std::cout << "No measurements available!\n";
        return;
    }
    
    const auto& measurements = storage.getAllMeasurements();
    
    std::cout << std::left << std::setw(20) << "Date/Time" 
              << std::setw(20) << "Sensor" 
              << std::setw(10) << "Value" 
              << std::setw(8) << "Unit" << "\n";
    std::cout << std::string(58, '-') << "\n";
    
    for (const auto& m : measurements) {
        char timeBuffer[20];
        struct tm* timeInfo = localtime(&m.time);
        strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M", timeInfo);
        
        std::cout << std::left << std::setw(20) << timeBuffer
                  << std::setw(20) << m.name
                  << std::setw(10) << std::fixed << std::setprecision(1) << m.value
                  << std::setw(8) << Utils::getUnitString(static_cast<int>(m.type)) << "\n";
    }
    
    std::cout << "\nTotal: " << storage.size() << " measurements\n";
}

void UserInterface::saveMeasurementsToFile() {
    std::cout << "\nSave measurements to file\n";
    
    if (storage.isEmpty()) {
        std::cout << "No measurements to save!\n";
        return;
    }
    
    std::string filename;
    std::cout << "Enter filename (e.g. measurements.csv): ";
    std::getline(std::cin, filename);
    
    if (filename.empty()) {
        filename = "measurements.csv";
    }
    
    if (storage.saveToFile(filename)) {
        std::cout << "Saved " << storage.size() << " measurements to " << filename << "\n";
    } else {
        std::cout << "Error: Could not save to file!\n";
    }
}

void UserInterface::loadMeasurementsFromFile() {
    std::cout << "\nLoad measurements from file\n";
    
    std::string filename;
    std::cout << "Enter filename (e.g. measurements.csv): ";
    std::getline(std::cin, filename);
    
    size_t beforeCount = storage.size();
    
    if (storage.loadFromFile(filename)) {
        size_t loadedCount = storage.size() - beforeCount;
        std::cout << "Loaded " << loadedCount << " measurements from " << filename << "\n";
    } else {
        std::cout << "Error: Could not load from file!\n";
    }
}


void UserInterface::clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}