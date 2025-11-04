//
// Created by hula_ on 2025-11-03.
//

#ifndef STI_TASKS_USERINTERFACE_H
#define STI_TASKS_USERINTERFACE_H
#include "Sensor.h"

struct Statistics;
class Storage;

class UserInterface {
public:
    explicit UserInterface(Storage* storage);
    void run() const;

private:

    static void showStatisticsPerSensor(SensorType type, Statistics stats);
    static void displayMenu();
    static int getMenuChoice();

    void readNewMeasurements() const;
    void showAllMeasurements() const;
    void saveMeasurementsToFile() const;
    void loadMeasurementsFromFile() const;


    Storage* storage;
};


#endif //STI_TASKS_USERINTERFACE_H