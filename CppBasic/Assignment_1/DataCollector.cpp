#include <chrono>
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
#include "DataCollector.h"
#include "Controller.h"


void DataCollector::Initialize() const
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

void DataCollector::GetManualTime(int iterations) const
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
void DataCollector::GenerateRandomData() const
{
    std::cout << genDataMsg << '\n';
    int iterator =  static_cast<int>(Controller::GetValidNumber());
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> hour_dist(0, 23);
    std::uniform_int_distribution<> minute_dist(0, 59);
    std::uniform_real_distribution<float> dist(-305, -150); //Saturn's moon is very cold.
    auto now = std::chrono::system_clock::now();
    
    for (int i = 0; i < iterator; i++)
    {

        auto timestamp = now - std::chrono::hours(24 * i) 
                      - std::chrono::hours(hour_dist(gen))
                      - std::chrono::minutes(minute_dist(gen));
        time_t time_point = std::chrono::system_clock::to_time_t(timestamp);
        std::pair<time_t,float> tempPair = std::make_pair(time_point,  dist(gen));
        dataCollection->emplace(tempPair);
    }
}

void DataCollector::ReadData(bool clearPrevious) const
{
    std::ifstream inFile("data.csv");
    
    if (!inFile.is_open()) {
        std::cerr << "Error: File doesn't exist or can't be opened" << '\n';
        return;
    }
    
    inFile.seekg(0, std::ios::end);
    if (inFile.tellg() == 0) {
        std::cerr << "Error: File is empty" << '\n';
        inFile.close();
        return;
    }
    inFile.seekg(0, std::ios::beg);
    if (clearPrevious)
    {
        dataCollection->clear();    
    }
    std::string line;
    if (!std::getline(inFile, line)) {
        std::cerr << "Error: Cannot read header" << '\n';
        inFile.close();
        return;
    }
    int lineNumber = 1;
    while (std::getline(inFile, line)) {
        lineNumber++;
        if (line.empty()) {
            continue;
        }
        std::stringstream ss(line);
        std::string timestampStr, valueStr;
        
        if (!std::getline(ss, timestampStr, ',')) {
            std::cerr << "Error: Cannot read timestamp at line " << lineNumber << '\n';
            continue;
        }
        if (!std::getline(ss, valueStr, ',')) {
            std::cerr << "Error: Cannot read value at line " << lineNumber << '\n';
            continue;
        }
        try {
            time_t timestamp = std::stoll(timestampStr);
            float value = std::stof(valueStr);
            (*dataCollection)[timestamp] = value;
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Error: Invalid data format at line " << lineNumber << '\n';
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Error: Number out of range at line " << lineNumber << '\n';
        }
    }
    inFile.close();
}

void DataCollector::SaveData() const
{
    std::ofstream outFile("data.csv");
    
    if (!outFile.is_open()) {
        std::cerr << "Error: Cannot open file for writing" << '\n';
        return;
    }
    
    if (!(outFile << "timestamp,value\n")) {
        std::cerr << "Error: Failed to write header" << '\n';
        outFile.close();
        return;
    }
    for (const auto& pair : *dataCollection) {
        if (!(outFile << pair.first << "," << pair.second << "\n")) {
            std::cerr << "Error: Failed to write data" << '\n';
            outFile.close();
            return;
        }
    }
    outFile.close();
}
