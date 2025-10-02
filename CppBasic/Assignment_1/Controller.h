#pragma once
#include <iostream>
#include <array>
#include "DataAnalyser.h"
#include "DataCollector.h"


class Controller
{
public:

    Controller(bool isInitialized, DataCollector* collector, DataAnalyser* analyser)
        : isInitialized(isInitialized),
          collector(collector),
          analyser(analyser) { }
    
    static int GetValidNumber();
    
    void ExecuteChoice(int choice);
    int DisplayMenu() const;
    void Run();
    void DisplayData();
    void Exit();
protected:
    enum class MenuOptions : uint8_t
    {
        none, calculateData, addData, generateRandomData, displayData, lookupValue, lookupDate, sortData, exit, maxNum,
    };
    
private:
   
    std::array<std::string, static_cast<int>(MenuOptions::maxNum)> menuStrings =
        {"Input number: "," to calculate the current data.","to input new Data to the system.",
        "to generate new mock data.", "to display the current calculated data",
        "to check for a specific temperature.", "to check the data at a specific date.",
        "to sort the data.", "to exit the module."};
    MenuOptions selectedOption;
    bool isInitialized = false;
    DataCollector* collector;
    DataAnalyser* analyser;
    
};
