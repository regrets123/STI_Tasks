#include "Controller.h"
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
    int year = static_cast<int>(GetValidNumber());
    std::cout << "Enter month MM:" << '\n';
    int month = static_cast<int>(GetValidNumber());
    std::cout << "Enter day DD:" << '\n';
    int day = static_cast<int>(GetValidNumber());
    
    std::tm startTm = {};
    startTm.tm_year = year - 1900;  // tm_year is years since 1900
    startTm.tm_mon = month - 1;      // tm_mon is 0-11
    startTm.tm_mday = day;
    startTm.tm_hour = 0;
    startTm.tm_min = 0;
    startTm.tm_sec = 0;
    return startTm;
}

