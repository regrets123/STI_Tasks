#include "Controller.h"

#include <chrono>
#include <utility>

#include "DataAnalyser.h"

void Controller::Run() const
{
    
    std::cout << welcomeMsg << '\n';
    MenuOptions choice = MenuOptions::none;
    while (choice != MenuOptions::exit)
    {
        choice = DisplayMenu();
        ExecuteChoice(choice);
    }
}

long long Controller::GetValidNumber()
{
    long long num;
    while (true)
    {
        std::cin >> num;
        if (std::cin.fail())
        {
            std::cout << ErrorMsg << '\n';
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        else
        {
            std::cin.ignore(10000, '\n');
            return num;
        }
    }
}

int Controller::GetValidYear()
{
    auto now = std::chrono::system_clock::now();
    auto nowTimeT = std::chrono::system_clock::to_time_t(now);
    std::tm nowTm = {};
    localtime_s(&nowTm, &nowTimeT);
    int currentYear = nowTm.tm_year + 1900; // tm_year is years since 1900
    
    while (true)
    {
        int year = static_cast<int>(GetValidNumber());
        if (year > 1969 && year <= currentYear) // we convert to time_t to be able to sort it, which starts at 1970
        {
            return year;
        }
        std::cout << "Input a year between 1970 and " << currentYear << '\n';
    }
}

int Controller::GetValidMonth(int year)
{
    auto now = std::chrono::system_clock::now();
    auto nowTimeT = std::chrono::system_clock::to_time_t(now);
    std::tm nowTm = {};
    localtime_s(&nowTm, &nowTimeT);
    int currentYear = nowTm.tm_year + 1900;
    int currentMonth = nowTm.tm_mon + 1; // tm_mon is 0-11
    
    while (true)
    {
        uint8_t month = static_cast<uint8_t>(GetValidNumber());
        
        if (year == currentYear && std::cmp_greater(month, currentMonth))
        {
            std::cout << "Cannot enter a future month. Input a month between 1 and " << currentMonth << '\n';
            continue;
        }
        
        if (month > 0 && month < 13)
        {
            return month;
        }
        std::cout << "Input a month between 1 and 12" << '\n';
    }
}

int Controller::GetValidDay(int year, int month)
{
    // Date time is such a pain
    auto now = std::chrono::system_clock::now();
    auto nowTimeT = std::chrono::system_clock::to_time_t(now);
    std::tm nowTm = {};
    localtime_s(&nowTm, &nowTimeT);
    int currentYear = nowTm.tm_year + 1900;
    int currentMonth = nowTm.tm_mon + 1;
    int currentDay = nowTm.tm_mday;
    
    int maxDay = 31;
    if (month == 2)
    {
        //leap year
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        maxDay = isLeap ? 29 : 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        maxDay = 30;
    }
    
    if (year == currentYear && month == currentMonth && currentDay < maxDay)
    {
        maxDay = currentDay;
    }
    
    while (true)
    {
        const uint8_t day = static_cast<uint8_t>(GetValidNumber());
        if (day > 0 && std::cmp_less_equal(day, maxDay))
        {
            return day;
        }
        std::cout << "Input a day between 1 and " << maxDay << '\n';
    }
}

void Controller::ExecuteChoice(MenuOptions choice) const
{
    switch (choice)
    {
    case MenuOptions::calculateData:
        {
            dataPtr->CalculateData(*collectorPtr->dataCollection);
            break;
        }
    case MenuOptions::addData:
        {
            collectorPtr->AddData();
            break;
        }
    case MenuOptions::generateRandomData:
        {
            collectorPtr->GenerateRandomData();
            break;
        }
    case MenuOptions::lookupValue:
        {
            dataPtr->LookupValue();
            break;
        }
    case MenuOptions::lookupDate:
        {
            dataPtr->LookupDate();
            break;
        }
    case MenuOptions::sortData:
        {
            dataPtr->SortData();
            break;
        }
    case MenuOptions::saveData:
        {
            collectorPtr->SaveData();
            break;
        }
    case MenuOptions::loadData:
        {
            std::cout << "If you want to keep previous Data: Press 0. \nIf you want to Delete previous data? Press 1. " << '\n';
            bool deleteData = static_cast<bool>(GetValidNumber());
            collectorPtr->ReadData(deleteData);
            break;
        }
    case MenuOptions::exit:
        {
            break;
        }
    default:
        {
            std::cout << ErrorMsg;
        }
    }
}

Controller::MenuOptions Controller::DisplayMenu() const
{
    for (std::size_t i = 1; i < menuStrings.size(); ++i)
    {
       std::cout << menuStrings[0] << i << " "<< menuStrings[i] << '\n';
    }
    MenuOptions inputValue = static_cast<MenuOptions>(GetValidNumber());
    return inputValue;
}

std::tm Controller::InputDate()
{
    std::cout << "Enter date Year YYYY:" << '\n';
    int year = GetValidYear();
    std::cout << "Enter month MM:" << '\n';
    int month = GetValidMonth(year);
    std::cout << "Enter day DD:" << '\n';
    int day = GetValidDay(year, month);
    
    std::tm startTm = {};
    startTm.tm_year = year - 1900;  // tm_year is years since 1900
    startTm.tm_mon = month - 1;      // tm_mon is 0-11
    startTm.tm_mday = day;
    startTm.tm_hour = 0;
    startTm.tm_min = 0;
    startTm.tm_sec = 0;
    startTm.tm_isdst = -1;
    const auto mkTime = mktime;
    mkTime(&startTm); 
    return startTm;
}

