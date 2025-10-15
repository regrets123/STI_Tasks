#include <chrono>
#include <iostream>
#include <random>
#include "DataCollector.h"
#include "Controller.h"


void DataCollector::Initialize()
{
    dataCollection->clear();
}

void DataCollector::AddData()
{
    std::cout << currentTimeMsg << "\n" << manualTimeMsg << "\n";
    bool manualTime = static_cast<bool>(Controller::GetValidNumber());
    std::cout << amountMsg << '\n';
    int dataIterations = static_cast<int>(Controller::GetValidNumber());
    manualTime ? GetManualTime(dataIterations) : GetAutoTime(dataIterations);
}

void DataCollector::GetManualTime(int iterations)
{
    std::map<long long,float> dataSets;
    for (int i = 0; i < iterations; i++)
    {
        std::array<long long,2> input;
        std::cout << pairMsg << '\n';
        tm time = Controller::InputDate();
        time_t startTime = std::mktime(&time);
        input[0] = startTime;
        std::cout << valueMsg << '\n';
        input[1] = Controller::GetValidNumber();
        dataCollection->insert(std::pair<long long,float>(input[0],input[1]));
    }
}

void DataCollector::GetAutoTime(int iterations)
{
    std::cout << valueMsg << '\n';
    std::map<long long,float> dataSets;
    for (int i = 0; i < iterations; i++)
    {
        float input = static_cast<float>(Controller::GetValidNumber());
        auto now = std::chrono::system_clock::now();
        time_t now_t = std::chrono::system_clock::to_time_t(now);
        dataCollection->insert(std::pair<long long,float>(now_t,input));
    }
}
void DataCollector::GenerateRandomData()
{
    std::cout << genDataMsg << '\n';
    int iterator =  static_cast<int>(Controller::GetValidNumber());
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> hour_dist(0, 23);
    std::uniform_int_distribution<> minute_dist(0, 59);
    std::uniform_real_distribution<float> dist(-305, -150); //Saturn's moon is very cold. 
    for (int i = 0; i < iterator; i++)
    {
        auto now = std::chrono::system_clock::now();
        auto timestamp = now - std::chrono::hours(24 * i) 
                      - std::chrono::hours(hour_dist(gen))
                      - std::chrono::minutes(minute_dist(gen));
        time_t time_point = std::chrono::system_clock::to_time_t(timestamp);
        std::pair<time_t,float> tempPair = std::make_pair(time_point,  dist(gen));
        dataCollection->insert(tempPair);
    }
}
