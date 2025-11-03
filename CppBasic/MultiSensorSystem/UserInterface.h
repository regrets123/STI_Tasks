//
// Created by hula_ on 2025-11-03.
//

#ifndef STI_TASKS_USERINTERFACE_H
#define STI_TASKS_USERINTERFACE_H


#include <vector>
#include <string>
#include <memory>

// Forward declarations
struct Measurement;
class Sensor;
class Storage;

class UserInterface {
public:
    UserInterface(std::vector<std::shared_ptr<Sensor>>& sensors,
                  Storage& storage);
    void run();

private:
    void readNewMeasurements();
    void showStatisticsPerSensor();
    void showAllMeasurements();
    void saveMeasurementsToFile();
    void loadMeasurementsFromFile();

    void displayMenu();
    int getMenuChoice();
    void clearInputBuffer();
    std::vector<std::shared_ptr<Sensor>>& sensors;
    Storage& storage;
};


#endif //STI_TASKS_USERINTERFACE_H