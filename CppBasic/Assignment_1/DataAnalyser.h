#pragma once
#include <memory>
#include <unordered_map>

class DataAnalyser
{
public:
    DataAnalyser(std::unique_ptr<std::unordered_map<time_t, float>> dataCollection)
         : dataCollection(std::move(dataCollection))
    {}
    void CalculateData();
    void SortData();
    void LookupValue();
    void LookupDate();
private:
    std::unique_ptr<std::unordered_map<time_t, float>> dataCollection;
};
