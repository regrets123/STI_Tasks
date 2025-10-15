#include "Controller.h"

#include <chrono>

#include "DataAnalyser.h"

void Controller::Run()
{
    
    std::cout << welcomeMsg << '\n';
    int choice = 0;
    while (choice != 7)
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
    std::tm* nowTm = std::localtime(&nowTimeT);
    int currentYear = nowTm->tm_year + 1900; // tm_year is years since 1900
    
    while (true)
    {
        int year = static_cast<int>(GetValidNumber());
        if (year > 1899 && year <= currentYear)
        {
            return year;
        }
        std::cout << "Input a year between 1900 and " << currentYear << '\n';
    }
}

int Controller::GetValidMonth(int year)
{
    auto now = std::chrono::system_clock::now();
    auto nowTimeT = std::chrono::system_clock::to_time_t(now);
    std::tm* nowTm = std::localtime(&nowTimeT);
    int currentYear = nowTm->tm_year + 1900;
    int currentMonth = nowTm->tm_mon + 1; // tm_mon is 0-11
    
    while (true)
    {
        uint8_t month = static_cast<uint8_t>(GetValidNumber());
        
        if (year == currentYear && month > currentMonth)
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
    std::tm* nowTm = std::localtime(&nowTimeT);
    int currentYear = nowTm->tm_year + 1900;
    int currentMonth = nowTm->tm_mon + 1;
    int currentDay = nowTm->tm_mday;
    
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
        uint8_t day = static_cast<uint8_t>(GetValidNumber());
        if (day > 0 && day <= maxDay)
        {
            return day;
        }
        std::cout << "Input a day between 1 and " << maxDay << '\n';
    }
}

void Controller::ExecuteChoice(const int& choice)
{
    const auto menuOption = static_cast<MenuOptions>(choice);
    switch (menuOption)
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

int Controller::DisplayMenu() const
{
    for (std::size_t i = 1; i < menuStrings.size(); ++i)
    {
       std::cout << menuStrings[0] << i << " "<< menuStrings[i] << '\n';
    }
    int inputValue = static_cast<int>(GetValidNumber());
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
    return startTm;
}

