#include "Controller.h"

void Controller::Run()
{
    std::string welcome =
        "Welcome to Saturn's moons Dione's Deep Ice Thermostat module.\nPlease input the corresponding option:";
    std::cout << welcome << '\n';
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
            std::cout << "Invalid input! Try again, use numbers!\n";
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
            dataPtr->CalculateData();
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
            Exit();
            break;
        }
    default:
        {
            std::cout << "Invalid input! Please try again.\n";
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

void Controller::DisplayData()
{
}

void Controller::Exit()
{
}
