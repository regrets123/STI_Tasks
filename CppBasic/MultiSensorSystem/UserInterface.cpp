#include "UserInterface.h"
#include "Storage.h"
#include "Measurement.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include "Utils.h"

UserInterface::UserInterface(Storage* storage)
    : storage(storage) {}

void UserInterface::run() const {
    bool running = true;
    
    while (running) {
        displayMenu();

        switch (getMenuChoice()) {
            case 1:
                readNewMeasurements();
                break;
            case 2: {
                std::cout << "\nStatistics per sensor\n";
                std::cout << "Input 1 for Celsius, 2 for Humidity. \n";
                auto type = static_cast<SensorType>(Utils::getValidInput(1,2));
                std::vector<Measurement> measurements = storage->GetMeasurementByType(type);
                Statistics newData = Storage::calculateStatistics(&measurements);
                showStatisticsPerSensor(type, newData);
                break;
            }

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

void UserInterface::readNewMeasurements() const {
    std::cout << "\nReading new measurements\n";
    const std::vector<Measurement> newMeasurements = storage->addMeasurements();
    for (const auto& measurement : newMeasurements) {
        char timeBuffer[20];
        std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M",
                      std::localtime(&measurement.time));

        std::cout << timeBuffer << ", "
                  << Utils::sensorTypeToString(measurement.type) << ", "
                  << measurement.value << ", "
                  << Utils::getUnitString(measurement.type) << "\n";
    }
}

void UserInterface::showStatisticsPerSensor(SensorType type, Statistics stats) {
    std::cout << "\nStatistics per sensor\n";
        std::cout << "\nSensor Type " << type << ":\n";
        std::cout << "  Size: " << static_cast<int>(stats.size) << "\n";
        std::cout << "  Average: " << stats.average << "\n";
        std::cout << "  Min Value: " << stats.minValue << "\n";
        std::cout << "  Max Value: " << stats.maxValue << "\n";
        std::cout << "  Std Dev: " << stats.stdDev << "\n";

}

void UserInterface::showAllMeasurements() const {
    std::cout << "\nAll measurements\n";
    
    if (storage->isEmpty()) {
        std::cout << "No measurements available!\n";
        return;
    }
    const auto& measurements = storage->getAllMeasurements();
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
                  << std::setw(8) << Utils::getUnitString(m.type) << "\n";
    }
    
    std::cout << "\nTotal: " << storage->measurementSize() << " measurements\n";
}

void UserInterface::saveMeasurementsToFile() const {
    std::cout << "\nSave measurements to file\n";
    
    if (storage->measurementSize() < 1 ) {
        std::cout << "No measurements to save!\n";
        return;
    }
    std::string filename;
    std::cout << "Enter filename (e.g. measurements.csv): ";
    std::getline(std::cin, filename);
    if (storage->saveToFile(filename))
        std::cout << "File successfully saved!\n";
    else
        std::cout << "File could not be saved!\n";
}

void UserInterface::loadMeasurementsFromFile() const {
    std::cout << "\nLoad measurements from file\n";
    
    std::string filename;
    std::cout << "Enter filename (e.g. measurements.csv): ";
    std::getline(std::cin, filename);
    if (storage->loadFromFile(filename))
        std::cout << "File successfully loaded!\n";
    else {
        std::cout << "File could not be loaded!\n";
    }
}

