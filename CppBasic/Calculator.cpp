
#include <array>
#include <iostream>
#include "Calculator.h"

#include <string>

static std::string enter = "Enter which mode you want to use.\n";

int Calculator::Main ()
{
    CalcState state = None;
    std::string welcome = "This is the calculator.";
    std::string allModes = "1: Addition, 2: Subtraction, 3: Multiplication, 4: Division, 5: Done";

    std::cout << welcome << '\n';
    while (state != Done)
    {
        std::cout << allModes << '\n';
        int switchTo;
        switchTo = GetValidNumber(enter);
        state = SwitchState(switchTo);
        ExecuteState(state);
    }
    return 0;
}

int Calculator::GetValidNumber(std::string prompt)
{
    int num;
    while (true)
    {
        std::cout << prompt << "\n";
        std::cin >> num;

        if (std::cin.fail())
        {
            std::cout << "Invalid input! Try again.\n";
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

std::array<int, 2> Calculator::QueryNumbers(const std::string &prompt)
{
    std::array<int,2> result;
    result[0] = GetValidNumber(prompt+ " first:");
    result[1] = GetValidNumber(prompt+ " second:");
    return result;
}

Calculator::CalcState Calculator::SwitchState(int state)
{
    CalcState newState = static_cast<CalcState>(state);
    return newState;
}

void Calculator::ExeAddition(std::array<int, 2> numbers)
{
    int sum;
    sum = numbers[0] + numbers[1];
    std::cout << "The sum of the addition is: "<<  sum << '\n';
}
void Calculator::ExeSubtraction(std::array<int, 2> numbers)
{
    int sum;
    sum = numbers[0] - numbers[1];
    std::cout << "The sum of the subtraction is: "<< sum << '\n';
}
void Calculator::ExeMultiplication(std::array<int, 2> numbers)
{
    int sum;
    sum = numbers[0] * numbers[1];
    std::cout << "The sum of the multiplication is: "<< sum << '\n';
}
void Calculator::ExeDivision(std::array<int, 2> numbers)
{
    int sum;
    if (numbers[1] != 0)
    {
        sum = numbers[0] / numbers[1];
        std::cout << "The sum of the division is: "<< sum << '\n';
    }
    else
    {
        std::cout << "DONT DIVIDE BY ZERO YOU BUFFON!"<< '\n';
    }
}

void Calculator::ExecuteState(CalcState state)
{
    std::array<int,2> toCalculate;
    switch (state)
    {
    case Addition:
        {
            toCalculate = QueryNumbers("input numbers to add.");
            ExeAddition(toCalculate);
            break;
        }
    case Subtraction:
        {
            toCalculate = QueryNumbers("input numbers to subtract.");
            ExeSubtraction(toCalculate);
            break;
        }
    case Multiplication:
        {
            toCalculate = QueryNumbers("input numbers to multiply.");
            ExeMultiplication(toCalculate);
            break;
        }
    case Division:
        {
            toCalculate = QueryNumbers("input numbers to divide.");
            ExeDivision(toCalculate);
            break;
        }
    default:
        {
            std::cout <<  "Invalid input: Enter a number between 1 and 5." << '\n';
            break;   
        }
    }
}