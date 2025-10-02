#include <chrono>
#include <iostream>
#include "DataCollector.h"
#include "Controller.h"


void DataCollector::Initialize()
{
    dataCollection.clear();
}

void DataCollector::AddData()
{
    std::cout << timeChoices[0] << "\n" << timeChoices[1] << "\n";
    bool manualTime = static_cast<bool>(Controller::GetValidNumber());
    std::cout << prompts[0] << '\n';
    int dataIterations = static_cast<int>(Controller::GetValidNumber());
    manualTime ? GetManualTime(dataIterations) : GetAutoTime(dataIterations);
    ProcessData();
}
void DataCollector::GetManualTime(int iterations)
{
    std::cout << prompts[2] << '\n';
    std::unordered_map<int,float> dataSets;
    for (int i = 0; i < iterations; i++)
    {
        std::array<float,2> input;
        std::cout << timeChoices[2] << '\n';
        input[0] = Controller::GetValidNumber();
        input[1] = Controller::GetValidNumber();
        dataCollection.insert(std::pair<int,float>(input[0],input[1]));
    }
}
void DataCollector::GetAutoTime(int iterations)
{
    std::cout << prompts[1] << '\n';
    std::unordered_map<int,float> dataSets;
    for (int i = 0; i < iterations; i++)
    {
        float input = Controller::GetValidNumber();
        auto now = std::chrono::system_clock::now();
        time_t now_t = std::chrono::system_clock::to_time_t(now);
        dataCollection.insert(std::pair<int,float>(now_t,input));
    }
}
void DataCollector::ProcessData()
{
    
}
void DataCollector::GenerateRandomData()
{
    
}
