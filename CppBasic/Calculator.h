#pragma once
#include <array>
#include <iostream>


class Calculator
{
public:
    enum CalcState { None, Addition, Subtraction, Multiplication, Division, Done, MaxNum };

    CalcState SwitchState(int state);
    int GetValidNumber(std::string prompt);
    std::array<int, 2> QueryNumbers(const std::string& prompt);
    void ExecuteState(CalcState state);
    void ExeAddition(std::array<int, 2> numbers);
    void ExeSubtraction(std::array<int, 2> numbers);
    void ExeMultiplication(std::array<int, 2> numbers);
    void ExeDivision(std::array<int, 2> numbers);
    int Main();
};

