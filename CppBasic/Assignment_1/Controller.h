#pragma once
#include <iostream>
#include <array>
#include "DataAnalyser.h"
#include "DataCollector.h"


class Controller
{


    
public:
    Controller(std::unique_ptr<DataAnalyser>&& dataPtr, std::unique_ptr<DataCollector>&& collectorPtr)
  : dataPtr(std::move(dataPtr)),
    collectorPtr(std::move(collectorPtr)){}

    static long long GetValidNumber();
    void ExecuteChoice(const int& choice);
    int DisplayMenu() const;
    void Run();
    void DisplayData();
    void Exit();

    static constexpr const char* ErrorMsg = "Invalid input! Try again, use numbers!";
protected:
    enum class MenuOptions : uint8_t
    {
        none, calculateData, addData, generateRandomData, lookupValue, lookupDate, sortData, exit, maxNum,
    };
    
private:
    std::array<const char*, static_cast<int>(MenuOptions::maxNum)> menuStrings =
        {"Input: ","to calculate and display the current data.","to input new Data to the system.",
        "to generate mock data.", "to check for a specific temperature.", "to check the data at a specific date.",
        "to sort the data.", "to exit the module."};

    const char* welcomeMsg = "Welcome to Saturn's moons Dione's Deep Ice Thermostat module.\nPlease input the corresponding option:";
    std::unique_ptr<DataAnalyser> dataPtr;
    std::unique_ptr<DataCollector> collectorPtr;
};
