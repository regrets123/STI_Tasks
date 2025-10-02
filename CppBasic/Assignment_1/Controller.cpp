#include "Controller.h"



void Controller::Run()
{
    std::string welcome = "Welcome to Saturn's moons Dione's Deep Ice Thermostat module.\n Please input the corresponding menu option number:";
    std::cout << welcome << '\n';
    while (true)
    {
        int choice = DisplayMenu();
        ExecuteChoice(choice);
    }
}

int Controller::GetValidNumber()
{
    int num;
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
            break;
        }
    case MenuOptions::addData:
        {
            break;
        }
    case MenuOptions::generateRandomData:
        {
            break;
        }
    case MenuOptions::displayData:
        {
            break;
        }
    case MenuOptions::lookupValue:
        {
            break;
        }
    case MenuOptions::lookupDate:
        {
            break;
        }
    case MenuOptions::sortData:
        {
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
       std::cout << menuStrings[0] << i << menuStrings[i] << '\n';
    }
    int inputValue = GetValidNumber();
    return inputValue;
}

void Controller::DisplayData()
{
}

void Controller::Exit()
{
}
