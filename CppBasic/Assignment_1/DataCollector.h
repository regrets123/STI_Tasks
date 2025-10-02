#pragma once
#include <unordered_map>

class DataCollector
{
public:

    void Initialize();
    void AddData();
    void GenerateRandomData();
private:
    std::unordered_map<std::tm,float> dataCollection;
};
