#include "Controller.h"



void Controller::Run()
{
    std::string welcome = "Welcome to Saturn's moons Dione's Deep Ice Thermostat module.\nPlease input the corresponding option:";
    std::cout << welcome << '\n';
    while (true)
    {
        int choice = DisplayMenu();
        ExecuteChoice(choice);
    }
    
}

float Controller::GetValidNumber()
{
    float num;
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
void Controller::ExecuteChoice(int choice)
{
    const auto menuOption = static_cast<MenuOptions>(choice);
    switch (menuOption)
    {
    case MenuOptions::calculateData:
        {
            analyser.CalculateData();
            break;
        }
    case MenuOptions::addData:
        {
            collector.AddData();
            break;
        }
    case MenuOptions::generateRandomData:
        {
            collector.GenerateRandomData();
            break;
        }
    case MenuOptions::displayData:
        {
            collector.ProcessData();
            break;
        }
    case MenuOptions::lookupValue:
        {
            analyser.LookupValue();
            break;
        }
    case MenuOptions::lookupDate:
        {
            analyser.LookupDate();
            break;
        }
    case MenuOptions::sortData:
        {
            analyser.SortData();
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
