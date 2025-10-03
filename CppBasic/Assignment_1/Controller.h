#pragma once
#include <iostream>
#include <array>
#include "DataAnalyser.h"
#include "DataCollector.h"


class Controller
{
public:
    
    static float GetValidNumber();
    void Initialize();
    void ExecuteChoice(int choice);
    int DisplayMenu() const;
    void Run();
    void DisplayData();
    void Exit();
protected:
    enum class MenuOptions : uint8_t
    {
        none, calculateData, addData, generateRandomData, lookupValue, lookupDate, sortData, exit, maxNum,
    };
    
private:
   
    std::array<std::string, static_cast<int>(MenuOptions::maxNum)> menuStrings =
        {"Input: ","to calculate and display the current data.","to input new Data to the system.",
        "to generate mock data.", "to check for a specific temperature.", "to check the data at a specific date.",
        "to sort the data.", "to exit the module."};
    MenuOptions selectedOption;
    bool isInitialized = false;
    DataCollector collector;
    DataAnalyser analyser;
    
};
