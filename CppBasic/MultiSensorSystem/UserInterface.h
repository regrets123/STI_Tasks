#pragma once

#include "Sensors/Sensor.h"

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
    void showActiveAlarms() const;
    void showTriggeredAlarms() const;


    Storage* storage;
};
