/*
#pragma once
#include <array>
#include "DataAnalyser.h"
#include "DataCollector.h"

class Controller
{
//In this solution I am trying to mimic embedded environment logic to the best of my understanding.
//Ex: using char* instead of std::string to avoid dynamic stack allocations, reusing the same strings instead of creating new at each method call.
    
public:
    Controller(std::unique_ptr<DataAnalyser>&& dataPtr, std::unique_ptr<DataCollector>&& collectorPtr)
  : dataPtr(std::move(dataPtr)),
    collectorPtr(std::move(collectorPtr)){}

    enum class MenuOptions : uint8_t
    {
        none, calculateData, addData, generateRandomData, lookupValue, lookupDate, sortData, saveData, loadData, exit, maxNum, 
    };
    
    static long long GetValidNumber();
    static int GetValidYear();
    static int GetValidMonth(int year);
    static int GetValidDay(int year, int month);
    static std::tm InputDate();
    void ExecuteChoice(MenuOptions choice) const;
    MenuOptions DisplayMenu() const;
    void Run() const;

    static constexpr auto ErrorMsg = "Invalid input! Try again, use numbers!";
    
private:
    std::array<const char*, static_cast<int>(MenuOptions::maxNum)> menuStrings =
        {"Input: ","to calculate and display the current data.","to input new Data to the system.",
        "to generate mock data.", "to check for a specific temperature.", "to check the data at a specific date.",
        "to sort the data.", "to Save the readings.", "to Load previous readings.", "to exit the module."};

    const char* welcomeMsg = "Welcome to Saturn's moons Dione's Deep Ice Thermostat module.\nPlease input the corresponding option:";
    std::unique_ptr<DataAnalyser> dataPtr;
    std::unique_ptr<DataCollector> collectorPtr;
};
*/
