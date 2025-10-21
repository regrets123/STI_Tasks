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

void DataCollector::ReadData() const
{
    std::ifstream inFile("data.bin", std::ios::binary);
    
    if (!inFile.is_open()) {
        std::cerr << "File doesn't exist or can't be opened" << '\n';
        return; 
    }
    
    inFile.seekg(0, std::ios::end);
    if (inFile.tellg() == 0) {
        std::cerr << "File is empty" << '\n';
        inFile.close();
        return;
    }
    inFile.seekg(0, std::ios::beg);
    
    dataCollection->clear();
    
    size_t size;
    if (!inFile.read(reinterpret_cast<char*>(&size), sizeof(size))) {
        std::cerr << "Error reading size" << '\n';
        inFile.close();
        return;
    }
    
    for (size_t i = 0; i < size; ++i) {
        time_t timestamp;
        float value;
        
        if (!inFile.read(reinterpret_cast<char*>(&timestamp), sizeof(timestamp)) ||
            !inFile.read(reinterpret_cast<char*>(&value), sizeof(value))) {
            std::cerr << "Error reading data at index " << i << '\n';
            break;
            }
        
        (*dataCollection)[timestamp] = value;
    }
    
    inFile.close();
}

void DataCollector::SaveData() const
{
    std::ofstream outFile("data.bin", std::ios::binary);
    
    if (!outFile.is_open()) {
        std::cerr << "Error: Cannot open file for writing" << '\n';
        return;
    }
    
    size_t size = dataCollection->size();
    if (!outFile.write(reinterpret_cast<const char*>(&size), sizeof(size))) {
        std::cerr << "Error: Failed to write size" << '\n';
        outFile.close();
        return;
    }
    
    for (const auto& pair : *dataCollection) {
        if (!outFile.write(reinterpret_cast<const char*>(&pair.first), sizeof(pair.first)) ||
            !outFile.write(reinterpret_cast<const char*>(&pair.second), sizeof(pair.second))) {
            std::cerr << "Error: Failed to write data" << '\n';
            outFile.close();
            return;
            }
    }
    outFile.close();
}
